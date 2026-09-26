// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

// BFME's LocomotorTemplateMap::operator[] is selected by the parser in
// AIUpdateModuleData::parseLocomotorSet.  The map key is the four-byte
// LocomotorSetType enum and its mapped value is the three-pointer vector from
// the canonical AIUpdate.h declaration.  Undefining STLport's compatibility
// switch selects the same value-initialisation shape as the retail COMDAT.

#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <map>
#include <vector>

class LocomotorTemplate;

enum LocomotorSetType
{
	LOCOMOTORSET_INVALID = -1
};

typedef std::vector<const LocomotorTemplate *> LocomotorTemplateVector;
typedef std::map<LocomotorSetType, LocomotorTemplateVector,
	std::less<LocomotorSetType> > LocomotorTemplateMap;

// ??A?$map@W4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@U?$less@W4LocomotorSetType@@@3@V?$allocator@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@@3@@_STL@@QAEAAV?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@1@ABW4LocomotorSetType@@@Z
template LocomotorTemplateVector &LocomotorTemplateMap::operator[](
	const LocomotorSetType &key);
