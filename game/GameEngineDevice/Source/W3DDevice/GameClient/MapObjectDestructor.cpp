// ??1MapObject@@MAE@XZ -- retail RVA 0x00088350, 236 bytes.
//
// IDENTITY. The name is the lift's and it is proven, not assumed: the body
// installs vtable 0x0107C7E0, the same vtable the MATCHED constructor
// ??0MapObject@@QAE@UCoord3D@@VAsciiString@@MHPBVDict@@PBVThingTemplate@@@Z
// (0x00088160) installs, and the MATCHED deleting destructor is reached
// through the vtable slot this very class declares.
//
// WHY A SEPARATE TU. WorldHeightMap.cpp includes the Zero Hour MapObject.h,
// whose member order puts m_nextMapObject at +0x1C; retail puts it at +0x04
// (this body's list walk) and every later member four bytes lower, so
// m_location lands at +0x08 and m_properties at +0x24. The reference header
// is vendored, so retail's layout is declared here instead -- the same
// TU-scoped shim the other landed MapObject methods use.
// cl: /DNDEBUG /MD /EHsc

typedef long Long;
typedef int Int;
typedef unsigned int AudioHandle;
typedef float Real;

// The decrement retail performs through the import slot at 0x01358E54.
extern "C" __declspec(dllimport) Long __stdcall InterlockedDecrement(Long volatile *addend);

class RenderObjClass;
class Shadow;
class ThingTemplate;

// WWLib/refcount.h: Release_Ref() is `NumRefs--; if (NumRefs == 0) Delete_This();`
// and vtable slot 0 of a W3D ref-counted object is the no-argument virtual the
// release calls -- retail's `call [eax]`, with no delete flag.
class RenderObjClass
{
public:
	virtual void Delete_This(void) { delete this; }
	void Add_Ref(void) { ++NumRefs; }
	void Release_Ref(void)
	{
		if (--NumRefs == 0)
			Delete_This();
	}
	Int NumRefs;
};

#define REF_PTR_SET(dst,src)	{ if (src) (src)->Add_Ref(); if (dst) (dst)->Release_Ref(); (dst) = (src); }
#define REF_PTR_RELEASE(x)		{ if (x) x->Release_Ref(); x = 0; }

// The narrow string is one pointer wide here and owns an out-of-line
// releaseBuffer on its base (matched at 0x00887940, private, so the name must
// be the real one or the call would not resolve).
template <typename T> class StringBase
{
	friend class AsciiString;
private:
	void releaseBuffer();
	void *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	~AsciiString() { releaseBuffer(); }
};

// One pointer wide, like retail's (this body only calls its out-of-line
// releaseData, matched at 0x000681C0 through the thunk 0x00014475).
class Dict
{
public:
	~Dict() { releaseData(); }
private:
	void releaseData();							///< matched at 0x000681C0.
	void *m_data;
};

// The referent at +0x5C is a differently-shaped ref-counted object from the
// W3D ones above: its vtable slot 0 is the destructor, so dropping the last
// reference is `push 1; call [p]`, not the flagless `call [eax]`.
class Rva00088350RefTarget
{
public:
	virtual ~Rva00088350RefTarget() {}
	Long m_refCount;
};

// One pointer wide, and its destructor is the conditional release this body
// carries as its third EH state: decrement the referent's count and, when it
// reaches zero, delete it. It does NOT null itself afterwards -- retail
// stores nothing back to +0x5C (its 0x00087C30 twin does).
class Rva00088350RefPtr
{
public:
	~Rva00088350RefPtr()
	{
		if (m_ptr)
		{
			Rva00088350RefTarget *p = m_ptr;
			Long refs = InterlockedDecrement(&p->m_refCount);
			if (refs <= 0)
				delete p;
		}
	}
private:
	Rva00088350RefTarget *m_ptr;
};

// Retail calls exactly one unidentified void method on `this` after the
// bridge-tower sweep and before any member destructor. The build carries a
// body for it at retail RVA 0x00087C30 under an address-derived class name
// (it releases the two audio handles at +0x54/+0x58 and drops the reference
// at +0x5C, exactly as its disassembly shows), so the call binds to that.
class Gen00087C30_00088480
{
public:
	void gen00087C30();
};

enum { BRIDGE_MAX_TOWERS = 4 };
enum BridgeTowerType { BRIDGE_TOWER_FIRST = 0 };

// The vptr lives in this base, not in MapObject: the body installs
// 0x0107C7E0 on entry and 0x0107C7DC -- a one-slot vtable whose slot 0 is a
// jump thunk -- on the way out, which is the compiler restoring the base
// vtable after the last destructor has run.
class MapObjectBase
{
public:
	virtual ~MapObjectBase() {}
};

class MapObject : public MapObjectBase
{
public:
	MapObject *getNext(void) const { return m_nextMapObject; }
	void setNextMap(MapObject *nextMap) { m_nextMapObject = nextMap; }
	void setRenderObj(RenderObjClass *pObj) { REF_PTR_SET(m_renderObj, pObj); }
	void setShadowObj(Shadow *pObj) { m_shadowObj = pObj; }
	void setBridgeRenderObject(BridgeTowerType type, RenderObjClass *renderObj)
	{
		if (type >= 0 && type < BRIDGE_MAX_TOWERS)
			REF_PTR_RELEASE(m_bridgeTowers[type]);
	}

protected:
	virtual ~MapObject();

private:
	MapObject *m_nextMapObject;					///< +0x04 linked list.
	char m_pad08[0x0C];							///< +0x08 m_location, Coord3D.
	AsciiString m_objectName;					///< +0x14
	const ThingTemplate *m_thingTemplate;		///< +0x18
	Real m_angle;								///< +0x1C
	Int m_flags;								///< +0x20
	Dict m_properties;							///< +0x24
	Int m_color;								///< +0x28
	RenderObjClass *m_renderObj;				///< +0x2C
	Shadow *m_shadowObj;						///< +0x30
	RenderObjClass *m_bridgeTowers[BRIDGE_MAX_TOWERS];	///< +0x34
	Int m_runtimeFlags;							///< +0x44
	char m_pad48[0x0C];							///< +0x48, unwritten by retail
	AudioHandle m_rva54;						///< +0x54, set true
	AudioHandle m_rva58;						///< +0x58, set true
	Rva00088350RefPtr m_rva5c;					///< +0x5C, set null
};

MapObject::~MapObject(void)
{
	setRenderObj(0);
	setShadowObj(0);
	if (m_nextMapObject) {
		MapObject *cur = m_nextMapObject;
		MapObject *next;
		while (cur) {
			next = cur->getNext();
			cur->setNextMap(0); // prevents recursion.
			delete cur;
			cur = next;
		}
	}
	for( Int i = 0; i < BRIDGE_MAX_TOWERS; ++i )
		setBridgeRenderObject( (BridgeTowerType)i, 0 );

	reinterpret_cast<Gen00087C30_00088480 *>(this)->gen00087C30();
}
