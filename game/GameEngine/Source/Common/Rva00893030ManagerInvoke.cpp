// Open-BFME: retail 0x00895C50 -- Rva00893030Manager::invoke
//
// Pinned by targets/game/reverse/symbols.csv: "retail 0x00893030 calls the four-argument
// thiscall manager body at 0x00895C50" with mangled name
// ?invoke@Rva00893030Manager@@QAEXVRva00893030Ref@@PAX11@Z.  The sole caller
// is the matched ?Rva00893030@@YAXVRva00893030Ref@@PAX11@Z at 0x00893030
// (Rva00893030RefDispatch.cpp), which already declares
// `void invoke(Rva00893030Ref value, void *first, void *second, void *third);`
// on this same class -- that fixes the parameter order and types.
//
// Body shape (from dis_retail.py 0x00895C50 211):
//   - `first == 0`: just drop `value`'s referenced object (early return).
//   - `first != 0`: populate the object `value` refers to as a deferred-run
//     BfmeDropObjectA (m_kind = 3, matching the m_kind==3||4||5 special case
//     in BfmeDropObjectA::~BfmeDropObjectA(), BfmeDtorVBW.cpp, which reads
//     m_argument/m_object/m_buffer back out and runs
//     `((Rva008A25C0Object *)((char *)m_object + 8))->run(m_argument)`).
//     `second`'s dword at +0x14 is a self-relative cursor that gets
//     temporarily rebased to absolute with `first` as base (add before use,
//     subtract back after) around the pinned
//     ?apply@BfmeFixup2580@@QAEXPAXPAVBfmeFixupChunk2580@@0@Z call -- the
//     same add/use/subtract idiom BfmeFixup2580::apply itself uses on its
//     own m_rel field (BfmeFixup008A2580.cpp), just applied here to a
//     different field of the same chunk.
//   - `value`'s destructor (its own drop-and-maybe-free of the referenced
//     BfmeDropObjectA) is written out at BOTH return points rather than
//     going through the shared noinline bfmeDropA() helper: retail's callee
//     list for this body has no third call, only the two direct calls to
//     ??1BfmeDropObjectA@@QAE@XZ (0x00895260) followed by the free through
//     the 0x01337830 pointer, so this TU gives Rva00893030Ref its own
//     inline-only destructor instead of routing through bfmeDropA.
//
// cl: /EHsc

class Rva008A25C0Object
{
public:
	void run(void *value);
};

struct BfmeString3AF0
{
	void *m_data;
};

class BfmeDropObjectA
{
public:
	~BfmeDropObjectA();

	int m_refCount;				// +0x00
	BfmeString3AF0 m_string;		// +0x04
	int m_kind;						// +0x08
	void *m_argument;				// +0x0c
	Rva008A25C0Object *m_object;	// +0x10
	void *m_buffer;					// +0x14
};

extern void (*TheBfmeFree)(void *p, unsigned int bytes);
extern void (__cdecl *g_rva01337850)(void *value);

class Rva00893030Ref
{
public:
	Rva00893030Ref(void *value) : m_value(value) {}
	Rva00893030Ref(const Rva00893030Ref &other) : m_value(other.m_value) {}

	~Rva00893030Ref()
	{
		BfmeDropObjectA *obj = (BfmeDropObjectA *)m_value;

		if (obj && --obj->m_refCount == 0)
		{
			obj->~BfmeDropObjectA();
			TheBfmeFree(obj, sizeof(BfmeDropObjectA));
		}
	}

	void *m_value;
};

class BfmeFixupChunk2580;

class BfmeFixup2580
{
public:
	void apply(void *a, BfmeFixupChunk2580 *chunk, void *c);
};

// Address-derived: the dword `second` carries at +0x14, temporarily rebased
// to an absolute pointer with `first` as base around the apply() call.
struct Rva00895C50Cursor
{
	char m_pad[0x14];
	int m_cursor;	// +0x14
};

class Rva00893030Manager
{
public:
	void invoke(Rva00893030Ref value, void *first, void *second, void *third);
};

void Rva00893030Manager::invoke(Rva00893030Ref value, void *first, void *second, void *third)
{
	if (!first)
		return;

	BfmeDropObjectA *obj = (BfmeDropObjectA *)value.m_value;
	Rva00895C50Cursor *cursor = (Rva00895C50Cursor *)second;

	obj->m_kind = 3;

	if (cursor->m_cursor)
		cursor->m_cursor += (int)first;

	((BfmeFixup2580 *)((char *)cursor->m_cursor + 8))->apply(first, (BfmeFixupChunk2580 *)second, third);

	Rva008A25C0Object *rebased = (Rva008A25C0Object *)cursor->m_cursor;
	obj->m_argument = first;
	obj->m_object = rebased;
	obj->m_buffer = third;

	if (cursor->m_cursor)
		cursor->m_cursor -= (int)first;

	g_rva01337850(second);
}
