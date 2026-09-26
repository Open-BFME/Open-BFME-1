// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// Named INI parsers parseScriptAction (340A40) and parseScriptCondition
// (340AE0) call both lifecycle bodies on a 0x7C stack record. Upstream
// Scripts.cpp independently uses the same UNUSED/(placeholder)/placeholder
// constructor literal. The reference MemoryPoolObject base is incompatible
// with this retail nonvirtual layout; use the witnessed view below.
// Same layout as the destructor at 0x3394E0: no vptr, m_uiStrings at 0x14,
// m_parameters at 0x48, m_helpText at 0x78. Everything through m_helpText is
// member construction in declaration order; only the m_parameters clear is a
// body statement, which is why it comes after m_helpText's zero store.
#include "ascii_string.h"

enum { MAX_PARMS = 12 };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Template
{
public:
	Template();

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

// ??0Template@@QAE@XZ
Template::Template() :
	m_uiName("UNUSED/(placeholder)/placeholder"),
	m_internalNameKey(0),
	m_numUiStrings(0),
	m_numParameters(0)
{
	for (int i = 0; i < MAX_PARMS; i++)
		m_parameters[i] = 0;
}

// ??1Template@@IAE@XZ
Template::~Template()
{
}
