struct BfmeCoord6DF1F0
{
	float x;
	float y;
	float z;
};

class BfmePolygon6DF1F0
{
public:
	char bfmeContains6DF1F0(const BfmeCoord6DF1F0 &point) const;
};

struct BfmePlayer6DF1F0
{
	char m_padding00[0x24];
	int m_index24;
};

struct BfmePlayerList6DF1F0
{
	char m_padding00[0x0c];
	BfmePlayer6DF1F0 *m_localPlayer0c;
};

class BfmeShroud6DF1F0
{
public:
	int bfmeStatus6DF1F0(int playerIndex, const BfmeCoord6DF1F0 *point) const;
};

extern BfmePlayerList6DF1F0 *g_bfmePlayerList6DF1F0;
extern BfmeShroud6DF1F0 *g_bfmeShroud6DF1F0;

class Rva006DF1F0
{
public:
	bool allowsLocation(const BfmeCoord6DF1F0 *point) const;

private:
	char m_padding00[0x1c];
	BfmePolygon6DF1F0 *m_polygon1c;
};

bool Rva006DF1F0::allowsLocation(const BfmeCoord6DF1F0 *point) const
{
	if (m_polygon1c == 0)
		return true;

	int playerIndex = g_bfmePlayerList6DF1F0->m_localPlayer0c->m_index24;
	if (g_bfmeShroud6DF1F0->bfmeStatus6DF1F0(playerIndex, point) == 2)
		return false;

	if (m_polygon1c->bfmeContains6DF1F0(*point))
		return true;
	return false;
}
