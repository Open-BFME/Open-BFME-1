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

// _Rva003F4F70@16
// Retail sibling: same independently verified predicate and logger; adds a
// selected-cell output as its third argument and returns with ret 0x10.
extern "C" Bool __stdcall Rva003F4F70(const ICoord2D *center, Int radius, ICoord2D *found, void *userData)
{
	if (Glo012F0239 && TheCRCParameterCheck)
	{
		bfmeRetailCritterDesyncLog(
			TheCRCParameterCheck,
			"\t\tIterateCircular1 called with center=%d,%d, maxCells=%d",
			center->x,
			center->y,
			radius);
	}

	BfmeCellTesterRva003F5340 *tester = (BfmeCellTesterRva003F5340 *)userData;

	if (tester->test(center->x, center->y))
	{
		if (Glo012F0239 && TheCRCParameterCheck)
			bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "\t\tfunc succeeded found=%d,%d", center->x, center->y);
		found->x = center->x;
		found->y = center->y;
		return true;
	}
	if (Glo012F0239 && TheCRCParameterCheck)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "\t\tfunc failed");

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
					{
						best = dx * dx + dy * dy;
						found->x = center->x + dx;
						found->y = center->y + dy;
					}
				}
			}
			for (count = delta; count > 0; count--)
			{
				dy++;
				if (best == 0 || dx * dx + dy * dy < best)
				{
					if (tester->test(center->x + dx, center->y + dy))
					{
						best = dx * dx + dy * dy;
						found->x = center->x + dx;
						found->y = center->y + dy;
					}
				}
			}

			for (count = 0; count <= delta; count++)
			{
				dx--;
				if (best == 0 || dx * dx + dy * dy < best)
				{
					if (tester->test(center->x + dx, center->y + dy))
					{
						best = dx * dx + dy * dy;
						found->x = center->x + dx;
						found->y = center->y + dy;
					}
				}
			}
			for (count = 0; count <= delta; count++)
			{
				dy--;
				if (best == 0 || dx * dx + dy * dy < best)
				{
					if (tester->test(center->x + dx, center->y + dy))
					{
						best = dx * dx + dy * dy;
						found->x = center->x + dx;
						found->y = center->y + dy;
					}
				}
			}
			if (best != 0) {
				if (Glo012F0239 && TheCRCParameterCheck)
					bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "\t\tbest return true. found=%d,%d", found->x, found->y);
				return true;
			}
			delta += 2;
		} while (radius > 0);
	}
	if (Glo012F0239 && TheCRCParameterCheck)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "\t\ttotal failure. found=%d,%d", found->x, found->y);
	return false;
}


// 0003DC4E -> 003F1690: verified ECX receiver, eleven stack arguments, AL/ret44.
extern void j_0003dc4e();
class Rva003F1690Owner {};
typedef bool (Rva003F1690Owner::*Rva0003DC4ECall)(int,int,unsigned char,int,int,int,int,unsigned char,void*,float,int*);
// MSVC 7.1 single-inheritance member pointers are one code address.  This
// typed boundary view binds the existing address-only thunk without claiming
// a semantic name for the eleven-argument predicate.  Its full callee reads
// ECX and returns AL with ret 0x2C; both caller bodies verify all REL32 bytes.
typedef char Rva0003DC4EPmfSize[(sizeof(Rva0003DC4ECall) == sizeof(void (*)())) ? 1 : -1];
class Rva003F2D20Query
{
public:
    bool test(int x, int y)
    {
        int result;
        union Rva0003DC4EBinding
        {
            void (*address)();
            Rva0003DC4ECall member;
        } target;
        target.address = &j_0003dc4e;
        if (!(f00->*target.member)(f04, f08, f0c, x, y, f14, f10,
                                  f0d, &f28, f18, &result))
            return false;
        if (result == 0)
            return true;
        if (result < f24 || f24 == 0)
        {
            f24 = result;
            f1c = x;
            f20 = y;
        }
        return false;
    }

    Rva003F1690Owner *f00;
    int f04, f08;
    unsigned char f0c, f0d;
    int f10, f14;
    float f18;
    int f1c, f20, f24;
    float f28[3];
};
// _Rva003F55E0@16
// Retail fourth-argument query specialization; five diagnostics, RET16.
// Caller 003F5D54 -> ILT 00034E0A, query constructor 003E6200.
// This is NOT prependCells, whose own ILT 0000AF24 targets 003DD930.
// Query offsets and all call contracts: build/unclaimed_map/astra_S/LAYOUTS.md.
extern "C" Bool __stdcall Rva003F55E0(const ICoord2D *center, Int radius, ICoord2D *found, void *userData)
{
	if (Glo012F0239 && TheCRCParameterCheck)
	{
		bfmeRetailCritterDesyncLog(
			TheCRCParameterCheck,
			"\t\tIterateCircular1 called with center=%d,%d, maxCells=%d",
			center->x,
			center->y,
			radius);
	}

	Rva003F2D20Query *tester = (Rva003F2D20Query *)userData;

	if (tester->test(center->x, center->y))
	{
		if (Glo012F0239 && TheCRCParameterCheck)
			bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "\t\tfunc succeeded found=%d,%d", center->x, center->y);
		found->x = center->x;
		found->y = center->y;
		return true;
	}
	if (Glo012F0239 && TheCRCParameterCheck)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "\t\tfunc failed");

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
					{
						best = dx * dx + dy * dy;
						found->x = center->x + dx;
						found->y = center->y + dy;
					}
				}
			}
			for (count = delta; count > 0; count--)
			{
				dy++;
				if (best == 0 || dx * dx + dy * dy < best)
				{
					if (tester->test(center->x + dx, center->y + dy))
					{
						best = dx * dx + dy * dy;
						found->x = center->x + dx;
						found->y = center->y + dy;
					}
				}
			}

			for (count = 0; count <= delta; count++)
			{
				dx--;
				if (best == 0 || dx * dx + dy * dy < best)
				{
					if (tester->test(center->x + dx, center->y + dy))
					{
						best = dx * dx + dy * dy;
						found->x = center->x + dx;
						found->y = center->y + dy;
					}
				}
			}
			for (count = 0; count <= delta; count++)
			{
				dy--;
				if (best == 0 || dx * dx + dy * dy < best)
				{
					if (tester->test(center->x + dx, center->y + dy))
					{
						best = dx * dx + dy * dy;
						found->x = center->x + dx;
						found->y = center->y + dy;
					}
				}
			}
			if (best != 0) {
				if (Glo012F0239 && TheCRCParameterCheck)
					bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "\t\tbest return true. found=%d,%d", found->x, found->y);
				return true;
			}
			delta += 2;
		} while (radius > 0);
	}
	if (Glo012F0239 && TheCRCParameterCheck)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "\t\ttotal failure. found=%d,%d", found->x, found->y);
	return false;
}
