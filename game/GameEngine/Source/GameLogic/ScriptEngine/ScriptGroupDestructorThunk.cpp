// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ lift of the retail pooled-list destructor.

// Retail's prologue stores the ScriptGroup vftable VA 0x01073744 at +0.
extern "C" const void *bfmeVftSnapshot[];
#pragma comment(linker, "/alternatename:_bfmeVftSnapshot=??_7Snapshot@@6B@")

class ScriptPoolObject
{
public:
	void deleteInstance(int destroy);
};

class ScriptGroupPoolObject
{
public:
	void deleteInstance(int destroy);
};

// Retail 0x00352950 reaches the two pooled deletions through ILT thunks, not
// through the class-qualified members: the group object's is 0x00002338 and
// the script object's is 0x00022039, each a five-byte E9 rel32 claimed by
// ?j_XXXXXXXX@@YAXXZ in game/gen_small/thunks_000.cpp and thunks_016.cpp.
// Those thunk names are the only ones the ledger defines at those addresses,
// so the calls name them; the member-pointer view of the union types the call
// thiscall (ecx = the pooled object, the flag 1 pushed by the caller) while
// emitting a direct call to the thunk.
extern "C" void __identifier("?j_00002338@@YAXXZ")();
extern "C" void __identifier("?j_00022039@@YAXXZ")();

// The pooled deletions are the two 38-byte bodies retail links at 0x00350E00
// (script) and 0x00350E30 (group): each checks the pooled pointer, calls the
// matching thunk with flag 1, and frees through the one 0x00881EB0 operator
// delete already matched in game/Libraries/Source/WWVegas/WWLib/mem_ops.cpp.
// Nothing in this TU allocates a PoolAllocation, so the primary template's
// destructor stays undefined and only the two explicit specializations below
// are ever emitted -- which is why they are spellable out of line.
template <class T>
class PoolAllocation
{
public:
	~PoolAllocation();

private:
	T *m_object;
};

// `inline` on both specializations keeps cl.exe's COMDAT selection at
// SELECT_ANY instead of NODUPLICATES: an explicit specialization without it is
// an exclusive definition, and game/GameEngine/Source/GameLogic/ScriptEngine/
// Rva00354A00NodeDestructor.cpp instantiates the same two destructors for the
// same pooled shapes, so LNK2005 fired on both pairs.
template <>
inline PoolAllocation<ScriptGroupPoolObject>::~PoolAllocation()
{
	if (m_object)
	{
		union DeleteCall {
			void (*bfmeThunk)();
			void (ScriptGroupPoolObject::*bfmeDelete)(int);
		} drop;

		drop.bfmeThunk = (void (*)())&__identifier("?j_00002338@@YAXXZ");
		(m_object->*drop.bfmeDelete)(1);
	}
}

template <>
inline PoolAllocation<ScriptPoolObject>::~PoolAllocation()
{
	if (m_object)
	{
		union DeleteCall {
			void (*bfmeThunk)();
			void (ScriptPoolObject::*bfmeDelete)(int);
		} drop;

		drop.bfmeThunk = (void (*)())&__identifier("?j_00022039@@YAXXZ");
		(m_object->*drop.bfmeDelete)(1);
	}
}

class __declspec(novtable) ScriptGroup
{
protected:
	virtual ~ScriptGroup();

private:
	PoolAllocation<ScriptPoolObject> *m_firstScript;
	PoolAllocation<ScriptGroupPoolObject> *m_nextGroup;
};

// ??1ScriptGroup@@MAE@XZ
ScriptGroup::~ScriptGroup()
{
	*(volatile unsigned int *)this = (unsigned int)bfmeVftSnapshot;
	PoolAllocation<ScriptGroupPoolObject> *nextGroup =
		*(PoolAllocation<ScriptGroupPoolObject> * volatile *)&m_nextGroup;
	delete nextGroup;
	PoolAllocation<ScriptPoolObject> *firstScript =
		*(PoolAllocation<ScriptPoolObject> * volatile *)&m_firstScript;
	delete firstScript;
}
