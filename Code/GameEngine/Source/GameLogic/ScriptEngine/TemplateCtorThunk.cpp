// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/campaignmanagerascii /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib

// Same layout as the destructor at 0x3394E0: no vptr, m_uiStrings at 0x14,
// m_parameters at 0x48, m_helpText at 0x78. Everything through m_helpText is
// member construction in declaration order; only the m_parameters clear is a
// body statement, which is why it comes after m_helpText's zero store.
#include "Common/AsciiString.h"

enum { MAX_PARMS = 12 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
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
