// ??1Rva0090D090@@UAE@XZ
// partial score=0.55 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: near-twin of ??1Rva00491DB0DisplayOwner (0x00491DB0,
// Rva00491DB0DisplayOwnerDtor.cpp); same single-vtable shape, but the +0x14
// member here is a plain owned pointer whose vtable slot 1 is invoked directly
// (rather than a TheDisplay vcall), and the tail call reuses the already-landed
// BfmeThingUB::bfmeResetUB instead of a plain thunk.

class Rva0090D090Owned
{
public:
	virtual void slot0();
	virtual void slot1(int);
};

class StringClass
{
public:
	~StringClass();
};

class BfmeThingUB
{
public:
	~BfmeThingUB();
private:
	void *m_bfmeVft;
};

class Rva0090D090 : public BfmeThingUB
{
public:
	virtual ~Rva0090D090();

private:
	unsigned char m_pad[0x14 - 4 - 4];
	Rva0090D090Owned *m_owned;
	StringClass m_str;
};

// ?d_0090d090@@YAXXZ
Rva0090D090::~Rva0090D090()
{
	if (m_owned)
		m_owned->slot1(1);
}
