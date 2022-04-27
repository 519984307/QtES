
#ifndef PLUGINDETAILSVIEW_H_
#define PLUGINDETAILSVIEW_H_

#include "extensionsystem_global.h"

#include <QWidget>

namespace ExtensionSystem {

class PluginSpec;

namespace Internal {
namespace Ui {
class PluginDetailsView;
} // namespace Ui
} // namespace Internal

class EXTENSIONSYSTEM_EXPORT PluginDetailsView : public QWidget
{
    Q_OBJECT

public:
    PluginDetailsView(QWidget *parent = 0);
    ~PluginDetailsView();

    void update(PluginSpec *spec);

private:
    Internal::Ui::PluginDetailsView *m_ui;
};

} // namespace ExtensionSystem

#endif
