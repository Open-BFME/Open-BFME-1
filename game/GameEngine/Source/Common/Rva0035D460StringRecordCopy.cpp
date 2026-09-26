// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME: Rva0035D460(dest, src) -- retail 0x0035D460, cdecl, 577 bytes in
// full (the carved 433 plus the catch block at 0x0035D611 and the stack
// teardown tail at 0x0035D626). Only caller is 0x0035E1F0, which passes a
// fresh temp record and the source record; identity stays address-derived.
//
// Copies one Rva00359530Record: the catch block hands dest to
// clearRva00359530Nodes (0x003595F0), which fixes the record type and its
// BfmeNodeY chain at +0x10. Each node is a link plus a Script (new 0x44, then
// Script's copy ctor 0x0035B550 at node+4 on the source node's Script).
// The source chain is pushed onto a local stack and popped back so the copy
// keeps the source order; the unwind map (state 0 = stack, try over the pop
// loop only, state 2 = the new-expression) fixes where the try sits.
#define _STLP_NO_EXCEPTIONS 1
#include <stack>

#include "ascii_string.h"

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

class BfmeNodeY
{
public:
	BfmeNodeY(const BfmeNodeY &that) : m_next(0), m_script(that.m_script) {}
	~BfmeNodeY();

	BfmeNodeY *m_next;
	Script m_script;
};

struct Rva00359530Record
{
	int m_previous;
	int m_next;
	AsciiString m_name;
	unsigned char m_released;
	unsigned char m_pad;
	unsigned short m_references;
	BfmeNodeY *m_nodes;
};

void clearRva00359530Nodes(Rva00359530Record *record);

// ?Rva0035D460@@YAXPAURva00359530Record@@PBU1@@Z
void Rva0035D460(Rva00359530Record *dest, const Rva00359530Record *src)
{
	dest->m_previous = src->m_previous;
	dest->m_next = src->m_next;
	dest->m_name = src->m_name;
	dest->m_released = src->m_released;
	dest->m_references = src->m_references;
	dest->m_nodes = 0;

	_STL::stack<BfmeNodeY *> nodes;
	for (BfmeNodeY *node = src->m_nodes; node; node = node->m_next)
		nodes.push(node);

	try
	{
		while (!nodes.empty())
		{
			BfmeNodeY *copy = new BfmeNodeY(*nodes.top());
			nodes.pop();
			copy->m_next = dest->m_nodes;
			dest->m_nodes = copy;
		}
	}
	catch (...)
	{
		clearRva00359530Nodes(dest);
		throw;
	}
}
