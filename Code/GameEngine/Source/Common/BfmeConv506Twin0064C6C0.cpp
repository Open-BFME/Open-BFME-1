// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: retail 0x0064C6C0 (29 bytes) is the twin of BfmeConv506.cpp bfmeGoBPB with the
// guarded object as the SIXTH argument (the two arguments before it are not read): the
// three leading arguments are forwarded to its thiscall member.

class BfmeSubBPB0064C6C0
{
public:
	void bfmeDoBPB(void *one, void *two, void *three);
};

void bfmeGoBPB0064C6C0(void *one, void *two, void *three, int unusedFour, int unusedFive, BfmeSubBPB0064C6C0 *sub)
{
	if (sub != 0)
		sub->bfmeDoBPB(one, two, three);
}
