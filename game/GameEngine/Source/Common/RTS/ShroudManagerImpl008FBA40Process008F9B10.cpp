// cl: /DNDEBUG /MD /EHsc

// Retail 0x008F9B10 (155 bytes).  The matched
// ShroudManagerImpl008FBA40::undoShroudReveal wrapper at 0x008FA040 is the
// only caller.  This is the paired circle walker beside the already matched
// 0x008F9A70 walker; its two update calls resolve to the independently
// matched BfmeShroudVRB::bfmeUpdateVRB at 0x008F9720.

class BfmePartVRB;

class BfmeShroudVRB
{
public:
	char bfmeUpdateVRB(int x, int y, int radius);
	BfmePartVRB *m_bfme00;
	int m_bfme04;
};

class ShroudManagerImpl008FBA40;

bool processShroudRevealCircle008F9B10(int cellX, int cellY, int cellRadius,
	ShroudManagerImpl008FBA40 *manager, int playerMask)
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

			if (!reinterpret_cast<BfmeShroudVRB *>(&manager)->bfmeUpdateVRB(
				left, right, cellY + currentRadius))
				return false;

			if (currentRadius == 0)
				return true;

			if (!reinterpret_cast<BfmeShroudVRB *>(&manager)->bfmeUpdateVRB(
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

	return true;
}
