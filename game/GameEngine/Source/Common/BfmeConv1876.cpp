class BfmeSurfaceZI
{
public:
	void *bfmeLockZI(int *rect, int a, int b, int c, int d);
};

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

	*out = surface->bfmeLockZI(rect, a, b, c, d);

	return this;
}
