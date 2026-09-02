// ?d_007ccf50@@YAXXZ
// partial score=0.15 date=2026-09-02
// cl: /DNDEBUG /MD
//
// Near-miss notes for the large filter postRender bodies in
// Code/gen_asm/d_007ccf50.asm:
//   0x007CCF50 size 3931  FUN_00bccf50
//   0x007CE290 size 8147  FUN_00bce290
//   0x007D3D40 size 1817  FUN_00bd3d40
//
// All three are thiscall, ret 4 (one stack arg) or ret 10h (mode + Coord2D by
// value + bool&), with C++ EH.  The 111-byte ScreenDefaultFilter::postRender
// at 0x007D46D0 (already landed) is the small sibling: endRenderToTexture via
// ILT 0x3FAC6, virtual set at vtable+0x14, device SetTexture at +0x104
// (_g_bfmeO1145), blit helper ILT 0x196A0 as bfmeDrawFilterUV(-1, 0, &uv1_1),
// virtual reset at +0x18.  The large bodies unroll many DrawImage / set-clip
// / UnicodeString sequences (the same helper family as BfmeConv1145) instead
// of a single blit.  Port from ZH ScreenBWFilter / ScreenCrossFadeFilter /
// ScreenMotionBlurFilter::postRender and replace the DrawPrimitiveUP quad
// with those helpers.  Do not lift the dump.

struct Coord2D
{
	float x;
	float y;
};

void *__cdecl bfmeEndRenderToTexture(void);
void __cdecl bfmeDrawFilterUV(int a, int b, Coord2D *uv);

class ScreenFilterPostRenderLarge
{
public:
	virtual int set(int mode);
	virtual void reset();
	bool postRender(int mode, Coord2D scroll, bool &extra);
};

bool ScreenFilterPostRenderLarge::postRender(int mode, Coord2D scroll, bool &extra)
{
	void *tex = bfmeEndRenderToTexture();
	if (!tex)
		return false;
	if (!set(mode))
		return false;
	Coord2D uv;
	uv.x = 1.0f;
	uv.y = 1.0f;
	bfmeDrawFilterUV(-1, 0, &uv);
	reset();
	return true;
}
