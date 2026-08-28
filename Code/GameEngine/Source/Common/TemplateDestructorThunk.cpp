// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/campaignmanagerascii /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib

// The ScriptEngine Template from Scripts.h. Retail has no vptr here: the
// constructor at 0x351260 builds an AsciiString at offset 0 from a literal
// rather than storing a vtable, and the layout only lines up without one --
// m_uiStrings at 0x14, m_parameters at 0x48, m_helpText at 0x78. A virtual
// destructor provably emits a vptr store, so this one is not virtual and the
// ledger's MAE was corrected to IAE. Protected comes from the reference,
// where MEMORY_POOL_GLUE and EMPTY_DTOR put the destructor there.
#include "Common/AsciiString.h"

enum { MAX_PARMS = 12 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Template
{
protected:
	~Template();

public:
	AsciiString m_uiName;
	AsciiString m_uiName2;
	AsciiString m_internalName;
	int m_internalNameKey;
	int m_numUiStrings;
	AsciiString m_uiStrings[MAX_PARMS];
	int m_numParameters;
	int m_parameters[MAX_PARMS];
	AsciiString m_helpText;
};

// ??1Template@@IAE@XZ
Template::~Template()
{
}
