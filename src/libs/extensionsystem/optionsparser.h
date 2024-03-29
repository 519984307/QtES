
#ifndef OPTIONSPARSER_H
#define OPTIONSPARSER_H

#include "pluginmanager_p.h"

#include <QMap>
#include <QStringList>

namespace ExtensionSystem {
namespace Internal {

class OptionsParser
{
public:
    OptionsParser(const QStringList &args, const QMap<QString, bool> &appOptions,
                  QMap<QString, QString> *foundAppOptions, QString *errorString,
                  PluginManagerPrivate *pmPrivate);

    bool parse();

    static const char *NO_LOAD_OPTION;
    static const char *LOAD_OPTION;
    static const char *TEST_OPTION;
    static const char *PROFILE_OPTION;

private:
    // return value indicates if the option was processed
    // it doesn't indicate success (--> m_hasError)
    bool checkForEndOfOptions();
    bool checkForLoadOption();
    bool checkForNoLoadOption();
    bool checkForTestOption();
    bool checkForAppOption();
    bool checkForPluginOption();
    bool checkForProfilingOption();
    bool checkForUnknownOption();

    enum TokenType
    {
        OptionalToken,
        RequiredToken
    };
    bool nextToken(TokenType type = OptionalToken);

    const QStringList &m_args;
    const QMap<QString, bool> &m_appOptions;
    QMap<QString, QString> *m_foundAppOptions;
    QString *m_errorString;
    PluginManagerPrivate *m_pmPrivate;

    // state
    QString m_currentArg;
    QStringList::const_iterator m_it;
    QStringList::const_iterator m_end;
    bool m_isDependencyRefreshNeeded;
    bool m_hasError;
};

} // namespace Internal
} // namespace ExtensionSystem

#endif // OPTIONSPARSER_H
