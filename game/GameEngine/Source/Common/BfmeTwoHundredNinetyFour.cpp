// cl: /Od /Ob1
// A held block let go of through one of two paths according to a size the
// caller never sees, built without optimisation but with the sizing helper
// spelled out in place. Both callees are pinned by address.

void bfmeBigFreeQJ(void *at);

void bfmeSmallFreeQJ(void *at, unsigned int bytes);

inline void bfmeFreeSizedQJ(void *at, unsigned int bytes)
{
	if (bytes > 0x80)
		bfmeBigFreeQJ(at);
	else
		bfmeSmallFreeQJ(at, bytes);
}

class BfmeThingQJ
{
public:
	void bfmeFreeQJ(void *at);
};

void BfmeThingQJ::bfmeFreeQJ(void *at)
{
	if (at != 0)
		bfmeFreeSizedQJ(at, 1);
}
