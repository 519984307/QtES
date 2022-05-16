#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <memory>
#include <sstream>

#ifndef NOMINMAX
#    undef min
#    undef max
#endif

#include <spdlog/spdlog.h>

/// spdlog wrap class
namespace Log {
class logger final
{
public:
    static logger &instance()
    {
        static logger logger;
        return logger;
    }

    bool init(std::string logFilePath);

    void shutdown();

    template <typename... Args>
    void log(const spdlog::source_loc &loc, spdlog::level::level_enum lvl, const char *fmt,
             const Args &...args);

    template <typename... Args>
    void printf(const spdlog::source_loc &loc, spdlog::level::level_enum lvl, const char *fmt,
                const Args &...args);

    spdlog::level::level_enum level();
    void set_level(spdlog::level::level_enum lvl);

    void set_flush_on(spdlog::level::level_enum lvl);

    static const char *get_shortname(std::string path);

private:
    logger() = default;
    ~logger() = default;

    logger(const logger &) = delete;
    void operator=(const logger &) = delete;

private:
    std::atomic<bool> is_inited_ {false};
    spdlog::level::level_enum log_level_ {spdlog::level::trace};
};
} // namespace Log

// got short filename(exlude file directory)
#define __FILENAME__ (Log::logger::get_shortname(__FILE__))

// use fmt lib, e.g. LOG_WARN("warn log, {1}, {1}, {2}", 1, 2);
#define LOG_TRACE(msg, ...)                                                                        \
    {                                                                                              \
        if (Log::logger::instance().level() == spdlog::level::trace)                               \
            spdlog::log({__FILENAME__, __LINE__, __FUNCTION__}, spdlog::level::trace, msg,         \
                        ##__VA_ARGS__);                                                            \
    };
#define LOG_DEBUG(msg, ...)                                                                        \
    spdlog::log({__FILENAME__, __LINE__, __FUNCTION__}, spdlog::level::debug, msg, ##__VA_ARGS__)
#define LOG_INFO(msg, ...)                                                                         \
    spdlog::log({__FILENAME__, __LINE__, __FUNCTION__}, spdlog::level::info, msg, ##__VA_ARGS__)
#define LOG_WARN(msg, ...)                                                                         \
    spdlog::log({__FILENAME__, __LINE__, __FUNCTION__}, spdlog::level::warn, msg, ##__VA_ARGS__)
#define LOG_ERROR(msg, ...)                                                                        \
    spdlog::log({__FILENAME__, __LINE__, __FUNCTION__}, spdlog::level::err, msg, ##__VA_ARGS__)
#define LOG_FATAL(msg, ...)                                                                        \
    spdlog::log({__FILENAME__, __LINE__, __FUNCTION__}, spdlog::level::critical, msg, ##__VA_ARGS__)

#endif // __LOGGER_H__
