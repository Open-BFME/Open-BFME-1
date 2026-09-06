// cl: /DNDEBUG /MD
// Retail 0x00726F70: fill a locked surface with the requested taint color.
//
// TaintBuffer is a descriptive name, not a recovered EA one.  What the exe
// proves is the subject: the GlobalData FieldParse table at 0x00C77018 maps the
// INI keys TaintOn to +0xCF5, TaintAlpha to +0xCA0 and TaintColor to +0xC88
// (reverse/field_names.csv), every body in this family gates on TheWritableGlobalData
// ->m_taintOn, TaintBuffer::init drives TheTaintManager -- the literal at 0x79060 --
// and the shaders it feeds are shaders\terraintaint.pso and terraintaint2.pso.
// The object itself is the render-side cell buffer for that overlay: a cell grid
// sized from WorldHeightMap, a destination texture it reacquires, and a dirty-cell
// set, which is the same shape W3DShroud has for the shroud.  No __FILE__ literal
// reaches this code run, so the retail class name is still unknown.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	unsigned char m_pad00[0xCF5];
	unsigned char m_taintOn;
};

extern GlobalData *TheWritableGlobalData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/surfaceclass.h
class SurfaceClass
{
public:
	void *Lock(int *pitch, bool discard);
	void Unlock(void);
};

class TaintBuffer
{
public:
	void fillTaintSurface(unsigned char alpha, SurfaceClass *surface);

private:
	unsigned char m_pad00[0x20];
	int m_width;
	int m_height;
};

// ?fillTaintSurface@TaintBuffer@@QAEXEPAVSurfaceClass@@@Z
void TaintBuffer::fillTaintSurface(unsigned char alpha, SurfaceClass *surface)
{
	GlobalData *g = TheWritableGlobalData;
	if (!g)
		return;
	if (!g->m_taintOn)
		return;

	unsigned int color = alpha;
	color = (color << 8) | alpha;
	color = (color << 8) | alpha;
	color = (color << 8) | alpha;

	int pitch;
	unsigned int *pixels = (unsigned int *)surface->Lock(&pitch, false);
	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
			pixels[x] = color;
		pixels = (unsigned int *)((unsigned char *)pixels + pitch);
	}
	surface->Unlock();
}
