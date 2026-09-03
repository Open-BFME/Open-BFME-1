// cl: /DNDEBUG /MD /EHsc

#define MAX_SHADOW_CASTER_MESHES 160

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
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
	virtual ~HashableClass(void) {}
	virtual const char *Get_Key(void) = 0;

private:
	HashableClass *NextHash;
};

struct AsciiStringData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(void);
	~AsciiString(void);

private:
	AsciiStringData *m_data;
};

class W3DShadowGeometryMesh
{
public:
	~W3DShadowGeometryMesh(void);

private:
	int m_opaque[13];
};

class W3DShadowGeometry : public RefCountClass, public HashableClass
{
public:
	~W3DShadowGeometry(void);
	virtual const char *Get_Key(void);

private:
	AsciiString m_namebuf;
	W3DShadowGeometryMesh m_meshList[MAX_SHADOW_CASTER_MESHES];
	Int m_meshCount;
	Int m_numTotalsVerts;
};

W3DShadowGeometry::~W3DShadowGeometry(void)
{
}
