// ??1Rva005E2C70@@UAE@XZ
// partial score=0.75 date=2026-09-06
// cl: /DNDEBUG /MD
//
// Open-BFME5: two more members of the V3_MI_NODE_DTOR family already
// converted in V3MiDtorsWithListNodeWave2.cpp (implicit destructor of a class
// with polymorphic bases and base-to-base pointer conversions that keep the
// null-propagating test/je/lea/jmp/xor form), except these two carry a
// FOURTH base (BfmeBaseVUQ, 0x01073744) immediately followed by a
// BFMERetailAsciiString member, so the third base here (V3Vt107375C) is the
// width-8 variant (vtable + one pad dword) to make room for it at +0x20.
//
// Same tail-call target (0x00013994, the GenNode_006fa270::unlink ILT) and
// same first base (V3NodeHead, vtable 0x0111126C) as the rest of that family.

struct GenOwner_006fa270;

struct GenNode_006fa270
{
	GenOwner_006fa270 *m_owner;                                 // +0
	GenNode_006fa270 *m_prev;                                   // +4
	GenNode_006fa270 *m_next;                                    // +8

	void unlink(void);

	~GenNode_006fa270(void) { unlink(); }
};

// first base -- vftable 0x0111126C, 0x14 bytes wide
class V3NodeHead
{
public:
	virtual ~V3NodeHead() { }
	GenNode_006fa270 m_node;                                    // +4
	int m_unreconstructed_10;                                   // +0x10
};

// second base, width 4 -- vftable 0x01110830
class V3Vt1110830
{
public:
	virtual void slot0();
	virtual ~V3Vt1110830() { }
};

// third base, width 8 (needs the pad to make room for the fourth base at +0x20) -- vftable 0x0107375C
class V3Vt107375CWide
{
public:
	virtual void slot0();
	virtual ~V3Vt107375CWide() { }
	int m_unreconstructed_04;
};

template <typename T>
class StringBase
{
public:
	~StringBase() { releaseBuffer(); }
	void *m_data;

private:
	void releaseBuffer();
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
	~BFMERetailAsciiString() { }
};

// fourth base -- the shared trivial BfmeBaseVUQ vftable, 0x01073744. Its own
// destructor releases the string that immediately follows it in the object,
// so both go through the same null-checked base-conversion pointer as every
// other base transition in this family (no extra class boundary/EH state).
class BfmeBaseVUQ
{
public:
	virtual ~BfmeBaseVUQ() { }
	BFMERetailAsciiString m_str;
};

#define V3_MI_STR_DTOR( NAME )                                              \
	class NAME : public V3NodeHead, public V3Vt1110830, public V3Vt107375CWide, public BfmeBaseVUQ \
	{                                                                        \
	};                                                                       \
	void use##NAME()                                                        \
	{                                                                        \
		NAME t;                                                             \
	}

V3_MI_STR_DTOR( Rva005E2C70 )
V3_MI_STR_DTOR( Rva005E2D20 )
