// Rva007EFF60::call at retail RVA 0x007EFF60 (28 bytes).
// The compiler barrier in the null branch preserves retail's duplicated
// ret 8 exits while emitting no instruction or relocation.
// cl: /O2

extern "C" void __cdecl _ReadWriteBarrier(void);

class Rva007EFF60
{
public:
	void call(void *a, void *b);
	char m_pad[4];
	void (*m_fn)(void *a, void *b);
};

#pragma intrinsic(_ReadWriteBarrier)

void Rva007EFF60::call(void *a, void *b)
{
	switch (m_fn == 0)
	{
	case 0:
		m_fn(a, b);
		break;
	default:
		_ReadWriteBarrier();
		return;
	}
}
