// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Iinputs/reference/shims/sweep
// BFME MeshClass constructors, retail 0x0092C270 and 0x0092CD00.
//
// The matched Rva00970EC0Proto::Load_Mesh caller allocates 0x318 bytes and
// calls the global ??0MeshClass@@QAE@XZ symbol.  Retail constructs an embedded
// LightEnvironmentClass at +0xD0; its exact constructor at 0x0094AAF0 proves
// the 0x228-byte BFME layout below, including the leading byte.  The matched
// MeshClass destructor calls the empty LightEnvironmentClass destructor at
// 0x0094A880 on the same +0xD0 receiver before destroying RenderObjClass.
//
// vtable_lookup identifies 0x0113C390 as MeshClass's RefCountClass-primary
// table and 0x0113C388 as its MultiListObjectClass secondary table.  Both are
// also installed by the matched MeshClass destructor, with the secondary
// deleting-destructor thunk adjusting this by -8.  The production RenderObj
// declaration supplies the reconciled virtual interface; this TU changes only
// the BFME-only Mesh member layout that the shared ZH-derived header lacks.
//
// Primary-vtable slot 2 is the matched body at 0x0092CEF0: it allocates 0x318
// bytes, passes its MeshClass receiver to 0x0092CD00, and returns the result.
// That is the exact shape of the production MeshClass::Clone implementation,
// NEW_REF(MeshClass, (*this)), and names 0x0092CD00 as this copy constructor.
// meshmdl.h supplies the real global MeshModelClass/RefCountClass hierarchy,
// so REF_PTR_SET below carries its actual intrusive-refcount lifetime.  MSVC's
// emitted unwind map destroys the constructed LightEnvironmentClass at +0xD0
// before the RenderObjClass base if that lifetime operation throws.

#include "rendobj.h"
#include "meshmdl.h"

class MeshBuilderClass;
class MeshLoadInfoClass;
class DecalMeshClass;
class MaterialPassClass;
class IndexBufferClass;
class ChunkLoadClass;
struct W3dMeshHeaderStruct;

class LightEnvironmentClass
{
public:
	LightEnvironmentClass(void);
	~LightEnvironmentClass(void);

private:
	struct InputLightStruct
	{
		Vector3 Direction;
		Vector3 Ambient;
		Vector3 Diffuse;
		bool DiffuseRejected;
		bool Point;
		Vector3 Center;
		float InnerRadius;
		float OuterRadius;
		Vector3 PointAmbient;
		Vector3 PointDiffuse;
	};

	struct OutputLightStruct
	{
		Vector3 Direction;
		Vector3 Diffuse;
	};

	unsigned char BfmeLeadingByte;
	int LightCount;
	Vector3 ObjectCenter;
	InputLightStruct InputLights[4];
	Vector3 OutputAmbient;
	OutputLightStruct OutputLights[4];
	InputLightStruct FillLight;
	float FillIntensity;
};

typedef char VerifyLightEnvironmentSize[
	(sizeof(LightEnvironmentClass) == 0x228) ? 1 : -1];

// Retail reads +0x314 as a pointer, null-tests it, and then dereferences its
// first word in MeshClass::Render_Material_Pass.  Its concrete pointee identity
// is not needed by this constructor, so retain only that proven pointer type.
struct MeshRuntimeData;

// upstream identity and virtual interface:
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mesh.h
class MeshClass : public W3DMPO, public RenderObjClass
{
public:
	MeshClass(void);
	MeshClass(const MeshClass &src);
	MeshClass &operator=(const MeshClass &src);
	virtual ~MeshClass(void);

	virtual RenderObjClass *Clone(void) const;
	virtual int Class_ID(void) const;
	virtual const char *Get_Name(void) const;
	virtual void Set_Name(const char *name);
	virtual int Get_Num_Polys(void) const;
	virtual void Render(RenderInfoClass &rinfo);
	void Render_Material_Pass(MaterialPassClass *pass, IndexBufferClass *ib);
	void Special_Render(SpecialRenderInfoClass &rinfo);

	virtual bool Cast_Ray(RayCollisionTestClass &raytest);
	bool Cast_AABox(AABoxCollisionTestClass &boxtest);
	bool Cast_OBBox(OBBoxCollisionTestClass &boxtest);
	virtual bool Intersect_AABox(AABoxIntersectionTestClass &boxtest);
	virtual bool Intersect_OBBox(OBBoxIntersectionTestClass &boxtest);

	virtual void Get_Obj_Space_Bounding_Sphere(SphereClass &sphere) const;
	virtual void Get_Obj_Space_Bounding_Box(AABoxClass &box) const;
	virtual void Scale(float scale);
	virtual void Scale(float scalex, float scaley, float scalez);
	virtual MaterialInfoClass *Get_Material_Info(void);
	virtual int Get_Sort_Level(void) const;
	virtual void Set_Sort_Level(int level);
	virtual void Create_Decal(DecalGeneratorClass *generator, bool unk = false);
	virtual void Delete_Decal(uint32 decal_id);

protected:
	virtual void Add_Dependencies_To_List(
		DynamicVectorClass<StringClass> &file_list, bool textures_only = false);
	virtual void Update_Cached_Bounding_Volumes(void) const;

private:
	MeshModelClass *Model;                 // +0x0C8
	DecalMeshClass *DecalMesh;             // +0x0CC
	LightEnvironmentClass LightEnvironment;// +0x0D0 .. +0x2F7
	float AlphaOverride;                   // +0x2F8
	float MaterialPassEmissiveOverride;    // +0x2FC
	float MaterialPassAlphaOverride;       // +0x300
	int BaseVertexOffset;                  // +0x304
	MeshClass *NextVisibleSkin;            // +0x308
	unsigned int MeshDebugId;              // +0x30C
	bool IsDisabledByDebugger;             // +0x310
	MeshRuntimeData *RuntimeData;           // +0x314
};

typedef char VerifyMeshClassSize[(sizeof(MeshClass) == 0x318) ? 1 : -1];

static unsigned int MeshDebugIdCount;

// ??0MeshClass@@QAE@XZ
MeshClass::MeshClass(void) :
	Model(0),
	DecalMesh(0),
	LightEnvironment(),
	BaseVertexOffset(0),
	NextVisibleSkin(0),
	IsDisabledByDebugger(false),
	MeshDebugId(MeshDebugIdCount++),
	AlphaOverride(1.0f),
	MaterialPassAlphaOverride(1.0f),
	MaterialPassEmissiveOverride(1.0f),
	RuntimeData(0)
{
}

// ??0MeshClass@@QAE@ABV0@@Z
MeshClass::MeshClass(const MeshClass &that) :
	RenderObjClass(that),
	Model(0),
	DecalMesh(0),
	LightEnvironment(),
	BaseVertexOffset(that.BaseVertexOffset),
	NextVisibleSkin(0),
	IsDisabledByDebugger(false),
	MeshDebugId(MeshDebugIdCount++),
	AlphaOverride(1.0f),
	MaterialPassAlphaOverride(1.0f),
	MaterialPassEmissiveOverride(1.0f),
	RuntimeData(0)
{
	REF_PTR_SET(Model, that.Model);
}
