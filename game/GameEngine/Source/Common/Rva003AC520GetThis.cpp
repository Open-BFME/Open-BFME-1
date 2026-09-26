// cl: /O2 /Ob0

// Retail 0x003AC520 returns this unchanged. No caller or identity table proves
// a semantic owner, so the ledger keeps the carved address identity.

class Rva003AC520
{
public:
	unsigned int getThis() const;
};

// ?b_003ac520@@YAXXZ
unsigned int Rva003AC520::getThis() const
{
	return (unsigned int)this;
}
