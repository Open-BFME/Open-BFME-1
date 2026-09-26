// cl: /DNDEBUG /MD /GX- /O2 /Ob2
//
// Retail has two Set_Texture_Tile_Factor bodies, and they are not the same
// function. The one at 0x0095FEF0 clamps at 50.0f and stores at +0x2c; this
// one, at 0x0095C4C0, clamps at 8.0f and stores at +0x28. Different cap,
// different offset, therefore a different class -- 8.0f is the cap Generals
// shipped, so this is very likely an earlier-generation line renderer still
// linked into the executable.
//
// Both addresses used to be claimed from seglinerenderer.cpp, which forced
// that file to carry a hardcoded `*(float *)((char *)this + 0x28) = factor`
// and the wrong 8.0f cap. That made this address match and silently broke the
// two bodies that are genuinely SegLineRendererClass's:
// Set_Texture_Tile_Factor at 0x0095FEF0 and Init at 0x00960190, which inlines
// it. They sat red in the ledger, counted as recovered.
//
// The class identity here is not recovered. The layout below is only what the
// bytes prove: something four bytes wide at +0x28, and nothing else this body
// touches.

class SegLineTileFactorAltClass
{
public:
	void					Set_Texture_Tile_Factor(float factor);

private:
	char					Unrecovered[0x28];
	float					TextureTileFactor;
};

void SegLineTileFactorAltClass::Set_Texture_Tile_Factor(float factor)
{
	const static float MAX_LINE_TILING_FACTOR = 8.0f;
	if (factor > MAX_LINE_TILING_FACTOR) {
		factor = MAX_LINE_TILING_FACTOR;
	} else {
		factor = (factor > 0.0f) ? factor : 0.0f;
	}
	TextureTileFactor = factor;
}
