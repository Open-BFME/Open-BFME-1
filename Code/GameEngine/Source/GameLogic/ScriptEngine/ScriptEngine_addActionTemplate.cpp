// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/campaignmanagerascii /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib
//
// ScriptEngine::addActionTemplate, retail 0x0033D680. ZH twin is
// addActionTemplateInfo; BFME iterates 543 action slots starting at +0x1C
// (see Rva00336C30Get and the landed addConditionTemplate at +0x10720).

#include "Common/AsciiString.h"

enum { MAX_PARMS = 12 };

class Template
{
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

class BfmeScriptEngineTemplates
{
public:
	void addActionTemplate(Template *tmpl);

private:
	unsigned char m_pad[0x1C];
	Template m_actionTemplates[543];
};

// ?addActionTemplate@BfmeScriptEngineTemplates@@QAEXPAVTemplate@@@Z
void BfmeScriptEngineTemplates::addActionTemplate(Template *tmpl)
{
	for (int i = 0; i < 543; ++i)
	{
		if (m_actionTemplates[i].m_internalName.compare(tmpl->m_internalName) == 0)
		{
			m_actionTemplates[i].m_uiName = tmpl->m_uiName;
			m_actionTemplates[i].m_uiName2 = tmpl->m_uiName2;
			m_actionTemplates[i].m_helpText = tmpl->m_helpText;
			return;
		}
	}
}
