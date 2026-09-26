// cl: /O2 /Ob0

class Rva0045EE00
{
	void *m_pad0;
	void *m_pad1;
	void (__cdecl *m_fn)(void *);

public:
	void apply(void *arg);
};

void Rva0045EE00::apply(void *arg)
{
	m_fn(arg);
}
