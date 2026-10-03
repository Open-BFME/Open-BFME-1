// cl: /Od /Ob1
// A held block let go of through one of two paths according to a size the
// caller never sees, built without optimisation but with the sizing helper
// spelled out in place. Both callees are pinned by address.

extern "C" void __identifier("?j_0002ab35@@YAXXZ")(void *at);

extern "C" void __identifier("?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z")
	(void *at, unsigned int bytes);

inline void bfmeFreeSizedPZ(void *at, unsigned int bytes)
{
	if (bytes > 0x80)
		__identifier("?j_0002ab35@@YAXXZ")(at);
	else
		__identifier("?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z")(at, bytes);
}

class BfmeThingPZ
{
public:
	void bfmeFreePZ(void *at);
};

void BfmeThingPZ::bfmeFreePZ(void *at)
{
	if (at != 0)
		bfmeFreeSizedPZ(at, 4);
}
