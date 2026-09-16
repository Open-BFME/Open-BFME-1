// cl: /DNDEBUG /MD /EHsc /O2
//
// Retail 0x002E7530, 225 bytes.  A __thiscall member with three arguments that
// walks the vector between this+0xA4 and this+0xA8 in 0x1C-byte steps.
//
// WHAT NAMES THE PARTS.  The per-record test at ILT 0x0000450C reaches the
// matched body at 0x002E0490, which the ledger already carries as
// ?bfmeTestYN@BfmeOwnerYN@@QAEDPAUBfmeMaskYN@@@Z, so the records are BfmeOwnerYN
// and the first two arguments are masks.  The dispatch at ILT 0x0003D4E7 is the
// tail the matched 17-byte wrapper ?bfmeGo939B@BfmeOwnerBR@@QAEXHPAVObject@@
// PAVDelayedLuaEventList@@@Z at 0x002E7650 calls on its own this, so this body
// is another member of BfmeOwnerBR and its third argument is the Object the
// wrapper passes.  The local is a DelayedLuaEventList: the constructor stores
// the named vtable 0x01085E10 and hands the EH vector constructor iterator
// three 0x18-byte elements at +4 with the element constructor and destructor
// ILTs 0x0003A1C5 and 0x00041362, exactly as the matched constructor at
// 0x000EDBB0 does.  The trailing store of 0x01073744 is the empty polymorphic
// base the matched destructor at 0x000EDC40 restores.  Nothing in the image
// names the member itself, so the name stays address-derived.
//
// SHAPE.  The list class takes the compiler-generated constructor and
// destructor.  With a user-written pair MSVC emits the vtable store at the top
// of both, which puts the store ahead of the iterator arguments and adds a
// second store at the head of the destructor; the implicit pair sinks the store
// to just before the call and emits nothing at the head of the destructor,
// which is retail's shape.

class Object;
struct BfmeMaskYN;
struct BfmeElem939B;

class BfmeOwnerYN
{
public:
	char bfmeTestYN(BfmeMaskYN *mask);			// retail 0x002E0490

private:
	char m_bfmeBody[0x1c];
};

class BfmeDelayedLuaEvent
{
public:
	BfmeDelayedLuaEvent(void);				// ILT 0x0003A1C5
	~BfmeDelayedLuaEvent(void);				// ILT 0x00041362

private:
	char m_bfmeBody[0x18];
};

class BfmeBaseVUQ
{
public:
	virtual ~BfmeBaseVUQ(void) {}
};

class DelayedLuaEventList : public BfmeBaseVUQ
{
public:
	BfmeDelayedLuaEvent m_bfmeEvents[3];			// +0x04
};

class BfmeOwnerBR
{
public:
	void bfmeGo7530(BfmeMaskYN *a, BfmeMaskYN *b, Object *object);
	void bfmeTail939B(BfmeElem939B *e, Object *object,
		DelayedLuaEventList *events);			// ILT 0x0003D4E7

private:
	char m_bfmePad[0xa4];
	BfmeOwnerYN *m_bfmeBegin;				// +0xa4
	BfmeOwnerYN *m_bfmeEnd;					// +0xa8
};

void BfmeOwnerBR::bfmeGo7530(BfmeMaskYN *a, BfmeMaskYN *b, Object *object)
{
	for (BfmeOwnerYN *it = m_bfmeBegin; it != m_bfmeEnd; ++it)
	{
		if (it->bfmeTestYN(a) && !it->bfmeTestYN(b))
		{
			DelayedLuaEventList events;
			bfmeTail939B((BfmeElem939B *)it, object, &events);
		}
	}
}
