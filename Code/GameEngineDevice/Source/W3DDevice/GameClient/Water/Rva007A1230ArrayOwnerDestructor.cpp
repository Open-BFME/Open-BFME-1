// cl: /DNDEBUG /MD /EHsc
//
// Clean reconstruction of the two-array owner destructor at retail
// 0x007A1230.  The target vtable and member layout are known, but no named
// caller identifies the retail class, so the owner and cell names remain
// address-derived.

class Rva007A1230Cell
{
public:
	~Rva007A1230Cell();

private:
	void *m_value;
};

class Rva007A1230ArrayOwner
{
public:
	virtual ~Rva007A1230ArrayOwner();

private:
	void releaseOwnedState(void);
	unsigned char m_beforeArrays[8];
	Rva007A1230Cell m_first[6];
	Rva007A1230Cell m_second[6];
};

Rva007A1230ArrayOwner::~Rva007A1230ArrayOwner()
{
	releaseOwnedState();
}
