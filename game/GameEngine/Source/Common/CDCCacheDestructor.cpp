// Open-BFME5: clean C++ conversion of the four-entry CDC cache destructor.
// cl: /O1

extern "C" __declspec(dllimport) int __stdcall DeleteDC(void *allocation);

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
			DeleteDC(m_allocations[index]);
	}
}
