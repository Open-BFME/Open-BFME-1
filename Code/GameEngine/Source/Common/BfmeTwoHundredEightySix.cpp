// cl: /Od /Ob1
// A held block let go of through one of two paths according to a size the
// caller never sees, built without optimisation but with the sizing helper
// spelled out in place. Both callees are pinned by address.

void bfmeBigFreePZ(void *at);

void bfmeSmallFreePZ(void *at, unsigned int bytes);

inline void bfmeFreeSizedPZ(void *at, unsigned int bytes)
{
	if (bytes > 0x80)
		bfmeBigFreePZ(at);
	else
		bfmeSmallFreePZ(at, bytes);
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
