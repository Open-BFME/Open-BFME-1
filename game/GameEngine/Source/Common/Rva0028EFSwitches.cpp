// Retail 0x0028EF30 and 0x0028EF80 each include a two-way jump table.
struct Rva0028EF30Switch
{
	bool accept(unsigned int value) const;
};

bool Rva0028EF30Switch::accept(unsigned int value) const
{
	switch (value)
	{
	case 0: case 3: case 4: case 5: case 6: case 7: case 9:
		return true;
	case 1: case 2: case 8:
		return false;
	default:
		return false;
	}
}

struct Rva0028EF80Switch
{
	bool accept(unsigned int value) const;
};

bool Rva0028EF80Switch::accept(unsigned int value) const
{
	switch (value)
	{
	case 1: case 2: case 8:
		return true;
	case 0: case 3: case 4: case 5: case 6: case 7: case 9:
		return false;
	default:
		return false;
	}
}
