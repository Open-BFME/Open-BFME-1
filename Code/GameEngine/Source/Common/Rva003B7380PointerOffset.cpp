// cl: /O2

// The carved body only proves an eight-byte pointer load followed by an
// addition of sixteen.  No caller or table provides a semantic identity.
class Rva003B7380PointerOffset
{
public:
	void *get();

private:
	void *m_base;
};

void *Rva003B7380PointerOffset::get()
{
	return static_cast<unsigned char *>(m_base) + 0x10;
}
