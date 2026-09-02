// _DeblockLoopFilteredBand_WMT
// partial score=0.12 date=2026-09-02
// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /arch:SSE2
// Semantic reconstruction of the VP6 postprocessor's SSE2 band filter at
// 0x009BFA40.  The retail routine performs the same operation eight pixels at
// a time with aligned word vectors; this scalar form keeps the recovered ABI,
// state layout, two passes, and variance accounting explicit for the next
// shaping pass.

typedef unsigned char UINT8;
typedef unsigned int UINT32;

struct POSTPROC_INSTANCE_9BFA40
{
	char unknown00[0x0c];
	UINT8 *FragQIndex;                 // +0x0c
	char unknown10[0x14];
	UINT32 *FragmentVariances;         // +0x24
};

static __forceinline int bfmeAbs9BFA40(int value)
{
	return value < 0 ? -value : value;
}

static __forceinline UINT8 bfmeClamp9BFA40(int value)
{
	if (value < 0)
		return 0;
	if (value > 255)
		return 255;
	return (UINT8)value;
}

// Filter one eight-sample line straddling a block boundary.  The two four
// sample variances and the centre discontinuity jointly gate the update.
static __forceinline UINT32 bfmeFilterLine9BFA40(const UINT8 *source, int step,
	UINT8 *destination, int destinationStep, UINT32 qStep)
{
	int sample[10];
	int i;
	int sum1 = 0;
	int sum2 = 0;
	int square1 = 0;
	int square2 = 0;

	for (i = 0; i < 10; ++i)
		sample[i] = source[(i - 5) * step];

	for (i = 1; i <= 4; ++i) {
		int value = sample[i] - 128;
		sum1 += value;
		square1 += value * value;
	}
	for (i = 5; i <= 8; ++i) {
		int value = sample[i] - 128;
		sum2 += value;
		square2 += value * value;
	}

	UINT32 variance1 = (UINT32)(square1 - (sum1 >> 1) * ((sum1 + 1) >> 1));
	UINT32 variance2 = (UINT32)(square2 - (sum2 >> 1) * ((sum2 + 1) >> 1));
	UINT32 limit = (3 * qStep * qStep) >> 5;
	bool filter = variance1 < limit && variance2 < limit
		&& bfmeAbs9BFA40(sample[4] - sample[5]) < (int)qStep;

	if (!filter) {
		for (i = 1; i <= 8; ++i)
			destination[(i - 5) * destinationStep] = (UINT8)sample[i];
		return variance1 + variance2;
	}

	int left = bfmeAbs9BFA40(sample[0] - sample[1]) < (int)qStep ? sample[0] : sample[1];
	int right = bfmeAbs9BFA40(sample[8] - sample[9]) < (int)qStep ? sample[9] : sample[8];
	int window = left * 3 + sample[1] + sample[2] + sample[3] + sample[4] + 4;

	for (i = 1; i <= 8; ++i) {
		int previous = i == 1 ? left : sample[i - 1];
		int next = i == 8 ? right : sample[i + 1];
		int value = ((window + sample[i]) * 2 + previous - next) >> 4;
		destination[(i - 5) * destinationStep] = bfmeClamp9BFA40(value);
		window -= i < 4 ? left : sample[i - 3];
		window += i < 4 ? sample[i + 4] : right;
	}

	return variance1 + variance2;
}

extern "C" void __cdecl DeblockLoopFilteredBand_WMT(
	POSTPROC_INSTANCE_9BFA40 *pbi, UINT8 *source, UINT8 *destination,
	UINT32 pitch, UINT32 fragmentsAcross, UINT32 startFragment,
	UINT32 *quantScale)
{
	UINT32 fragment = startFragment;
	UINT32 end = startFragment + fragmentsAcross;

	while (fragment < end) {
		UINT32 qStep = quantScale[pbi->FragQIndex[fragment + fragmentsAcross]];
		if (qStep > 3) {
			UINT32 horizontalVariance = 0;
			UINT32 verticalVariance = 0;
			int i;

			for (i = 0; i < 8; ++i)
				horizontalVariance += bfmeFilterLine9BFA40(
					source + i, (int)pitch, destination + i, (int)pitch, qStep);

			for (i = -4; i < 4; ++i)
				verticalVariance += bfmeFilterLine9BFA40(
					source + i * (int)pitch, 1,
					destination + i * (int)pitch, 1, qStep);

			pbi->FragmentVariances[fragment] += horizontalVariance;
			pbi->FragmentVariances[fragment + fragmentsAcross] += horizontalVariance;
			pbi->FragmentVariances[fragment] += verticalVariance;
			pbi->FragmentVariances[fragment + 1] += verticalVariance;
		} else {
			int row;
			for (row = -4; row < 4; ++row) {
				int column;
				for (column = 0; column < 8; ++column)
					destination[row * (int)pitch + column] = source[row * (int)pitch + column];
			}
		}

		++fragment;
		source += 8;
		destination += 8;
	}
}
