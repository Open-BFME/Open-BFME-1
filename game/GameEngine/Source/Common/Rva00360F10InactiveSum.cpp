// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// The caller at 0x00367010 proves this thiscall receiver and the int return.
// The original method name is not recovered; the address is retained in the
// owner and method names.  Its body sums +0x34 for entries whose +0x38 byte is
// clear, over the +0x30 vector with 0xB4-byte elements.

struct Rva00360F10Elem
{
	char m_pad[ 0x34 ];
	int m_value;
	bool m_active;
	char m_pad2[ 0xB4 - 0x39 ];
};

struct Rva00360F10Owner
{
	char m_pad[ 0x30 ];
	Rva00360F10Elem * volatile m_begin;
	Rva00360F10Elem * volatile m_end;
	unsigned int size() const { return m_end - m_begin; }
	int sumInactive();
};

int Rva00360F10Owner::sumInactive()
{
	int sum = 0;
	unsigned int i = 0;
	if (i < size()) {
		char *element = reinterpret_cast<char *>( m_begin );
		element += 0x34;
		do {
			if (!*reinterpret_cast<unsigned char *>( element + 4 ))
				sum += *reinterpret_cast<int *>( element );
			++i;
			element += 0xB4;
		} while (i < size());
	}
	return sum;
}
