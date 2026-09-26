// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/ini /Iinputs/reference/shims/sweep
//     /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include
//     /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source
//     /Igame/Libraries/Source/WWVegas/WWLib

#include "Common/AsciiString.h"
#include "game_logic_dispatch.h"

enum { MAX_PARMS = 12 };

static int bfmeStringLength(const AsciiString &value)
{
	const char *data = *(const char *const *)&value;
	return data ? *(const unsigned short *)(data + 4) : 0;
}

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

class ScriptEngine
{
public:
	void Rva0033D8B0();

private:
	unsigned char m_unreconstructed[0x1c];
	Template m_actionTemplates[543];
	Template m_conditionTemplates[184];
};

// ?Rva0033D8B0@ScriptEngine@@QAEXXZ
void ScriptEngine::Rva0033D8B0()
{
	int i;
	for (i = 0; i < 543; ++i)
	{
		AsciiString str;
		str.format("[%d]", i);
		((StringBase<char> *)&m_actionTemplates[i].m_uiName)->concat(
			str.str(), bfmeStringLength(str));
		m_actionTemplates[i].m_internalNameKey =
			TheNameKeyGenerator->nameToKey(m_actionTemplates[i].m_internalName.str());
	}

	for (i = 0; i < 184; ++i)
	{
		AsciiString str;
		str.format("[%d]", i);
		((StringBase<char> *)&m_conditionTemplates[i].m_uiName)->concat(
			str.str(), bfmeStringLength(str));
		m_conditionTemplates[i].m_internalNameKey =
			TheNameKeyGenerator->nameToKey(m_conditionTemplates[i].m_internalName.str());
	}
}
