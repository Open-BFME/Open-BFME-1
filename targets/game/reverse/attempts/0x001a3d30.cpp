// ?rva001A3D30@TerrainLogic@@QAE_NABVVector3@@PAV2@@Z
// partial score=0.6394 date=2026-09-30
// cl: /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /D_STLP_USE_STATIC_LIB /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/scriptenginelayout /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
#include "Lib/BaseType.h"
#include "vector3.h"

// TerrainLogic view: map extent at +0x10/+0x14 and a BGR sample grid at +0x18..+0x20.
class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual Real sampleOrigin();

	Bool rva001A3D30(const Vector3 &position, Vector3 *color);
	char m_pad04[0xC];
	Int m_mapDX;
	Int m_mapDY;
	unsigned char *m_samples;
	UnsignedInt m_sampleWidth;
	UnsignedInt m_sampleHeight;
};

// Bilinear BGR sample at a world position, scaled to 0..1; false when no grid is loaded.
Bool TerrainLogic::rva001A3D30(const Vector3 &position, Vector3 *color)
{
	if (m_samples == NULL || m_mapDX < 1 || m_mapDY < 1)
		return false;

	Real origin = sampleOrigin();
	Real x = position.X + origin;
	Real y = position.Y + origin;
	if (x < 0.0f)
		x = 0.0f;
	else if (x > m_mapDX * 10.0f)
		x = m_mapDX * 10.0f;
	if (y < 0.0f)
		y = 0.0f;
	else if (y > m_mapDY * 10.0f)
		y = m_mapDY * 10.0f;

	x = m_sampleWidth / (m_mapDX * 10.0f) * x;
	y = m_sampleHeight / (m_mapDY * 10.0f) * y;
	Int ix = fast_float2long_round(floorf(x));
	Int iy = fast_float2long_round(floorf(y));
	if (ix >= m_sampleWidth - 1)
		ix = m_sampleWidth - 2;
	if (iy >= m_sampleHeight - 1)
		iy = m_sampleHeight - 2;

	Real fx = x - ix;
	Real fy = y - iy;
	if (fx > 1.0f)
		fx = 1.0f;
	if (fy > 1.0f)
		fy = 1.0f;
	const unsigned char *top = m_samples + (m_sampleWidth * iy + ix) * 3;
	Real gx = 1.0f - fx;
	Real gy = 1.0f - fy;
	const unsigned char *bottom = top + m_sampleWidth * 3;

	color->Z = ((top[3] * fx + top[0] * gx) * gy + (bottom[3] * fx + bottom[0] * gx) * fy) * (1.0f / 255.0f);
	color->Y = ((bottom[1] * gx + bottom[4] * fx) * fy + (top[1] * gx + top[4] * fx) * gy) * (1.0f / 255.0f);
	color->X = ((bottom[2] * gx + bottom[5] * fx) * fy + (top[2] * gx + top[5] * fx) * gy) * (1.0f / 255.0f);
	return true;
}
