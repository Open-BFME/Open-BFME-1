// ILT 0x0001DA34 -> 0x003A04A0, the matched
// accepts@Rva2225E0Filter@@QAE_NPAVObject@@PAVPlayer@@@Z.
class Object;
class Player;

class Rva2225E0Filter
{
public:
	bool accepts(Object *obj, Player *player);
};

typedef Rva2225E0Filter BfmeAskerRJ;

class BfmeThingRJ
{
public:
	bool bfmeCheckRJ(void *what);
	unsigned char m_bfmeHead[8];
	BfmeAskerRJ *m_bfmeSub;
	void *m_bfmeExtra;
	bool m_bfmeFlag;
};

bool BfmeThingRJ::bfmeCheckRJ(void *what)
{
	if (m_bfmeSub->accepts((Object *)what, (Player *)m_bfmeExtra))
		return m_bfmeFlag;
	return !m_bfmeFlag;
}
