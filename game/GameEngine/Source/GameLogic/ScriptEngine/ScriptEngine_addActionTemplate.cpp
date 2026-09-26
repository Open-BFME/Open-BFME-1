// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib
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
	for (int templateIndex = 0; templateIndex < 543; ++templateIndex)
	{
		if (m_actionTemplates[templateIndex].m_internalName.compare(tmpl->m_internalName) == 0)
		{
			m_actionTemplates[templateIndex].m_uiName = tmpl->m_uiName;
			m_actionTemplates[templateIndex].m_uiName2 = tmpl->m_uiName2;
			m_actionTemplates[templateIndex].m_helpText = tmpl->m_helpText;
			return;
		}
	}
}
