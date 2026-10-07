
// cl: /O2 /Ob1 /DNDEBUG /MD
//
// Retail 0x004120E0 (49B): if counter at 0x012F12F0 is already non-zero, still
// increments it; else if TheGameClient is set, call vslot+0x30, walk the
// returned chain via +0x104 until null, then increment the counter.

class ClientNode4120
{
public:
	char m_pad[0x104];
	ClientNode4120 *m_next;					///< +0x104
};

class ClientRoot4120
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual ClientNode4120 *getHead();		///< slot 12 / +0x30
};

// The 0x012F1464 global is EA's `GameClient *TheGameClient`, defined once in
// GameClient.cpp; only the pointee type may differ per TU, so it is forward
// declared here and this TU's head-list view is applied at the use.
class GameClient;
extern GameClient *TheGameClient;		// 0x012F1464
// 0x012F12F0 is Drawable::s_modelLockCount (dir32_addresses.csv), defined once
// in GameClient/Drawable.cpp; this body is the BFME friend_lockDirtyStuffForIteration
// shape (matched unlock sibling at 0x00412120 decrements the same cell).
void bfmeBumpClientGuard();
class Drawable
{
	friend void bfmeBumpClientGuard();
	static int s_modelLockCount;
};

// ?bfmeBumpClientGuard@@YAXXZ
void bfmeBumpClientGuard()
{
	if (!Drawable::s_modelLockCount)
	{
		ClientRoot4120 *client = (ClientRoot4120 *)TheGameClient;
		if (client)
		{
			ClientNode4120 *n = client->getHead();
			if (n)
			{
				do
				{
					n = n->m_next;
				} while (n);
			}
		}
	}
	++Drawable::s_modelLockCount;
}
