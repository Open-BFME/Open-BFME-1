class BfmeStateAN
{
public:
	unsigned char m_bfmeHeadAN[0x20];
	int m_bfmeCountAN;
};

class BfmeObjAN
{
public:
	unsigned char m_bfmeHeadAN[0x210];
	BfmeStateAN *m_bfmeStateAN;
};

class GameLogic
{
public:
	BfmeObjAN *bfmeFindAN(int id);
};

class ClientRoot4120
{
public:
	unsigned char m_bfmeHeadAN[0xb4];
	int m_bfmeIdAN;
};

extern GameLogic *TheBfmeGameLogic;
extern ClientRoot4120 *TheGameClient;

bool __cdecl bfmeCheckAN(void)
{
	BfmeObjAN *object = TheBfmeGameLogic->bfmeFindAN(TheGameClient->m_bfmeIdAN);

	if (object)
		return object->m_bfmeStateAN->m_bfmeCountAN > 0;

	return false;
}
