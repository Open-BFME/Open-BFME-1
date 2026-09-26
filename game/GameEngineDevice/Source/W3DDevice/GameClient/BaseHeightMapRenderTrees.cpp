// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// Retail 0x006CD990, complete boundary [0x006CD990,0x006CDCA6).
// DoTrees at 0x006CDF50 calls the public renderTrees ILT at 0x0003FE36;
// PhysicsRenderThunks.cpp forwards that public method to this direct body.
// BFME's terrain owner differs from the Zero Hour layout: Scene remains at
// RenderObjClass+0x80, while the material and two draw buffers are at
// +0x304C, +0x3094, and +0x3098 respectively.

#define Matrix4x4 Matrix4
#include "winbase_shim.h"
#include "rendobj.h"
#include "scene.h"
#include "dx8wrapper.h"

struct Rva006CD990GlobalData
{
	unsigned char m_unmodeled00[0x3b];
	unsigned char m_useTrees;
};

extern Rva006CD990GlobalData *TheWritableGlobalData;

class W3DTreeBuffer
{
public:
	void drawTrees(CameraClass *camera,
		RefMultiListIterator<RenderObjClass> *dynamicLights);

	unsigned char m_observedBody[0x2a98fc];
	unsigned char m_anyPushChanged;
};

// The second BFME-only buffer has a distinct, 0x1E1CD0-byte layout.  Its
// public class name has not been recovered, but the call at +0x308 proves the
// same CameraClass/RefRenderObjListIterator ABI and target body 0x0071EEC0.
class Rva0071EEC0Buffer
{
public:
	void rva0071EEC0(CameraClass *camera,
		RefMultiListIterator<RenderObjClass> *dynamicLights);

	unsigned char m_observedBody[0x1e1cd0];
	unsigned char m_renderEnabled;
};

class BfmeRTS3DScene : public SceneClass
{
public:
	RefMultiListClass<RenderObjClass> *getDynamicLights(void)
	{
		return &m_dynamicLights;
	}

private:
	unsigned char m_unmodeledScene[0x110 - sizeof(SceneClass)];
	RefMultiListClass<RenderObjClass> m_dynamicLights;
};

class BaseHeightMapRenderObjClass : public RenderObjClass
{
protected:
	void rva006C96B0(void);

	unsigned char m_unmodeledBaseHeightMap[0x2ff4 - sizeof(RenderObjClass)];
	void *m_map;                                      // +0x2FF4
	unsigned char m_unmodeled2FF8[0x304c - 0x2ff8];
	VertexMaterialClass *m_vertexMaterialClass;       // +0x304C
	unsigned char m_unmodeled3050[0x3094 - 0x3050];
	W3DTreeBuffer *m_treeBuffer;                      // +0x3094
	Rva0071EEC0Buffer *m_buffer3098;                  // +0x3098
};

// The already matched public method is a five-byte ILT-forwarding TU.  This
// class supplies its established direct-body symbol without changing the
// underlying BaseHeightMapRenderObjClass receiver or data layout.
class BaseHeightMapRenderTreesShim : public BaseHeightMapRenderObjClass
{
public:
	void render(CameraClass *camera);
};

void BaseHeightMapRenderTreesShim::render(CameraClass *camera)
{
	if (!m_map || !Scene || !TheWritableGlobalData->m_useTrees)
		return;

	if (m_treeBuffer) {
		Matrix3D transform(Transform);
		DX8Wrapper::Set_Transform(D3DTS_WORLD, transform);
		DX8Wrapper::Set_Material(m_vertexMaterialClass);

		BfmeRTS3DScene *scene = static_cast<BfmeRTS3DScene *>(Scene);
		RefMultiListIterator<RenderObjClass> dynamicLights(
			scene->getDynamicLights());
		m_treeBuffer->drawTrees(camera, &dynamicLights);
		if (m_treeBuffer->m_anyPushChanged)
			rva006C96B0();
	}

	if (m_buffer3098) {
		Matrix3D transform(Transform);
		DX8Wrapper::Set_Transform(D3DTS_WORLD, transform);
		DX8Wrapper::Set_Material(m_vertexMaterialClass);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILENABLE, 0);

		BfmeRTS3DScene *scene = static_cast<BfmeRTS3DScene *>(Scene);
		RefMultiListIterator<RenderObjClass> dynamicLights(
			scene->getDynamicLights());
		m_buffer3098->rva0071EEC0(camera, &dynamicLights);
	}
}
