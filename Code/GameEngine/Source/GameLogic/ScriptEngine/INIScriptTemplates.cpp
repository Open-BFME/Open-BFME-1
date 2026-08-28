// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/campaignmanagerascii /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib

// FILE: INIScriptTemplates.cpp ///////////////////////////////////////////////
//
// The ScriptAction and ScriptCondition blocks, retail 0x00340A40 and
// 0x00340AE0. The INI block table in .data names both. They are the same five
// lines and differ only in which ScriptEngine member takes the finished
// Template - 0x0033D680 for actions, 0x0033D790 for conditions.
//
// Template is a real name with a landed constructor and destructor; the layout
// here is TemplateCtorThunk.cpp's, unchanged, and the 0x7C frame the two bodies
// reserve is exactly its size. The two engine members have no recoverable name,
// so they are spelled for what these call sites prove: one Template pointer,
// thiscall, callee-cleaned.
//
// The destructor is protected - retail spells it ??1Template@@IAE@XZ - so the
// two parsers are friends rather than the access being widened, which would
// change the symbol to QAE and stop resolving.
//
///////////////////////////////////////////////////////////////////////////////
#include "Common/AsciiString.h"


enum { MAX_PARMS = 12 };

struct FieldParse;

// Spelled under its own name so initFromINI resolves to the row the ledger
// already carries at 0x008520A0 rather than needing a pin of its own.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI( void *what, const FieldParse *table );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Template
{
public:
	Template();

	friend void parseScriptAction( INI *ini );
	friend void parseScriptCondition( INI *ini );

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

	static const FieldParse m_fieldParseTable[];
};

class BfmeScriptEngineTemplates
{
public:
	void addActionTemplate( Template *tmpl );
	void addConditionTemplate( Template *tmpl );

private:
	// The template tables are the only part of ScriptEngine needed here.  The
	// action table starts at +0x1C; the condition table follows it at +0x10720.
	// Keep the uninterpreted prefix explicit so the member offsets are the
	// retail offsets used by addConditionTemplate.
	unsigned char m_unreconstructed_00[0x10720];
	Template m_conditionTemplates[184];
};

extern BfmeScriptEngineTemplates *TheScriptEngine;		// 0x012F076C

// ?addConditionTemplate@BfmeScriptEngineTemplates@@QAEXPAVTemplate@@@Z
void BfmeScriptEngineTemplates::addConditionTemplate( Template *tmpl )
{
	for( int i = 0; i < 184; ++i )
	{
		if( m_conditionTemplates[i].m_internalName.compare( tmpl->m_internalName ) == 0 )
		{
			m_conditionTemplates[i].m_uiName = tmpl->m_uiName;
			m_conditionTemplates[i].m_uiName2 = tmpl->m_uiName2;
			m_conditionTemplates[i].m_helpText = tmpl->m_helpText;
			return;
		}
	}
}

// ?parseScriptAction@@YAXPAVINI@@@Z
void parseScriptAction( INI *ini )
{
	Template tmpl;

	ini->initFromINI( &tmpl, Template::m_fieldParseTable );

	if( TheScriptEngine )
		TheScriptEngine->addActionTemplate( &tmpl );
}

// ?parseScriptCondition@@YAXPAVINI@@@Z
void parseScriptCondition( INI *ini )
{
	Template tmpl;

	ini->initFromINI( &tmpl, Template::m_fieldParseTable );

	if( TheScriptEngine )
		TheScriptEngine->addConditionTemplate( &tmpl );
}
