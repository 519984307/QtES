
#ifndef PLUGINERRORVIEW_H
#define PLUGINERRORVIEW_H

#include "extensionsystem_global.h"

#include <QWidget>

namespace ExtensionSystem {

class PluginSpec;
namespace Internal {
namespace Ui {
class PluginErrorView;
} // namespace Ui
} // namespace Internal

class EXTENSIONSYSTEM_EXPORT PluginErrorView : public QWidget
{
    Q_OBJECT

public:
    PluginErrorView(QWidget *parent = 0);
    ~PluginErrorView();

    void update(PluginSpec *spec);

private:
    Internal::Ui::PluginErrorView *m_ui;
};

} // namespace ExtensionSystem

#endif // PLUGINERRORVIEW_H
