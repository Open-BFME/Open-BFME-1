// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: W3DHordeModelDraw scalar-deleting destructor at retail RVA
// 0x00752FC0 (30 bytes). The exact constructor at 0x00751CF0 installs vtable
// 0x01122470, whose slot zero routes through ILT 0x000370B0 to this wrapper.
// The named draw-module factory at 0x006BFBE0 corroborates identity; the
// wrapper calls the complete destructor through ILT 0x000305F3.

class W3DHordeModelDraw
{
public:
	virtual ~W3DHordeModelDraw();
};

void forceW3DHordeModelDrawDeletingDestructor()
{
	W3DHordeModelDraw value;
}
