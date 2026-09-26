// cl: /O2 /Ob1 /Igame/Libraries/Source/WWVegas/WWLib

// Retail 0x0035D1E0 is the Script-valued overload in the same string-record
// table family as the matched 0x0035D2B0 default-node overload.  The table
// identity remains address-derived: its matched sibling proves the +0x0C
// record array and the shared findOrCreateIndex helper, while retail's 0x44
// allocation and call at node+4 prove this overload's node is {link, Script}.

template <typename T>
struct StringInlineData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	T m_text[1];
};

#include "string_base.h"

// Same four-byte StringBase-backed view as the matched Script copy
// constructor.  The string-record table stores this header at record +0x08.
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
};

class Xfer;

class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot();

protected:
	virtual void loadPostProcess() = 0;
	virtual const char *getSnapshotName() const = 0;
	virtual void xfer(Xfer *xfer) = 0;
};

class OrCondition
{
public:
	OrCondition *duplicate() const;
};

class ScriptAction
{
public:
	ScriptAction *duplicate() const;
};

// Full data-bearing BFME Script view copied from ScriptCopyCtor.cpp.  Its
// size is 0x40, so the retail 0x44 node's Script begins at offset +0x04.
class Script : public Snapshot
{
public:
	Script();
	Script(const Script &that);
	virtual ~Script();
	virtual void loadPostProcess();
	virtual const char *getSnapshotName() const;
	virtual void xfer(Xfer *xfer);

private:
	AsciiString m_scriptName;
	AsciiString m_comment;
	AsciiString m_conditionComment;
	int m_delayEvaluationSeconds;
	bool m_isActive;
	bool m_isOneShot;
	bool m_easy;
	bool m_isSubroutine;
	bool m_normal;
	bool m_hard;
	bool m_bfmeFlag;
	OrCondition *m_condition;
	ScriptAction *m_action;
	ScriptAction *m_actionFalse;
	Script *m_nextScript;
	bool m_hasWarnings;
	AsciiString m_conditionTeamName;
	float m_conditionTime;
	float m_curTime;
	int m_conditionExecutedCount;
};

class Rva0035D1E0ScriptNode
{
public:
	Rva0035D1E0ScriptNode *m_link;
	Script m_script;

	__forceinline explicit Rva0035D1E0ScriptNode(const Script *script)
		: m_script(*script)
	{
	}
};

struct Rva0035D1E0Record
{
	int m_previous;
	int m_next;
	AsciiString m_name;
	unsigned char m_released;
	unsigned char m_pad;
	unsigned short m_references;
	Rva0035D1E0ScriptNode *m_nodes;
};

// This address-derived table name is shared with the matched default-node
// overload so the real 0x0004599E helper resolves through its existing pin.
class Rva0035D2B0StringRecordTable
{
public:
	int addNode(AsciiString *name, const Script *script);
	void release(int index);

private:
	int findOrCreateIndex(AsciiString *name);

	int *m_nameIndexesBegin;
	int *m_nameIndexesEnd;
	int *m_nameIndexesCapacity;
	Rva0035D1E0Record *m_records;
	int m_10;
	int m_14;
	int m_freeHead;
	int m_activeTail;
};

int Rva0035D2B0StringRecordTable::addNode(
	AsciiString *name, const Script *script)
{
	int index = findOrCreateIndex(name);
	if (index != -1)
	{
		Rva0035D1E0Record *records = m_records;
		try
		{
			Rva0035D1E0Record *record = records + index;
			Rva0035D1E0ScriptNode *newNode =
				new Rva0035D1E0ScriptNode(script);
			newNode->m_link = record->m_nodes;
			record->m_nodes = newNode;
		}
		catch (...)
		{
			release(index);
			throw;
		}
	}
	return index;
}
