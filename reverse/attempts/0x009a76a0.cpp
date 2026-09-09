// ?bfmeGo76A0@@YAXHPAHPAXHHH1@Z
// partial score=0.92 date=2026-09-09
// cl: /DNDEBUG /MD /O2

extern int g_bfmeTableC7E0;
extern int g_bfmeTableC800;

void __cdecl bfmeGo7760(int *table, void *p1, int a, int b, int c, int d, void *p5);

// ?bfmeGo76A0@@YAXHPAHPAXHHH1@Z
void __cdecl bfmeGo76A0(int delta, int *table, void *p2, int a, int b, int c, void *p3)
{
	if ((unsigned int)b > 0)
	{
		int columnCount = c;
		const int *weights = (const int *)p3;
		int rowCount = b;
		unsigned char *sourcePointer = (unsigned char *)delta;

		do
		{
			int column = 0;
			if ((unsigned int)columnCount > 0)
			{
				unsigned char *previous = sourcePointer - a;
				unsigned char *next = sourcePointer + a;

				do
				{
					int value = next[a] * weights[3];
					value += next[0] * weights[2];
					value += sourcePointer[0] * weights[1];
					value += previous[0] * weights[0];
					value = (value + 0x40) >> 7;
					if (value < 0)
						value = 0;
					else if (value > 0xFF)
						value = 0xFF;
					table[column] = value;
					++sourcePointer;
					++next;
					++previous;
					++column;
				}
				while ((unsigned int)column < (unsigned int)columnCount);
			}

			sourcePointer += (int)p2 - columnCount;
			table += columnCount;
		}
		while (--rowCount != 0);
	}
}

// ?bfmeGo7820@@YAXPAX0000@Z
void __cdecl bfmeGo7820(void *p0, void *p1, void *p2, void *p3, void *p4)
{
	bfmeGo76A0((int)((char *)p0 - (char *)p2), &g_bfmeTableC7E0, p2, 1, 0xB, 8, p3);
	bfmeGo7760(&g_bfmeTableC800, p1, 8, 8, 8, 8, p4);
}
