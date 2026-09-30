// Open-BFME: clean C++ lift of the list teardown at 0x0005D7E0.

extern "C" __declspec(dllimport) int __cdecl free(void *memory);

class Rva0005D7E0
{
public:
	~Rva0005D7E0(void);

private:
	void *m_first;
	void *m_sentinel;
};

Rva0005D7E0::~Rva0005D7E0(void)
{
	if (m_first != &m_sentinel)
		free(m_first);
}
