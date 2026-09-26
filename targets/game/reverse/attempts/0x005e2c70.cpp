// ??1Rva005E2C70@@UAE@XZ
// partial score=0.84 date=2026-09-08
// cl: /DNDEBUG /MD
// The vtable stores, base offsets, and the 0x00013994 unlink tail identify
// this body as an implicit destructor in the V3 multiple-inheritance family.
// The fourth base wraps BfmeBaseVUQ at +0x20 and a StringBase member at +0x24.

struct GenOwner_006fa270;

struct GenNode_006fa270
{
	GenOwner_006fa270 *m_owner;
	GenNode_006fa270 *m_prev;
	GenNode_006fa270 *m_next;

	void unlink(void);

	~GenNode_006fa270(void) { unlink(); }
};

class V3NodeHead
{
public:
	virtual ~V3NodeHead() { }
	GenNode_006fa270 m_node;
	int m_unreconstructed_10;
};

class V3Vt1110830
{
public:
	virtual ~V3Vt1110830() { }
};

class V3Vt107375CWide
{
public:
	virtual ~V3Vt107375CWide() { }
	int m_unreconstructed_04;
};

template <typename T>
class StringBase
{
public:
	~StringBase() throw() { releaseBuffer(); }
	void *m_data;

private:
	void releaseBuffer();
};

class BfmeBaseVUQ
{
public:
	virtual ~BfmeBaseVUQ();
};

BfmeBaseVUQ::~BfmeBaseVUQ()
{
}

class BfmeStringBaseVUQ : public BfmeBaseVUQ
{
	public:
	StringBase<char> m_str;
};

#define V3_MI_STR_DTOR(NAME) \
	class NAME : public V3NodeHead, public V3Vt1110830, public V3Vt107375CWide, public BfmeStringBaseVUQ \
	{ \
	}; \
	void use##NAME() \
	{ \
		NAME t; \
	}

V3_MI_STR_DTOR(Rva005E2C70)
V3_MI_STR_DTOR(Rva005E2D20)
