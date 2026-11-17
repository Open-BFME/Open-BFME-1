// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/scriptenginevtable /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
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
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"



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
