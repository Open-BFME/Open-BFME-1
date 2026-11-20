// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// BFME script handles keep older versions alive so editor references remain stable.

#include "ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class DataChunkOutput
{
public:
	void openDataChunk(char *name, unsigned short version);
	void closeDataChunk();
	void writeAsciiString(const AsciiString &string);
	void writeByte(char value);
	void writeInt(int value);
};

class Script;

class OrCondition;
class ScriptAction;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class OrCondition
{
public:
	static void WriteOrConditionDataChunk(DataChunkOutput &, OrCondition *);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class ScriptAction
{
public:
	static void WriteActionDataChunk(DataChunkOutput &, ScriptAction *);
	static void WriteActionFalseDataChunk(DataChunkOutput &, ScriptAction *);
};

struct ScriptBodyData
{
	ScriptBodyData *previousVersion;
	void *unused;
	AsciiString comment;
	AsciiString conditionComment;
	AsciiString actionComment;
	int delayEvaluationSeconds;
	char unused18;
	bool isActive;
	bool isOneShot;
	bool isSubroutine;
	bool easy;
	bool normal;
	bool hard;
	OrCondition *condition;
	ScriptAction *action;
	ScriptAction *actionFalse;
};

struct ScriptBodyRecord
{
	char unused[8];
	AsciiString name;
	bool deleted;
	char alignment;
	volatile short version;
	ScriptBodyData *data;
};

struct ScriptData
{
	ScriptData *previousVersion;
	void *unused;
	Script *childGroups;
	Script *scripts;
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class ScriptList
{
private:
	char unused[0x18];
	ScriptRecord *records;
	char unused1C[0x1C];
	ScriptBodyRecord *scriptRecords;

	friend void WriteScriptDataChunk(DataChunkOutput &, ScriptList *, Script *);
	friend void Rva00357B30(DataChunkOutput &, ScriptList *, Script *);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Script
{
private:
	Script *next;
	int recordIndex;
	volatile int version;

	friend void WriteScriptDataChunk(DataChunkOutput &, ScriptList *, Script *);
	friend void Rva00357B30(DataChunkOutput &, ScriptList *, Script *);
};


// Retail 0x00357B30 (ILT 0x000285D3), 318 bytes: BFME's writer for a chain of
// script handles, the counterpart of the reference Script::WriteScriptDataChunk.
// It opens the "Script" chunk (version 2) and writes the name, the three
// comments, the six flags, the delay and the condition/action chains. The
// decorated names the ledger had for it (Script::WriteScriptDataChunk with two
// arguments, WriteGroupDataChunk at the ILT) are both refuted by the thunk
// table, so it keeps its address. ScriptList::WriteScriptListDataChunk calls it
// on the list's +0x08 chain and the group writer below on each group's scripts.
void Rva00357B30(DataChunkOutput &output, ScriptList *list, Script *script)
{
	while (script)
	{
		int recordIndex = script->recordIndex;
		ScriptBodyRecord *records = list->scriptRecords;
		int scriptVersion = script->version;
		ScriptBodyRecord *record = &records[recordIndex];
		if (record->version == scriptVersion && !record->deleted)
		{
			int recordVersion = record->version;
			ScriptBodyData *data = record->data;
			if (recordVersion > scriptVersion)
			{
				int versionsBack = recordVersion - scriptVersion;
				do
				{
					--versionsBack;
					data = data->previousVersion;
				} while (versionsBack);
			}

			output.openDataChunk("Script", 2);
			output.writeAsciiString(list->scriptRecords[script->recordIndex].name);
			output.writeAsciiString(data->comment);
			output.writeAsciiString(data->conditionComment);
			output.writeAsciiString(data->actionComment);
			output.writeByte(data->isActive);
			output.writeByte(data->isOneShot);
			output.writeByte(data->easy);
			output.writeByte(data->normal);
			output.writeByte(data->hard);
			output.writeByte(data->isSubroutine);
			output.writeInt(data->delayEvaluationSeconds);
			if (data->condition)
				OrCondition::WriteOrConditionDataChunk(output, data->condition);
			if (data->action)
				ScriptAction::WriteActionDataChunk(output, data->action);
			if (data->actionFalse)
				ScriptAction::WriteActionFalseDataChunk(output, data->actionFalse);
			output.closeDataChunk();
		}
		script = script->next;
	}
}

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

			output.openDataChunk("ScriptGroup", 3);
			output.writeAsciiString(list->records[script->recordIndex].name);
			output.writeByte(data->active);
			output.writeByte(data->subroutine);
			if (data->childGroups)
				WriteScriptDataChunk(output, list, data->childGroups);
			if (data->scripts)
				Rva00357B30(output, list, data->scripts);
			output.closeDataChunk();
		}
		script = script->next;
	}
}
