// Open-BFME5: clean C++ conversion of the four-entry CDC cache destructor.

extern void (__stdcall *g_destroy)(void *allocation);

class CDCCache
{
public:
	~CDCCache();

private:
	void *m_allocations[4];
};

CDCCache::~CDCCache()
{
	for (int index = 0; index < 4; ++index)
	{
		if (m_allocations[index] != 0)
			g_destroy(m_allocations[index]);
	}
}
