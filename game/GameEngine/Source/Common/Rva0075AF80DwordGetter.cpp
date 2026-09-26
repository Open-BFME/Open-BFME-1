// Dword-field getter at 0x0075AF80.
//
//     mov eax, dword ptr [ecx+0x2EC] / ret
//
// Identity is not recovered. The class name is the retail RVA.

class Rva0075AF80
{
public:
	unsigned int get();
	char m_lead[0x2EC];
	unsigned int m_value;
};

unsigned int Rva0075AF80::get()
{
	return m_value;
}
