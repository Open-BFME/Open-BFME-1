// ?bfmeSetGI@BfmeSecondGI@@QAEXI@Z (identity unknown)
// partial score=0.97 date=2026-09-06
// 63/63 exact size; retail reloads the stored float BEFORE cleaning the argument
// stack, MSVC cleans first and reloads at the adjusted offset.
// Pins: __imp__bfmeMathGI 0x00F59394, ?g_bfmeScaleGI@@3MB 0x00D23690 (200.0f),
//       ?bfmeApplyGI@BfmePrimaryGI@@QAEXM@Z 0x0003F215
typedef float Real;

extern "C" __declspec(dllimport) double __cdecl bfmeMathGI(double value);

extern const Real g_bfmeScaleGI;

class BfmePrimaryGI
{
public:
	void bfmeApplyGI(Real value);
};

class BfmeSecondGI
{
public:
	void bfmeSetGI(unsigned int amount);
};

void BfmeSecondGI::bfmeSetGI(unsigned int amount)
{
	Real result = (Real)bfmeMathGI((Real)amount * g_bfmeScaleGI);

	((BfmePrimaryGI *)((char *)this - 0xc))->bfmeApplyGI(result);
}
