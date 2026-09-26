// cl: /DNDEBUG /MD /EHs-c-
// The outer global-pointer guard and the inlined Release_Ref method are both
// material to the retail shape.  MSVC does not carry the first guard through
// the inlined method's delete-this expansion, so the second null test remains.
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *value);

class C6GlobalReleaseTarget
{
public:
	virtual ~C6GlobalReleaseTarget();

	void Release_Ref(void)
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;
};

extern C6GlobalReleaseTarget *g_c6GlobalReleaseTarget;

// ?c6GlobalReleaseB@@YAXXZ
void c6GlobalReleaseB(void)
{
	if (g_c6GlobalReleaseTarget)
		g_c6GlobalReleaseTarget->Release_Ref();
}
