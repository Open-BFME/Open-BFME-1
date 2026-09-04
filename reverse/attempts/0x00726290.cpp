// ?Render@W3DStatusCircle@@UAEXAAVRenderInfoClass@@@Z
// partial score=0.41 date=2026-09-04
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4

#define private public
#define protected public
#define inline __forceinline
#include "WW3D2/Shader.h"
#include <ww3d.h>
#include "W3DDevice/GameClient/W3DStatusCircle.h"

#include <camera.h>
#include <rinfo.h>
#include "WW3D2/DX8Wrapper.h"
#include "Common/GlobalData.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/ScriptEngine.h"
#include "Common/GameEngine.h"
#undef private
#undef protected
#undef inline

#define SC_ADD ( SHADE_CNST(ShaderClass::PASS_ALWAYS, ShaderClass::DEPTH_WRITE_DISABLE, ShaderClass::COLOR_WRITE_ENABLE, ShaderClass::SRCBLEND_ONE, \
	ShaderClass::DSTBLEND_ONE, ShaderClass::FOG_DISABLE, ShaderClass::GRADIENT_DISABLE, ShaderClass::SECONDARY_GRADIENT_DISABLE, ShaderClass::TEXTURING_ENABLE, \
	ShaderClass::ALPHATEST_DISABLE, ShaderClass::CULL_MODE_ENABLE, ShaderClass::DETAILCOLOR_DISABLE, ShaderClass::DETAILALPHA_DISABLE) )

template <class T>
static __forceinline T &bfme_member(W3DStatusCircle *object, unsigned offset)
{
	return *(T *)((char *)object + offset);
}

#define BFME_SET_RENDER_STATE(state_, value_) do { \
	if (DX8Wrapper::RenderStates[(state_)] != (value_)) { \
		if (WW3D::Is_Snapshot_Activated()) { \
			StringClass valueName(0, true); \
			DX8Wrapper::Get_DX8_Render_State_Value_Name(valueName, (state_), (value_)); \
			SNAPSHOT_SAY(("DX8 - SetRenderState(state: %s, value: %s)\n", \
				DX8Wrapper::Get_DX8_Render_State_Name((state_)), valueName)); \
		} \
		DX8Wrapper::RenderStates[(state_)] = (value_); \
		DX8Wrapper::_Get_D3D_Device8()->SetRenderState((state_), (value_)); \
		number_of_DX8_calls++; \
		DX8Wrapper::render_state_changes++; \
	} \
} while (0)

#define BFME_SET_SHADER(bits_) do { \
	unsigned shaderBits = (bits_); \
	if (ShaderClass::ShaderDirty || \
		shaderBits != *(unsigned *)&DX8Wrapper::render_state.shader) { \
		*(unsigned *)&DX8Wrapper::render_state.shader = shaderBits; \
		DX8Wrapper::render_state_changed |= 0x8000; \
		StringClass shaderDescription; \
	} \
} while (0)

void W3DStatusCircle::Render(RenderInfoClass &)
{
	if (*(Int *)((char *)TheGameLogic + 0x10c) == 8)
		return;

	DX8IndexBufferClass *&indexBuffer = bfme_member<DX8IndexBufferClass *>(this, 0xd8);
	if (indexBuffer == NULL) {
		initData();
	}
	if (indexBuffer == NULL) {
		return;
	}

	Bool setIndex = false;
	Matrix3D tm(true);
	if (*(Bool *)((char *)TheWritableGlobalData + 0xa9c) &&
		*(Int *)((char *)TheGameLogic + 0x10c) != 4) {
		if (m_needUpdate) {
			updateCircleVB();
		}
		DX8Wrapper::Set_Material(bfme_member<VertexMaterialClass *>(this, 0xe0));
		BFME_SET_SHADER(*(unsigned *)((char *)this + 0xdc));
		DX8Wrapper::Set_Texture(0, NULL);
		DX8Wrapper::Set_Index_Buffer(indexBuffer, 0);
		DX8Wrapper::Set_Vertex_Buffer(bfme_member<DX8VertexBufferClass *>(this, 0xe4));
		setIndex = true;

		Vector3 vec(0.95f, 0.67f, 0.0f);
		tm.Set_Translation(vec);
		DX8Wrapper::Set_Transform(D3DTS_WORLD, tm);
		DX8Wrapper::Draw_Triangles(0, 20, 0, bfme_member<Int>(this, 0xc8) * 3);
	}

	Int &fade = bfme_member<Int>(this, 0xcc);
	Real &previousIntensity = bfme_member<Real>(this, 0xd0);
	Real &currentIntensity = bfme_member<Real>(this, 0xd4);
	if (*(Int *)((char *)TheGameEngine + 0x30) == 1) {
		previousIntensity = currentIntensity;
		fade = *(Int *)((char *)TheScriptEngine + 0x170b4);
		if (fade == 0) {
			currentIntensity = 0.0f;
			return;
		}
		currentIntensity = *(Real *)((char *)TheScriptEngine + 0x170c4);
		if (*(Bool *)((char *)TheScriptEngine + 0x170b8)) {
			previousIntensity = currentIntensity;
		}
	}
	if (fade == 0) {
		return;
	}

	if (!setIndex) {
		DX8Wrapper::Set_Material(bfme_member<VertexMaterialClass *>(this, 0xe0));
		DX8Wrapper::Set_Index_Buffer(indexBuffer, 0);
		DX8Wrapper::Set_Texture(0, NULL);
	}

	tm.Make_Identity();
	Real intensity;
	Real frameFraction = *(Real *)((char *)TheGameEngine + 0x38);
	if (previousIntensity <= 0.0f) {
		previousIntensity = currentIntensity;
		intensity = currentIntensity;
	} else if (previousIntensity != currentIntensity) {
		intensity = (1.0f - frameFraction) * previousIntensity + frameFraction * currentIntensity;
	} else {
		intensity = previousIntensity;
	}
	Int clr = 255 * intensity;
	Int diffuse = (0xff << 24) | (clr << 16) | (clr << 8) | clr;
	updateScreenVB(diffuse);
	DX8Wrapper::Set_Transform(D3DTS_WORLD, tm);
	BFME_SET_SHADER(SC_ADD);
	DX8Wrapper::Set_Vertex_Buffer(bfme_member<DX8VertexBufferClass *>(this, 0xe8));
	DX8Wrapper::Apply_Render_State_Changes();

	switch (fade) {
		default:
		case ScriptEngine::FADE_ADD:
			DX8Wrapper::Draw_Triangles(0, 2, 0, 6);
			break;
		case ScriptEngine::FADE_SUBTRACT:
			BFME_SET_RENDER_STATE(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			DX8Wrapper::Draw_Triangles(0, 2, 0, 6);
			BFME_SET_RENDER_STATE(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			break;
		case ScriptEngine::FADE_SATURATE:
			BFME_SET_RENDER_STATE(D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR);
			BFME_SET_RENDER_STATE(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
			DX8Wrapper::Draw_Triangles(0, 2, 0, 6);
			DX8Wrapper::Draw_Triangles(0, 2, 0, 6);
			break;
		case ScriptEngine::FADE_MULTIPLY:
			BFME_SET_RENDER_STATE(D3DRS_SRCBLEND, D3DBLEND_ZERO);
			BFME_SET_RENDER_STATE(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
			DX8Wrapper::Draw_Triangles(0, 2, 0, 6);
			break;
	}
	ShaderClass::Invalidate();
}
