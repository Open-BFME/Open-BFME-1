// cl: /O2 /Ob2 /GR- /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS
// BFME layout reconstruction of W3DGhostObject::snapShot at retail RVA 0x006BDE00.

class Drawable;
class DrawModule;
class RenderObjClass;

class GhostObjectManager
{
public:
	virtual void anchor();
	int m_localPlayer;
	int m_padding;
	int getLocalPlayerIndex() const { return m_localPlayer; }
};

extern GhostObjectManager *TheGhostObjectManager;

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
	virtual void slot0A();
	virtual void slot0B();
	virtual void slot0C();
	virtual void slot0D();
	virtual void slot0E();
	virtual void slot0F();
	virtual void Remove();
};

class DrawModule
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual bool getObjectDrawInterface();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6C();
	virtual void slot70();
	virtual void slot74();
	virtual void slot78();
	virtual void slot7C();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void slot8C();
	virtual void slot90();
	virtual void slot94();
	virtual void slot98();
	virtual void slot9C();
	virtual void slotA0();
	virtual void slotA4();
	virtual void slotA8();
	virtual void slotAC();
	virtual void slotB0();
	virtual void slotB4();
	virtual RenderObjClass *getRenderObject();
};

class Drawable
{
public:
	void **getDrawModules();
	bool isDrawableEffectivelyHidden() const;
};

struct DrawableInfo
{
	void *field0;
	void *drawable;
	void *ghostObject;
	void *fieldC;
};

struct BfmeCopyElementA
{
public:
	BfmeCopyElementA *bfmeAssign(BfmeCopyElementA *other);
	char storage[0x5c];
};

class Object
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual Drawable *getDrawable();
	char padding[0x34];
	struct GeometryValues
	{
		unsigned int type;
		unsigned int small;
		unsigned int majorRadius;
	};
	unsigned int geometryType;
	unsigned int geometrySmall;
	unsigned int geometryMajorRadius;
	unsigned int geometryMinorRadius;
	unsigned int geometryAngle;
	char padding2[0x60];
	BfmeCopyElementA geometryInfo;

	unsigned int getGeometryType() const { return geometryType; }
	unsigned int getGeometrySmall() const { return geometrySmall; }
	unsigned int getGeometryMajorRadius() const { return geometryMajorRadius; }
	unsigned int getGeometryMinorRadius() const { return geometryMinorRadius; }
	unsigned int getGeometryAngle() const { return geometryAngle; }
	GeometryValues *getGeometryValues() { return (GeometryValues *)&geometryType; }
	BfmeCopyElementA *getGeometryInfo() { return &geometryInfo; }
	unsigned int *getPosition() { return &geometryType; }
};

class SnapshotBase
{
public:
	virtual void anchor();
};

class W3DGhostObject;

class W3DRenderObjectSnapshot : public SnapshotBase
{
private:
	W3DRenderObjectSnapshot(RenderObjClass *robj, DrawableInfo *drawInfo, bool cloneParentRobj = true);
	void update(RenderObjClass *robj, DrawableInfo *drawInfo, bool cloneParentRobj = true);
	friend class W3DGhostObject;

public:
	RenderObjClass *m_robj;
	W3DRenderObjectSnapshot *m_next;
};

class BfmeScene
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void addRenderObject(RenderObjClass *renderObject);
};

extern BfmeScene *g_bfmeGlobPB;

class W3DGhostObject
{
public:
	virtual void snapShot(int playerIndex);
	void *baseField4;
	Object *m_parentObject;
	Object::GeometryValues m_parentGeometry;
	unsigned int m_parentGeometryMinorRadius;
	BfmeCopyElementA m_geometryInfo;
	unsigned int baseField7c;
	W3DRenderObjectSnapshot *m_parentSnapshots[32];
	DrawableInfo m_drawableInfo;
};

void W3DGhostObject::snapShot(int playerIndex)
{
	if (playerIndex != TheGhostObjectManager->getLocalPlayerIndex())
		return;

	Drawable *draw = m_parentObject->getDrawable();
	if (draw->isDrawableEffectivelyHidden())
		return;

	W3DRenderObjectSnapshot *snap = m_parentSnapshots[playerIndex];
	W3DRenderObjectSnapshot *prevSnap = 0;

	for (DrawModule **dm = (DrawModule **)draw->getDrawModules(); *dm; ++dm)
	{
		RenderObjClass *robj = (*dm)->getRenderObject();
		if (robj)
		{
			if (snap == 0)
			{
				snap = new W3DRenderObjectSnapshot(robj, &m_drawableInfo);
				if (prevSnap)
					prevSnap->m_next = snap;
				else
					m_parentSnapshots[playerIndex] = snap;
			}
			else
			{
				m_parentSnapshots[playerIndex]->update(robj, &m_drawableInfo);
			}

			if (playerIndex == TheGhostObjectManager->getLocalPlayerIndex())
			{
				robj->Remove();
				if (!(*dm)->getObjectDrawInterface())
					g_bfmeGlobPB->addRenderObject(snap->m_robj);
			}

			prevSnap = snap;
			snap = snap->m_next;
		}
	}

	if (snap != m_parentSnapshots[playerIndex])
	{
		m_geometryInfo.bfmeAssign(m_parentObject->getGeometryInfo());
		m_parentGeometry = *m_parentObject->getGeometryValues();
		m_parentGeometryMinorRadius = m_parentObject->getGeometryMinorRadius();
	}
}
