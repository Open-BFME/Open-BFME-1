// cl: /O2 /Ob0
//
// 17-byte flag test + tail jmp: test byte [this+0x3F0], 1; if set,
// xor al,al / ret; else jmp ILT 0x000042BE (thiscall, ecx unchanged).

class Rva002BC210
{
	char m_lead[0x3F0];
	unsigned char m_flag;

public:
	bool handle();
	bool call();
};

bool Rva002BC210::call()
{
	if (m_flag & 1)
		return false;
	return handle();
}
