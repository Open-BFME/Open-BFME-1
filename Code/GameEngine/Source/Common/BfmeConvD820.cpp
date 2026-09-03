// cl: /DNDEBUG /MD /EHs-c-
// Convert 0x0026D820: GameLogic findObjectByID + Coord3D + this-adj -8.

struct Coord3D
{
	float x, y, z;
};

class Object
{
public:
	char m_bfmePad00[0x38];
	Coord3D m_bfmePos;
	char m_bfmePad44[0x204 - 0x44];
	void *m_bfmeMod;
};

class BfmeHelpD820
{
public:
	void bfmeGoD820(Object *parent, const Coord3D *pos, int extra);
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

extern GameLogic *TheGameLogic;

class BfmeHeadD820
{
public:
	Object *m_bfmeObject;
	char m_bfmePad[4];
};

class BfmeTailD820
{
public:
	void bfmeTickD820(void);
	void bfmeTailD820(void);

	char m_bfmePad00[0x20];
	int m_bfmeMode;
	char m_bfmePad24[0x9c - 0x24];
	int m_bfmeId;
};

class BfmeBothD820 : public BfmeHeadD820, public BfmeTailD820
{
};

void BfmeTailD820::bfmeTickD820(void)
{
	if (m_bfmeMode == 2)
	{
		Object *parent = static_cast<BfmeBothD820 *>(this)->m_bfmeObject;
		Object *found = TheGameLogic->findObjectByID(m_bfmeId);
		void *mod = parent->m_bfmeMod;
		if (found && mod)
		{
			Coord3D pos;
			pos.x = found->m_bfmePos.x;
			pos.y = found->m_bfmePos.y;
			pos.z = found->m_bfmePos.z;
			BfmeHelpD820 *help = *(BfmeHelpD820 **)((char *)mod + 0x1cc);
			help->bfmeGoD820(parent, &pos, 0);
		}
	}
	bfmeTailD820();
}
