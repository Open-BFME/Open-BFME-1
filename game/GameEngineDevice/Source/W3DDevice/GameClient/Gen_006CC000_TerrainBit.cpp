// cl: /DNDEBUG /MD /EHsc
// Retail 0x006CC000: the second terrain coordinate/bit-plane query wrapper.
// Its ILT calls the matched 0x006CB500 bit-plane body.

typedef bool Bool;

extern void j_0003cc04(void);

class Gen006CB500BitPlane
{
public:
	Bool test(int x, int y) const;

	unsigned char m_pad00[0x08];
	int m_width;
	int m_height;
	int m_origin;
};

#define BFME_AT(type, address) (*reinterpret_cast<type *>(address))

class Gen_006CC000Terrain
{
public:
	Bool query(float first, float second);

private:
	unsigned char m_pad00[0x2ff4];
	Gen006CB500BitPlane *m_map;
};

Bool Gen_006CC000Terrain::query(float first, float second)
{
	if (m_map == 0)
		return false;

	int x = m_map->m_origin - (int)(first * BFME_AT(float, 0x010C2E78));
	int y = m_map->m_origin - (int)(second * BFME_AT(float, 0x010C2E78));
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x >= m_map->m_width - 1)
		x = m_map->m_width - 2;
	if (y >= m_map->m_height - 1)
		y = m_map->m_height - 2;

	typedef Bool (Gen006CB500BitPlane::*MemberThunk)(int, int) const;
	union
	{
		void (*function)(void);
		MemberThunk member;
	} thunk;
	thunk.function = j_0003cc04;
	return (m_map->*thunk.member)(x, y);
}
