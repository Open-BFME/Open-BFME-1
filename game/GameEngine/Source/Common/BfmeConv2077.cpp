class BfmeSubAJK
{
public:
	void bfmeInitJK(int a);

	unsigned char m_bfmeGapJK[12];
};

struct BfmePod16WR
{
	char m_b[16];
};

struct BfmeTagWR
{
};

BfmePod16WR *bfmeCopyWR(BfmePod16WR *first, BfmePod16WR *last,
	BfmePod16WR *result, const BfmeTagWR &, int *);

class BfmeVecWR
{
public:
	BfmePod16WR *begin() { return m_start; }
	BfmePod16WR *end() { return m_finish; }
	unsigned size() const { return (unsigned)(m_finish - m_start); }

	void resize(unsigned n, BfmePod16WR value);
	void resize(unsigned n);
	void fillInsert(BfmePod16WR *pos, unsigned n, const BfmePod16WR &value);

	BfmePod16WR *m_start;
	BfmePod16WR *m_finish;
	BfmePod16WR *m_end;
};

class BfmeBigJK
{
public:
	void bfmeClearJK();

	unsigned char m_bfmeHeadJK[8];
	int m_width;
	int m_height;
	unsigned char m_bfmeGap0JK[0x10];
	int m_dataSize;
	int m_bfme24JK;
	unsigned char m_bfmeGap1JK[0x64];
	int m_tileNdxes;
	int m_blendTileNdxes;
	int m_cliffInfoNdxes;
	int m_extraBlendTileNdxes;
	int m_bfme9cJK;
	unsigned char m_bfmeGap2JK[4];
	int m_sourceTiles[0x1000];
	int m_edgeTiles[0x1000];
	BfmeVecWR m_bfmeSubBJK;
	BfmeSubAJK m_bfmeSubAJK;
	int m_bfme80bcJK;
	unsigned char m_bfmeGap3JK[0xa008];
	int m_terrainTexHeight;
	unsigned char m_bfmeGap4JK[4];
	int m_alphaTexHeight;
	unsigned char m_bfmeGap5JK[0xc];
	int m_drawOriginX;
	int m_drawOriginY;
	int m_drawWidthX;
	int m_drawHeightY;
};

void BfmeBigJK::bfmeClearJK()
{
	m_width = 0;
	m_height = 0;
	m_dataSize = 0;
	m_bfme24JK = 0;
	m_drawOriginX = 0;
	m_drawOriginY = 0;
	m_bfme80bcJK = 0;
	m_drawWidthX = 0x81;
	m_drawHeightY = 0x81;
	m_tileNdxes = 0;
	m_blendTileNdxes = 0;
	m_extraBlendTileNdxes = 0;
	m_cliffInfoNdxes = 0;
	m_terrainTexHeight = 1;
	m_alphaTexHeight = 1;

	m_bfmeSubAJK.bfmeInitJK(1);

	m_bfme9cJK = 0;

	m_bfmeSubBJK.resize(1);

	for (int i = 0; i < 0x1000; i++)
	{
		m_sourceTiles[i] = 0;
		m_edgeTiles[i] = 0;
	}
}
