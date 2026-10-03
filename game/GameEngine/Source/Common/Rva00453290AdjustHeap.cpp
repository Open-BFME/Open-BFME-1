// cl: /DNDEBUG /MD /EHsc

// STLport's comparator overload of __adjust_heap for a four-byte scalar.
// twin of ??$__adjust_heap@PAHHHUQ4Cmp00344A60@@@_STL@@YAXPAHHHHUQ4Cmp00344A60@@@Z
// (retail 0x00342D60, game/GameEngine/Source/Common/Rva00342D60AdjustHeap.cpp).
// The comparator's own operator() is out of line and ICF-folded with the
// pinned callee named BfmeCompAP (targets/game/reverse/symbols.csv, 0x00039CB1); the
// __push_heap instantiation ICF-folds with Q4Sort004567A0's at 0x0001EFC9's
// thunk target.

struct Q4Cmp00453C20
{
	bool operator()(int left, int right) const;
};

// Both out-of-line callees are reached in retail through 5-byte ILT thunks:
// 0x00039CB9 -> ?j_00039cb1@@YAXXZ, whose target 0x00451E90 is
// ??RS4Cmp00452A50@@QBE_NHH@Z, and 0x0001EFC9 -> ?j_0001efc9@@YAXXZ, whose
// target 0x00452A50 is
// ??$__push_heap@PAHHHUS4Cmp00452A50@@@_STL@@YAXPAHHHHUS4Cmp00452A50@@@Z
// (game/gen_small/thunks_027.cpp and thunks_006.cpp).  The address-scoped
// pins ?RQ4Cmp00453C20@@QBE_NHH@Z and
// ??$__push_heap@PAHHHUQ4Cmp00453C20@@@_STL@@YAXPAHHHHUQ4Cmp00453C20@@@Z
// name those same thunks, but nothing defines them.  S4Cmp00452A50 carries the
// real callee signatures so the calls below spell the thunks' ABI without
// inventing a body here.
struct S4Cmp00452A50
{
	bool operator()(int left, int right) const;
};

extern void j_00039cb1();
extern void j_0001efc9();

typedef bool (Q4Cmp00453C20::*CompareCall)(int, int) const;

union ComparePointer
{
	void (*entry)();
	CompareCall member;
};

typedef void (*PushHeapCall)(int *, int, int, int, S4Cmp00452A50);

union PushHeapPointer
{
	void (*entry)();
	PushHeapCall member;
};

namespace _STL
{
	template <class RandomAccessIterator, class Distance, class Tp, class Compare>
	void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
		Distance length, Tp value, Compare compare)
	{
		Distance topIndex = holeIndex;
		Distance secondChild = 2 * holeIndex + 2;
		ComparePointer compareCall;
		compareCall.entry = j_00039cb1;
		while (secondChild < length)
		{
			if ((compare.*compareCall.member)(*(first + secondChild),
				*(first + (secondChild - 1))))
			{
				--secondChild;
			}
			*(first + holeIndex) = *(first + secondChild);
			holeIndex = secondChild;
			secondChild = 2 * (secondChild + 1);
		}
		if (secondChild == length)
		{
			*(first + holeIndex) = *(first + (secondChild - 1));
			holeIndex = secondChild - 1;
		}
		PushHeapPointer pushCall;
		pushCall.entry = j_0001efc9;
		pushCall.member(first, holeIndex, topIndex, value,
			*(S4Cmp00452A50 *)&compare);
	}

	template void __adjust_heap<int *, int, int, Q4Cmp00453C20>(
		int *, int, int, int, Q4Cmp00453C20);
}