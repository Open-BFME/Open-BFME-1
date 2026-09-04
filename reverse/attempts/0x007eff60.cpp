// ?d_007eff60@@YAXXZ
// partial score=0.92 date=2026-09-04
// ?call@Rva007EFF60@@QAEXPAX0@Z
// partial score=0.92 date=2026-09-02
// cl: /O2
// 0x007EFF60: if the +4 cdecl callback is live, call it with the two stack args.

class Rva007EFF60
{
public:
	void call(void *a, void *b);
	char m_pad[4];
	void (*m_fn)(void *a, void *b);
};

void Rva007EFF60::call(void *a, void *b)
{
	switch (m_fn != 0)
	{
	case 0:
		return;
	default:
		m_fn(a, b);
		break;
	}
}
