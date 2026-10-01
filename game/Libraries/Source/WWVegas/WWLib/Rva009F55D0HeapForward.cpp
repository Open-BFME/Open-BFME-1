// cl: /DNDEBUG /MD /EHsc
// Native three-slot wrapper for retail 0x009F55D0. Both additional argument
// slots passed to 0x009F53D0 are zero. No original helper/type identity claim.
// Evidence: targets/game/reverse/identity_evidence/009f55d0-five-slot-call.md.

struct S4SortElem24
{
	int m_key;
	int m_values[5];
};

struct S4Cmp009F4BF0
{
	bool operator()(const S4SortElem24 &a, const S4SortElem24 &b) const;
};

void Rva009F53D0(S4SortElem24 *first, S4SortElem24 *last,
	S4Cmp009F4BF0 comp, void *, void *);

// ?Rva009F55D0@@YAXPAUS4SortElem24@@0US4Cmp009F4BF0@@@Z
void Rva009F55D0(S4SortElem24 *first, S4SortElem24 *last,
	S4Cmp009F4BF0 comp)
{
	Rva009F53D0(first, last, comp, 0, 0);
}
