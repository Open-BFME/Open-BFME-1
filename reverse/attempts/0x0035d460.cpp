// ?Rva0035D460@@YAXPAURva0035D460Item@@PBU1@@Z
// partial score=0.21 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Oy- /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport

// Open-BFME: anonymous carved body at 0x0035D460 (433 bytes), boundary
// "jmp-tail" (ends in an unconditional jmp to a shared continuation at
// retail 0x0035D570, not a ret -- the carve is a self-contained slice of a
// larger routine). Only caller is the unlanded 0x0035E1F0 (d_0035aa50.asm).
//
// Retail copies a small record: dword@0, a UnicodeString via
// UnicodeString::set (0x00887C90) at +4, a byte at +0xc, a word at +0xe,
// then default-constructs a deque<Script*> at +0x10 (element type pinned as
// Rva0035AF80Element, 4 bytes -- matches a pointer) via the already-matched
// _M_initialize_map (RvaDequeInitializeMap.cpp) and copies each source
// Script* by allocating (operator new, mem_ops.cpp) and copy-constructing
// (Script::Script(const Script&), ScriptCopyCtor.cpp) a duplicate, pushing
// the duplicate's pointer onto the destination deque (STLport push_back,
// _M_reallocate_map / __new_alloc::allocate / _M_deallocate already pinned).
//
// docs/shape_levers.md note: retail inlines the deque push_back/grow logic
// directly into this body (no call to a separate push_back symbol); our
// STLport build calls out to deque<T>::push_back normally, which is the
// most likely source of any frame/instruction-count drift here.

class UnicodeString
{
public:
	void set(const UnicodeString &src);

	const void *m_data;
};

#define _STLP_NO_EXCEPTIONS 1
#include <deque>

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

class AsciiString;

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
	unsigned char m_bfmeStrings[0x0c];
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
	unsigned char m_bfmeTail[0x0c];
	float m_conditionTime;
	float m_curTime;
	int m_conditionExecutedCount;
};

struct Rva0035D460Item
{
	unsigned int m_field0;
	unsigned int m_field1;
	UnicodeString m_name;
	unsigned char m_flag;
	unsigned short m_word;
	_STL::deque<Script *> m_scripts;
};

// address-derived identity: only reachable via one unlanded caller
void Rva0035D460(Rva0035D460Item *dest, const Rva0035D460Item *src)
{
	dest->m_field0 = src->m_field0;
	dest->m_field1 = src->m_field1;
	dest->m_name.set(src->m_name);
	dest->m_flag = src->m_flag;
	dest->m_word = src->m_word;

	new (&dest->m_scripts) _STL::deque<Script *>();

	for (_STL::deque<Script *>::const_iterator it = src->m_scripts.begin();
		it != src->m_scripts.end(); ++it)
	{
		dest->m_scripts.push_back(new Script(**it));
	}
}
