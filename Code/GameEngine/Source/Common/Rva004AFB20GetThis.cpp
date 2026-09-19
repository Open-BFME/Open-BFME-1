// cl: /O2 /Ob0

// Retail 0x004AFB20 returns this unchanged. No caller or identity table proves
// a semantic owner, so the ledger keeps the carved address identity.

class Rva004AFB20
{
public:
	unsigned int getThis() const;
};

// ?d_004afb20@@YAXXZ
unsigned int Rva004AFB20::getThis() const
{
	return (unsigned int)this;
}
