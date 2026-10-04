extern "C" void *bfmeVft1030B[];
extern "C" char *g_bfmeFreeList1150[];
extern "C" int g_bfmeGuardXH;

// 0x0082C760 is STLport's _STL::_STLP_mutex_spin<0>::_M_do_lock, owned by
// game/Libraries/Source/WWVegas/WWLib/STLPortMutexSpinLock.cpp
// (?_M_do_lock@?$_STLP_mutex_spin@$0A@@_STL@@SAXPCJ@Z). Declare the same
// template STLportMutexSpinLock.cpp defines and never define it here, so the
// object only references that body -- the pattern game/stlport/Rva008327E0.cpp
// and game/GameEngine/Source/Common/NodeAllocMutexAcquireLock.cpp already use.
namespace _STL
{

template <int Instance>
struct _STLP_mutex_spin
{
	static void __cdecl _M_do_lock(volatile long *lock);
};

}  // namespace _STL

void __cdecl operator delete(void *block);

class BfmeBufXH
{
public:
	void bfmeDtorXH();

	void *volatile m_bfmeVfptrXH;
	unsigned char m_bfmePadXH[8];
	char *volatile m_bfmeStartXH;
	char *m_bfmeMidXH;
	char *volatile m_bfmeEndXH;
};

void BfmeBufXH::bfmeDtorXH()
{
	m_bfmeVfptrXH = bfmeVft1030B;

	char *end = m_bfmeEndXH;
	char *start = m_bfmeStartXH;
	unsigned int used = end - start;

	if (start != 0)
	{
		if (used > 0x80)
		{
			operator delete(start);
		}
		else
		{
			char **list = g_bfmeFreeList1150 + ((used - 1) >> 3);

			_STL::_STLP_mutex_spin<0>::_M_do_lock((volatile long *)&g_bfmeGuardXH);
			*(char **)start = *list;
			*list = start;
			g_bfmeGuardXH = 0;
		}
	}
}
