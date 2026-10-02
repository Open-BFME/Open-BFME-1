// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport

#include <map>

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ModuleFactory.h
class ModuleFactory
{
public:
    // upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ModuleFactory.h
    class ModuleTemplate
    {
    };

    class ModuleTemplateMap
    {
    public:
        ModuleTemplate &operator[](const int &);
    };
};

template <>
ModuleFactory::ModuleTemplate &std::map<int, ModuleFactory::ModuleTemplate>::operator[](const int &);

ModuleFactory::ModuleTemplate &ModuleFactory::ModuleTemplateMap::operator[](const int &key)
{
	return ((std::map<int, ModuleFactory::ModuleTemplate> *)this)->operator[](key);
}
