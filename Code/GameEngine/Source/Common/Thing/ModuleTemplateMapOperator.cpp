// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport

#include <map>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ModuleFactory.h
class ModuleFactory
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ModuleFactory.h
	class ModuleTemplate
	{
	public:
		ModuleTemplate() : m_first( 0 ), m_second( 0 ), m_third( 0 ), m_fourth( 0 ) {}

	private:
		int m_first;
		int m_second;
		int m_third;
		int m_fourth;
	};

};

// ModuleFactory::ModuleTemplateMap is the retail typedef for this exact map.
template class std::map<int, ModuleFactory::ModuleTemplate>;
