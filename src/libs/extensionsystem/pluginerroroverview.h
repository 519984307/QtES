
#ifndef PLUGINERROROVERVIEW_H
#define PLUGINERROROVERVIEW_H

#include "extensionsystem_global.h"

#include <QDialog>

QT_BEGIN_NAMESPACE
class QListWidgetItem;
QT_END_NAMESPACE

namespace ExtensionSystem {

namespace Internal {
namespace Ui { class PluginErrorOverview; }
} // namespace Internal

class EXTENSIONSYSTEM_EXPORT PluginErrorOverview : public QDialog
{
    Q_OBJECT

public:
    explicit PluginErrorOverview(QWidget *parent = 0);
    ~PluginErrorOverview();

private slots:
    void showDetails(QListWidgetItem *item);

private:
    Internal::Ui::PluginErrorOverview *m_ui;
};

} // ExtensionSystem

#endif // PLUGINERROROVERVIEW_H
