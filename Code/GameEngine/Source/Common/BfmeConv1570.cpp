// cl: /GX

// PartitionManager world-to-cell X converter, retail 0x008F7480, 44 bytes.
// Twin of the Y converter at 0x008F74B0: both floor a world coordinate
// relative to an origin and scaled by the cell-size reciprocal, then
// truncate with a bare fistp. Same floor-import plus __asm truncation
// idiom as the matched Gen_008812D0 helpers in Bfme5SeventySix.cpp; the
// X half reads the origin at +0x04, the Y half the origin at +0x08, and
// both share the scale at +0x20 with the converted bounds-checked cell
// lookup ?bfmeAt@Gen_008F7CD0@@QBEPAVBfmeCellFD@@HH@Z at 0x008F7CD0.

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
	int bfmeCellX(Real value) const;

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

// ?bfmeCellX@Gen_008F7CD0@@QBEHM@Z
int Gen_008F7CD0::bfmeCellX(Real value) const
{
	return bfmeFloatToLongFD(bfmeFloatFloorFD(
		(value - m_bfmeOriginX) * m_bfmeScale));
}
