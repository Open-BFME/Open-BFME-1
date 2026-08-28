// cl: /DNDEBUG /MD /EHsc
// readable body of ?newMap@Player@@QAEXXZ: Code/GameEngine/Source/Common/RTS/Player.cpp

// Open-BFME5: Player::newMap, retail 0x000C9200, 43 bytes. The body carried
// only a machine byte-dump row; reverse/reloc_names.csv carries the name with
// identity=real.
//
// Zero Hour's newMap is one line -- if (m_ai) m_ai->newMap() -- through a
// virtual. BFME's is not: it reads a flag out of the AI object at +0x118 and
// hands it, with the field at Player+0x24, to a non-virtual call on the
// subobject at Player+0x30. The two call sites are separate in retail rather
// than one call with a conditional argument, which is what an if/else with a
// statement in each arm compiles to.

typedef int Int;
typedef bool Bool;

class BfmePlayerAI
{
public:
	char m_bfmeHead[0x118];
	Bool m_bfmeFlag;					// +0x118
};

class BfmePlayerMapState
{
public:
	void bfmeNewMap(Int field, Bool flag);			// ILT 0x00018679 -> 0x000C7A30
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	void newMap(void);

private:
	char m_bfmeHeadA[0x04];
	BfmePlayerAI *m_bfmeAI;					// +0x04
	char m_bfmeHeadB[0x24 - 0x08];
	Int m_bfmeField24;					// +0x24
	char m_bfmeHeadC[0x30 - 0x28];
	BfmePlayerMapState m_bfmeMapState;			// +0x30
};

// ?newMap@Player@@QAEXXZ
void Player::newMap(void)
{
	if (m_bfmeAI)
		m_bfmeMapState.bfmeNewMap(m_bfmeField24, m_bfmeAI->m_bfmeFlag);
	else
		m_bfmeMapState.bfmeNewMap(m_bfmeField24, false);
}
