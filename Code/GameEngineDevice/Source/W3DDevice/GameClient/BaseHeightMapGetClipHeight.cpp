// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME retail 0x006C5B40: BaseHeightMapRenderObjClass::getClipHeight.
// The BFME height samples are 16-bit and m_data is at WorldHeightMap +0x24.

typedef unsigned short UnsignedShort;

class WorldHeightMap
{
public:
	char m_padding00[8];
	int m_width;
	int m_height;
	char m_padding10[0x14];
	unsigned short *m_data;

};

class BaseHeightMapRenderObjClass
{
public:
	UnsignedShort getClipHeight(int x, int y) const;

private:
	char m_padding00[0x2ff4];
	WorldHeightMap *m_map;
};

UnsignedShort BaseHeightMapRenderObjClass::getClipHeight(int x, int y) const
{
	WorldHeightMap *map = m_map;
	int xextent = map->m_width;
	int yextent = map->m_height;

	if (x < 0)
		x = 0;
	else if (x >= xextent)
		x = xextent - 1;

	if (y < 0)
		y = 0;
	else if (y >= yextent)
		y = yextent - 1;

	return map->m_data[x + y * xextent];
}
