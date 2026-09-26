void bfmeUnpackTwoColors1280(float *output, const unsigned int *colors);

class BfmeSubmitter1283
{
public:
	void bfmeSubmit1283(int a1, int a2, int a3, int a4, int a5, int a6, int a7,
		float *colors, int a9, int a10, int a11, int zero);
	void bfmeSubmitColors1283(int a1, int a2, int a3, int a4, int a5, int a6, int a7,
		const unsigned int *colors, int a9, int a10, int a11);
};

void BfmeSubmitter1283::bfmeSubmitColors1283(int a1, int a2, int a3, int a4, int a5,
	int a6, int a7, const unsigned int *colors, int a9, int a10, int a11)
{
	float unpacked[8];
	if (colors != 0) {
		bfmeUnpackTwoColors1280(unpacked, colors);
		bfmeSubmit1283(a1, a2, a3, a4, a5, a6, a7, unpacked, a9, a10, a11, 0);
	} else {
		bfmeSubmit1283(a1, a2, a3, a4, a5, a6, a7, 0, a9, a10, a11, 0);
	}
}
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
