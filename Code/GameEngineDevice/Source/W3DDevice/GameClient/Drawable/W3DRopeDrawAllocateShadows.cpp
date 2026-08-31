// cl: /DNDEBUG /MD /EHsc

class W3DRopeDraw
{
public:
	virtual void allocateShadows();
};

// W3DRopeDraw's primary vtable slot points through ILT 0x0000C987 to
// 0x0075A570. Rope lines have no shadow resources to allocate.
void W3DRopeDraw::allocateShadows()
{
}
