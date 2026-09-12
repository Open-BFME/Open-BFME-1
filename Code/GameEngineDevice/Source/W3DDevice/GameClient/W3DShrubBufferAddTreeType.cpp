// ?addTreeType@W3DShrubBuffer@@QAEHABVAsciiString@@0PBXH00@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
//
// BFME's shrub-type insertion. The owner is proven by the destructor at
// RVA 0x007206E0: vtable 0x01120F94 slot +8 reaches 0x007207E0, which
// returns "W3DShrubBuffer". Its type array/count are +0x1E1CD4/+0x1E33D4.
// The texture set/concat pair proves textureName at +0x48, followed by
// modelName at +0x4C and the remaining names at +0x50/+0x54.
// Keep the real inline WWMath constructors visible: treating SphereClass
// construction as opaque changes the x87 lifetime of the translated center.

typedef int Int;
typedef float Real;
typedef unsigned char UnsignedByte;

class MeshClass;
class RenderObjClass;

#include "vector3.h"
#include "matrix3d.h"
#include "sphere.h"
#include "aabox.h"

// The BFME narrow string owns one reference-counted data pointer. The
// copy-set target is the matched StringBase<char> body at RVA 0x00887C90.
template <typename T> struct TreeStringData
{
    int m_refCount;
    int m_length;
    T m_text[1];
};

template <typename T> class StringBase
{
public:
    void set(const StringBase<T> &other);
protected:
    TreeStringData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    void set(const AsciiString &other) { StringBase<char>::set(other); }
    void concat(const char *text);
    const char *str(void) const { return m_data ? m_data->m_text : ""; }
};

class Rva0071EB50TreeType
{
public:
	MeshClass *m_mesh;
	Vector3 m_offset;
	SphereClass m_bounds;
	const void *m_data;
	unsigned char m_gap0024[0x44 - 0x24];
	UnsignedByte m_doShadow;
	UnsignedByte m_pad0045[3];
	AsciiString m_textureName;
	AsciiString m_modelName;
	AsciiString m_nameC;
	AsciiString m_nameD;
	Int m_field0058;
};

struct Rva0071EB50VertexBuffer
{
	unsigned char m_head[0x0c];
	Vector3 *m_array;
};

struct Rva0071EB50Model
{
	unsigned char m_head[0x28];
	Int m_vertexCount;
	unsigned char m_gap002c[4];
	Rva0071EB50VertexBuffer *m_vertexBuffer;

	Int Get_Vertex_Count(void) const { return m_vertexCount; }
	Vector3 *Get_Vertex_Array(void) const { return m_vertexBuffer->m_array; }
};

class RenderObjClass
{
public:
	virtual void Delete_This(void) = 0;
	virtual void renderObjSlot04(void) = 0;
	virtual void renderObjSlot08(void) = 0;
	virtual Int Class_ID(void) const = 0;
	virtual void renderObjSlot10(void) = 0;
	virtual MeshClass *As_Mesh(void) = 0;
	virtual void renderObjSlot18(void) = 0;
	virtual void renderObjSlot1C(void) = 0;
	virtual void renderObjSlot20(void) = 0;
	virtual void renderObjSlot24(void) = 0;
	virtual void renderObjSlot28(void) = 0;
	virtual void renderObjSlot2C(void) = 0;
	virtual void renderObjSlot30(void) = 0;
	virtual void renderObjSlot34(void) = 0;
	virtual void renderObjSlot38(void) = 0;
	virtual void renderObjSlot3C(void) = 0;
	virtual void renderObjSlot40(void) = 0;
	virtual void renderObjSlot44(void) = 0;
	virtual void renderObjSlot48(void) = 0;
	virtual void renderObjSlot4C(void) = 0;
	virtual const Matrix3D &Get_Transform(void) const = 0;
	virtual void renderObjSlot54(void) = 0;
	virtual void renderObjSlot58(void) = 0;
	virtual void renderObjSlot5C(void) = 0;
	virtual void renderObjSlot60(void) = 0;
	virtual void renderObjSlot64(void) = 0;
	virtual void renderObjSlot68(void) = 0;
	virtual void renderObjSlot6C(void) = 0;
	virtual void renderObjSlot70(void) = 0;
	virtual RenderObjClass *Get_Sub_Object(Int index) const = 0;
	virtual void renderObjSlot78(void) = 0;
	virtual void renderObjSlot7C(void) = 0;
	virtual void renderObjSlot80(void) = 0;
	virtual void renderObjSlot84(void) = 0;
	virtual void renderObjSlot88(void) = 0;
	virtual void renderObjSlot8C(void) = 0;
	virtual void renderObjSlot90(void) = 0;
	virtual void renderObjSlot94(void) = 0;
	virtual void renderObjSlot98(void) = 0;
	virtual void renderObjSlot9C(void) = 0;
	virtual void renderObjSlotA0(void) = 0;
	virtual void renderObjSlotA4(void) = 0;
	virtual void renderObjSlotA8(void) = 0;
	virtual void renderObjSlotAC(void) = 0;
	virtual void renderObjSlotB0(void) = 0;
	virtual void renderObjSlotB4(void) = 0;
	virtual void renderObjSlotB8(void) = 0;
	virtual void renderObjSlotBC(void) = 0;
	virtual void renderObjSlotC0(void) = 0;
	virtual void renderObjSlotC4(void) = 0;
	virtual const Matrix3D &Get_Bone_Transform(Int index) const = 0;
	virtual void renderObjSlotCC(void) = 0;
	virtual void renderObjSlotD0(void) = 0;
	virtual void renderObjSlotD4(void) = 0;
	virtual void renderObjSlotD8(void) = 0;
	virtual void renderObjSlotDC(void) = 0;
	virtual void renderObjSlotE0(void) = 0;
	virtual void renderObjSlotE4(void) = 0;
	virtual void renderObjSlotE8(void) = 0;
	virtual void renderObjSlotEC(void) = 0;
	virtual void renderObjSlotF0(void) = 0;
	virtual void renderObjSlotF4(void) = 0;
	virtual void renderObjSlotF8(void) = 0;
	virtual void renderObjSlotFC(void) = 0;
	virtual void renderObjSlot100(void) = 0;
	virtual void renderObjSlot104(void) = 0;
	virtual void renderObjSlot108(void) = 0;
	virtual void Get_Obj_Space_Bounding_Box(AABoxClass &box) const = 0;

	void Release_Ref(void)
	{
		--m_refCount;
		if (m_refCount == 0)
			Delete_This();
	}

	Int m_refCount;
};

class MeshClass : public RenderObjClass
{
public:
	Rva0071EB50Model *Peek_Model(void) const { return m_model; }

	unsigned char m_meshGap[0xC8 - 8];
	Rva0071EB50Model *m_model;
};

extern RenderObjClass *Create_Render_Obj(const char *name);

class W3DShrubBuffer
{
public:
	Int addTreeType(const AsciiString &modelName, const AsciiString &nameC,
		const void *data, Int shadowKind, const AsciiString &textureName,
		const AsciiString &nameD);

	unsigned char m_head[0x1e1cd1];
	UnsignedByte m_needToUpdateTexture;
	UnsignedByte m_pad1e1cd2[2];
	Rva0071EB50TreeType m_treeTypes[64];
	Int m_numTreeTypes;
};

// ?addTreeType@W3DShrubBuffer@@QAEHABVAsciiString@@0PBXH00@Z
Int W3DShrubBuffer::addTreeType(const AsciiString &modelName,
	const AsciiString &nameC, const void *data, Int shadowKind,
	const AsciiString &textureName, const AsciiString &nameD)
{
	if (m_numTreeTypes >= 64) {
		return 0;
	}
	m_needToUpdateTexture = 1;

	if (m_treeTypes[m_numTreeTypes].m_mesh != 0) {
		m_treeTypes[m_numTreeTypes].m_mesh->Release_Ref();
		m_treeTypes[m_numTreeTypes].m_mesh = 0;
	}

	RenderObjClass *robj = Create_Render_Obj(modelName.str());

	if (robj == 0) {
		return 0;
	}
	AABoxClass box;

	robj->Get_Obj_Space_Bounding_Box(box);
	Vector3 offset(0, 0, 0);
	if (robj->Class_ID() == 0x19) {
		RenderObjClass *hlod = robj;
		robj = hlod->Get_Sub_Object(0);
		const Matrix3D xfm = robj->Get_Bone_Transform(0);
		xfm.Get_Translation(&offset);
		hlod->Release_Ref();
	}

	if (robj->Class_ID() == 0)
		m_treeTypes[m_numTreeTypes].m_mesh = robj->As_Mesh();

	MeshClass *mesh = m_treeTypes[m_numTreeTypes].m_mesh;
	if (mesh == 0) {
		robj->Release_Ref();
		return 0;
	}

	Int numVertex = mesh->Peek_Model()->Get_Vertex_Count();
	Vector3 *pVert = mesh->Peek_Model()->Get_Vertex_Array();

	const Matrix3D xfm = mesh->Get_Transform();
	SphereClass bounds(pVert, numVertex);
	SphereClass &destBounds = m_treeTypes[m_numTreeTypes].m_bounds;
	bounds.Center += offset;
	destBounds = bounds;
	m_treeTypes[m_numTreeTypes].m_data = data;
	m_treeTypes[m_numTreeTypes].m_offset = offset;
	m_treeTypes[m_numTreeTypes].m_doShadow = (shadowKind == 1);
	m_treeTypes[m_numTreeTypes].m_textureName.set(textureName);
	m_treeTypes[m_numTreeTypes].m_textureName.concat(".tga");
	m_treeTypes[m_numTreeTypes].m_modelName.set(modelName);
	m_treeTypes[m_numTreeTypes].m_nameC.set(nameC);
	m_treeTypes[m_numTreeTypes].m_nameD.set(nameD);
	// Retail initializes this per-type sentinel after the string fields.
	m_treeTypes[m_numTreeTypes].m_field0058 = -2;
	m_numTreeTypes++;
	return m_numTreeTypes - 1;
}
