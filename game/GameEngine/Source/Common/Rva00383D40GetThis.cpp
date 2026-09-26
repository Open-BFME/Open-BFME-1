// cl: /O2 /Ob0

// Retail 0x00383D40 returns this unchanged. No identity evidence names an
// owning class, so the source keeps the carved address identity.

class Rva00383D40
{
public:
	unsigned int getThis() const;
};

unsigned int Rva00383D40::getThis() const
{
	return (unsigned int)this;
}
