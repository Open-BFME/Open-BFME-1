// cl: /O2 /Ob0 /G6

struct BfmeTailF0
{
	char *m_p;
	void copyFrom(const BfmeTailF0 *src);
};

struct BfmeShapeF0
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	BfmeTailF0 m_1C;
	char m_20;
	char m_pad[3];
};

struct BfmePosF0
{
	int m_x;
	int m_y;
	int m_z;
};

class BfmeObjF0
{
public:
	BfmeObjF0 *set(const BfmePosF0 *pos, const BfmeShapeF0 *src, int extra);

	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	BfmeTailF0 m_1C;
	char m_20;
	char m_pad[3];
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
};

BfmeObjF0 *BfmeObjF0::set(const BfmePosF0 *pos, const BfmeShapeF0 *src, int extra)
{
	const BfmeShapeF0 *v = src;
	m_00 = v->m_00;
	m_04 = v->m_04;
	m_08 = v->m_08;
	m_0C = v->m_0C;
	m_10 = v->m_10;
	m_14 = v->m_14;
	m_18 = v->m_18;
	m_1C.copyFrom(&v->m_1C);
	m_20 = v->m_20;
	m_24 = pos->m_x;
	m_28 = pos->m_y;
	m_2C = pos->m_z;
	m_30 = extra;
	return this;
}
