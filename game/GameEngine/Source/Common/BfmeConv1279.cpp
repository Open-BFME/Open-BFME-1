// Open-BFME5 conversions.

// The copy this file used to spell bfmeCopy1279@BfmeQ1279 sits at 0x007E8A80,
// whose ledger row and defining body are BfmeConv1339.cpp's
// ?bfmeGoUPB@BfmeThingUPB@@QAEDPAXPAD0@Z. Name the call by that spelling so
// the link resolves; the byte shape (three cdecl args, result discarded) is
// unchanged.
class BfmeThingUPB
{
public:
	char bfmeGoUPB(void *s, char *dst, void *n);            // 0x007E8A80
};

// BfmeQ1279 stays the ctor's parameter type: it is spelled in
// ?bfmeA1279@@QAE@PAVBfmeQ1279@@@Z and in
// GameNetwork/GameSpy/Thread/BuddyThreadClassThreadFunction.cpp.
class BfmeQ1279;


class BfmeA1279
{
public:
	BfmeA1279(BfmeQ1279 *a);
	BfmeQ1279 *m_bfme00;
	char m_bfme04[0x100];
	char m_bfme104[0x100];
};

BfmeA1279::BfmeA1279(BfmeQ1279 *a)
{
	m_bfme00 = a;
	reinterpret_cast< BfmeThingUPB * >( a )->bfmeGoUPB("ticket", m_bfme04, (void *)0x100);
	reinterpret_cast< BfmeThingUPB * >( m_bfme00 )->bfmeGoUPB("challenge", m_bfme104, (void *)0x100);
}
