// ?Rva004BE9C0@@YA_NPAXI@Z
// partial score=0.35 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc
//
// Address-derived candidate for retail 0x004BE9C0 (411 B). Real identity is
// NOT proven: only the callee ?bfmeFindAWB@BfmeKeyAWB@@... is pinned
// (reverse/symbols.csv). Landed neighbours are GadgetTextEntryGetText
// (0x004BE6F0) and GadgetVerticalSliderInput (0x004BF660), so this body sits
// in the text-entry gadget family; the shape (charPos/maxLen check, a
// StringBase<unsigned short> "GetText"-like virtual call, a substring copy
// ctor, concat of one char, then a "SetText"-like virtual call and a
// trailing '*' appendChar through a second vtable) resembles the IME
// composition helper the Generals source comments out (InformEntry) but the
// owning classes at node+0x0 and node+0x4 are unidentified vtables -- see
// --notes on the banked attempt.

struct BfmeNodeAWB;

class BfmeKeyAWB
{
public:
	BfmeNodeAWB *bfmeFindAWB();
};

template <typename T> class StringBase
{
public:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &src);
	StringBase(const StringBase<T> &src, int start, int len);
	~StringBase();
	void concat(const T *str, int len);
	void releaseBuffer();

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};
	Header *m_data;
};
typedef StringBase<unsigned short> UStrBase;

// extra call targets -- addresses pinned in reverse/symbols.csv under these
// exact mangled names (see notes on the banked attempt for the guessed ABI).
extern "C++" bool __cdecl Rva000275C0(unsigned int msg, void *field);
extern "C++" void __cdecl Rva00011D83(void *window);
extern "C++" void __stdcall Rva000148A8(void *window, int val);

#define NODE_PC(n)  (*(void **)((char *)(n) + 0x0c))
#define NODE_W10(n) (*(short *)((char *)(n) + 0x10))
#define NODE_W1C(n) (*(short *)((char *)(n) + 0x1c))
#define NODE_W1E(n) (*(short *)((char *)(n) + 0x1e))
#define NODE_B13(n) (*(unsigned char *)((char *)(n) + 0x13))

class Obj0Vtbl
{
public:
	virtual void slot0();
	virtual void setText(UStrBase byValue, UStrBase *out);
	virtual void getText(UStrBase *out);
};

class Obj4Vtbl
{
public:
	virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03();
	virtual void pad04(); virtual void pad05(); virtual void pad06(); virtual void pad07();
	virtual void pad08(); virtual void pad09(); virtual void pad10(); virtual void pad11();
	virtual void pad12(); virtual void pad13(); virtual void pad14(); virtual void pad15();
	virtual void pad16(); virtual void pad17(); virtual void pad18(); virtual void pad19();
	virtual void pad20(); virtual void pad21();
	virtual void appendChar(int ch);
};

#define NODE_P0(n) (*(Obj0Vtbl **)((char *)(n) + 0x00))
#define NODE_P4(n) (*(Obj4Vtbl **)((char *)(n) + 0x04))

bool __cdecl Rva004BE9C0(void *window, unsigned int msg)
{
	void *win = window;
	BfmeNodeAWB *node = ((BfmeKeyAWB *)win)->bfmeFindAWB();
	unsigned int m = msg;

	if (!Rva000275C0(m, NODE_PC(node)))
		return false;

	if (NODE_W1E(node) != NODE_W1C(node))
		Rva00011D83(win);

	UStrBase outA;
	NODE_P0(node)->getText(&outA);

	int len = outA.m_data ? outA.m_data->length : 0;
	if (len >= (short)NODE_W10(node))
	{
		outA.releaseBuffer();
		return false;
	}

	UStrBase trimmed(outA, 0, NODE_W1C(node));
	unsigned short ch = (unsigned short)m;
	trimmed.concat(&ch, 1);

	outA.releaseBuffer();

	NODE_P0(node)->setText(trimmed, &outA);

	Rva000148A8(win, NODE_W1C(node) + 1);

	NODE_W1E(node) = NODE_W1C(node);

	NODE_P4(node)->appendChar(0x2a);

	NODE_B13(node) = 1;

	outA.releaseBuffer();
	trimmed.releaseBuffer();

	return true;
}
