// cl: /DNDEBUG /MD /EHsc

void operator delete[]( void *block );

struct Rva00402C50GridState
{
	unsigned short firstZone;
	unsigned short numZones;
	void *grid[12][5];
	unsigned char marked;
	unsigned char padding[3];
};

class Rva00402C50
{
	char beforeStates[0x38];
	Rva00402C50GridState active;
	Rva00402C50GridState pending;

public:
	void transferBlocks();
};

void Rva00402C50::transferBlocks()
{
	for (int column = 0; column < 5; ++column)
	{
		for (int row = 0; row < 12; ++row)
			delete [] active.grid[row][column];
	}

	active = pending;

	for (int column = 0; column < 5; ++column)
	{
		for (int row = 0; row < 12; ++row)
			pending.grid[row][column] = 0;
	}
}
