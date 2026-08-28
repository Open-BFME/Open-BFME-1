// cl: /DNDEBUG /MD /EHsc
// readable body of ?WriteScriptsDataChunk@ScriptList@@SAXAAVDataChunkOutput@@QAPAV1@H@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/Scripts.cpp
// Open-BFME5: lift the ScriptList::WriteScriptsDataChunk MASM dump to clean C++.
//
// Zero Hour keeps the per-list body in WriteScriptListDataChunk
// (Scripts.cpp:604); BFME inlines it here, and writes the group before the
// script where the reference does the reverse.
//
// The array parameter is spelled as a pointer to const pointer rather than with
// array syntax: ScriptList *const [] picks up a top-level const and mangles QB,
// where the ledger row wants PB.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class DataChunkOutput
{
public:
	void openDataChunk(char *name, unsigned short version);	///< body at 0x0003A256
	void closeDataChunk(void);								///< ILT 0x00004B42
};

class Script;
class ScriptGroup;
class ScriptList;

void WriteGroupDataChunk(DataChunkOutput &chunkWriter, ScriptList *list, ScriptGroup *group);
void WriteScriptDataChunk(DataChunkOutput &chunkWriter, ScriptList *list, Script *script);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class ScriptList
{
public:
	static void WriteScriptsDataChunk(DataChunkOutput &chunkWriter, ScriptList *const *scriptLists, int numLists);

	unsigned int m_00;
	Script *m_firstScript;						///< retail this+0x04
	ScriptGroup *m_firstGroup;					///< retail this+0x08
};

// ?WriteScriptsDataChunk@ScriptList@@SAXAAVDataChunkOutput@@QAPAV1@H@Z
void ScriptList::WriteScriptsDataChunk(DataChunkOutput &chunkWriter, ScriptList *const *scriptLists, int numLists)
{
	chunkWriter.openDataChunk("PlayerScriptsList", 5);

	for (int i = 0; i < numLists; i++)
	{
		chunkWriter.openDataChunk("ScriptList", 1);

		ScriptList *list = scriptLists[i];

		if (list != 0)
		{
			if (list->m_firstGroup != 0)
			{
				WriteGroupDataChunk(chunkWriter, list, list->m_firstGroup);
			}

			if (list->m_firstScript != 0)
			{
				WriteScriptDataChunk(chunkWriter, list, list->m_firstScript);
			}
		}

		chunkWriter.closeDataChunk();
	}

	chunkWriter.closeDataChunk();
}
