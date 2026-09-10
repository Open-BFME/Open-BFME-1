// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWDebug /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /Ireference/shims/sweep
// BFME MeshClass::Render_Material_Pass uses the BFME member block witnessed by
// bfme_layout.py and the matched MeshClass constructor: the light-environment
// pointer is at +0xCC, the embedded environment starts at +0xD0, and the
// runtime parent pointer is at +0x314.  Keep this mirror local because the
// shared ZH-derived mesh header still models the old decal member at +0xCC.

#define Matrix4x4 Matrix4
#include "winbase_shim.h"
#include "rendobj.h"
#include "meshmdl.h"
#include "meshgeometry.h"
#include "matpass.h"
#include "vertmaterial.h"
#include "dx8wrapper.h"
#define MESH_H
#include "dx8polygonrenderer.h"

class LightEnvironmentClass;
class IndexBufferClass;

extern const float BfmeZeroRange;

struct MeshRuntimeData
{
	RenderObjClass *Parent;
};

class MeshClass : public W3DMPO, public RenderObjClass
{
public:
	void Render_Material_Pass(MaterialPassClass *pass, IndexBufferClass *ib);

private:
	MeshModelClass *Model;                         // +0x0C8
	LightEnvironmentClass *LightEnvironment;      // +0x0CC
	unsigned char LocalLightEnvironment[0x228];   // +0x0D0
	float AlphaOverride;                           // +0x2F8
	float MaterialPassEmissiveOverride;            // +0x2FC
	float MaterialPassAlphaOverride;               // +0x300
	int BaseVertexOffset;                          // +0x304
	MeshClass *NextVisibleSkin;                    // +0x308
	unsigned int MeshDebugId;                      // +0x30C
	bool IsDisabledByDebugger;                     // +0x310
	MeshRuntimeData *RuntimeData;                  // +0x314
};

typedef char VerifyMeshClassRenderLayout[
	(sizeof(MeshClass) == 0x318) ? 1 : -1];

// ?Render_Material_Pass@MeshClass@@QAEXPAVMaterialPassClass@@PAVIndexBufferClass@@@Z
void MeshClass::Render_Material_Pass(MaterialPassClass *pass, IndexBufferClass *ib)
{
	float oldOpacity = -1.0f;
	Vector3 oldEmissive(-1, -1, -1);

	if (LightEnvironment != NULL) {
		DX8Wrapper::Set_Light_Environment(LightEnvironment);
	}

	if (Model->Get_Flag(MeshModelClass::SKIN)) {
		if (MaterialPassAlphaOverride != 1.0f) {
			VertexMaterialClass *mat = pass->Peek_Material();
			if (mat) {
				oldOpacity = mat->Get_Opacity();
				mat->Set_Opacity(MaterialPassAlphaOverride);
			}
		}
		if (MaterialPassEmissiveOverride != 1.0f) {
			VertexMaterialClass *mat = pass->Peek_Material();
			if (mat) {
				mat->Get_Emissive(&oldEmissive);
				mat->Set_Emissive(MaterialPassEmissiveOverride * oldEmissive);
			}
		}

		DX8Wrapper::Set_Index_Buffer(ib, 0);

		if (RuntimeData != NULL && RuntimeData->Parent != NULL) {
			RenderObjClass *parent = RuntimeData->Parent;
			parent->Validate_Transform();
			Matrix3D parent_inverse;
			(reinterpret_cast<Matrix3D *>(reinterpret_cast<unsigned char *>(parent) + 0x18))->Get_Inverse(parent_inverse);
			Validate_Transform();
			Matrix3D world;
			Matrix3D::Multiply(Transform, parent_inverse, &world);
			DX8Wrapper::Set_Transform(D3DTS_WORLD, world);
		} else {
			DX8Wrapper::Set_World_Identity();
		}
		pass->Install_Materials();

		DX8PolygonRendererListIterator it(&Model->PolygonRendererList);
		while (!it.Is_Done()) {
			if (it.Peek_Obj()->Get_Pass() == 0)
				it.Peek_Obj()->Render(BaseVertexOffset);
			it.Next();
		}

		if (oldOpacity >= BfmeZeroRange)
			pass->Peek_Material()->Set_Opacity(oldOpacity);
		if (oldEmissive.X >= BfmeZeroRange)
			pass->Peek_Material()->Set_Emissive(oldEmissive);
		pass->UnInstall_Materials();
	} else {
		if (MaterialPassAlphaOverride != 1.0f) {
			VertexMaterialClass *mat = pass->Peek_Material();
			if (mat) {
				oldOpacity = mat->Get_Opacity();
				mat->Set_Opacity(MaterialPassAlphaOverride);
			}
		}
		if (MaterialPassEmissiveOverride != 1.0f) {
			VertexMaterialClass *mat = pass->Peek_Material();
			if (mat) {
				mat->Get_Emissive(&oldEmissive);
				mat->Set_Emissive(MaterialPassEmissiveOverride * oldEmissive);
			}
		}

		DX8Wrapper::Set_Transform(D3DTS_WORLD, Transform);
		DX8Wrapper::Set_Index_Buffer(ib, 0);
		pass->Install_Materials();

		DX8PolygonRendererListIterator it(&Model->PolygonRendererList);
		while (!it.Is_Done()) {
			if (it.Peek_Obj()->Get_Pass() == 0)
				it.Peek_Obj()->Render(BaseVertexOffset);
			it.Next();
		}

		if (oldOpacity >= BfmeZeroRange)
			pass->Peek_Material()->Set_Opacity(oldOpacity);
		if (oldEmissive.X >= BfmeZeroRange)
			pass->Peek_Material()->Set_Emissive(oldEmissive);
		pass->UnInstall_Materials();
	}
}
