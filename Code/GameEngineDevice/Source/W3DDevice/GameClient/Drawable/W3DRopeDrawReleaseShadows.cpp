// cl: /DNDEBUG /MD /EHsc

class W3DRopeDraw
{
public:
	virtual void releaseShadows();
};

// W3DRopeDraw's primary vtable slot points through ILT 0x0000EDBD to
// 0x0075A560. Rope lines have no shadow resources to release.
void W3DRopeDraw::releaseShadows()
{
}
