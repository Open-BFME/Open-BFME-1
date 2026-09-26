// Word-field getter at 0x000C9010.
//
//     mov ax, word ptr [ecx+0x478] / ret
//
// Identity is not recovered. The class name is the retail RVA.

class Rva000C9010
{
public:
	unsigned short get() const;
	char m_lead[0x478];
	unsigned short m_value;
};

unsigned short Rva000C9010::get() const
{
	return m_value;
}
