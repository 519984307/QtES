
#include "optionsparser.h"

#include <QCoreApplication>

using namespace ExtensionSystem;
using namespace ExtensionSystem::Internal;

static const char END_OF_OPTIONS[] = "--";
const char *OptionsParser::NO_LOAD_OPTION = "-noload";
const char *OptionsParser::LOAD_OPTION = "-load";
const char *OptionsParser::TEST_OPTION = "-test";
const char *OptionsParser::PROFILE_OPTION = "-profile";

OptionsParser::OptionsParser(const QStringList &args,
        const QMap<QString, bool> &appOptions,
        QMap<QString, QString> *foundAppOptions,
        QString *errorString,
        PluginManagerPrivate *pmPrivate)
    : m_args(args), m_appOptions(appOptions),
      m_foundAppOptions(foundAppOptions),
      m_errorString(errorString),
      m_pmPrivate(pmPrivate),
      m_it(m_args.constBegin()),
      m_end(m_args.constEnd()),
      m_isDependencyRefreshNeeded(false),
      m_hasError(false)
{
    ++m_it; // jump over program name
    if (m_errorString)
        m_errorString->clear();
    if (m_foundAppOptions)
        m_foundAppOptions->clear();
    m_pmPrivate->arguments.clear();
}

bool OptionsParser::parse()
{
    while (!m_hasError) {
        if (!nextToken()) // move forward
            break;
        if (checkForEndOfOptions())
            break;
        if (checkForLoadOption())
            continue;
        if (checkForNoLoadOption())
            continue;
        if (checkForProfilingOption())
            continue;
#ifdef WITH_TESTS
        if (checkForTestOption())
            continue;
#endif
        if (checkForAppOption())
            continue;
        if (checkForPluginOption())
            continue;
        if (checkForUnknownOption())
            break;
        // probably a file or something
        m_pmPrivate->arguments << m_currentArg;
    }
    if (m_isDependencyRefreshNeeded)
        m_pmPrivate->resolveDependencies();
    return !m_hasError;
}

bool OptionsParser::checkForEndOfOptions()
{
    if (m_currentArg != QLatin1String(END_OF_OPTIONS))
        return false;
    while (nextToken()) {
        m_pmPrivate->arguments << m_currentArg;
    }
    return true;
}

bool OptionsParser::checkForTestOption()
{
    if (m_currentArg != QLatin1String(TEST_OPTION))
        return false;
    if (nextToken(RequiredToken)) {
        if (m_currentArg == QLatin1String("all")) {
            foreach (PluginSpec *spec, m_pmPrivate->pluginSpecs) {
                if (spec && !m_pmPrivate->containsTestSpec(spec))
                    m_pmPrivate->testSpecs.append(PluginManagerPrivate::TestSpec(spec));
            }
        } else {
            QStringList args = m_currentArg.split(QLatin1Char(','));
            const QString pluginName = args.takeFirst();
            if (PluginSpec *spec = m_pmPrivate->pluginByName(pluginName)) {
                if (m_pmPrivate->containsTestSpec(spec)) {
                    if (m_errorString)
                        *m_errorString = QCoreApplication::translate("PluginManager",
                                                                     "The plugin '%1' is specified twice for testing.").arg(pluginName);
                    m_hasError = true;
                } else {
                    m_pmPrivate->testSpecs.append(PluginManagerPrivate::TestSpec(spec, args));
                }
            } else  {
                if (m_errorString)
                    *m_errorString = QCoreApplication::translate("PluginManager",
                                                                 "The plugin '%1' does not exist.").arg(pluginName);
                m_hasError = true;
            }
        }
    }
    return true;
}

bool OptionsParser::checkForLoadOption()
{
    if (m_currentArg != QLatin1String(LOAD_OPTION))
        return false;
    if (nextToken(RequiredToken)) {
        PluginSpec *spec = m_pmPrivate->pluginByName(m_currentArg);
        if (!spec) {
            if (m_errorString)
                *m_errorString = QCoreApplication::translate("PluginManager",
                                                             "The plugin '%1' does not exist.")
                    .arg(m_currentArg);
            m_hasError = true;
        } else {
            spec->setForceEnabled(true);
            m_isDependencyRefreshNeeded = true;
        }
    }
    return true;
}

bool OptionsParser::checkForNoLoadOption()
{
    if (m_currentArg != QLatin1String(NO_LOAD_OPTION))
        return false;
    if (nextToken(RequiredToken)) {
        PluginSpec *spec = m_pmPrivate->pluginByName(m_currentArg);
        if (!spec) {
            if (m_errorString)
                *m_errorString = QCoreApplication::translate("PluginManager",
                                                             "The plugin '%1' does not exist.").arg(m_currentArg);
            m_hasError = true;
        } else {
            spec->setForceDisabled(true);
            m_isDependencyRefreshNeeded = true;
        }
    }
    return true;
}

bool OptionsParser::checkForAppOption()
{
    if (!m_appOptions.contains(m_currentArg))
        return false;
    QString option = m_currentArg;
    QString argument;
    if (m_appOptions.value(m_currentArg) && nextToken(RequiredToken)) {
        //argument required
        argument = m_currentArg;
    }
    if (m_foundAppOptions)
        m_foundAppOptions->insert(option, argument);
    return true;
}

bool OptionsParser::checkForProfilingOption()
{
    if (m_currentArg != QLatin1String(PROFILE_OPTION))
        return false;
    m_pmPrivate->initProfiling();
    return true;
}

bool OptionsParser::checkForPluginOption()
{
    bool requiresParameter;
    PluginSpec *spec = m_pmPrivate->pluginForOption(m_currentArg, &requiresParameter);
    if (!spec)
        return false;
    spec->addArgument(m_currentArg);
    if (requiresParameter && nextToken(RequiredToken))
        spec->addArgument(m_currentArg);
    return true;
}

bool OptionsParser::checkForUnknownOption()
{
    if (!m_currentArg.startsWith(QLatin1Char('-')))
        return false;
    if (m_errorString)
        *m_errorString = QCoreApplication::translate("PluginManager",
                                                     "Unknown option %1").arg(m_currentArg);
    m_hasError = true;
    return true;
}

bool OptionsParser::nextToken(OptionsParser::TokenType type)
{
    if (m_it == m_end) {
        if (type == OptionsParser::RequiredToken) {
            m_hasError = true;
            if (m_errorString)
                *m_errorString = QCoreApplication::translate("PluginManager",
                                                             "The option %1 requires an argument.").arg(m_currentArg);
        }
        return false;
    }
    m_currentArg = *m_it;
    ++m_it;
    return true;
}
