// ?Rva009B6740BuildTable@@YAXPAE@Z
// partial score=0.45 date=2026-09-10
// ?Rva009B6740BuildTable@@YAXPAE@Z
// VP6 probability-table builder called by the verified decoder setup at 0x009B6A30.
// Retail boundary: [0x009B6740, 0x009B6942).
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

void Rva009B6740BuildTable(unsigned char *ctx)
{
	unsigned int sum;
	int i;
	Rva009B6740Work work;
	work.row = 0;
	work.offset = -10;
	work.historyBase = ctx + 0x736;
	work.outputBase = ctx + 0x7A5;

	do {
	{
		unsigned char *history = work.historyBase;
		unsigned char *output = work.outputBase;
		work.ratio = history + 0x46;
		work.repeat = 3;

		do {
			sum = 0;
			int ratioDenominator;
			unsigned int rowDivisor;
			unsigned int left;
			i = 0;

			do {
				work.weights[i] = work.row == (unsigned int)i ? 0 : history[work.offset + i] * 100;
				sum += work.weights[i];
				++i;
			} while (i < 10);

			ratioDenominator = history[0] + history[work.offset] + 1;
			work.ratio[0] = (unsigned char)(255 - history[0] * 255 / ratioDenominator);

			work.first = work.weights[2] + work.weights[3] + work.weights[4] + work.weights[0];
			output[-1] = (unsigned char)(1 + work.first * 255 / (sum + 1));

			work.pair = work.weights[2] + work.weights[0];
			output[0] = (unsigned char)(1 + work.pair * 255 / (work.first + 1));

			work.tail = work.weights[8] + work.weights[9];
			work.right = work.tail + work.weights[6] + work.weights[5];
			work.first = work.weights[7] + work.weights[1];
			output[1] = (unsigned char)(1 + work.first * 255 / (work.right + work.first + 1));

			output[2] = (unsigned char)(1 + work.weights[0] * 255 / (work.pair + 1));

			rowDivisor = work.row;
			++rowDivisor;
			output[3] = (unsigned char)(1 + work.weights[3] * 255 / rowDivisor);
			output[4] = (unsigned char)(1 + work.weights[1] * 255 / rowDivisor);

			left = work.weights[6] + work.weights[0];
			history += 0x14;
			output += 0x5A;
			output[-0x55] = (unsigned char)(1 + left * 255 / (work.right + 1));
			output[-0x54] = (unsigned char)(1 + work.weights[0] * 255 / (left + 1));
			output[-0x53] = (unsigned char)(1 + work.weights[8] * 255 / (work.tail + 1));

			work.ratio += 10;
			--work.repeat;
		} while (work.repeat);
	}

		++work.historyBase;
		work.outputBase += 9;
		++work.row;
		--work.offset;
	} while (work.offset > -20);
}
