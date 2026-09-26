// cl: /DNDEBUG /MD /EHsc
// Retail 0x006C6F60: convert a pair of terrain coordinates and query the
// height-map bit plane.  The bit-plane owner is the matched 0x0074BB30 body.

typedef bool Bool;

class Gen_0074BB30
{
public:
	Bool bfmeBitA(int x, int y) const;

public:
	unsigned char m_pad00[0x08];
	int m_width;
	int m_height;
	int m_origin;
};

#define BFME_AT(type, address) (*reinterpret_cast<type *>(address))

class Gen_006C6F60Terrain
{
public:
	Bool query(float first, float second);

private:
	unsigned char m_pad00[0x2ff4];
	Gen_0074BB30 *m_map;
};

Bool Gen_006C6F60Terrain::query(float first, float second)
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
	return m_map->bfmeBitA(x, y);
}
