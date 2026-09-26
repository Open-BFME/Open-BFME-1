// cl: /DNDEBUG /MD /EHsc
// stlport

#include <vector>

// The receiver has the BFME height-map field offsets, but its exporting
// class/method is not proved by a named caller. Keep the owner address-derived.
// This view starts the STLport vector at its three pointer control words at
// +0x80B0; the preceding allocator word at +0x80AC is untouched here.

struct Rva0074BD10CliffInfo
{
	float m_uv[8];
	bool m_flip;
	bool m_mutant;
	short m_tileIndex;
};

struct Rva0074BD10TextureClass
{
	int m_globalTextureClass;
	int m_firstTile;
	int m_numTiles;
	char m_other[28];
};

class Rva0074BD10Owner
{
public:
	bool rva0074BD10(int x, int y);

private:
	char m_pad000[8];
	int m_width;
	char m_pad00C[0x20 - 0x0C];
	int m_dataSize;
	char m_pad024[0x8C - 0x24];
	short *m_tileIndices;
	char m_pad090[4];
	int *m_cliffIndices;
	char m_pad098[0x80B0 - 0x98];
	std::vector<Rva0074BD10CliffInfo> m_cliffInfo;
	int m_numTextureClasses;
	Rva0074BD10TextureClass m_textureClasses[0x200];
	char m_padD0C0[0x120E0 - 0xD0C0];
	int m_drawOriginX;
	int m_drawOriginY;
};

bool Rva0074BD10Owner::rva0074BD10(int x, int y)
{
	Rva0074BD10CliffInfo info;
	bool sameClass = false;
	int index = (m_drawOriginY + y) * m_width + m_drawOriginX + x;
	if (index >= 0 && index < m_dataSize)
	{
		info = m_cliffInfo[m_cliffIndices[index]];
		int tileA = m_tileIndices[index] >> 2;
		int tileB = info.m_tileIndex >> 2;
		for (int i = 0; i < m_numTextureClasses; ++i)
		{
			if (tileA >= m_textureClasses[i].m_firstTile &&
				tileA < m_textureClasses[i].m_firstTile + m_textureClasses[i].m_numTiles)
			{
				sameClass = tileB >= m_textureClasses[i].m_firstTile &&
					tileB < m_textureClasses[i].m_firstTile + m_textureClasses[i].m_numTiles;
				break;
			}
		}
	}
	return !sameClass;
}
