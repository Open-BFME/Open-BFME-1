// cl: /DNDEBUG /MD /EHsc
// Open-BFME6: 0x00232350. If the argument or its melee-resolved target shares
// this+0x100, stamp TheGameLogic's frame plus 15 into this+0x104.

class Object
{
public:
	Object *bfmeResolveMeleeTarget(int);
	char m_pad[0x74];
	int m_74;
};

class GameLogic
{
public:
	char m_pad[0x3C];
	int m_frame;
};

extern GameLogic *TheGameLogic;

class Gen_00232350
{
public:
	void bfmeNote(Object *obj);

private:
	char m_pad[0x100];
	int m_100;
	int m_104;
};

// ?bfmeNote@Gen_00232350@@QAEXPAVObject@@@Z
void Gen_00232350::bfmeNote(Object *obj)
{
	if (obj == 0)
		return;
	int saved = obj->m_74;
	Object *resolved = obj->bfmeResolveMeleeTarget(0);
	if (resolved != 0)
		saved = resolved->m_74;
	if (obj->m_74 == m_100 || saved == m_100)
		m_104 = TheGameLogic->m_frame + 15;
}
