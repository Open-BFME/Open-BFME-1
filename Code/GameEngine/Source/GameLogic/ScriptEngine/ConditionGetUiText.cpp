// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/scriptenginevtable /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Condition::getUiText, retail RVA 0x00355E20, 395 bytes.
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
#include "GameLogic/ScriptEngine.h"

// The definitions precede Condition::getUiText just as they do in the
// original Scripts.cpp translation unit.  This keeps the template copy loop
// and ScriptEngine lookup inline at this call site.
Int Template::getUiStrings(AsciiString strings[MAX_PARMS]) const
{
	Int i;
	for (i = 0; i < m_numUiStrings; i++) {
		strings[i] = m_uiStrings[i];
	}
	return m_numUiStrings;
}

Int Condition::getUiStrings(AsciiString strings[MAX_PARMS])
{
	const ConditionTemplate *pTemplate = TheScriptEngine->getConditionTemplate(m_conditionType);
	return pTemplate->getUiStrings(strings);
}

// ?getUiText@Condition@@QAE?AVAsciiString@@XZ
AsciiString Condition::getUiText(void)
{
	AsciiString uiText;
	AsciiString strings[MAX_PARMS];
	Int numStrings = getUiStrings(strings);
	Int i;

	if (m_hasWarnings) {
		uiText = "[???]";
	}

	for (i = 0; i < MAX_PARMS; i++) {
		if (i < numStrings) {
			uiText.concat(strings[i]);
		}
		if (i < m_numParms) {
			uiText.concat(m_parms[i]->getUiText());
		}
	}

	return uiText;
}
