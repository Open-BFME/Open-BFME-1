// cl: /Od /Gy

namespace _STL
{
class NodeAllocMutex
{
public:
	void _M_acquire_lock();
};
}

// BfmeGrokOdIf0.cpp defines the cells at 0x0130B250 and 0x0130B254.
// Both call sites use the node allocator's mutex-acquire body at 0x0082DA10.
struct Gen_0082ad50;
extern Gen_0082ad50 g_bfme0130b250;
extern Gen_0082ad50 g_bfme0130b254;

class BfmeThingVLY
{
public:
	BfmeThingVLY *bfmeCtorVLY();
};

BfmeThingVLY *BfmeThingVLY::bfmeCtorVLY()
{
	if (0)
		reinterpret_cast<_STL::NodeAllocMutex *>(&g_bfme0130b250)->_M_acquire_lock();
	return this;
}


class BfmeThingVLZ
{
public:
	BfmeThingVLZ *bfmeCtorVLZ();
};

BfmeThingVLZ *BfmeThingVLZ::bfmeCtorVLZ()
{
	if (1)
		reinterpret_cast<_STL::NodeAllocMutex *>(&g_bfme0130b254)->_M_acquire_lock();
	return this;
}
