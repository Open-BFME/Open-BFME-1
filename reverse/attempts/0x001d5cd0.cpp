// ?clear@Rva001D5CD0Owner@@QAEXXZ
// partial score=0.7 date=2026-09-20
// cl: /DNDEBUG /MD

class W3DProjectileStreamResources
{
public:
	__declspec(noinline) void erase(void *, void *);
	void *begin()
	{
		return m_first;
	}

	void *end()
	{
		return m_last;
	}

	void *m_first;
	void *m_last;
};

class Rva001D5CD0Owner
{
public:
	void clear();

private:
	char m_padding[0x20];
	W3DProjectileStreamResources m_resources;
};

// ?clear@Rva001D5CD0Owner@@QAEXXZ
void Rva001D5CD0Owner::clear()
{
	m_resources.erase(m_resources.begin(), m_resources.end());
}
