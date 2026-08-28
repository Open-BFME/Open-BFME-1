// cl: /DNDEBUG /MD /EHsc
// BFME script handles keep older versions alive so editor references remain stable.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class DataChunkOutput
{
public:
	void openDataChunk(char *name, unsigned short version);
	void closeDataChunk();
	void writeAsciiString(const AsciiString &string);
	void writeByte(char value);
};

class Script;
class ScriptGroup;

struct ScriptData
{
	ScriptData *previousVersion;
	void *unused;
	Script *script;
	ScriptGroup *group;
	bool active;
	bool subroutine;
};

struct ScriptRecord
{
	char unused[8];
	AsciiString name;
	bool deleted;
	char alignment;
	volatile short version;
	ScriptData *data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class ScriptList
{
private:
	char unused[0x18];
	ScriptRecord *records;

	friend void WriteScriptDataChunk(DataChunkOutput &, ScriptList *, Script *);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Script
{
private:
	Script *next;
	int recordIndex;
	volatile int version;

	friend void WriteScriptDataChunk(DataChunkOutput &, ScriptList *, Script *);
};

void WriteGroupDataChunk(DataChunkOutput &output, ScriptList *list, ScriptGroup *group);

void WriteScriptDataChunk(DataChunkOutput &output, ScriptList *list, Script *script)
{
	while (script)
	{
		int recordIndex = script->recordIndex;
		ScriptRecord *records = list->records;
		int scriptVersion = script->version;
		ScriptRecord *record = &records[recordIndex];
		if (record->version == scriptVersion && !record->deleted)
		{
			int recordVersion = record->version;
			ScriptData *data = record->data;
			if (recordVersion > scriptVersion)
			{
				int versionsBack = recordVersion - scriptVersion;
				do
				{
					--versionsBack;
					data = data->previousVersion;
				} while (versionsBack);
			}

			output.openDataChunk("Script", 3);
			output.writeAsciiString(list->records[script->recordIndex].name);
			output.writeByte(data->active);
			output.writeByte(data->subroutine);
			if (data->script)
				WriteScriptDataChunk(output, list, data->script);
			if (data->group)
				WriteGroupDataChunk(output, list, data->group);
			output.closeDataChunk();
		}
		script = script->next;
	}
}
