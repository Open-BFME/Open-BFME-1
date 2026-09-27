// ?rva006D2480@Rva006D2480Owner@@QAEXHPAVRenderInfoClass@@_NPAH222@Z
// partial score=0.988 date=2026-09-27
// candidate for 0x006D2480 (249 B: ret 0x1c + 246): tile-state scan with
// conditional render. Owner layout witnessed by TerrainTiles006D2730
// (+0x2ff4 map, +0x30d8 tiles, +0x30e0 W, +0x30e4 H) and Rva006D2460
// (+0x3178 state); the +0x30dc limit, +0x30f8 flag, +0x30fc count and
// +0x3100 height slots are read here.
class RenderInfoClass;
typedef bool Bool;
class Rva006D2480Tile
{
public:
	void rva0072DC30(RenderInfoClass &, int, Bool);
	int m_state;
	char m_pad[0x50];
	float m_54;
	char m_tail[0xc4 - 0x58];
};
class Rva006D2480Owner
{
public:
	void rva006D2480(int unused, RenderInfoClass *info, Bool flag, int *maxX, int *maxA, int *maxY, int *maxB);
private:
	char m_pad[0x30d8];
	Rva006D2480Tile *m_tiles;
	int m_limit;
	int m_width;
	int m_height;
	char m_pad2[0x30f8 - 0x30e8];
	unsigned char m_flag;
	char m_pad3[3];
	int m_count;
	float m_heightF;
};
inline int Rva006D2480InfoKey(RenderInfoClass *info)
{
	return (int)info;
}
void Rva006D2480Owner::rva006D2480(int unused, RenderInfoClass *info, Bool flag, int *maxX, int *maxA, int *maxY, int *maxB)
{
	int x = 0;
	int xOff = 0;
	(void)unused;
	if (m_width <= 0)
		return;
	for (; x < m_width; ++x, xOff += 0x10)
	{
		int y = 0;
		if (y >= m_height)
			continue;
		int yOff = 0;
		do
		{
			Rva006D2480Tile *tile = m_tiles + y * m_width + x;
			if (tile->m_state != 2)
			{
				if (m_flag == 0 || m_count >= m_limit || !(m_heightF < tile->m_54))
				{
					tile->rva0072DC30(*info, Rva006D2480InfoKey(info), flag);
					if (xOff < *maxX)
						*maxX = xOff;
					if (yOff < *maxY)
						*maxY = yOff;
					if (xOff + 0x10 > *maxA)
						*maxA = xOff + 0x10;
					if (yOff + 0x10 > *maxB)
						*maxB = yOff + 0x10;
				}
			}
			++y;
			yOff += 0x10;
		} while (y < m_height);
	}
}
