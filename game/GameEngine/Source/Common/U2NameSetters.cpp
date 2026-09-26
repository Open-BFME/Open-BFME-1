// Two members that copy a string into a fixed-size buffer of their own object
// through one shared cdecl callee:
//
//     0x00801470   buffer at +0x30, size 0x25
//     0x008014A0   buffer at +0x55, size 0x80
//
// Both push, right to left, the source pointer, the buffer's SIZE, and the
// buffer's ADDRESS (`add ecx,DISP` -- the buffer is inline in the object, not a
// pointer field, or the compiler would have loaded it).  A destination, a
// capacity and a source in that order is a bounded copy; the capacity is a
// literal that matches the gap to the next member exactly, so it is written
// here as `sizeof(m_name)` rather than as a magic number.
//
// The two sizes and the two offsets are different, so these are two classes.
// The callee is one function for both, pinned by an address-derived name;
// nothing in the image names it or the two owners.

extern void Rva007E8640Copy(char *dst, unsigned int size, const char *src);

struct Rva00801470Owner
{
	char m_head[0x30];
	char m_name[0x25];

	void setName(const char *name);
};

void Rva00801470Owner::setName(const char *name)
{
	Rva007E8640Copy(m_name, sizeof(m_name), name);
}

struct Rva008014A0Owner
{
	char m_head[0x55];
	char m_name[0x80];

	void setName(const char *name);
};

void Rva008014A0Owner::setName(const char *name)
{
	Rva007E8640Copy(m_name, sizeof(m_name), name);
}
