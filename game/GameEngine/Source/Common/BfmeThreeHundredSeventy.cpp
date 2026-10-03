// cl: /O2 /Ob0
//
// Retail 0x000DE680 and 0x000DE710 copy 16-byte nodes whose head is a
// StringBase<char> (0x00887C90 is StringBase<char>::set, the narrow
// function-local static block at 0x01336E10) and whose +4 subobject is assigned
// through the five-byte ILT thunk 0x00007A63 (?j_00007a63@@YAXXZ). The members
// the original shape declared here are not the ones retail calls, so both calls
// keep their call shape and name the recorded definition instead: the head call
// takes the address of the real out-of-line set, the subobject call stores the
// thunk's address (the thunk drops the assignment's result, so its void
// signature loses nothing).

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

struct BfmeDestWE
{
	unsigned char m_bfmeHead[4];
	unsigned char m_bfmeField[4];
};

class BfmeSubWE
{
public:
	void bfmeAssignWE(void *what);

	unsigned char m_bfmeHead[4];
};

struct BfmeNodeWE
{
public:
	unsigned char m_bfmeHead[4];
	BfmeSubWE m_bfmeSub;
	unsigned char m_bfmeRest[8];
};

void j_00007a63();

union BfmeSubWEAssign
{
	void (*function)(void);
	void (BfmeSubWE::*member)(void *);
};

union BfmeNodeWESet
{
	void (StringBase<char>::*member)(const StringBase<char> &src);
};

void bfmeCopyWE(BfmeNodeWE *first, BfmeNodeWE *last, BfmeDestWE *to)
{
	BfmeNodeWESet set;
	set.member = &StringBase<char>::set;
	BfmeSubWEAssign assign;
	assign.function = &j_00007a63;

	while (first != last)
	{
		(reinterpret_cast<StringBase<char> *>(first)->*set.member)(
			*reinterpret_cast<const StringBase<char> *>(to));
		(first->m_bfmeSub.*assign.member)(&to->m_bfmeField);
		++first;
	}
}

BfmeNodeWE *bfmeUninitCopyWE(BfmeNodeWE *first, BfmeNodeWE *last, BfmeNodeWE *to)
{
	BfmeNodeWESet set;
	set.member = &StringBase<char>::set;
	BfmeSubWEAssign assign;
	assign.function = &j_00007a63;

	int count = last - first;

	while (count > 0)
	{
		(reinterpret_cast<StringBase<char> *>(to)->*set.member)(
			*reinterpret_cast<const StringBase<char> *>(first));
		(to->m_bfmeSub.*assign.member)(&first->m_bfmeSub);
		++first;
		++to;
		--count;
	}

	return to;
}