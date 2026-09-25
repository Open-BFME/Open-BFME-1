// cl: /DNDEBUG /MD /EHsc /O2
//
// Open-BFME: W3DRenderObjectSnapshot scalar-deleting destructor at retail RVA
// 0x006BCE10 (30 bytes).  The exact constructor at 0x006BCD80 installs
// vtable 0x0111D024, and the matched complete destructor at 0x006BCE40
// owns the +0x4 reference-counted member before chaining through the
// BfmeBaseVUQ base.

class W3DRenderObjectSnapshot
{
public:
	virtual ~W3DRenderObjectSnapshot();
};

void forceRva006BCE40DeletingDestructor()
{
	W3DRenderObjectSnapshot value;
}
