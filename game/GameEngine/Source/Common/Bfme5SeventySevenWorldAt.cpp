// cl: /GX
// Open-BFME: world-coordinate cell lookup for the partition cell table.

typedef float Real;
typedef int Int;

extern "C" __declspec(dllimport) double __cdecl floor(double value);

__forceinline Real bfmeFloatFloorFD(Real value)
{
	return (Real)floor((double)value);
}

__forceinline long bfmeFloatToLongFD(Real value)
{
	long result;
	__asm
	{
		fld [value]
		fistp [result]
	}
	return result;
}

class BfmeCellFD
{
public:
	int m_bfmeData[26];
};

class Gen_008F7CD0
{
public:
	BfmeCellFD *bfmeAt(Real x, Real y) const;

private:
	char m_bfmeHead[4];
	Real m_bfmeOriginX;
	Real m_bfmeOriginY;
	char m_bfmeMid[20];
	Real m_bfmeScale;
	Int m_bfmeWidth;
	Int m_bfmeHeight;
	BfmeCellFD *m_bfmeCells;
};

BfmeCellFD *Gen_008F7CD0::bfmeAt(Real x, Real y) const
{
	Int cellX = bfmeFloatToLongFD(bfmeFloatFloorFD(
		(x - m_bfmeOriginX) * m_bfmeScale));
	if (cellX < 0 || cellX >= m_bfmeWidth)
		return 0;

	Int cellY = bfmeFloatToLongFD(bfmeFloatFloorFD(
		(y - m_bfmeOriginY) * m_bfmeScale));
	if (cellY < 0 || cellY >= m_bfmeHeight)
		return 0;

	return &m_bfmeCells[m_bfmeWidth * cellY + cellX];
}
