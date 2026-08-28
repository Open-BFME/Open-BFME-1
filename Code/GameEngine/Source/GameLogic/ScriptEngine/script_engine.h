#pragma once
#include "ascii_string.h"

// Layout recovered from 0x3107F0: sizeof(Template) == 0x7C, no vtable
// (lea edi,[esi+0x1c] points straight at m_uiName).
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Template {
public:
	AsciiString m_uiName;         // +0x00
	AsciiString m_uiName2;        // +0x04
	AsciiString m_internalName;   // +0x08
	int         m_internalNameKey;// +0x0C
	int         m_numUiStrings;   // +0x10
	AsciiString m_uiStrings[12];  // +0x14
	int         m_numParameters;  // +0x44
	int         m_parameters[12]; // +0x48
	int         m_pad;            // +0x78
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine {
public:
	virtual void init();
	char m_pre[0x18];
	Template m_actionTemplates[600];   // +0x1C
};
