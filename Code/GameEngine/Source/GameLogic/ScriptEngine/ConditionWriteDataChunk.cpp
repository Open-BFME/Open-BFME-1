// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/scriptenginevtable /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Condition::WriteConditionDataChunk, retail RVA 0x00352DB0, 160 bytes.
// The former getUiText claim here was this two-argument cdecl writer.

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

#include "Common/DataChunk.h"
#define K_SCRIPT_CONDITION_VERSION_4 4
void Condition::WriteConditionDataChunk(DataChunkOutput &chunkWriter, Condition	*pCondition)
{
	/**********Condition  DATA ***********************/
	while (pCondition) {
		chunkWriter.openDataChunk("Condition", K_SCRIPT_CONDITION_VERSION_4);
			chunkWriter.writeInt(pCondition->m_conditionType);
			const ConditionTemplate* ct = TheScriptEngine->getConditionTemplate(pCondition->m_conditionType);
			if (ct) {
				chunkWriter.writeNameKey(ct->m_internalNameKey);
			}	else {
				DEBUG_CRASH(("Invalid condition."));
				chunkWriter.writeNameKey(NAMEKEY("Bogus"));
			}
			chunkWriter.writeInt(pCondition->m_numParms);
			Int i;
			for (i=0; i<pCondition->m_numParms; i++) {
				pCondition->m_parms[i]->WriteParameter(chunkWriter);
			}
		chunkWriter.closeDataChunk();
		pCondition = pCondition->getNext();
	}	
}
