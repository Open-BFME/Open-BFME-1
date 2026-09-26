// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: W3DBuffDraw scalar-deleting destructor at retail RVA 0x007504C0
// (30 bytes). The exact constructor at 0x00750240 installs vtable 0x01121CD8,
// whose slot zero routes through ILT 0x0002CC14 to this wrapper. The named
// module factory and methods corroborate identity; dtor ILT 0x0001FCB7.

class W3DBuffDraw
{
public:
	virtual ~W3DBuffDraw();
};

void forceW3DBuffDrawDeletingDestructor()
{
	W3DBuffDraw value;
}
