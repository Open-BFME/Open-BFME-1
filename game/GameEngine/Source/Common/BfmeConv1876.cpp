// Retail 0x006C1390 calls 0x008FC710 directly: the matched SurfaceClass::Lock
// rectangle overload (surfaceclass_lock_rectangle.cpp).
class SurfaceClass
{
public:
	void *Lock(int *rect, int a, int b, int c, int d);
};

class BfmeSurfaceZI;

class BfmeLockZI
{
public:
	BfmeLockZI *bfmeInitZI(BfmeSurfaceZI *surface, void **out, int *rect,
	                       int a, int b, int c, int d);

	BfmeSurfaceZI *m_bfmeSurfaceZI;
};

BfmeLockZI *BfmeLockZI::bfmeInitZI(BfmeSurfaceZI *surface, void **out, int *rect,
                                   int a, int b, int c, int d)
{
	m_bfmeSurfaceZI = surface;

	*out = reinterpret_cast<SurfaceClass *>(surface)->Lock(rect, a, b, c, d);

	return this;
}
