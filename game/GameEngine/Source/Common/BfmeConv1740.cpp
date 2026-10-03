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
};

// The lookup callee is retail's ILT thunk at 0x0001F253, defined in the
// ledger as ?j_0001f253@@YAXXZ (game/gen_small/thunks_014.cpp) and routed by
// a matched caller to GameLogic::findObjectByID.  Reference that name through
// the project-wide thunk convention and apply the callee's __thiscall
// "BfmeObjAN *(int)" shape at the call.
extern void j_0001f253();

typedef BfmeObjAN *(GameLogic::*BfmeFindANCall)(int);

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
	union
	{
		void (*asThunk)(void);
		BfmeFindANCall asFind;
	} callee;

	callee.asThunk = j_0001f253;

	BfmeObjAN *object = (TheGameLogic->*callee.asFind)(((ClientRoot4120 *)TheGameClient)->m_bfmeIdAN);

	if (object)
		return object->m_bfmeStateAN->m_bfmeCountAN > 0;

	return false;
}
