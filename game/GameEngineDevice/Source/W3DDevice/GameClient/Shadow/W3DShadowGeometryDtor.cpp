// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#define MAX_SHADOW_CASTER_MESHES 160

#include "../../../../../GameEngine/Include/Common/ScalarTypes.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	virtual void Delete_This(void);

protected:
	virtual ~RefCountClass(void) {}

private:
	int NumRefs;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/hash.h
#include "../../../../../Libraries/Source/WWVegas/WWLib/hash.h"

struct AsciiStringData;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
#include "ascii_string.h"

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
