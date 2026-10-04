// cl: /DNDEBUG /MD /EHsc

typedef unsigned int UnsignedInt;
typedef float Real;

class BfmeCell
{
public:
	void bfmeDecay(Real scale, Real subtract);

private:
	unsigned char m_data[0x88];
};

class BfmeCellGrid
{
public:
	~BfmeCellGrid();
	void _bfme_reset();
	void bfmeDecayCells(Real scale, Real subtract);

private:
	unsigned char m_unreconstructed_000[0x08];
	UnsignedInt m_cellCount;
	unsigned char m_unreconstructed_00C[0x14 - 0x0C];
	BfmeCell *m_cells;
};

BfmeCellGrid::~BfmeCellGrid()
{
	_bfme_reset();
}

void BfmeCellGrid::bfmeDecayCells(Real scale, Real subtract)
{
	for (UnsignedInt index = 0; index < m_cellCount; ++index)
		m_cells[index].bfmeDecay(scale, subtract);
}
