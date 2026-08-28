// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ModuleFactory.h
class ModuleFactory
{
public:
    // upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ModuleFactory.h
    class ModuleTemplate
    {
    };

    class ModuleTemplateMap
    {
    public:
        ModuleTemplate &operator[](const int &);
    };
};

class ModuleTemplateMapOperatorShim
{
public:
    ModuleFactory::ModuleTemplate &at(const int &key);
};

ModuleFactory::ModuleTemplate &ModuleFactory::ModuleTemplateMap::operator[](const int &key)
{
    return ((ModuleTemplateMapOperatorShim *)this)->at(key);
}
