
#ifndef CRASHHANDLERDIALOG_H
#define CRASHHANDLERDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QString;
namespace Ui {
class CrashHandlerDialog;
}
QT_END_NAMESPACE

class CrashHandler;

class CrashHandlerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CrashHandlerDialog(CrashHandler *handler, const QString &signalName,
                                QWidget *parent = 0);
    ~CrashHandlerDialog();

public:
    void setApplicationInfo(const QString &signalName);
    void appendDebugInfo(const QString &chunk);
    void selectLineWithContents(const QString &text);
    void setToFinalState();
    void disableRestartAppCheckBox();
    void disableDebugAppButton();
    bool runDebuggerWhileBacktraceNotFinished();

private slots:
    void copyToClipboardClicked();
    void close();

private:
    CrashHandler *m_crashHandler;
    Ui::CrashHandlerDialog *m_ui;
};

#endif // CRASHHANDLERDIALOG_H
