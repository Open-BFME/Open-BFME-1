// cl: /DNDEBUG /MD /O2

// The carved body has no identity evidence beyond its address.  It returns
// the address eight bytes after the pointer stored at the receiver.
class Rva000CA090PointerOffset
{
public:
	void *get();

private:
	void *m_base;
};

void *Rva000CA090PointerOffset::get()
{
	return static_cast<unsigned char *>(m_base) + 8;
}
