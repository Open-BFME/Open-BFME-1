// cl: /DNDEBUG /MD /EHsc
// Retail 0x006C6E20: convert two terrain coordinates and query the map plane.

typedef bool Bool;

extern void j_000480d1(void);

#define BFME_AT(type, address) (*reinterpret_cast<type *>(address))

class Gen006C6E20Map
{
public:
	unsigned char m_pad00[0x08];
	int m_width;
	int m_height;
	int m_border;

	private:
	unsigned char m_pad14[0x20];
};

class Gen006C6E20Terrain
{
public:
	Bool query(float first, float second);

private:
	unsigned char m_pad00[0x2ff4];
	Gen006C6E20Map *m_map;
};

Bool Gen006C6E20Terrain::query(float first, float second)
{
	if (m_map == 0)
		return false;

	int firstCoordinate = m_map->m_border -
		(int)(first * BFME_AT(float, 0x010C2E78));
	int secondCoordinate = m_map->m_border -
		(int)(second * BFME_AT(float, 0x010C2E78));
	if (firstCoordinate < 0)
		firstCoordinate = 0;
	if (secondCoordinate < 0)
		secondCoordinate = 0;

	int widthLimit = m_map->m_width - 1;
	if (firstCoordinate >= widthLimit)
	 	firstCoordinate = m_map->m_width - 2;
	int heightLimit = m_map->m_height - 1;
	if (secondCoordinate >= heightLimit)
		secondCoordinate = m_map->m_height - 2;

	typedef Bool (Gen006C6E20Map::*MemberThunk)(int, int) const;
	union
	{
		void (*function)(void);
		MemberThunk member;
	} thunk;
	thunk.function = j_000480d1;
	return (m_map->*thunk.member)(firstCoordinate, secondCoordinate);
}
