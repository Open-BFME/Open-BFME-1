// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Oy /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4

#include "W3DDevice/GameClient/heightmap.h"
#include "W3DDevice/GameClient/W3DWaterTracks.h"
#include "GameClient/InGameUI.h"
#include "common/GlobalData.h"
#include "WW3D2/DX8Wrapper.h"
#include "rinfo.h"
#include "camera.h"

void TestWaterUpdate(void);
extern void j_00015e47();
extern void j_000371dc();

struct WaterTracksRenderSystemUpdateCall
{
	void call();
};

struct WaterTracksObjRenderCall
{
	Int call(DX8VertexBufferClass *, Int, RenderInfoClass &);
};

static void callWaterTracksUpdate(WaterTracksRenderSystem *system)
{
	typedef void (WaterTracksRenderSystemUpdateCall::*Call)();
	union { void (*function)(); Call member; } target;
	target.function = j_00015e47;
	(reinterpret_cast<WaterTracksRenderSystemUpdateCall *>(system)->*target.member)();
}

static Int callWaterTracksRender(WaterTracksObj *object,
	DX8VertexBufferClass *vertexBuffer, Int batchStart, RenderInfoClass &rinfo)
{
	typedef Int (WaterTracksObjRenderCall::*Call)(DX8VertexBufferClass *, Int, RenderInfoClass &);
	union { void (*function)(); Call member; } target;
	target.function = j_000371dc;
	return (reinterpret_cast<WaterTracksObjRenderCall *>(object)->*target.member)(vertexBuffer, batchStart, rinfo);
}

void BaseHeightMapScorchSetShader(const ShaderClass &shader);
void BaseHeightMapScorchSetZBias(Int bias);
void BoxSetTexture(unsigned stage, TextureBaseClass *&texture);

struct WaterTracksGlobalDataView
{
	char padding[0x8d];
	UnsignedByte m_usingWaterTrackEditor;
};

void WaterTracksRenderSystem::flush(RenderInfoClass &rinfo)
{
	WaterTracksGlobalDataView *globalData =
		reinterpret_cast<WaterTracksGlobalDataView *>(TheWritableGlobalData);
	if (globalData->m_usingWaterTrackEditor)
		TestWaterUpdate();

	callWaterTracksUpdate(this);
	rinfo.Camera.Apply();

	if (!m_usedModules || ShaderClass::Is_Backface_Culling_Inverted())
		return;

	m_batchStart = 0xffff;

	Matrix3D tm(1);
	DX8Wrapper::Set_Transform(D3DTS_WORLD, tm);
	DX8Wrapper::Set_Material(m_vertexMaterialClass);
	BaseHeightMapScorchSetShader(m_shaderClass);
	DX8Wrapper::Set_Vertex_Buffer(m_vertexBuffer);
	BaseHeightMapScorchSetZBias(8);

	WaterTracksObj *mod = m_usedModules;
	while (mod)
	{
		if (mod->m_type != -1)
		{
			BoxSetTexture(0, reinterpret_cast<TextureBaseClass *&>(mod->m_stageZeroTexture));
		}

		m_batchStart = callWaterTracksRender(mod, m_vertexBuffer, m_batchStart, rinfo);
		mod = mod->m_nextSystem;
	}

	BaseHeightMapScorchSetZBias(0);
}
