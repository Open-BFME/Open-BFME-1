// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ??0W3DShroud@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShroud.cpp
//
// Retail 0x0071B590. BFME W3DShroud constructor: 10.0f cell size, filter 4,
// border alpha from TheWritableGlobalData+0xC86, dirty-cell tree at +0x44.

#include <set>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
	unsigned char m_pad[0xc86];

public:
	unsigned char m_shroudAlpha;
};

extern GlobalData *TheWritableGlobalData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureBaseClass
{
public:
	void Release_Ref();
};

class TexHandle
{
public:
	TexHandle() : m_p(0) {}
	~TexHandle()
	{
		if (m_p)
			m_p->Release_Ref();
	}
	TextureBaseClass *m_p;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DShroud.h
class W3DShroud
{
public:
	W3DShroud();

private:
	int m_numCellsX;
	int m_numCellsY;
	int m_numMaxVisibleCellsX;
	int m_numMaxVisibleCellsY;
	float m_cellWidth;
	float m_cellHeight;
	void *m_shroudData;
	TexHandle m_dstTexture;
	void *m_20;
	void *m_24;
	int m_shroudFilter;
	int m_2c;
	int m_30;
	unsigned char m_34;
	unsigned char m_clearDstTexture;
	unsigned char m_borderShroudLevel;
	unsigned char m_pad37;
	void *m_38;
	void *m_3c;
	unsigned char m_40;
	unsigned char m_pad41[3];
	_STL::set<int> m_dirty;
};

W3DShroud::W3DShroud()
	: m_numCellsX(0)
	, m_numCellsY(0)
	, m_numMaxVisibleCellsX(0)
	, m_numMaxVisibleCellsY(0)
	, m_cellWidth(10.0f)
	, m_cellHeight(10.0f)
	, m_shroudData(0)
	, m_20(0)
	, m_24(0)
	, m_shroudFilter(4)
	, m_2c(0)
	, m_30(0)
	, m_34(0)
	, m_clearDstTexture(1)
	, m_borderShroudLevel(TheWritableGlobalData->m_shroudAlpha)
	, m_38(0)
	, m_3c(0)
	, m_40(1)
{
}
