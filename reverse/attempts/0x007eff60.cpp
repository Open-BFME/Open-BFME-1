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
	void (*fn)(void *, void *) = m_fn;
	if (!fn)
		return;
	fn(a, b);
}
