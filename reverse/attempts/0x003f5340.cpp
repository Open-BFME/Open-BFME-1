// ?d_003f5340@@YAXXZ
// partial score=0.55 date=2026-09-21
// model=Sonnet 5
// Algorithm and callee ABIs confirmed (see prior re_attempts.log entry, score=0.5).
// THIS REVISION fixes two real structural bugs the 0.5 candidate had (found by
// walking tools/dis_retail.py 0x003F5340 527 instruction-by-instruction):
//  - retail does NOT do "delta++" twice (once after arm2, once after arm4).
//    It keeps the persistent `delta` slot [esp+0x1c] UNCHANGED for the whole
//    ring: arm1/arm2 use `count = delta`, arm3/arm4 use a SCRATCH `count =
//    delta + 1` (computed fresh each time, never written back), and only at
//    the very end of the ring does it do a single `delta += 2` (`add dword
//    ptr [esp+0x1c], 2` at +0x1df). The old candidate's double delta++
//    happened to be numerically equivalent this ring but drifts the byte
//    shape entirely.
//  - retail has an `if (best != 0) return true;` at the END of every ring
//    (+0x1db..+0x1dd, tests esi) -- i.e. once ANY hit is found in the current
//    ring it returns immediately rather than continuing to search further
//    (correct closest-first early-out). The old candidate never returned
//    true from the ring search at all.
//  - retail also wraps arm1+arm2 in a nested `if (step > 0) { arm1; if
//    (step > 0) { arm2; } }` guard (dead at runtime, step only grows, but
//    it IS emitted -- confirmed by tracing jump targets: the ring-start
//    check at +0x93 and the post-arm1 check at +0xe7 both jump to the SAME
//    address, +0x137, which is the post-arm2 guard's own test -- i.e. two
//    nested ifs whose false edges both fall through to the code right after
//    the block). Reproducing this pair-1 guard fixed the +0x53 eax/ecx
//    register choice for the `radius` reload to match retail exactly.
// RESIDUAL after all of the above: object is 526B vs retail 527B (size now
// within 1 byte!), first diff still at +0x62: retail stores `delta`'s
// initial value with a bare `mov dword ptr [slot], 1` (no register), while
// every source shape tried here (combined decl+init, split decl-then-assign,
// reordering vs best/dx/dy, scoping `step` inside vs outside the `if`)
// still routes it through a register (`mov ecx,1; mov [slot],ecx`) --
// `step`'s init (`mov eax,4` then store) matches retail already, so the
// asymmetry is specific to `delta`. This single register-vs-immediate
// choice is the entire remaining gap; because it's a 1-byte-shorter
// encoding it shifts every relative branch after +0x62, which is why the
// non-reloc diff count still looks large (382B) despite the size gap being
// almost closed. NEXT LEVER TO TRY: something about how many other locals
// are simultaneously "dead" at the point of the delta=1 store -- possibly
// initializing `best`/`dx`/`dy` via memset-style zero-fill (single wider
// store) frees up whatever register pressure is currently forcing `delta`
// through ecx, or the second arm-pair (arm3/arm4) may need its OWN
// `if (step >= 0)` guard pair (tried in an intermediate revision, made size
// overshoot to 542B, so probably wrong shape -- but not exhaustively ruled
// out with the pair-1 fix combined).

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
			if (step > 0)
			{
				for (count = delta; count > 0; count--)
				{
					dx++;
					if (best == 0 || dx * dx + dy * dy < best)
					{
						if ((tester->*fn.member)(center->x + dx, center->y + dy))
							best = dx * dx + dy * dy;
					}
				}
				if (step > 0)
				{
					for (count = delta; count > 0; count--)
					{
						dy++;
						if (best == 0 || dx * dx + dy * dy < best)
						{
							if ((tester->*fn.member)(center->x + dx, center->y + dy))
								best = dx * dx + dy * dy;
						}
					}
				}
			}
			for (count = delta + 1; count > 0; count--)
			{
				dx--;
				if (best == 0 || dx * dx + dy * dy < best)
				{
					if ((tester->*fn.member)(center->x + dx, center->y + dy))
						best = dx * dx + dy * dy;
				}
			}
			for (count = delta + 1; count > 0; count--)
			{
				dy--;
				if (best == 0 || dx * dx + dy * dy < best)
				{
					if ((tester->*fn.member)(center->x + dx, center->y + dy))
						best = dx * dx + dy * dy;
				}
			}
			if (best != 0)
				return true;
			delta += 2;
			step += 8;
		} while (radius > 0);
	}
	return false;
}
