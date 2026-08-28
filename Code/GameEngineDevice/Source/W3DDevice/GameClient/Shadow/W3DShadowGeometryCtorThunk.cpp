// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

#define MAX_SHADOW_CASTER_MESHES 160

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	RefCountClass(void) : NumRefs(1) {}
	void Add_Ref(void) { NumRefs++; }
	int Num_Refs(void) { return NumRefs; }
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

struct AsciiStringData;

// BFME drift: the geometry name is a StringBase-derived string object at +0x10,
// not Zero Hour's inline char[2*W3D_NAME_LEN].
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(void) : m_data(0) {}
	~AsciiString(void);
	const char *str(void) const;

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

class W3DShadowGeometry : public RefCountClass, public HashableClass
{
public:
	W3DShadowGeometry(void);
	~W3DShadowGeometry(void) {}

	virtual const char *Get_Key(void);

private:
	AsciiString m_namebuf;
	W3DShadowGeometryMesh m_meshList[MAX_SHADOW_CASTER_MESHES];
	Int m_meshCount;
	Int m_numTotalsVerts;
};

// ??0W3DShadowGeometry@@QAE@XZ
W3DShadowGeometry::W3DShadowGeometry(void)
{
	m_numTotalsVerts = 0;
	m_meshCount = 0;
}
