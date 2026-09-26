// cl: /O2 /DNDEBUG /MD
// Retail 0x00549FB0 returns the receiver pointer and has no semantic owner evidence.

class Rva00549FB0
{
public:
	void *self(void);
};

void *Rva00549FB0::self(void)
{
	return this;
}
