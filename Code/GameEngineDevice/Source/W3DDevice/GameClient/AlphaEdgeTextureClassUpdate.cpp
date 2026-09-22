// Retail 0x006D60D0, AlphaEdgeTextureClass::update.
// BFME COM and terrain layouts are local to this translation unit.

struct BfmeLockedRect
{
	int Pitch;
	void *pBits;
};

struct BfmeSurfaceDesc
{
	unsigned Format;
	unsigned Type;
	unsigned Usage;
	unsigned Pool;
	unsigned Size;
	unsigned reserved;
	unsigned Width;
	unsigned Height;
};

class SurfaceResource
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void __stdcall Release(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2c(void);
	virtual int __stdcall GetDesc(BfmeSurfaceDesc *desc);
	virtual int __stdcall LockRect(BfmeLockedRect *locked, const void *rect, unsigned flags);
	virtual int __stdcall UnlockRect(void);
};

class BfmeD3DTexture
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2c(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual void slot38(void);
	virtual void slot3c(void);
	virtual void slot40(void);
	virtual void slot44(void);
	virtual int __stdcall GetSurfaceLevel(unsigned level, SurfaceResource **surface);
};

class BfmeMsgIBD
{
public:
	virtual BfmeMsgIBD *slot00(const void *value);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2c(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual BfmeMsgIBD *slot38(const void *value);
	virtual void slot3c(void);
	virtual void slot40(void);
	virtual void slot44(void);
	virtual void slot48(void);
	virtual void slot4c(int value);
};

class BfmeLogIBD
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2c(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual void slot38(void);
	virtual void slot3c(void);
	virtual void slot40(void);
	virtual void slot44(void);
	virtual void slot48(void);
	virtual void slot4c(void);
	virtual void slot50(void);
	virtual void slot54(void);
	virtual void slot58(void);
	virtual void slot5c(void);
	virtual void slot60(void);
	virtual void slot64(void);
	virtual void slot68(void);
	virtual BfmeMsgIBD *slot6c(int first, int second);
};

extern BfmeLogIBD *g_BFMEIndexBufferDebug;
extern void _bfme_debugRecordCallsite(int kind);

static __forceinline void BFME_DX8_ErrorCode(int result)
{
	if (result != 0)
	{
		_bfme_debugRecordCallsite(1);
		g_BFMEIndexBufferDebug->slot60();
		g_BFMEIndexBufferDebug->slot6c(0, 0)->slot38((const void *)0x111d770)
			->slot00((const void *)result)->slot4c(1);
	}
}

struct IDirect3DBaseTexture8;

class TextureBaseClass
{
public:
	IDirect3DBaseTexture8 *Peek_D3D_Base_Texture(void) const;
};

class TextureClass : public TextureBaseClass
{
};

class BfmeRefCountClass
{
public:
	virtual void Delete_This(void);
	int m_numRefs;
};

struct BfmeCoord2D
{
	int x;
	int y;
};

class TileData : public BfmeRefCountClass
{
protected:
	unsigned char m_tileData[0x4000];
	unsigned char m_tileDataMip32[0x1000];
	unsigned char m_tileDataMip16[0x400];
	unsigned char m_tileDataMip8[0x100];
	unsigned char m_tileDataMip4[0x40];
	unsigned char m_tileDataMip2[0x10];
	unsigned char m_tileDataMip1[4];

public:
	BfmeCoord2D m_tileLocationInTexture;

	unsigned char *getRGBDataForWidth(int width)
	{
		if (width == 32) return m_tileDataMip32;
		if (width == 16) return m_tileDataMip16;
		if (width == 8) return m_tileDataMip8;
		if (width == 4) return m_tileDataMip4;
		if (width == 2) return m_tileDataMip2;
		if (width == 1) return m_tileDataMip1;
		return m_tileData;
	}
};

class WorldHeightMap
{
private:
	unsigned char m_pad00[0xa0];

public:
	int m_numEdgeTiles;
	TileData *m_sourceTiles[0x1000];
	TileData *m_edgeTiles[0x1000];

	TileData *getEdgeTile(unsigned ndx)
	{
		if (ndx < 0x1000) return m_edgeTiles[ndx];
		return 0;
	}
};

class AlphaEdgeTextureClass : public TextureClass
{
public:
	int update(WorldHeightMap *htMap);
};

extern "C" int __stdcall D3DXFilterTexture(
	void *texture, const void *palette, unsigned level, unsigned filter);

// ?update@AlphaEdgeTextureClass@@QAEHPAVWorldHeightMap@@@Z
int AlphaEdgeTextureClass::update(WorldHeightMap *htMap)
{
	SurfaceResource *surface_level;
	BfmeLockedRect locked_rect;
	BfmeSurfaceDesc surface_desc;
	BFME_DX8_ErrorCode(reinterpret_cast<BfmeD3DTexture *>(
		Peek_D3D_Base_Texture())->GetSurfaceLevel(0, &surface_level));
	BFME_DX8_ErrorCode(surface_level->LockRect(&locked_rect, 0, 0));
	BFME_DX8_ErrorCode(surface_level->GetDesc(&surface_desc));

	int tilePixelExtent = 64;
	if (surface_desc.Format == 0x15)
	{
		int cellX, cellY;
		for (cellX = 0; (unsigned)cellX < surface_desc.Width; cellX++)
		{
			for (cellY = 0; cellY < surface_desc.Height; cellY++)
			{
				unsigned char *pBGR = ((unsigned char *)locked_rect.pBits) +
					(cellY * surface_desc.Width + cellX) * 4;
				pBGR[2] = 255 - cellY / 2;
				pBGR[0] = cellX / 2;
				pBGR[3] = cellX / 2;
				pBGR[3] = 128;
			}
		}

		int tileNdx;
		int pixelBytes = 4;
		for (tileNdx = 0; tileNdx < htMap->m_numEdgeTiles; tileNdx++)
		{
			TileData *pTile = htMap->getEdgeTile(tileNdx);
			if (!pTile) continue;
			BfmeCoord2D position = pTile->m_tileLocationInTexture;
			if (position.x <= 0) continue;
			int i, j;
			int column = position.x;
			for (j = 0; j < tilePixelExtent; j++)
			{
				int row = position.y + j;
				unsigned char *pBGR = htMap->getEdgeTile(tileNdx)->getRGBDataForWidth(tilePixelExtent);
				pBGR += (tilePixelExtent - 1 - j) * 4 * tilePixelExtent;
				unsigned char *pBGRX = ((unsigned char *)locked_rect.pBits) +
					row * surface_desc.Width * pixelBytes;
				pBGRX += column * pixelBytes;

				for (i = 0; i < tilePixelExtent; i++)
				{
					pBGRX[0] = pBGR[0];
					pBGRX[1] = pBGR[1];
					pBGRX[2] = pBGR[2];
					if (pBGR[0] == 0 && pBGR[1] == 0 && pBGR[2] == 0)
						pBGRX[3] = 0x80;
					else if (pBGR[0] == 0xff && pBGR[1] == 0xff && pBGR[2] == 0xff)
						pBGRX[3] = 0x00;
					else
						pBGRX[3] = 0xff;
					pBGRX += pixelBytes;
					pBGR += 4;
				}
			}
		}
	}
	surface_level->UnlockRect();
	surface_level->Release();
	BFME_DX8_ErrorCode(D3DXFilterTexture(Peek_D3D_Base_Texture(), 0, 0, 5));
	return surface_desc.Height;
}
