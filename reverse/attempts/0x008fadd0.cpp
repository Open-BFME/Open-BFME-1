// ?processPending@ShroudManagerImpl008FBA40@@AAEX_N@Z
// partial score=0.97 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc
// stlport
//
// ShroudManagerImpl008FBA40's private pending-queue drain (declared in
// Code/GameEngine/Source/Common/RTS/ShroudManagerImpl008FBA40.cpp, called
// from drainPending() as processPending(true) and from configure() as
// processPending(false)). drainAll==true uses unknown38 (the current tick)
// as the due-date threshold; drainAll==false forces the whole queue through
// by using 0xffffffff as the threshold. Logic, control flow and the two
// callees (processShroudRevealCircle008F9B10 at 0x008F9B10, direct E8;
// __stlp_deallocate_small at 0x0082E5F0, direct E8) are all byte-verified
// correct: probe.py shows only register-encoding drift after the first
// diff, no missing/extra logic.
//
// Only remaining diff (156 B compiled vs 155 B target): retail keeps the
// front-of-deque pointer in ECX through the whole per-entry check/call
// block (loads playerMask into EAX, radius into EDX off that ECX base),
// letting `and eax, 0xffff` use the 5-byte EAX-immediate short form.
// Every source shape tried here (named pointer local, reference local,
// register hint, inline chained ->access with no local, locals extracted
// before/after the branch, reordering field loads) makes MSVC 7.1 put the
// front pointer in EAX instead, so the mask ends up in ECX/EDX and needs
// the 6-byte ModRM form (81 e1 ff ff 00 00), which is the whole +1 byte.
// Next attempt: try forcing ECX via an artificial `__asm mov ecx, ...`-free
// method-call boundary (e.g. routing the per-entry work through a
// non-inlined `static` helper taking the pointer as its only argument,
// so __fastcall/__thiscall register-arg convention picks ECX for it), or
// grep other already-matched STLport deque pop_front bodies in this repo
// for the shape that produced ECX there.

typedef unsigned int UnsignedInt;
typedef int Int;

struct Gen_t_008fb350_p12pod
{
	unsigned int timestamp;
	int x;
	int y;
	int radius;
	int playerMask;
};

struct RecordsDequeIterator
{
	Gen_t_008fb350_p12pod *cur;
	Gen_t_008fb350_p12pod *first;
	Gen_t_008fb350_p12pod *last;
	Gen_t_008fb350_p12pod **node;
};

struct RecordsDequeLayout
{
	RecordsDequeIterator start;
	RecordsDequeIterator finish;
};

class ShroudManagerImpl008FBA40;

bool processShroudRevealCircle008F9B10(Int cellX, Int cellY, Int cellRadius,
	ShroudManagerImpl008FBA40 *manager, Int playerMask);
void __stlp_deallocate_small(void *ptr, unsigned int n);

// Field layout excerpt: unknown38 at +0x38, records (a
// _STL::deque<Gen_t_008fb350_p12pod, _STL::allocator<...> >) at +0x3C.
class ShroudManagerImpl008FBA40StubLayout
{
public:
	void processPending(bool drainAll);

private:
	char padding00[0x38];
	int unknown38;
	RecordsDequeLayout records;
};

void ShroudManagerImpl008FBA40StubLayout::processPending(bool drainAll)
{
	RecordsDequeLayout *layout = &records;

	unsigned int threshold = drainAll ? (unsigned int)unknown38 : 0xffffffffu;

	while (layout->finish.cur != layout->start.cur)
	{
		if (layout->start.cur->timestamp >= threshold)
			break;

		if (layout->start.cur->playerMask != 0 && layout->start.cur->radius >= 0)
		{
			processShroudRevealCircle008F9B10(layout->start.cur->x,
				layout->start.cur->y, layout->start.cur->radius,
				reinterpret_cast<ShroudManagerImpl008FBA40 *>(this),
				layout->start.cur->playerMask & 0xffff);
		}

		if (layout->start.cur != layout->start.last - 1)
		{
			++layout->start.cur;
		}
		else
		{
			if (layout->start.first)
				__stlp_deallocate_small(layout->start.first, sizeof(Gen_t_008fb350_p12pod) * 6);
			++layout->start.node;
			layout->start.first = *layout->start.node;
			layout->start.last = layout->start.first + 6;
			layout->start.cur = layout->start.first;
		}
	}
}
