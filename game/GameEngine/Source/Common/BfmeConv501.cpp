// Retail calls the bucket lookup through the ILT thunk 0x0001DB92, five bytes of
// `jmp 0x000932F0`. The only symbol defined at 0x0001DB92 itself is the generated
// zero-argument thunk ?j_0001db92@@YAXXZ (game/gen_small/thunks_014.cpp); the body
// the thunk reaches is the ledger's matched STLport
// _Rb_tree<AsciiString, pair<const AsciiString, Rva00093670Value>, ...>::_M_find,
// whose template name cannot be spelled as this BfmeThingBPA member. So the
// reference carries the thunk's name and the thiscall shape -- receiver in ECX,
// one stack argument, pointer in EAX -- is recovered through the union pun the
// tree already uses for thunks reached with arguments (BfmeConv1850.cpp,
// game/GameEngine/Source/Common/INI/INIWindowTransition.cpp).
extern void j_0001db92();

struct BfmeGotBPA
{
	unsigned char m_bfmeHead[0x14];
	void *m_bfmeWhat;
};

class BfmeThingBPA
{
public:
	void *bfmeGoBPA(void *what);
	BfmeGotBPA *m_bfmeEnd;
};

void *BfmeThingBPA::bfmeGoBPA(void *what)
{
	union { void (*thunk)(); BfmeGotBPA *(BfmeThingBPA::*find)(void *); } pun;
	pun.thunk = j_0001db92;

	BfmeGotBPA *got = (this->*pun.find)(what);
	if (got == m_bfmeEnd)
		return 0;
	return got->m_bfmeWhat;
}