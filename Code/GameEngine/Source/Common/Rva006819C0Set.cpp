// cl: /DNDEBUG /MD /O2

class BfmeThingHT;

class BfmeOwnerHT
{
public:
	void bfmeSetHT(BfmeThingHT *value);
};

class Rva006819C0Owner
{
public:
	void set(BfmeThingHT *value);

private:
	char m_pad0[8];
	BfmeOwnerHT *m_owner;
};

void Rva006819C0Owner::set(BfmeThingHT *value)
{
	if (m_owner != 0)
		m_owner->bfmeSetHT(value);
}
