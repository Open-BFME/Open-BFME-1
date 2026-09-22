// Retail00147560/122B, called by the matched001BD0D0 locomotor parser.
// Existing bfmeResetANB spelling is preserved on its proven ThingTemplate receiver.
// Native map<LocomotorSetType,vector<const LocomotorTemplate*> > at+34C;
// erase(begin,end) followed by push_back preserves the retail vector lifetime.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

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



class ThingTemplate
{
private:
	char m_prefix34C[0x34C];
	LocomotorTemplateMap m_locomotorTemplateMap;

public:
	void bfmeResetANB(LocomotorSetType set, const LocomotorTemplate *templ);
};

void ThingTemplate::bfmeResetANB(LocomotorSetType set,
	const LocomotorTemplate *templ)
{
	LocomotorTemplateVector &slot = m_locomotorTemplateMap[set];
	slot.erase(slot.begin(), slot.end());
	m_locomotorTemplateMap[set].push_back(templ);
}
