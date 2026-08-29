// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/scriptenginevtable /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// readable body of ?WriteScriptListDataChunk@ScriptList@@QAEXAAVDataChunkOutput@@@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/Scripts.cpp

#include "Lib/BaseType.h"

class DataChunkOutput;
class Script;
class ScriptGroup;
class ScriptList;

// These are the BFME three-argument writer thunks already pinned in the
// ledger.  The retail ScriptList stores the group pointer at +0x8 and the
// script pointer at +0x4, unlike the shared Zero Hour declaration.
void WriteGroupDataChunk(DataChunkOutput &chunk_writer, ScriptList *script_list,
	ScriptGroup *script_group);
void WriteScriptDataChunk(DataChunkOutput &chunk_writer, ScriptList *script_list,
	Script *script);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class ScriptList
{
public:
	void WriteScriptListDataChunk(DataChunkOutput &chunk_writer);

private:
	unsigned char m_padding[4];
	Script *m_firstScript;
	ScriptGroup *m_firstGroup;
};

void ScriptList::WriteScriptListDataChunk(DataChunkOutput &chunk_writer)
{
	if (m_firstGroup)
		WriteGroupDataChunk(chunk_writer, this, m_firstGroup);
	if (m_firstScript)
		WriteScriptDataChunk(chunk_writer, this, m_firstScript);
}
