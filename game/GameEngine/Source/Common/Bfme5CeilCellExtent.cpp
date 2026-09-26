// cl: /GX
// Convert a scaled positive extent to its enclosing cell count.
typedef float Real;

extern "C" __declspec(dllimport) double __cdecl ceil(double value);

__forceinline long bfmeCeilFloatToLong(Real value)
{
	long result;
	__asm
	{
		fld [value]
		fistp [result]
	}
	return result;
}

class Gen_008F7CD0
{
public:
	int bfmeCellExtent8F74E0(Real value) const;

private:
	char m_reserved[0x20];
	Real m_bfmeScale;
};

int Gen_008F7CD0::bfmeCellExtent8F74E0(Real value) const
{
	return bfmeCeilFloatToLong((Real)ceil((double)(value * m_bfmeScale)));
}
