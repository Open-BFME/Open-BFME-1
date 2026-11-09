// cl: /O2 /Ob2 /GR- /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS
// The game passes this method a W3DGhostObject pointer four bytes into the object.

class GhostObjectManager
{
public:
	virtual void anchor();
	int m_localPlayer;
};

extern GhostObjectManager *TheGhostObjectManager;

class Snapshot
{
public:
	virtual ~Snapshot();
};

class W3DRenderObjectSnapshot : public Snapshot
{
public:
	void *m_robj;
	W3DRenderObjectSnapshot *m_next;
};

class BfmeThingPA
{
public:
	void bfmeGoPA(int playerIndex);
};

// Retail's restoreParentObject body at 0x006BC7B0 is the ledger row ?bfmeSweepBP@BfmeHostBP.
class BfmeHostBP
{
public:
	void bfmeSweepBP();
};

class W3DGhostObject
{
public:
	virtual void freeSnapShot(int playerIndex);

protected:
	void *m_baseField4;
	void *m_parentObject;
	char m_padding[0x70];
	W3DRenderObjectSnapshot *m_parentSnapshots[32];

};

void W3DGhostObject::freeSnapShot(int playerIndex)
{
	if (playerIndex != TheGhostObjectManager->m_localPlayer)
		return;

	if (m_parentSnapshots[playerIndex])
	{
		((BfmeThingPA *)((char *)this - 4))->bfmeGoPA(playerIndex);
		if (m_parentObject)
			((BfmeHostBP *)((char *)this - 4))->bfmeSweepBP();

		W3DRenderObjectSnapshot *snap = m_parentSnapshots[playerIndex];
		while (snap)
		{
			W3DRenderObjectSnapshot *nextSnap = snap->m_next;
			delete snap;
			snap = nextSnap;
		}
		m_parentSnapshots[playerIndex] = 0;
	}
}
