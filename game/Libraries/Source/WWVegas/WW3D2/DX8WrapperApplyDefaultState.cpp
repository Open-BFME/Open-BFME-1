// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// BFME 0x009095A0. Complete 5155-byte Apply_Default_State body.
// Identity/callee/layout proof: targets/game/reverse/identity_evidence/009095a0.md.
#define Matrix4x4 Matrix4
#include "dx8wrapper.h"
#include "vertmaterial.h"
#include "dx8caps.h"
#include "dx8fvf.h"

// Keep the separately matched 0x00907BE0 formatter visible so literal render
// states specialize at each snapshot call. This is the existing canonical body.
__forceinline void DX8Wrapper::Get_DX8_Render_State_Value_Name(StringClass& name, D3DRENDERSTATETYPE state, unsigned value)
{
	switch (state) {
	case D3DRS_ZENABLE:
		name=Get_DX8_ZBuffer_Type_Name(value);
		break;

	case D3DRS_FILLMODE:
		name=Get_DX8_Fill_Mode_Name(value);
		break;

	case D3DRS_SHADEMODE:
		name=Get_DX8_Shade_Mode_Name(value);
		break;

	case D3DRS_FOGCOLOR:
	case D3DRS_ALPHAREF:
	case D3DRS_STENCILMASK:
	case D3DRS_STENCILWRITEMASK:
	case D3DRS_TEXTUREFACTOR:
	case D3DRS_AMBIENT:
	case D3DRS_CLIPPLANEENABLE:
	case D3DRS_MULTISAMPLEMASK:
		name.Format("0x%x",value);
		break;

	case D3DRS_ZWRITEENABLE:
	case D3DRS_ALPHATESTENABLE:
	case D3DRS_LASTPIXEL:
	case D3DRS_DITHERENABLE:
	case D3DRS_ALPHABLENDENABLE:
	case D3DRS_FOGENABLE:
	case D3DRS_SPECULARENABLE:
	case D3DRS_STENCILENABLE:
	case D3DRS_RANGEFOGENABLE:
	case D3DRS_CLIPPING:
	case D3DRS_LIGHTING:
	case D3DRS_COLORVERTEX:
	case D3DRS_LOCALVIEWER:
	case D3DRS_NORMALIZENORMALS:
	case D3DRS_POINTSPRITEENABLE:
	case D3DRS_POINTSCALEENABLE:
	case D3DRS_MULTISAMPLEANTIALIAS:
	case D3DRS_INDEXEDVERTEXBLENDENABLE:
		name=value ? "TRUE" : "FALSE";
		break;

	case D3DRS_SRCBLEND:
	case D3DRS_DESTBLEND:
		name=Get_DX8_Blend_Name(value);
		break;

	case D3DRS_CULLMODE:
		name=Get_DX8_Cull_Mode_Name(value);
		break;

	case D3DRS_ZFUNC:
	case D3DRS_ALPHAFUNC:
	case D3DRS_STENCILFUNC:
		name=Get_DX8_Cmp_Func_Name(value);
		break;

	case D3DRS_FOGTABLEMODE:
	case D3DRS_FOGVERTEXMODE:
		name=Get_DX8_Fog_Mode_Name(value);
		break;

	case D3DRS_FOGSTART:
	case D3DRS_FOGEND:
	case D3DRS_FOGDENSITY:
	case D3DRS_POINTSIZE:
	case D3DRS_POINTSIZE_MIN:
	case D3DRS_POINTSCALE_A:
	case D3DRS_POINTSCALE_B:
	case D3DRS_POINTSCALE_C:
	case D3DRS_POINTSIZE_MAX:
	case D3DRS_TWEENFACTOR:
		name.Format("%f",*(float*)&value);
		break;

	// BFME's Direct3D 9 headers call this state D3DRS_DEPTHBIAS (195).
	case (D3DRENDERSTATETYPE)195:
	case D3DRS_STENCILREF:
		name.Format("%d",value);
		break;

	case D3DRS_STENCILFAIL:
	case D3DRS_STENCILZFAIL:
	case D3DRS_STENCILPASS:
		name=Get_DX8_Stencil_Op_Name(value);
		break;

	case D3DRS_WRAP0:
	case D3DRS_WRAP1:
	case D3DRS_WRAP2:
	case D3DRS_WRAP3:
	case D3DRS_WRAP4:
	case D3DRS_WRAP5:
	case D3DRS_WRAP6:
	case D3DRS_WRAP7:
		name="0";
		if (value&D3DWRAP_U) name+="|D3DWRAP_U";
		if (value&D3DWRAP_V) name+="|D3DWRAP_V";
		if (value&D3DWRAP_W) name+="|D3DWRAP_W";
		break;

	case D3DRS_DIFFUSEMATERIALSOURCE:
	case D3DRS_SPECULARMATERIALSOURCE:
	case D3DRS_AMBIENTMATERIALSOURCE:
	case D3DRS_EMISSIVEMATERIALSOURCE:
		name=Get_DX8_Material_Source_Name(value);
		break;

	case D3DRS_VERTEXBLEND:
		name=Get_DX8_Vertex_Blend_Flag_Name(value);
		break;

	case D3DRS_PATCHEDGESTYLE:
		name=Get_DX8_Patch_Edge_Style_Name(value);
		break;

	case D3DRS_DEBUGMONITORTOKEN:
		name=Get_DX8_Debug_Monitor_Token_Name(value);
		break;

	case D3DRS_COLORWRITEENABLE:
		name="0";
		if (value&D3DCOLORWRITEENABLE_RED) name+="|D3DCOLORWRITEENABLE_RED";
		if (value&D3DCOLORWRITEENABLE_GREEN) name+="|D3DCOLORWRITEENABLE_GREEN";
		if (value&D3DCOLORWRITEENABLE_BLUE) name+="|D3DCOLORWRITEENABLE_BLUE";
		if (value&D3DCOLORWRITEENABLE_ALPHA) name+="|D3DCOLORWRITEENABLE_ALPHA";
		break;
	case D3DRS_BLENDOP:
		name=Get_DX8_Blend_Op_Name(value);
		break;
	default:
		name.Format("UNKNOWN (%d)",value);
		break;
	}
}

// VC7.1 does not inline these exception-owning header wrappers in this TU.
// Expand their native blocks here; typed parameters preserve snapshot scheduling.
#define	APPLY_RENDER_STATE(input_state, input_value) do { \
 D3DRENDERSTATETYPE state = input_state; unsigned value = input_value; \
 if (RenderStates[state] != (value)) { \
  if (WW3D::Is_Snapshot_Activated()) { \
   StringClass value_name(0,true); \
   Get_DX8_Render_State_Value_Name(value_name,state,value); \
  } \
  RenderStates[state]=value; \
  DX8CALL(SetRenderState(state,value)); \
  DX8_RECORD_RENDER_STATE_CHANGE(); \
 } \
} while (0)

#define APPLY_TEXTURE_STAGE(input_stage,input_state,input_value) do { \
 D3DTEXTURESTAGESTATETYPE state = input_state; unsigned value = input_value; \
 const unsigned stage = input_stage; \
 if ((stage) >= MAX_TEXTURE_STAGES) { { IDirect3DDevice8 *device = _Get_D3D_Device8(); (*(Rva009095A0TextureStage **)device)[67](device,stage,state,value); number_of_DX8_calls++; } break; } \
 if (TextureStageStates[stage][state] == (value)) break; \
 if (WW3D::Is_Snapshot_Activated()) { \
  StringClass value_name(0,true); \
  Get_DX8_Texture_Stage_State_Value_Name(value_name,state,value); \
 } \
 TextureStageStates[stage][state]=value; \
 { IDirect3DDevice8 *device = _Get_D3D_Device8(); (*(Rva009095A0TextureStage **)device)[67](device,stage,state,value); number_of_DX8_calls++; } \
 DX8_RECORD_TEXTURE_STAGE_STATE_CHANGE(); \
} while (0)

struct Rva009095A0CapsView { unsigned char beforeMaxTextures[0x278]; int maxTexturesPerPass; };
typedef HRESULT (__stdcall *Rva009095A0DeviceUint)(IDirect3DDevice8 *, unsigned);
typedef HRESULT (__stdcall *Rva009095A0DeviceConstants)(IDirect3DDevice8 *, unsigned, const void *, unsigned);
typedef HRESULT (__stdcall *Rva009095A0TextureStage)(IDirect3DDevice8 *, unsigned, unsigned, unsigned);
#define	CALL_DEVICE_UINT(slot,value) do { IDirect3DDevice8 *device = _Get_D3D_Device8(); (*(Rva009095A0DeviceUint **)device)[slot](device,value); number_of_DX8_calls++; } while (0)
#define	APPLY_SAMPLER(stage,state,value) do { \
 IDirect3DDevice8 *device = _Get_D3D_Device8(); \
 (*(Rva009095A0TextureStage **)device)[69](device,stage,state,value); \
 number_of_DX8_calls++; texture_stage_state_changes++; \
} while (0)
class BFMEZBiasSetter : public DX8Wrapper { public: static void set(float); };

class Rva009095A0TextureHandle {
 TextureBaseClass *value;
public:
 Rva009095A0TextureHandle(TextureBaseClass *texture = 0) : value(texture) { if (value) value->Add_Ref(); }
 ~Rva009095A0TextureHandle() { if (value) value->Release_Ref(); }
 operator TextureBaseClass *&() { return value; }
};
extern TextureBaseClass *TheBoxTextures[];
extern unsigned TheBoxTextureDirtyMask;
// The assignment boundary is significant: it retains the independently witnessed
// release-null check after the outer slot-change comparison.
static __forceinline void AssignDefaultTexture(TextureBaseClass *&slot, TextureBaseClass *texture) {
 if (texture) texture->Add_Ref();
 if (slot) slot->Release_Ref();
 slot = texture;
}

__forceinline void BoxSetTexture(unsigned index, TextureBaseClass *&texture) {
 if (texture != TheBoxTextures[index]) {
  AssignDefaultTexture(TheBoxTextures[index], texture);
  TheBoxTextureDirtyMask |= 0x40 << index;
 }
}

void DX8Wrapper::Apply_Default_State()
{
	SNAPSHOT_SAY(("DX8Wrapper::Apply_Default_State()\n"));

	// only set states used in game
	unsigned zbuffer_enable = TRUE;
	APPLY_RENDER_STATE(D3DRS_ZENABLE, zbuffer_enable);
	unsigned shade_mode = D3DSHADE_GOURAUD;
	APPLY_RENDER_STATE(D3DRS_SHADEMODE, shade_mode);
	APPLY_RENDER_STATE(D3DRS_ZWRITEENABLE, TRUE);
	APPLY_RENDER_STATE(D3DRS_ALPHATESTENABLE, FALSE);
	APPLY_RENDER_STATE(D3DRS_SRCBLEND, D3DBLEND_ONE);
	APPLY_RENDER_STATE(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	APPLY_RENDER_STATE(D3DRS_CULLMODE, D3DCULL_CW);
	APPLY_RENDER_STATE(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	APPLY_RENDER_STATE(D3DRS_ALPHAREF, 0);
	APPLY_RENDER_STATE(D3DRS_ALPHAFUNC, D3DCMP_LESSEQUAL);
	APPLY_RENDER_STATE(D3DRS_DITHERENABLE, FALSE);
	APPLY_RENDER_STATE(D3DRS_ALPHABLENDENABLE, FALSE);
	APPLY_RENDER_STATE(D3DRS_FOGENABLE, FALSE);
	APPLY_RENDER_STATE(D3DRS_SPECULARENABLE, FALSE);

	BFMEZBiasSetter::set(0.0f);
	APPLY_RENDER_STATE(D3DRS_TEXTUREFACTOR, 0);

	APPLY_RENDER_STATE(D3DRS_CLIPPING, TRUE);
	APPLY_RENDER_STATE(D3DRS_LIGHTING, FALSE);
	APPLY_RENDER_STATE(D3DRS_COLORVERTEX, TRUE);

	CALL_DEVICE_UINT(77,0);
	APPLY_RENDER_STATE(D3DRS_COLORWRITEENABLE, 0x00000007);
	APPLY_RENDER_STATE(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	// disable TSS stages
	int i;
	for (i=0; i<reinterpret_cast<const Rva009095A0CapsView *>(CurrentCaps)->maxTexturesPerPass; i++)
	{
		APPLY_TEXTURE_STAGE(i, D3DTSS_COLOROP, D3DTOP_DISABLE);
		APPLY_TEXTURE_STAGE(i, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		APPLY_TEXTURE_STAGE(i, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

		APPLY_TEXTURE_STAGE(i, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
		APPLY_TEXTURE_STAGE(i, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		APPLY_TEXTURE_STAGE(i, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

		APPLY_TEXTURE_STAGE(i, D3DTSS_TEXCOORDINDEX, i);
	APPLY_SAMPLER(i,1,1);
	APPLY_SAMPLER(i,2,1);
	APPLY_SAMPLER(i,4,1);

		APPLY_TEXTURE_STAGE(i, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
		BoxSetTexture(i,(TextureBaseClass *&)Rva009095A0TextureHandle());
	}

	VertexMaterialClass::Apply_Null();

	for (unsigned index=0;index<4;++index) {
		SNAPSHOT_SAY(("Clearing light %d to NULL\n",index));
		Set_DX8_Light(index,NULL);
	}

	// set up simple default TSS
	Vector4 vconst[MAX_VERTEX_SHADER_CONSTANTS];
	memset(vconst,0,sizeof(Vector4)*MAX_VERTEX_SHADER_CONSTANTS);
	Set_Vertex_Shader_Constant(0, vconst, MAX_VERTEX_SHADER_CONSTANTS);

	Vector4 pconst[MAX_PIXEL_SHADER_CONSTANTS];
	memset(pconst,0,sizeof(Vector4)*MAX_PIXEL_SHADER_CONSTANTS);
	if (memcmp(pconst, Pixel_Shader_Constants, sizeof(pconst)) != 0) {
 memcpy(Pixel_Shader_Constants,pconst,sizeof(pconst));
 IDirect3DDevice8 *device = _Get_D3D_Device8();
 (*(Rva009095A0DeviceConstants **)device)[109](device,0,pconst,MAX_PIXEL_SHADER_CONSTANTS);
 number_of_DX8_calls++;
 }

	CALL_DEVICE_UINT(92,0);
	CALL_DEVICE_UINT(89,DX8_FVF_XYZNDUV2);
	CALL_DEVICE_UINT(107,0);

	ShaderClass::Invalidate();
}
