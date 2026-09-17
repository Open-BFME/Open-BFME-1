// Retail 0x0090F050 releases every registered device-reset resource.
// DX8Wrapper::Reset_Device calls this helper at 0x009082B0 after the mesh
// renderer cleanup and before it clears the reset state.

struct BfmeLockTEA
{
	char m_pad[0x18];
	bool m_armed;
};

extern "C" __declspec(dllimport) void __stdcall bfmeEnterTEA(BfmeLockTEA *lock);
extern "C" __declspec(dllimport) void __stdcall bfmeLeaveTEA(BfmeLockTEA *lock);

class Rva00886F60Class
{
public:
	Rva00886F60Class(BfmeLockTEA *lock)
	{
		m_lock = lock;
		if (lock && lock->m_armed)
		{
			bfmeEnterTEA(lock);
		}
	}

	~Rva00886F60Class() {}

	virtual void guardVirtual();

private:
	BfmeLockTEA *m_lock;
};

class Rva0090F050Resource
{
public:
	virtual ~Rva0090F050Resource();
	virtual void unusedVirtual();
	virtual void __stdcall releaseResources();
};

class Gen_00C71060Target
{
public:
	Rva0090F050Resource **m_begin;
	Rva0090F050Resource **m_end;
	Rva0090F050Resource **m_capacity;
};

extern Gen_00C71060Target TheBfmeObject_00C71060;

extern void W3DRadarResetLock(void);
extern void W3DRadarResetUnlock(void);

void Rva0090F050()
{
	Rva0090F050Resource **end = TheBfmeObject_00C71060.m_end;
	Rva0090F050Resource **begin = TheBfmeObject_00C71060.m_begin;
	if (begin == end)
	{
		return;
	}

	Rva00886F60Class guard(reinterpret_cast<BfmeLockTEA *>(0x012D6DE0u));
	W3DRadarResetLock();
	for (Rva0090F050Resource **it = TheBfmeObject_00C71060.m_begin;
		it != TheBfmeObject_00C71060.m_end; ++it)
	{
		(*it)->releaseResources();
	}
	W3DRadarResetUnlock();
	bool armed = *reinterpret_cast<bool *>(0x012D6DF8u);
	*reinterpret_cast<Rva0090F050Resource ***>(0x013411F4u) =
		*reinterpret_cast<Rva0090F050Resource ***>(0x013411F0u);
	if (armed)
	{
		bfmeLeaveTEA(reinterpret_cast<BfmeLockTEA *>(0x012D6DE0u));
	}
}
