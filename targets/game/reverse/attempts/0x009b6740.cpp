// ?Rva009B6740BuildTable@@YAXPAE@Z
// partial score=0.0895 date=2026-10-09
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva009B6740Work
{
	unsigned char *ratio;
	unsigned int row;
	int offset;
	int repeat;
	unsigned char *historyBase;
	unsigned char *outputBase;
	unsigned int first;
	unsigned int pair;
	unsigned int right;
	unsigned int tail;
	unsigned int weights[10];
};

// ?Rva009B6740BuildTable@@YAXPAE@Z
void Rva009B6740BuildTable(unsigned char *ctx)
{
	unsigned int sum;
	int i;
	unsigned char *ratio;
	unsigned int row;
	int offset;
	int repeat;
	unsigned char *historyBase;
	unsigned char *outputBase;
	unsigned int first;
	unsigned int pair;
	unsigned int right;
	unsigned int tail;
	unsigned int weights[10];
	row = 0;
	offset = -10;
	historyBase = ctx + 0x736;
	outputBase = ctx + 0x7A5;

	do {
	{
		unsigned char *history = historyBase;
		unsigned char *output = outputBase;
		ratio = history + 0x46;
		repeat = 3;

		do {
			sum = 0;
			int ratioDenominator;
			unsigned int rowDivisor;
			unsigned int left;
			i = 0;

			do {
				if (row == (unsigned int)i)
					weights[i] = 0;
				else
					weights[i] = history[offset + i] * 100;
				sum += weights[i];
				++i;
			} while (i < 10);

			ratioDenominator = history[0] + history[-10] + 1;
			ratio[0] = (unsigned char)(255 - history[0] * 255 / ratioDenominator);

			rowDivisor = weights[4] + weights[3];
			first = rowDivisor + weights[2] + weights[0];
			output[-1] = (unsigned char)(1 + first * 255 / (sum + 1));

			pair = weights[2] + weights[0];
			output[0] = (unsigned char)(1 + pair * 255 / (first + 1));

			tail = weights[8] + weights[9];
			right = tail + weights[6] + weights[5];
			first = weights[7] + weights[1];
			output[1] = (unsigned char)(1 + first * 255 / (right + first + 1));

			output[2] = (unsigned char)(1 + weights[0] * 255 / (pair + 1));

			++rowDivisor;
			output[3] = (unsigned char)(1 + weights[3] * 255 / rowDivisor);
			output[4] = (unsigned char)(1 + weights[1] * 255 / (first + 1));

			left = weights[6] + weights[5];
			history += 0x14;
			output += 0x5A;
			output[-0x55] = (unsigned char)(1 + left * 255 / (right + 1));
			output[-0x54] = (unsigned char)(1 + weights[5] * 255 / (left + 1));
			output[-0x53] = (unsigned char)(1 + weights[8] * 255 / (tail + 1));

			ratio += 10;
			--repeat;
		} while (repeat);
	}

		++historyBase;
		outputBase += 9;
		++row;
		--offset;
	} while (offset > -20);
}
