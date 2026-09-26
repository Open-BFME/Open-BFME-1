// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: W3DProjectedShadowManager scalar-deleting destructor at retail
// RVA 0x007B4FB0 (30 bytes). The exact constructor at 0x007AF5A0 installs
// vtable 0x01128404, whose slot zero routes through ILT 0x000352D3 to this
// wrapper. The global singleton allocation corroborates identity; the wrapper
// calls the complete destructor through ILT 0x0001412D.

class W3DProjectedShadowManager
{
public:
	virtual ~W3DProjectedShadowManager();
};

void forceW3DProjectedShadowManagerDeletingDestructor()
{
	W3DProjectedShadowManager value;
}
