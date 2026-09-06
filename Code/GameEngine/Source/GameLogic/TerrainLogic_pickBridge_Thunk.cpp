// cl: /DNDEBUG /MD /EHsc
// stlport
// Retail 0x001AADA0. Pick the first visible bridge intersection.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

class Drawable;
class Object;
typedef int ObjectID;

class Bridge
{
public:
	bool pickBridge(const Vector3 &, const Vector3 &, Vector3 *);

	void *m_vtable;
	Bridge *m_next;
	char m_pad08[0x58];
	ObjectID m_bridgeObjectID;
};

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>,
	_STL::equal_to<ObjectID> > ObjectPtrHash;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id)
	{
		if (id == 0)
			return 0;
		ObjectPtrHash::iterator it = m_objHash.find(id);
		if (it == m_objHash.end())
			return 0;
		return (*it).second;
	}

private:
	char m_pad00[0xb0];
	ObjectPtrHash m_objHash;
};

class Object
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
	virtual Drawable *getDrawable();
};

extern GameLogic *TheGameLogic;

class Pathfinder
{
public:
	bool bfmePickBridge(const Vector3 &, const Vector3 &, Vector3 *);
};

class AI
{
public:
	Pathfinder *pathfinder()
	{
		return *(Pathfinder **)((char *)this + 0xc);
	}
};

extern AI *TheAI;

#pragma comment(linker, "/alternatename:?bfmePickBridge@Pathfinder@@QAE_NABVVector3@@0PAV2@@Z=?d_003d8c40@@YAXXZ")

class TerrainLogic
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
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual Bridge *getFirstBridge();
	virtual bool pickBridge(const Vector3 &, const Vector3 &, Vector3 *);
};

bool TerrainLogic::pickBridge(const Vector3 &from, const Vector3 &to,
	Vector3 *pos)
{
	Drawable *curDraw = 0;
	Vector3 curPos;
	curPos.X = 0;
	curPos.Y = 0;
	curPos.Z = 0;

	Bridge *pBridge = getFirstBridge();
	while (pBridge) {
		Vector3 thisPos;
		bool thisDraw = pBridge->pickBridge(from, to, &thisPos);
		if (thisDraw) {
			Object *bridgeObject = TheGameLogic->findObjectByID(
				pBridge->m_bridgeObjectID);
			Drawable *draw;
			if (bridgeObject) {
				draw = bridgeObject->getDrawable();
			} else {
				draw = 0;
			}
			if (!curDraw) {
				curDraw = draw;
				curPos = thisPos;
			}
		}
		pBridge = pBridge->m_next;
	}
	if (curDraw) {
		pos->X = curPos.X;
		pos->Y = curPos.Y;
		pos->Z = curPos.Z;
		return true;
	}
	Pathfinder *pathfinder = TheAI->pathfinder();
	return pathfinder->bfmePickBridge(from, to, pos);
}
