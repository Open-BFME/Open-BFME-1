// cl: /O2 /Ob0 /MD /EHsc
// The 50-by-21 mouse-cursor texture table at VA 0x012F8798: retail builds it
// as 1050 four-byte BfmeHandleCX cells (stride 4, zero-filled .data extent
// 4200). ILT110D6 routes to RVA 0044F3C0 (thiscall: zero the pointer at +0
// and return this) and ILT30652 routes to the existing BfmeHandleCX
// destructor RVA 0005CC00 (null guard and Release_Ref). The image records the
// datum under the pointer-array name
// ?g_w3dMouseCursorTextures@@3PAY0BF@PAVTextureClass@@A (dir32 record and data
// row), which W3DMouse.cpp/W3DMouseConstructor.cpp also use; defining the
// handle array under that recorded spelling through __identifier makes this
// unit emit retail's compiler initializer _$E1 (00C6C4A0: ??_L vector ctor
// plus atexit) and its atexit cleanup _$E2 (00C709D0: ??_M vector dtor).
class TextureClass;
class BfmeHandleCX
{
public:
    BfmeHandleCX();
    ~BfmeHandleCX();
    TextureClass *rva00000000;
};
extern "C" {
BfmeHandleCX __identifier("?g_w3dMouseCursorTextures@@3PAY0BF@PAVTextureClass@@A")[50][21];
}
// The recorded C++ spelling of the same datum (sizeof 4200), for its other users.
extern TextureClass *g_w3dMouseCursorTextures[50][21];
inline BfmeHandleCX::BfmeHandleCX()
{
    rva00000000 = 0;
}
