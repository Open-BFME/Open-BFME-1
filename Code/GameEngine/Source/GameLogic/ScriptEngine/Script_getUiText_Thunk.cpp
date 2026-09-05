// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/scriptenginevtable /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Script::getUiText, retail RVA 0x00357860, 570 bytes.
// The old 564-byte dump omitted add esp,18h / ret 4; retail then has CC padding.
// BFME StringBase ABI and the condition-template slot of ScriptEngine.

#include <string.h>
#include "string_base.h"

// BFME's script UI strings use the WWLib StringBase<char> ABI: a string is a
// single data pointer, with an eight-byte header, and the set/concat calls take
// an explicit character count.  Keep this view local to the thunk so the
// shared reference headers remain untouched.
#define ASCIISTRING_H
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	static AsciiString TheEmptyString;

	AsciiString() : m_text(0) {}
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}
	AsciiString(const char *text)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(text);
	}
	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

	AsciiString &operator=(const AsciiString &that)
	{
		((StringBase<char> *)this)->set(*(const StringBase<char> *)&that);
		return *this;
	}
	AsciiString &operator=(const char *text)
	{
		((StringBase<char> *)this)->set(text, text ? (int)strlen(text) : 0);
		return *this;
	}

	const char *str() const
	{
		return m_text ? (const char *)(m_text + 8) : "";
	}
	int getLength() const
	{
		return m_text ? *(const unsigned short *)(m_text + 4) : 0;
	}
	int compareNoCase(const AsciiString &that) const
	{
		return ((const StringBase<char> *)this)->compareNoCase(
			*(const StringBase<char> *)&that);
	}
	void concat(const AsciiString &that)
	{
		((StringBase<char> *)this)->concat(that.str(), that.getLength());
	}

	void concat(const char *text)
	{
		((StringBase<char> *)this)->concat(text, text ? (int)strlen(text) : 0);
	}

private:
	char *m_text;
};

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
	return strcmp(left.str(), right.str()) == 0;
}

// The ScriptEngine header includes the game-memory placement-new shim.  Keep
// the CRT's duplicate inline overloads suppressed in this TU.
#define __PLACEMENT_NEW_INLINE
#define __PLACEMENT_VEC_NEW_INLINE
#define Script ZHScriptReference
#include "GameLogic/ScriptEngine.h"
#undef Script

// BFME stores its three clause heads eight bytes earlier than the ZH layout.
// These offsets are read directly by the retail getUiText body.
class Script {
    char prior_fields[0x1c];
    OrCondition *m_condition;
    ScriptAction *m_action;
    ScriptAction *m_actionFalse;
public:
    AsciiString getUiText();
};

AsciiString Script::getUiText(void)
{
	AsciiString uiText("*** IF ***\r\n");
	OrCondition *pOr = m_condition;
	Int count=0;

	while (pOr) {
		Condition *pCond = pOr->getFirstAndCondition();
		if (count>0) uiText.concat("  *** OR ***\r\n");
		count = 0;
		while (pCond) {
			if (count>0) {
				uiText.concat("    *AND* ");
			} else {
				uiText.concat("    ");
			}
			uiText.concat(pCond->getUiText());
			uiText.concat("\r\n");
			pCond = pCond->getNext();
			count++;
		}
		pOr = pOr->getNextOrCondition();
	}
	uiText.concat("*** THEN ***\r\n");
	ScriptAction *pAction = m_action;
	while (pAction) {
		uiText.concat("  ");
		uiText.concat(pAction->getUiText());
		uiText.concat("\r\n");
		pAction = pAction->getNext();
	}
	pAction = m_actionFalse;
	if (pAction) {
		uiText.concat("*** ELSE ***\r\n");
		while (pAction) {
			uiText.concat("  ");
			uiText.concat(pAction->getUiText());
			uiText.concat("\r\n");
			pAction = pAction->getNext();
		}
	}
	return uiText;
}
