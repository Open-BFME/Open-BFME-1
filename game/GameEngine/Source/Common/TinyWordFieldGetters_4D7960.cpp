// Word-field getter at 0x004D7960.
//
//     mov ax, word ptr [ecx+0x450] / ret
//
// Identity is not recovered. The class name is the retail RVA.

class Rva004D7960
{
public:
	unsigned short get() const;
	char m_lead[0x450];
	unsigned short m_value;
};

unsigned short Rva004D7960::get() const
{
	return m_value;
}
