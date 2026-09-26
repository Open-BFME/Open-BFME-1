// Retail 0x008F9BB0, complete boundary 155 bytes.
//
// BfmeOwnerXO::bfmeSendXO constructs the four-word BfmeArgXO value in its
// outgoing argument area and calls this circle walker.  Its instruction shape
// is the exact sibling of the two verified shroud reveal walkers; this variant
// dispatches each horizontal span through BfmeShroudVRC::bfmeUpdateVRC.

struct BfmeArgXO
{
	void *owner;
	unsigned int tag;
	int slot;
	void *data;
};

class BfmeShroudVRC
{
public:
	char bfmeUpdateVRC(int x, int y, int radius);
};

bool __cdecl bfmeCallXO(int cellX, int cellY, int cellRadius, BfmeArgXO arg)
{
	int touched = 0;
	int currentRadius = cellRadius;
	int error = 2;
	error -= currentRadius * 2;
	int left = cellX;
	int right = cellX;

	for (;;)
	{
		if (error + currentRadius > 0)
		{
			if (currentRadius == 0 && cellRadius == 1)
			{
				++touched;
				++right;
				--left;
			}

			if (!reinterpret_cast<BfmeShroudVRC *>(&arg)->bfmeUpdateVRC(
				left, right, cellY + currentRadius))
				return false;

			if (currentRadius == 0)
				return true;

			if (!reinterpret_cast<BfmeShroudVRC *>(&arg)->bfmeUpdateVRC(
				left, right, cellY - currentRadius))
				return false;

			--currentRadius;
			error += 1 - currentRadius * 2;
		}

		if (touched > error)
		{
			++touched;
			++right;
			--left;
			error += touched * 2 + 1;
		}
	}
}
