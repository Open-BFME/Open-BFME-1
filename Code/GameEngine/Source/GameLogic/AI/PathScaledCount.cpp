typedef float Real;

extern volatile const Real TheBfmeCountScaleA;
extern volatile const Real TheBfmeCountScaleB;

extern "C" __declspec(dllimport) double __cdecl BfmeScaledCountImport(double value);

int __stdcall bfmeScaledCount(Real first, Real second)
{
	double product = second;
	product *= TheBfmeCountScaleA;
	product *= first;
	product *= TheBfmeCountScaleB;
	second = (Real)BfmeScaledCountImport(product);

	// MSVC otherwise keeps this float-to-int conversion in SSE. The retail
	// function uses the two-instruction x87 conversion sequence.
	__asm
	{
		fld second
		fistp first
	}

	int count = *(int *)&first;
	if (count < 1)
		return 1;
	if (count > 0x80)
		return 0x80;
	return count;
}
