// ?run@Gen_002E4470@@QAEXPAX000@Z
// partial score=0.16 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc

// Retail RVA 0x002E4470 (230 bytes). Served from Code/gen_asm/d_001107b0.asm.
// No named caller, vtable slot, or canonical LuaScriptEngine method name
// proves the owner; the class and both parameter/local shapes below are
// address-derived from the disassembly alone (tools/callers_of.py finds no
// reaching caller for this RVA).
//
// WHAT THE BYTES SHOW.  A __thiscall member with 3 explicit stack args
// (ebp+0xc, ebp+0x10, ebp+0x14).  It stashes the ebp+0x14 argument into
// this+0x78, resets ebp+0x14's stack slot to zero, runs
// lua_settop(this->L, 0), then walks a small fixed structure at
// arg1->0xc[1] to call the pinned BfmeSubBIA::ask() helper and read a field
// at +0x20 off its result (falling back to Rva006A16B0Empty on every
// negative test). It then calls lua_dobuffer(this->L, arg1, arg2, "") and,
// on success, if lua_gettop(this->L) > 0, pulls lua_tostring(this->L, 1),
// measures the returned C string's length by hand, and calls
// RetailLayoutString::set on the (reused) ebp+0x14 slot before resetting
// lua_settop(this->L, 0) again. Every path -- including the SEH local-
// unwind state stores around the RetailLayoutString slot -- ends by jumping
// into 0x002E4561, a still-dump sibling body carved as its own RVA
// (?d_002e4561@@YAXXZ) that is not landed; without its real prototype this
// TU cannot express that shared tail as an ordinary call, so the candidate
// below stops short of it and cannot byte-match past that jump.

typedef struct lua_State lua_State;

extern "C"
{
	void __cdecl lua_settop(lua_State *L, int idx);
	int __cdecl lua_dobuffer(lua_State *L, const char *buff, unsigned long size, const char *name);
	int __cdecl lua_gettop(lua_State *L);
	const char *__cdecl lua_tostring(lua_State *L, int idx);
}

extern const char Rva006A16B0Empty[];

class RetailLayoutString
{
public:
	void set(const char *text, int length);
};

// Address-derived: the call's own signature is pinned int-returning, but the
// caller immediately treats the result as a pointer and reads +0x20 off it.
class BfmeSubBIA
{
public:
	int ask();
};

class Gen_002E4470
{
public:
	void run(void *arg1, void *arg2, void *outParam, void *wrapper);

private:
	unsigned char m_pad00[0xc];
	lua_State *m_L; // +0xc
	unsigned char m_pad10[0x78 - 0xc - 4];
	void *m_field78; // +0x78
};

// ?run@Gen_002E4470@@QAEXPAX000@Z
void Gen_002E4470::run(void *arg1, void *arg2, void *outParam, void *wrapper)
{
	m_field78 = wrapper;
	outParam = 0;

	lua_settop(m_L, 0);

	void **slot = *(void ***)((unsigned char *)arg1 + 0xc);
	void *entry = slot ? slot[1] : 0;
	const char *text = Rva006A16B0Empty;
	int length = 0;
	if (entry)
	{
		BfmeSubBIA *sub = (BfmeSubBIA *)((unsigned char *)entry + 4);
		int askResult = sub->ask();
		if (askResult)
		{
			void *field = *(void **)(askResult + 0x20);
			if (field)
				text = (const char *)field + 8;
		}
	}
	(void)text;
	(void)length;

	if (lua_dobuffer(m_L, (const char *)arg1, (unsigned long)arg2, Rva006A16B0Empty) == 0)
	{
		if (lua_gettop(m_L) > 0)
		{
			const char *result = lua_tostring(m_L, 1);
			if (result)
			{
				int len = 0;
				while (result[len])
					++len;
				RetailLayoutString *layout = (RetailLayoutString *)&outParam;
				layout->set(result, len);
			}

			lua_settop(m_L, 0);
		}
	}

	// UNRESOLVED: retail jumps into the still-dump sibling 0x002E4561 here
	// on every path (including the early bail after lua_dobuffer fails and
	// after gettop <= 0); that shared tail is not modelled.
}
