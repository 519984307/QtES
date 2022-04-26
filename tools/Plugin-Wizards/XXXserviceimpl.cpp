#include "%{ServiceImplHdrFileName}"

using namespace %{PluginName};

%{ServiceImpl}::%{ServiceImpl}(QObject *parent) : QObject(parent)
{}

%{ServiceImpl}::~%{ServiceImpl}()
{}
