// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: a destructor at retail 0x001F6D40, 90 bytes.  The vftable store
// lands after the member teardown because it belongs to an inline base
// destructor, which runs last.

extern "C" void *bfmeVftableBX[];

class BfmeBaseBX
{
public:
	~BfmeBaseBX(void)
	{
		m_bfmeVfptrBX = bfmeVftableBX;
	}

	void *volatile m_bfmeVfptrBX;
};

class BfmeElemBX
{
public:
	~BfmeElemBX(void);

	void *m_bfmeSlotBX;
};

class BfmeMemberBX
{
public:
	~BfmeMemberBX(void);

	void *m_bfmeSlotBX;
};

class BfmeOwnerBX : public BfmeBaseBX
{
public:
	~BfmeOwnerBX(void);

	char m_bfmePadBX[4];
	BfmeElemBX m_bfmeElemsBX[4];
	BfmeMemberBX m_bfmeMemberBX;
};

BfmeOwnerBX::~BfmeOwnerBX(void)
{
}
