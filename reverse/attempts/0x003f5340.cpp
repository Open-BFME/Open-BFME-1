// ?d_003f5340@@YAXXZ
// partial score=0.5 date=2026-09-11
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// PARTIAL, score ~0.5. Algorithm and both callee ABIs are confirmed correct
// (see reverse/re_attempts.log); byte gap is in codegen shape, not identity.
// Residual, from tools/probe.py at 0x003F5340:
//  - object is 508B vs retail 527B; first diff at +0x84.
//  - the "delta" local (reuses P1's own dead argument stack slot) and the
//    "step" local (a genuine sub-esp,8 frame slot, init 4, += 8/ring) have
//    their store shapes SWAPPED from retail: retail stores delta's initial 1
//    directly to memory (`mov dword ptr [slot],1`, no register) and step's
//    initial 4 through eax (`mov eax,4; mov [slot],eax`); this candidate
//    does the opposite. Tried and ruled out: separating delta's declaration
//    statement, declaring step inside vs. outside the `if(radius>0)` guard,
//    declaring both before the guard -- none changed the register choice.
//  - deeper in the first ring, retail's per-arm distance test uses
//    eax/ecx (`mov eax,edi; mov ecx,ebx; imul eax,edi; imul ecx,ebx; add
//    eax,ecx; cmp eax,esi`) where this candidate uses edx/eax for the same
//    computation -- a real register-allocation difference, not just an
//    offset shift from the delta/step gap above.
//  - retail re-tests the frame "step" slot for <=0 (dead code: step only
//    grows) between EVERY pair of arm loops (e.g. `mov eax,[esp+0x10];
//    test eax,eax; jle` right after the first arm's inner loop closes,
//    at +0xe1..+0xe7); this candidate does not emit that recheck at all.
//    That recheck recurring per arm (not just once per ring) suggests the
//    real source may factor the ring into a shared per-arm helper/loop
//    rather than four independent unrolled `for` statements -- worth
//    trying before another register-shuffle pass.


typedef bool Bool;
typedef int Int;

struct ICoord2D
{
	Int x, y;
};

class CRCParameterCheck
{
};

extern CRCParameterCheck *TheCRCParameterCheck;
extern bool Glo012F0239;
extern void j_0003a17a(void);
extern void j_00046e6b(void);

typedef void (__cdecl *BfmeCritterDesyncLog)(void *, const char *, ...);

class BfmeCellTesterRva003F5340
{
public:
	bool test(Int x, Int y);
};

typedef bool (BfmeCellTesterRva003F5340::*TestMemberFn)(Int, Int);

extern "C" Bool __stdcall Rva003F5340(const ICoord2D *center, Int radius, void *userData)
{
	if (Glo012F0239 && TheCRCParameterCheck)
	{
		((BfmeCritterDesyncLog)j_0003a17a)(
			TheCRCParameterCheck,
			(const char *)0x010EFBC0,
			center->x,
			center->y,
			radius);
	}

	union
	{
		void (*raw)(void);
		TestMemberFn member;
	} fn;
	fn.raw = j_00046e6b;
	BfmeCellTesterRva003F5340 *tester = (BfmeCellTesterRva003F5340 *)userData;

	if ((tester->*fn.member)(center->x, center->y))
		return true;

	Int best = 0;
	Int dx = 0, dy = 0;
	Int delta = 1;
	Int step;
	if (radius > 0)
	{
		step = 4;
		do
		{
			radius -= step + 2;
			Int count;
			for (count = delta; count > 0; count--)
			{
				dx++;
				if (best == 0 || dx * dx + dy * dy < best)
				{
					if ((tester->*fn.member)(center->x + dx, center->y + dy))
						best = dx * dx + dy * dy;
				}
			}
			for (count = delta; count > 0; count--)
			{
				dy++;
				if (best == 0 || dx * dx + dy * dy < best)
				{
					if ((tester->*fn.member)(center->x + dx, center->y + dy))
						best = dx * dx + dy * dy;
				}
			}
			delta++;
			for (count = delta; count > 0; count--)
			{
				dx--;
				if (best == 0 || dx * dx + dy * dy < best)
				{
					if ((tester->*fn.member)(center->x + dx, center->y + dy))
						best = dx * dx + dy * dy;
				}
			}
			for (count = delta; count > 0; count--)
			{
				dy--;
				if (best == 0 || dx * dx + dy * dy < best)
				{
					if ((tester->*fn.member)(center->x + dx, center->y + dy))
						best = dx * dx + dy * dy;
				}
			}
			delta++;
			step += 8;
		} while (radius > 0);
	}
	return false;
}
