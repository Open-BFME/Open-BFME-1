// ?d_009c8240@@YAXXZ
// partial score=0.09 date=2026-09-23
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

extern "C" void * __cdecl memcpy(void *, const void *, unsigned int);
#pragma intrinsic(memcpy)

void __cdecl rva009C8240(const int *table, unsigned char *pixels,
	int stride, unsigned int width, unsigned int height)
{
	unsigned char minimum = 0xff;
	volatile unsigned char maximum = 0;
	unsigned char *scan = pixels;
	unsigned int rows = height;

	if (rows != 0) {
		do {
			unsigned int columns = width;
			if (columns != 0) {
				do {
					unsigned char value = *scan;
					if (value < minimum)
						minimum = value;
					if (maximum < value)
						maximum = value;
					++scan;
					--columns;
				} while (columns != 0);
			}
			scan += stride - (int)width;
			--rows;
		} while (rows != 0);
	}

	int maximumBound = table[0x453c / 4 + maximum];
	int minimumBound = table[0x124e - minimum];
	if (minimumBound > maximumBound)
		minimumBound = maximumBound;
	volatile int threshold = minimumBound + ((maximum - minimum) >> 5);
	unsigned char work[16];

	unsigned char *row = pixels;
	rows = height;
	if (rows != 0) {
		do {
			unsigned char *sample = row;
			unsigned int columns = width;
			if (columns != 0) {
				unsigned int index = 0;
				do {
					int center = sample[0];
					int left = sample[-1];
					int right = sample[1];
					int value = 2 * center;
					int difference = center - left;
					if (difference < 0)
						difference = -difference;
					if (difference > threshold)
						value += center;
					else
						value += left;
					difference = center - right;
					if (difference < 0)
						difference = -difference;
					if (difference > threshold)
						value += center;
					else
						value += right;
					work[index] = (unsigned char)((value + 2) >> 2);
					++sample;
					++index;
					--columns;
				} while (columns != 0);
			}
			memcpy(row, work, width);
			row += stride;
			--rows;
		} while (rows != 0);
	}

	unsigned char *column = pixels;
	unsigned int columns = width;
	if (columns != 0) {
		do {
			unsigned char *above = column - stride;
			unsigned char *center = column;
			unsigned char *below = column + stride;
			unsigned int rowsRemaining = height;
			if (rowsRemaining != 0) {
				unsigned int index = 0;
				do {
					int middle = *center;
					int upper = *above;
					int lower = *below;
					int value = 2 * middle;
					int difference = middle - upper;
					if (difference < 0)
						difference = -difference;
					if (difference > threshold)
						value += middle;
					else
						value += upper;
					difference = middle - lower;
					if (difference < 0)
						difference = -difference;
					if (difference > threshold)
						value += middle;
					else
						value += lower;
					work[index] = (unsigned char)((value + 2) >> 2);
					above += stride;
					center += stride;
					below += stride;
					++index;
					--rowsRemaining;
				} while (rowsRemaining != 0);
			}
			unsigned char *output = column;
			rowsRemaining = height;
			if (rowsRemaining != 0) {
				unsigned int index = 0;
				do {
					*output = work[index];
					output += stride;
					++index;
					--rowsRemaining;
				} while (rowsRemaining != 0);
			}
			++column;
			--columns;
		} while (columns != 0);
	}
}
