// cl: /O2

class Rva000A31E0PointerOffset
{
public:
	void *get(void) const;

private:
	void *m_base;
};

// ?get@Rva000A31E0PointerOffset@@QBEPAXXZ
void *Rva000A31E0PointerOffset::get(void) const
{
	return (char *)m_base + 0x10;
}
