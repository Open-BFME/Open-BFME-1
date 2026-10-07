// Open-BFME5: clean C++ conversion of the child-or-owner predicate.

class Rva0016AE80Child
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual bool testChild();
};

// Matched owner predicate at 0x000A0040, reached through ILT 0x00029C3F.
class BfmeThingDVA
{
public:
	bool bfmeGoDVA();
};

class Rva0016AE80Owner
{
public:
	bool testChildOrOwner();

	char m_pad00[0x58];
	Rva0016AE80Child *m_child;
};

bool Rva0016AE80Owner::testChildOrOwner()
{
	if (m_child != 0 && m_child->testChild())
		return true;

	return reinterpret_cast<BfmeThingDVA *>(this)->bfmeGoDVA();
}
