// cl: /O2 /Ob0 /MD /EHsc
// Retail initializer 00C6C4A0 constructs the 50-by-21 texture handle table
// at VA012F8798; stride4 count1050. ILT110D6 routes to RVA0044F3C0
// (thiscall: zero pointer at +0 and return this). ILT30652 routes to the
// existing BfmeHandleCX destructor RVA0005CC00 (null guard and Release_Ref).
// Compiler cleanup _$E2 reproduces RVA00C709D0; atexit registration
// belongs to native array lifetime. Both artifacts retain address identity.
// PE virtual .data contains4200zero bytes with4-byte alignment.
class TextureClass;
class BfmeHandleCX {
public:
    BfmeHandleCX();
    ~BfmeHandleCX();
    TextureClass *rva00000000;
};
inline BfmeHandleCX::BfmeHandleCX()
{
    rva00000000 = 0;
}
BfmeHandleCX g_w3dMouseCursorTextures[50][21];
