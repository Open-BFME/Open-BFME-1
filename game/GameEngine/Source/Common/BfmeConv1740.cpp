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

// The 0x012F1464 global is EA's `GameClient *TheGameClient`, defined once in
// GameClient.cpp; only the pointee type may differ per TU, so it is forward
// declared here and this TU's id view is applied at the use.
class GameClient;
extern GameLogic *TheGameLogic;
extern GameClient *TheGameClient;

bool __cdecl bfmeCheckAN(void)
{
	BfmeObjAN *object = TheGameLogic->bfmeFindAN(((ClientRoot4120 *)TheGameClient)->m_bfmeIdAN);

	if (object)
		return object->m_bfmeStateAN->m_bfmeCountAN > 0;

	return false;
}
