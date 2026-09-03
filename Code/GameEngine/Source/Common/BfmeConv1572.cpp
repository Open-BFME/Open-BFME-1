// cl: /GX

// PartitionManager world-to-cell Y converter, retail 0x008F74B0, 44 bytes.
// Twin of the X converter ?bfmeCellX@Gen_008F7CD0@@QBEHM@Z at 0x008F7480
// landed in BfmeConv1570.cpp: identical shape, reading the Y origin at
// +0x08 instead of the X origin at +0x04, sharing the scale at +0x20.

typedef float Real;

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
	int m_bfmeData[26];					// 104 bytes
};

class Gen_008F7CD0
{
public:
	int bfmeCellY(Real value) const;

private:
	char m_bfmeHead[4];					// +0x00
	Real m_bfmeOriginX;					// +0x04
	Real m_bfmeOriginY;					// +0x08
	char m_bfmeMid[20];					// +0x0C
	Real m_bfmeScale;					// +0x20
	int m_bfmeWidth;					// +0x24
	int m_bfmeHeight;					// +0x28
	BfmeCellFD *m_bfmeCells;				// +0x2C
};

// ?bfmeCellY@Gen_008F7CD0@@QBEHM@Z
int Gen_008F7CD0::bfmeCellY(Real value) const
{
	return bfmeFloatToLongFD(bfmeFloatFloorFD(
		(value - m_bfmeOriginY) * m_bfmeScale));
}
