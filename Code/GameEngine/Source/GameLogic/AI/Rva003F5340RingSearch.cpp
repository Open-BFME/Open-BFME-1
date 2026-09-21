// _Rva003F5340@12
// Retail 0x003F5340, 527 bytes. The diagnostic names the circular search, but
// does not distinguish its several retail instances; retain the RVA identity.
// ILT 00046E6B -> 003F2B60 is bool thiscall(x,y), independently witnessed by
// the callee reading ECX and its two stack arguments and returning AL/ret 8.
// ILT 0003A17A -> 00065C80 is the landed variadic CRCParameterCheck logger.
// Let VC7.1 derive the 4*delta induction variable. The last two inclusive
// loops generate retail's >=0 guards and delta+1 counts without manual guards.

typedef bool Bool;
typedef int Int;

struct ICoord2D
{
	Int x, y;
};

class CRCParameterCheck;

extern CRCParameterCheck *TheCRCParameterCheck;
extern bool Glo012F0239;
extern "C" void __cdecl bfmeRetailCritterDesyncLog(CRCParameterCheck *, const char *, ...);



class BfmeCellTesterRva003F5340
{
public:
	bool test(Int x, Int y);
};


extern "C" Bool __stdcall Rva003F5340(const ICoord2D *center, Int radius, void *userData)
{
	if (Glo012F0239 && TheCRCParameterCheck)
	{
		bfmeRetailCritterDesyncLog(
			TheCRCParameterCheck,
			"\t\tIterateCircular2 called with center=%d,%d, maxCells=%d",
			center->x,
			center->y,
			radius);
	}

	BfmeCellTesterRva003F5340 *tester = (BfmeCellTesterRva003F5340 *)userData;

	if (tester->test(center->x, center->y))
		return true;

	Int best = 0;
	Int dx = 0, dy = 0;
	Int delta = 1;
	if (radius > 0)
	{
		do
		{
			radius -= 4 * delta + 2;
			Int count;
			for (count = delta; count > 0; count--)
			{
				dx++;
				if (best == 0 || dx * dx + dy * dy < best)
				{
					if (tester->test(center->x + dx, center->y + dy))
						best = dx * dx + dy * dy;
				}
			}
			for (count = delta; count > 0; count--)
			{
				dy++;
				if (best == 0 || dx * dx + dy * dy < best)
				{
					if (tester->test(center->x + dx, center->y + dy))
						best = dx * dx + dy * dy;
				}
			}

			for (count = 0; count <= delta; count++)
			{
				dx--;
				if (best == 0 || dx * dx + dy * dy < best)
				{
					if (tester->test(center->x + dx, center->y + dy))
						best = dx * dx + dy * dy;
				}
			}
			for (count = 0; count <= delta; count++)
			{
				dy--;
				if (best == 0 || dx * dx + dy * dy < best)
				{
					if (tester->test(center->x + dx, center->y + dy))
						best = dx * dx + dy * dy;
				}
			}
			if (best != 0) return true;
			delta += 2;
		} while (radius > 0);
	}
	return false;
}
