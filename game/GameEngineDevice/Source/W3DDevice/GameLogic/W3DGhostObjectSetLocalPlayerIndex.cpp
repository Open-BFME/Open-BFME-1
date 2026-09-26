// cl: /O2 /Ob2 /GR- /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS
// BFME-layout reconstruction of W3DGhostObjectManager::setLocalPlayerIndex.

class RenderObjClass
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void Remove();
};

class BfmeGlobPB
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void addRenderObject(RenderObjClass *renderObject);
};

extern BfmeGlobPB *g_bfmeGlobPB;

class SnapshotBase
{
public:
	virtual void anchor();
};

class W3DRenderObjectSnapshot : public SnapshotBase
{
public:
	RenderObjClass *m_robj;
	W3DRenderObjectSnapshot *m_next;
};

class GhostObject
{
public:
	virtual void anchor();
	void *m_baseField4;
	void *m_baseField8;
	void *m_parentObject;
	char m_bfmeBasePadding[0x70];
};

class W3DGhostObjectManager;

class W3DGhostObject : public GhostObject
{
public:
	W3DRenderObjectSnapshot *m_parentSnapshots[32];
	char m_drawableInfo[0x10];
	W3DGhostObject *m_nextSystem;
	W3DGhostObject *m_prevSystem;

	friend class W3DGhostObjectManager;

protected:
	void removeParentObject();
	void restoreParentObject();

	void removeFromScene(int playerIndex)
	{
		W3DRenderObjectSnapshot *snap = m_parentSnapshots[playerIndex];
		while (snap)
		{
			snap->m_robj->Remove();
			snap = snap->m_next;
		}
	}

	void addToScene(int playerIndex)
	{
		W3DRenderObjectSnapshot *snap = m_parentSnapshots[playerIndex];
		while (snap)
		{
			g_bfmeGlobPB->addRenderObject(snap->m_robj);
			snap = snap->m_next;
		}
	}
};

class GhostObjectManager
{
public:
	virtual void anchor();

protected:
	int m_localPlayer;
	char m_managerPadding[4];
};

class W3DGhostObjectManager : public GhostObjectManager
{
protected:
	W3DGhostObject *m_freeModules;
	W3DGhostObject *m_usedModules;

public:
	virtual void setLocalPlayerIndex(int index);
};

void W3DGhostObjectManager::setLocalPlayerIndex(int index)
{
	W3DGhostObject *mod = m_usedModules;

	while (mod)
	{
		mod->removeFromScene(m_localPlayer);
		if (mod->m_parentSnapshots[index])
		{
			if (!mod->m_parentSnapshots[m_localPlayer] && mod->m_parentObject)
			{
				mod->removeParentObject();
			}
			mod->addToScene(index);
		}
		else if (mod->m_parentSnapshots[m_localPlayer] && mod->m_parentObject)
		{
			mod->restoreParentObject();
		}

		mod = mod->m_nextSystem;
	}

	m_localPlayer = index;
}
