
#ifndef UTILS_ENVIRONMENT_H
#define UTILS_ENVIRONMENT_H

#include "utils_global.h"

#include <QMap>
#include <QStringList>

QT_FORWARD_DECLARE_CLASS(QProcessEnvironment)

namespace Utils {

class UTILSSHARED_EXPORT EnvironmentItem
{
public:
    EnvironmentItem(const QString &n, const QString &v) : name(n), value(v), unset(false) {}

    QString name;
    QString value;
    bool unset;

    bool operator==(const EnvironmentItem &other) const
    {
        return unset == other.unset && name == other.name && value == other.value;
    }

    static void sort(QList<EnvironmentItem> *list);
    static QList<EnvironmentItem> fromStringList(const QStringList &list);
    static QStringList toStringList(const QList<EnvironmentItem> &list);
};

class UTILSSHARED_EXPORT Environment
{
public:
    typedef QMap<QString, QString>::const_iterator const_iterator;

    Environment() {}
    explicit Environment(const QStringList &env);
    static Environment systemEnvironment();

    QStringList toStringList() const;
    QProcessEnvironment toProcessEnvironment() const;
    QString value(const QString &key) const;
    void set(const QString &key, const QString &value);
    void unset(const QString &key);
    void modify(const QList<EnvironmentItem> &list);
    /// Return the Environment changes necessary to modify this into the other environment.
    QList<EnvironmentItem> diff(const Environment &other) const;
    bool hasKey(const QString &key) const;

    QString userName() const;

    void appendOrSet(const QString &key, const QString &value, const QString &sep = QString());
    void prependOrSet(const QString &key, const QString &value, const QString &sep = QString());

    void appendOrSetPath(const QString &value);
    void prependOrSetPath(const QString &value);

    void prependOrSetLibrarySearchPath(const QString &value);

    void clear();
    int size() const;

    QString key(Environment::const_iterator it) const;
    QString value(Environment::const_iterator it) const;

    Environment::const_iterator constBegin() const;
    Environment::const_iterator constEnd() const;
    Environment::const_iterator constFind(const QString &name) const;

    QString searchInPath(const QString &executable,
                         const QStringList &additionalDirs = QStringList()) const;
    QStringList path() const;

    QString expandVariables(const QString &input) const;
    QStringList expandVariables(const QStringList &input) const;

    bool operator!=(const Environment &other) const;
    bool operator==(const Environment &other) const;

private:
    QString searchInDirectory(const QStringList &execs, QString directory) const;
    QMap<QString, QString> m_values;
};

} // namespace Utils

#endif // UTILS_ENVIRONMENT_H
