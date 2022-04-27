%{Cpp:LicenseTemplate}\
#ifndef %{JS: Cpp.headerGuard('%{ServiceImplHdrFileName}')}
#define %{JS: Cpp.headerGuard('%{ServiceImplHdrFileName}')}

#include "%{ServiceHdrFileName}"

namespace %{PluginName} {

class %{ServiceImpl}Private;

class %{ServiceImpl} : public QObject, public %{PluginName}::Service
{
    Q_OBJECT
    Q_INTERFACES(%{PluginName}::Service)

public:
    explicit %{ServiceImpl}(QObject *parent = nullptr);
    ~%{ServiceImpl}();
};

} // namespace %{PluginName}

#endif // %{JS: Cpp.headerGuard('%{ServiceImplHdrFileName}')}
