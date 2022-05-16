#include "logger.h"

#include <spdlog/async.h>
#include <spdlog/fmt/bundled/printf.h>
#include <spdlog/fmt/fmt.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/msvc_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/stdout_sinks.h>

#include <QDir>
#include <QFileInfo>

namespace Log {

bool logger::init(QString logFilePath)
{
    if (is_inited_)
        return true;
    try {
        // check log path and try to create log directory
        QFileInfo log_pat_info(logFilePath);

        QDir log_dir = log_pat_info.dir();
        if (!log_dir.exists()) {
            log_dir.mkdir(log_dir.path());
        }

        // initialize spdlog
        constexpr std::size_t log_buffer_size = 32 * 1024; // 32kb
        // constexpr std::size_t max_file_size = 50 * 1024 * 1024; // 50mb
        spdlog::init_thread_pool(log_buffer_size, 10 /*std::thread::hardware_concurrency()*/);
        std::vector<spdlog::sink_ptr> sinks;
        auto daily_sink
            = std::make_shared<spdlog::sinks::daily_file_sink_mt>(logFilePath.toStdString(), 0, 30);
        sinks.push_back(daily_sink);

        // auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_path.string(), true);
        // sinks.push_back(file_sink);

#if defined(_DEBUG) && defined(WIN32)
        auto ms_sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
        sinks.push_back(ms_sink);
#endif //  _DEBUG

#ifdef _LOG_CONSOLE
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        sinks.push_back(console_sink);
#endif
        spdlog::set_default_logger(
            std::make_shared<spdlog::logger>("", sinks.begin(), sinks.end()));

        // spdlog::set_pattern("%s(%#): [%L %D %T.%e %P %t %!] %v");
        spdlog::set_pattern("[%D %T.%e] [%^%L%$] [thread %t] [%! %s(%#)]: %v");
        spdlog::flush_on(spdlog::level::warn);
        spdlog::set_level(log_level_);
    } catch (std::exception_ptr e) {
        assert(false);
        return false;
    }
    is_inited_ = true;
    return true;
}

void logger::shutdown()
{
    spdlog::shutdown();
}

template <typename... Args>
void logger::log(const spdlog::source_loc &loc, spdlog::level::level_enum lvl, const char *fmt,
                 const Args &...args)
{
    spdlog::log(loc, lvl, fmt, args...);
}

template <typename... Args>
void logger::printf(const spdlog::source_loc &loc, spdlog::level::level_enum lvl, const char *fmt,
                    const Args &...args)
{
    spdlog::log(loc, lvl, fmt::sprintf(fmt, args...).c_str());
}

spdlog::level::level_enum logger::level()
{
    return log_level_;
}

void logger::set_level(spdlog::level::level_enum lvl)
{
    log_level_ = lvl;
    spdlog::set_level(lvl);
}

void logger::set_flush_on(spdlog::level::level_enum lvl)
{
    spdlog::flush_on(lvl);
}

const char *logger::get_shortname(std::string path)
{
    if (path.empty())
        return path.data();

    size_t pos = path.find_last_of("/\\");
    return path.data() + ((pos == path.npos) ? 0 : pos + 1);
}

} // namespace Log
