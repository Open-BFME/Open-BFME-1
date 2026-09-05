// ?Rva004C9C60@@YA_NPAXIII@Z
// partial score=0.15 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc
//
// Address-derived candidate for retail 0x004C9C60 (991 B). Only partially
// reconstructed: the message dispatch shape (a `switch` compiling to retail's
// dec/sub-chain) recovers GWM_CREATE(1)/GWM_DESTROY(2) as no-ops,
// GWM_INPUT_FOCUS(0x17), and the outline of GBM_SELECTED(0x4008). The
// GLM_RIGHT_CLICKED(0x4014) and GCM_SET_TEXT(0x4025) branches are NOT
// modelled: they walk a global list at [0x012F4C98+8], index a jump table at
// 0x0010FE7E0, and call several callees outside the given list
// (0x004226EC, 0x0043B75A, 0x00408945, 0x004456D3, and StringBase members at
// 0xC88530/0xC88FF0/0xC891F0) -- out of scope for this pass. Left as `return
// false` placeholders. Globals identified via reverse/symbols.csv:
// 0x012F147C looks like a GameText-style manager (virtual slot 0x28 builds a
// UnicodeString from a wide literal), 0x012F3AE8 is reused across branches as
// a cached BfmeKeyAWB-like self handle. Not proven.

class BfmeNodeAWB;
class BfmeKeyAWB
{
public:
	BfmeNodeAWB *bfmeFindAWB();
};

class GameWindow
{
public:
	int winGetWindowId();
};

template <typename T> class StringBase
{
public:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &src);
	~StringBase();
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
typedef StringBase<unsigned short> UnicodeStr;

class GameTextManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09();
	virtual UnicodeStr fetch(const unsigned short *label, int flag);
};

bool __cdecl Rva004C9C60(void *self, unsigned int msg, unsigned int mData1, unsigned int mData2)
{
	switch (msg)
	{
	case 1:  // GWM_CREATE
	case 2:  // GWM_DESTROY
		return true;

	case 0x17: // GWM_INPUT_FOCUS
		if (mData1 == 1)
			*(bool *)mData2 = true;
		return true;

	case 0x4008: // GBM_SELECTED -- outline only, three cached-key branches
	{
		GameWindow *child = (GameWindow *)mData1;
		unsigned int childId = (unsigned int)child->winGetWindowId();

		static unsigned int keyA, keyB, keyC;
		(void)keyA; (void)keyB; (void)keyC;

		// Not fully modelled: key resolution / callback dispatch omitted.
		(void)childId;
		return true;
	}

	case 0x4014: // GLM_RIGHT_CLICKED -- not modelled
	case 0x4025: // GCM_SET_TEXT -- not modelled
	default:
		return false;
	}
}
