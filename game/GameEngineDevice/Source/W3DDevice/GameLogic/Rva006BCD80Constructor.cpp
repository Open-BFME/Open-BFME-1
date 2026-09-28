// cl: /DNDEBUG /MD /EHsc /O2
// ??0W3DRenderObjectSnapshot@@AAE@PAVRenderObjClass@@PAUDrawableInfo@@_N@Z
// Retail 0x006BCD80: vtable 0x0111D024 names the class by literal; W3DGhostObject::snapShot allocates 12 bytes and calls it.

class BfmeBaseVUQ
{
public:
	virtual ~BfmeBaseVUQ() { }
};

class RenderObjClass;
struct DrawableInfo;

class W3DRenderObjectSnapshot : public BfmeBaseVUQ
{
	W3DRenderObjectSnapshot( RenderObjClass *parentRobj, DrawableInfo *drawInfo, bool cloneParentRobj );
	void update( RenderObjClass *robj, DrawableInfo *drawInfo, bool cloneParentRobj );

	RenderObjClass *m_robj;           ///< +0x04
	W3DRenderObjectSnapshot *m_next;  ///< +0x08
};

W3DRenderObjectSnapshot::W3DRenderObjectSnapshot( RenderObjClass *parentRobj, DrawableInfo *drawInfo, bool cloneParentRobj )
	: m_robj( 0 ), m_next( 0 )
{
	update( parentRobj, drawInfo, cloneParentRobj );
}
