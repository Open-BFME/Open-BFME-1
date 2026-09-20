// cl: /O2 /Ob2 /DNDEBUG /MD

// The carved body at retail RVA 0x00748FE0 returns the pointer at offset 0.
// The class and method names keep that unproven identity tied to the address.
class Rva00748FE0Pointer
{
public:
	void *value();

private:
	void *m_value;
};

void *Rva00748FE0Pointer::value()
{
	return m_value;
}
