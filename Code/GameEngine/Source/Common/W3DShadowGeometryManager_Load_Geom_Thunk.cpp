// cl: /DNDEBUG /MD /EHsc
// readable body of ?Load_Geom@W3DShadowGeometryManager@@QAEHPAVRenderObjClass@@PBD@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadow.cpp
// Open-BFME5: clean C++ reconstruction of W3DShadowGeometryManager::Load_Geom.

typedef bool Bool;
#define FALSE false
#define TRUE true
#ifndef NULL
#define NULL 0
#endif

extern "C" unsigned int __cdecl strlen(const char *text);
#pragma intrinsic(strlen)

// BFME's RefCountClass keeps the count immediately after its primary vptr.
// Release_Ref is inline in the retail build, while Delete_This occupies the
// first virtual slot.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	RefCountClass(void) : NumRefs(1) {}
	void Add_Ref(void) { NumRefs++; }
	void Release_Ref(void)
	{
		NumRefs--;
		if (NumRefs == 0)
			Delete_This();
	}
	virtual void Delete_This(void);

protected:
	virtual ~RefCountClass(void) {}

private:
	int NumRefs;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/hash.h
class HashableClass
{
public:
	HashableClass(void) : NextHash(0) {}
	virtual ~HashableClass(void) {}
	virtual const char *Get_Key(void) = 0;

private:
	HashableClass *NextHash;
};

// The BFME StringBase header is eight bytes (refcount, length, capacity), so
// its character data begins at m_data+8.  set() remains an out-of-line call;
// str() is the tiny accessor inlined by the retail compiler.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
struct AsciiStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	char data[1];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(void) : m_data(0) {}
	~AsciiString(void);
	void set(const char *text, int length);
	const char *str(void) const
	{
		static const char nullCharacter = 0;
		return m_data ? (const char *)((const char *)m_data + 8) : &nullCharacter;
	}

private:
	AsciiStringData *m_data;
};

class W3DShadowGeometryMesh
{
public:
	W3DShadowGeometryMesh(void);
	~W3DShadowGeometryMesh(void);

private:
	int m_opaque[13];
};

class W3DShadowGeometry;

// Only the two virtual slots reached by this body are named.  The class-id
// slot is +0x0c and the mesh model accessor is +0x14 in BFME's RenderObjClass
// vtable.
class RenderObjClass
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual int Class_ID(void);
	virtual void slot10(void);
	virtual RenderObjClass *Get_Model(int lod, W3DShadowGeometry *owner);
};

class W3DShadowGeometry : public RefCountClass, public HashableClass
{
public:
	W3DShadowGeometry(void);
	~W3DShadowGeometry(void);

	virtual const char *Get_Key(void) { return m_namebuf.str(); }

	int initFromHLOD(RenderObjClass *robj);
	int initFromMesh(RenderObjClass *robj);

	const char *Get_Name(void) const { return m_namebuf.str(); }
	void Set_Name(const char *name)
	{
		AsciiString *namebuf = &m_namebuf;
		int length = name ? (int)strlen(name) : 0;
		namebuf->set(name, length);
	}

private:
	AsciiString m_namebuf;
	W3DShadowGeometryMesh m_meshList[160];
	int m_meshCount;
	int m_numTotalsVerts;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/hash.h
class HashTableClass
{
public:
	HashableClass *Find(const char *key);
	void Add(HashableClass *entry);
};

class W3DShadowGeometryManager
{
public:
	int Load_Geom(RenderObjClass *robj, const char *name);

	W3DShadowGeometry *Peek_Geom(const char *name)
	{
		return (W3DShadowGeometry *)GeomPtrTable->Find(name);
	}

	Bool Add_Geom(W3DShadowGeometry *new_geom)
	{
		new_geom->Add_Ref();
		GeomPtrTable->Add(new_geom);
		return TRUE;
	}

private:
	HashTableClass *GeomPtrTable;
};

// ?Load_Geom@W3DShadowGeometryManager@@QAEHPAVRenderObjClass@@PBD@Z
int W3DShadowGeometryManager::Load_Geom(RenderObjClass *robj, const char *name)
{
	Bool res = FALSE;
	W3DShadowGeometry *newgeom = new W3DShadowGeometry;

	if (newgeom == NULL)
	{
		goto Error;
	}

	newgeom->Set_Name(name);

	switch (robj->Class_ID())
	{
		case 25:
			res = newgeom->initFromHLOD(robj);
			break;
		case 0:
			res = newgeom->initFromMesh(robj->Get_Model(-1, newgeom));
			break;
		default:
			break;
	}

	if (res != TRUE)
	{
		newgeom->Release_Ref();
		goto Error;
	}
	else if (Peek_Geom(newgeom->Get_Name()) != NULL)
	{
		newgeom->Release_Ref();
		goto Error;
	}
	else
	{
		Add_Geom(newgeom);
		newgeom->Release_Ref();
	}

	return 0;

Error:
	return 1;
}
