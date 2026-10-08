// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Benchmark /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
#define HEAP_ZERO_MEMORY 8
extern "C" __declspec(dllimport) void * __stdcall GetProcessHeap(void);
extern "C" __declspec(dllimport) void * __stdcall HeapAlloc(void *, unsigned long, unsigned long);
extern "C" __declspec(dllimport) int __stdcall HeapFree(void *, unsigned long, void *);
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

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: W3DShaderManager.cpp ////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Westwood Studios Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2001 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
// Project:   RTS3
//
// File name: W3DShaderManager.cpp
//
// Created:   Mark Wilczynski, August 2001
//
// Desc:      Perform tests on currently selected WW3D/D3D device to determine
//			  which of our rendering features are supported.  The system allows
//			  setting up a few custom shaders that are selected based on video
//			  card features.
//
//			  To add a new shader to the system:
//			  0) Add your shader to the ShaderTypes enum
//			  1) Create shader using W3DShaderInterface
//			  2) Repeat step 1 for any alternate shaders
//			  3) Create list of alternate shaders sorted by order of preference.
//				 The first shader which passes hardware validation will be selected.
//			  4) Add list from step 3) to MasterShaderList[].
//
//-----------------------------------------------------------------------------

// The DX8 state caches and per-frame counters this file's shader passes update
// in line are protected statics of DX8Wrapper; retail reached them because the
// updates lived inside DX8Wrapper's own inline members. See BFME_SET_TSS below
// for why they cannot stay there here.
// Confined to this include: leaving it on re-mangles every protected member
// declared later in this file (?...@@IAE... becomes ?...@@QAE...), which breaks
// the ledger rows that name them.
#define private public
#define protected public
#include "dx8wrapper.h"
#undef private
#undef protected
#include "assetmgr.h"
#include "Lib/BaseType.h"
#include "Common/File.h"
#include "Common/FileSystem.h"
#include "W3DDevice/GameClient/W3DShaderManager.h"
#include "W3DDevice/GameClient/W3DShroud.h"
#include "W3DDevice/GameClient/HeightMap.h"
#include "W3DDevice/GameClient/W3DCustomScene.h"
#include "W3DDevice/GameClient/W3DSmudge.h"
#include "GameClient/view.h"
#include "GameClient/CommandXlat.h"
#include "GameClient/display.h"
#include "GameClient/Water.h"
#include "GameLogic/GameLogic.h"
#include "common/GlobalData.h"
#include "common/GameLOD.h"
#include "d3dx8tex.h"
#include "dx8caps.h"
#include "common/gamelod.h"
#include "Benchmark.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

// Turn this on to turn off pixel shaders. jba[4/3/2003]
#define do_not_DISABLE_PIXEL_SHADERS 1

// BFME's IDirect3DDevice8 is not the retail-SDK interface the sweep shim models:
// its method table is shifted, so calling the shim's SetTexture/SetPixelShader
// declarations emits the wrong vtable slot. dx8wrapper.h already reaches slot 65
// by hand for Set_DX8_Texture; these do the same for the slots this file needs.
// BFME's texture release is not RefCountClass's inline decrement -- its
// TextureClass does not derive RefCountClass at all and releases through an
// out-of-line body that can auto-delete via the vtable. The shim's
// TextureBaseClass only spells the inline one, so name the real entry point.
class BFMETextureRelease { public: void Release_Ref(); };
extern TCHAR g_bfmeCh1035;

// bfmeGet returns this one-pointer handle by hidden sret storage.  The
// returned texture owns a reference which the caller releases at scope exit;
// keep the wrapper local so MSVC emits the retail unwind state and tail.
class BfmeHandleCX
{
	BFMETextureRelease *m_bfmeThing;

public:
	~BfmeHandleCX()
	{
		if (m_bfmeThing)
			m_bfmeThing->Release_Ref();
	}
	operator TextureBaseClass *&()
	{
		return *(TextureBaseClass **)&m_bfmeThing;
	}
};

BfmeHandleCX __cdecl bfmeGet(int index);

__forceinline void bfmeStoreNull(TCHAR *buffer, TCHAR value)
{
		*buffer = value;
}

class BFMEValueName
{
	TCHAR *m_Buffer;

public:
	BFMEValueName(int initial_len, bool hint_temporary)
		: m_Buffer(StringClass::m_EmptyString)
	{
		((StringClass *)this)->Get_String(initial_len, hint_temporary);
		TCHAR null_char = g_bfmeCh1035;
		TCHAR *buffer = m_Buffer;
		*buffer = null_char;
	}

	~BFMEValueName()
	{
		((StringClass *)this)->Free_String();
	}
};

class BFMEValueNameLate
{
	TCHAR *m_Buffer;

public:
	BFMEValueNameLate(int initial_len, bool hint_temporary)
		: m_Buffer(StringClass::m_EmptyString)
	{
		((StringClass *)this)->Get_String(initial_len, hint_temporary);
		m_Buffer[0] = *(volatile TCHAR *)&g_bfmeCh1035;
	}

	~BFMEValueNameLate()
	{
		((StringClass *)this)->Free_String();
	}
};

namespace {
	enum { BFME_SET_TEXTURE_SLOT = 65, BFME_SET_PIXEL_SHADER_SLOT = 107 };
	typedef HRESULT (__stdcall *BFMESetTextureFn)(IDirect3DDevice8 *, DWORD, IDirect3DBaseTexture8 *);
	typedef HRESULT (__stdcall *BFMESetPixelShaderFn)(IDirect3DDevice8 *, DWORD);

	__forceinline void bfmeSetTexture(DWORD stage, IDirect3DBaseTexture8 *texture)
	{
		IDirect3DDevice8 *device = DX8Wrapper::_Get_D3D_Device8();
		(*(BFMESetTextureFn **)device)[BFME_SET_TEXTURE_SLOT](device, stage, texture);
	}

	__forceinline void bfmeSetDX8Texture(DWORD stage, IDirect3DBaseTexture8 *texture)
	{
		if (stage >= MAX_TEXTURE_STAGES)
		{
			bfmeSetTexture(stage, texture);
			number_of_DX8_calls++;
			return;
		}

		if (DX8Wrapper::Textures[stage] == texture)
			return;

		if (DX8Wrapper::Textures[stage])
			DX8Wrapper::Textures[stage]->Release();
		DX8Wrapper::Textures[stage] = texture;
		if (texture)
			texture->AddRef();
		bfmeSetTexture(stage, texture);
		number_of_DX8_calls++;
		DX8Wrapper::texture_changes++;
	}

	__forceinline void bfmeSetPixelShader(DWORD handle)
	{
		IDirect3DDevice8 *device = DX8Wrapper::_Get_D3D_Device8();
		(*(BFMESetPixelShaderFn **)device)[BFME_SET_PIXEL_SHADER_SLOT](device, handle);
	}

	// BFME's device splits the sampler states (addressing, filtering, anisotropy)
	// out of the texture-stage state block onto their own method, indexed the way
	// D3D9 numbers D3DSAMPLERSTATETYPE rather than the DX8 D3DTSS_ values. Those
	// sets are neither cached nor snapshot-logged; only the two counters move.
	enum { BFME_SAMP_ADDRESSU = 1, BFME_SAMP_ADDRESSV = 2, BFME_SAMP_MAGFILTER = 5,
	       BFME_SAMP_MINFILTER = 6, BFME_SAMP_MIPFILTER = 7, BFME_SAMP_MAXANISOTROPY = 10 };
	enum { BFME_SET_TSS_SLOT = 67, BFME_SET_RS_SLOT = 57, BFME_SET_SAMP_SLOT = 69 };

	// BFME's texture binding hands the stage's previous texture back through the
	// reference argument for the caller to release, so clearing a stage means
	// owning a local whose destructor drops it -- which is why the call site sits
	// inside an unwind state. Same shape boxrobj.cpp already matches.
	class StageTextureRef
	{
		BFMETextureRelease *Texture;

	public:
		StageTextureRef() : Texture(NULL) {}
		~StageTextureRef() { if (Texture) Texture->Release_Ref(); }
		operator TextureBaseClass *&() { return *(TextureBaseClass **)&Texture; }
	};
	typedef HRESULT (__stdcall *BFMESetTSSFn)(IDirect3DDevice8 *, DWORD, DWORD, DWORD);
	typedef HRESULT (__stdcall *BFMESetRSFn)(IDirect3DDevice8 *, DWORD, DWORD);
}

// The shader passes below expand the state setters in line, the way retail did.
// They cannot call DX8Wrapper's inline wrappers to get that: MSVC 7.1 refuses
// __forceinline for any function that constructs an object with a destructor
// (warning C4714), and the snapshot block builds a StringClass. Every pass that
// wants the out-of-line form calls Set_DX8_Texture_Stage_State instead, which
// resolves to retail's ..._Body.
#define BFME_SET_TSS(stage_, state_, value_)                                                 \
	if ((unsigned)(stage_) >= MAX_TEXTURE_STAGES) {                                          \
		IDirect3DDevice8 *tss_raw_ = DX8Wrapper::_Get_D3D_Device8();                         \
		(*(BFMESetTSSFn **)tss_raw_)[BFME_SET_TSS_SLOT](tss_raw_,                            \
			(stage_), (state_), (value_));                                                   \
		number_of_DX8_calls++;                                                               \
	} else if (DX8Wrapper::TextureStageStates[stage_][state_] != (unsigned)(value_)) {       \
		if (WW3D::Is_Snapshot_Activated()) {                                                 \
			BFMEValueName value_name(0, true);                                               \
			DX8Wrapper::Get_DX8_Texture_Stage_State_Value_Name(*(StringClass *)&value_name, \
				(D3DTEXTURESTAGESTATETYPE)(state_), (value_));                               \
			SNAPSHOT_SAY(("DX8 - SetTextureStageState(stage: %d, state: %s, value: %s)\n", \
				(stage_), DX8Wrapper::Get_DX8_Texture_Stage_State_Name(                    \
					(D3DTEXTURESTAGESTATETYPE)(state_)), value_name));                         \
		}                                                                                    \
		DX8Wrapper::TextureStageStates[stage_][state_] = (value_);                           \
		IDirect3DDevice8 *tss_device_ = DX8Wrapper::_Get_D3D_Device8();                      \
		(*(BFMESetTSSFn **)tss_device_)[BFME_SET_TSS_SLOT](tss_device_,                      \
			(stage_), (state_), (value_));                                                   \
		number_of_DX8_calls++;                                                               \
		DX8Wrapper::texture_stage_state_changes++;                                           \
	}

#define BFME_SET_TSS_LATE(stage_, state_, value_)                                            \
	if ((unsigned)(stage_) >= MAX_TEXTURE_STAGES) {                                           \
		IDirect3DDevice8 *tss_raw_ = DX8Wrapper::_Get_D3D_Device8();                          \
		(*(BFMESetTSSFn **)tss_raw_)[BFME_SET_TSS_SLOT](tss_raw_,                             \
			(stage_), (state_), (value_));                                                    \
		number_of_DX8_calls++;                                                               \
	} else if (DX8Wrapper::TextureStageStates[stage_][state_] != (unsigned)(value_)) {      \
		if (WW3D::Is_Snapshot_Activated()) {                                                 \
			BFMEValueNameLate value_name(0, true);                                            \
			DX8Wrapper::Get_DX8_Texture_Stage_State_Value_Name(*(StringClass *)&value_name,    \
				(D3DTEXTURESTAGESTATETYPE)(state_), (value_));                                  \
			SNAPSHOT_SAY(("DX8 - SetTextureStageState(stage: %d, state: %s, value: %s)\\n",  \
				(stage_), DX8Wrapper::Get_DX8_Texture_Stage_State_Name(                          \
					(D3DTEXTURESTAGESTATETYPE)(state_)), value_name));                             \
		}                                                                                    \
		DX8Wrapper::TextureStageStates[stage_][state_] = (value_);                            \
		IDirect3DDevice8 *tss_device_ = DX8Wrapper::_Get_D3D_Device8();                      \
		(*(BFMESetTSSFn **)tss_device_)[BFME_SET_TSS_SLOT](tss_device_,                      \
			(stage_), (state_), (value_));                                                    \
		number_of_DX8_calls++;                                                               \
		DX8Wrapper::texture_stage_state_changes++;                                           \
	}

#define BFME_SET_SAMP(stage_, type_, value_)                                                 \
	{                                                                                        \
		IDirect3DDevice8 *samp_device_ = DX8Wrapper::_Get_D3D_Device8();                      \
		(*(BFMESetTSSFn **)samp_device_)[BFME_SET_SAMP_SLOT](samp_device_,                    \
			(stage_), (type_), (value_));                                                     \
		number_of_DX8_calls++;                                                                \
		DX8Wrapper::texture_stage_state_changes++;                                            \
	}

// BFME hoisted the per-stage min/mag/mip filter selection (TheGlobalData's
// bilinear/trilinear flags, plus an anisotropy cap check) out of every shader
// pass into one helper each pass calls once per texture stage.
void __cdecl setTerrainTextureFilters(unsigned stage);
void BoxSetTexture(unsigned stage, TextureBaseClass *&texture);

#define BFME_SET_RS(state_, value_)                                                          \
	if (DX8Wrapper::RenderStates[state_] != (unsigned)(value_)) {                            \
		if (WW3D::Is_Snapshot_Activated()) {                                                 \
			StringClass value_name(0, true);                                                 \
			DX8Wrapper::Get_DX8_Render_State_Value_Name(value_name,                          \
				(D3DRENDERSTATETYPE)(state_), (value_));                                     \
		}                                                                                    \
		DX8Wrapper::RenderStates[state_] = (value_);                                         \
		IDirect3DDevice8 *rs_device_ = DX8Wrapper::_Get_D3D_Device8();                       \
		(*(BFMESetRSFn **)rs_device_)[BFME_SET_RS_SLOT](rs_device_, (state_), (value_));     \
		number_of_DX8_calls++;                                                               \
		DX8Wrapper::render_state_changes++;                                                  \
	}

/** Interface definition for custom shaders we define in our app.  These shaders can perform more complex
	operations than those allowed in the WW3D2 shader system.
*/
class W3DShaderInterface
{
public:
	Int getNumPasses(void) {return m_numPasses;};	///<return number of passes needed for this shader
	virtual Int set(Int pass) {return TRUE;};		///<setup shader for the specified rendering pass.
	 ///do any custom resetting necessary to bring W3D in sync.
	virtual void reset(void) {
		ShaderClass::Invalidate();
		DX8Wrapper::_Get_D3D_Device8()->SetTexture(0, NULL);
		DX8Wrapper::_Get_D3D_Device8()->SetTexture(1, NULL);};
	virtual Int init(void) = 0;			///<perform any one time initialization and validation
	virtual Int shutdown(void) { return TRUE;};			///<release resources used by shader
protected:
	Int m_numPasses;						///<number of passes to complete shader
};

//this table will contain custom versions of each shader tuned for specific video card and user options.
static W3DFilterInterface *W3DFilters[10];
static W3DShaderInterface *W3DShaders[W3DShaderManager::ST_MAX];
static Int W3DShadersPassCount[W3DShaderManager::ST_MAX];	//number of passes for each of the above shaders
struct ShaderComResource;
extern ShaderComResource *__identifier("?m_resource012F9D14@W3DShaderManager@@1PAUShaderComResource@@A"); // BFME shader resource cleared by shutdown.
extern ShaderComResource *__identifier("?m_resource012F9D18@W3DShaderManager@@1PAUShaderComResource@@A"); // BFME shader resource cleared by shutdown.
extern VertexBufferClass *ShaderQuadBuffer; // BFME vertex buffer cleared by shutdown.
extern int ShaderQuadIndex; // BFME quad-ring cursor.
TextureClass *W3DShaderManager::m_Textures[8];
W3DShaderManager::ShaderTypes W3DShaderManager::m_currentShader;
FilterTypes W3DShaderManager::m_currentFilter=FT_NULL_FILTER; ///< Last filter that was set.
Int W3DShaderManager::m_currentShaderPass;
ChipsetType W3DShaderManager::m_currentChipset;
GraphicsVenderID W3DShaderManager::m_currentVendor;
__int64 W3DShaderManager::m_driverVersion;

Bool W3DShaderManager::m_renderingToTexture = false;
IDirect3DSurface8 *W3DShaderManager::m_oldRenderSurface=NULL;	///<previous render target
IDirect3DTexture8 *W3DShaderManager::m_renderTexture=NULL;		///<texture into which rendering will be redirected.
IDirect3DSurface8 *W3DShaderManager::m_newRenderSurface=NULL;	///<new render target inside m_renderTexture
IDirect3DSurface8 *W3DShaderManager::m_oldDepthSurface=NULL;	///<previous depth buffer surface
/*===========================================================================================*/
/*=========      Screen Shaders	=============================================================*/
/*===========================================================================================*/

class ScreenDefaultFilter : public W3DFilterInterface
{
public:
	virtual Int init(void);			///<perform any one time initialization and validation
	virtual Bool preRender(Bool &skipRender, CustomScenePassModes &scenePassMode); ///< Set up at start of render.  Only applies to screen filter shaders.
	virtual Bool postRender(enum FilterModes mode, Coord2D &scrollDelta,Bool &doExtraRender); ///< Called after render.  Only applies to screen filter shaders.
	virtual Bool setup(enum FilterModes mode){return true;} ///< Called when the filter is started, one time before the first prerender.
protected:
	virtual Int set(enum FilterModes mode);		///<setup shader for the specified rendering pass.
	virtual void reset(void);		///<do any custom resetting necessary to bring W3D in sync.
};

ScreenDefaultFilter screenDefaultFilter;

///Default filter that just renders screen to off-screen texture and then copies it the the screen.
///Useful because we added some full-time unit effects (microwave tank smudge) to Generals MD that need access
///to the background as a texture.  This filter makes that texture always available for these effects.
W3DFilterInterface *ScreenDefaultFilterList[]=
{
	&screenDefaultFilter,
	NULL
};

Int ScreenDefaultFilter::init(void)
{
	if (!W3DShaderManager::canRenderToTexture()) {
		// Have to be able to render to texture.
		return FALSE;
	}

	//Can render to texture, but we don't know if it can read and write to the same texture.
	//Since there is no D3D caps bit to tell you this, we will just hard-code some specific
	//cards that we know should work.

	Int res;

	if ((res=W3DShaderManager::getChipset()) != DC_UNKNOWN)
	{
		if ( res >=	DC_GEFORCE2)
		{	
			//Check if their driver is newer than what we tested for this vendor
/*			if (TheGameLODManager)
			{
				if (TheGameLODManager->getTestedDriverVersion(W3DShaderManager::getCurrentVendor()) < W3DShaderManager::getCurrentDriverVersion())
					return FALSE;
			}*/
		}
	}

	W3DFilters[FT_VIEW_DEFAULT]=&screenDefaultFilter;

	return TRUE;
}

Bool ScreenDefaultFilter::preRender(Bool &skipRender, CustomScenePassModes &scenePassMode)
{
	//Right now this filter is only used for smudges, so don't bother if none are present.
	if (TheSmudgeManager)
	{	if (((W3DSmudgeManager *)TheSmudgeManager)->getSmudgeCountLastFrame() == 0)
			return FALSE;
	}
	W3DShaderManager::startRenderToTexture();
	return true;
}

// byte-exact reconstruction: game/GameEngine/Source/Common/ScreenDefaultFilter_postRender.cpp
// ?postRender@ScreenDefaultFilter@@ present-unmatched
Bool ScreenDefaultFilter::postRender(enum FilterModes mode, Coord2D &scrollDelta,Bool &doExtraRender)
{
	IDirect3DTexture8 * tex =	W3DShaderManager::endRenderToTexture();
	DEBUG_ASSERTCRASH(tex, ("Require rendered texture."));
	if (!tex) return false;
	if (!set(mode)) return false;

	LPDIRECT3DDEVICE8 pDev=DX8Wrapper::_Get_D3D_Device8();

	struct _TRANS_LIT_TEX_VERTEX {
		D3DXVECTOR4 p;
		DWORD color;   // diffuse color    
		float	u;
		float	v;
	} v[4];

	Int xpos, ypos, width, height;

// ?_Get_D3D_Device8@DX8Wrapper@@SAPAUIDirect3DDevice8@@XZ present-unmatched
	DX8Wrapper::_Get_D3D_Device8()->SetTexture(0,tex);	//previously rendered frame inside this texture
	TheTacticalView->getOrigin(&xpos,&ypos);
	width=TheTacticalView->getWidth();
	height=TheTacticalView->getHeight();

	//bottom right
	v[0].p = D3DXVECTOR4( xpos+width-0.5f, ypos+height-0.5f, 0.0f, 1.0f );
	v[0].u = (Real)(xpos+width)/(Real)TheDisplay->getWidth();	v[0].v = (Real)(ypos+height)/(Real)TheDisplay->getHeight();
	//top right
	v[1].p = D3DXVECTOR4( xpos+width-0.5f, ypos-0.5f, 0.0f, 1.0f );
	v[1].u = (Real)(xpos+width)/(Real)TheDisplay->getWidth();	v[1].v = (Real)(ypos)/(Real)TheDisplay->getHeight();
	//bottom left
	v[2].p = D3DXVECTOR4(  xpos-0.5f, ypos+height-0.5f, 0.0f, 1.0f );
	v[2].u = (Real)(xpos)/(Real)TheDisplay->getWidth();	v[2].v = (Real)(ypos+height)/(Real)TheDisplay->getHeight();
	//top left
	v[3].p = D3DXVECTOR4(  xpos-0.5f,  ypos-0.5f, 0.0f, 1.0f );
	v[3].u = (Real)(xpos)/(Real)TheDisplay->getWidth();	v[3].v = (Real)(ypos)/(Real)TheDisplay->getHeight();
	v[0].color = 0xffffffff;
	v[1].color = 0xffffffff;
	v[2].color = 0xffffffff;
	v[3].color = 0xffffffff;

	//draw polygons like this is very inefficient but for only 2 triangles, it's
	//not worth bothering with index/vertex buffers.
	pDev->SetVertexShader(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	pDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(_TRANS_LIT_TEX_VERTEX));

	reset();
	return true;
}

// ?set@ScreenDefaultFilter@@MAEHW4FilterModes@@@Z present-unmatched
Int ScreenDefaultFilter::set(enum FilterModes mode)
{
	VertexMaterialClass *vmat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
	DX8Wrapper::Set_Material(vmat);
	REF_PTR_RELEASE(vmat);	//no need to keep a reference since it's a preset.
	DX8Wrapper::Set_Shader(ShaderClass::_PresetOpaqueShader);
	DX8Wrapper::Set_Texture(0,NULL);
// ?Apply_Render_State_Changes@DX8Wrapper@@ present-unmatched
	DX8Wrapper::Apply_Render_State_Changes();	//force update of view and projection matrices

	DX8Wrapper::Set_DX8_Render_State(D3DRS_ZFUNC,D3DCMP_ALWAYS);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ZWRITEENABLE,FALSE);
// ?Apply_Render_State_Changes@DX8Wrapper@@ present-unmatched
	DX8Wrapper::Apply_Render_State_Changes();	//force update of view and projection matrices

	return true;
}

void ScreenDefaultFilter::reset(void)
{
	bfmeSetTexture(0,NULL);	//previously rendered frame inside this texture
	DX8Wrapper::Invalidate_Cached_Render_States();
}

/*=========  ScreenBWFilter	=============================================================*/
///converts viewport to black & white.

Int ScreenBWFilter::m_fadeFrames;
Int ScreenBWFilter::m_curFadeFrame;
Real ScreenBWFilter::m_curFadeValue;
Int ScreenBWFilter::m_fadeDirection;

ScreenBWFilter screenBWFilter;
ScreenBWFilterDOT3 screenBWFilterDOT3;	//slower version for older cards without pixel shaders.

///List of different BW shader implementations in order of preference
W3DFilterInterface *ScreenBWFilterList[]=
{
	&screenBWFilter,
	&screenBWFilterDOT3,	//slower version for older cards without pixel shaders.
	NULL
};

// BFME's shader loader takes only the file name and the handle to fill. The
// reference header declares five parameters, so every call site here builds a
// D3DVSD vertex-shader declaration array the retail loader never sees. The
// two-argument spelling is already pinned at ILT 0x0001FC99 under the real
// class name; this view is that same function reached under a name this TU can
// declare beside the five-argument one.
class BfmeShaderLoader
{
public:
	static HRESULT LoadAndCreateD3DShader( const char *filename, DWORD *shader );
};

// BFME's chipset ladder puts the generic pixel-shader 1.1 tier at 3 where the
// reference enum in Common/GameLOD.h numbers it 9 -- six entries earlier in the
// same list. Only the VALUE is proven by these bodies; what the six entries the
// reference has ahead of it are called in BFME is not. Left local rather than
// corrected in the header, which every other consumer of that enum shares --
// including the still-unconverted comparisons at lines below, which keep the
// reference value because no body here has proven them.
enum {
	BFME_DC_GEFORCE2 = 1,
	BFME_DC_GENERIC_PIXEL_SHADER_1_1 = 3
};

// BFME tests the two device globals directly where the reference calls
// W3DShaderManager::canRenderToTexture().
extern void *g_deviceGlobal;								///< retail [0x012F9D04]
extern void *g_pixelShaderGlobal;							///< retail [0x012F9D0C]

// getChipset is DEFINED in this TU, and MSVC then reaches it with its private
// convention for a static whose call sites it can all see -- which lets the
// shader-handle address stay in ECX across the call, where retail has to park
// it in ESI. A declared-only view restores the ordinary call and with it
// retail's register choice. Same function, same ILT.
class BfmeChipsetQuery
{
public:
	static ChipsetType getChipset( void );
};

Int ScreenBWFilter::init(void)
{
	Int res;
	HRESULT hr;

	m_dwBWPixelShader = NULL;
	m_curFadeFrame = 0;

	if (g_deviceGlobal != 0 && g_pixelShaderGlobal != 0)
	{
		if ((res=BfmeChipsetQuery::getChipset()) != 0)
		{
			if (res >= BFME_DC_GENERIC_PIXEL_SHADER_1_1)
			{
				//Monochrome pixel shader.
				hr = BfmeShaderLoader::LoadAndCreateD3DShader("shaders\\monochrome.pso", &m_dwBWPixelShader);
				if (FAILED(hr))
					return FALSE;

				W3DFilters[FT_VIEW_BW_FILTER]=&screenBWFilter;

				return TRUE;
			}
		}
	}
	return FALSE;
}

Bool ScreenBWFilter::preRender(Bool &skipRender, CustomScenePassModes &scenePassMode)
{
	skipRender = false;
	W3DShaderManager::startRenderToTexture();
	return true;
}

// ?postRender@ScreenBWFilter@@ present-unmatched
Bool ScreenBWFilter::postRender(enum FilterModes mode, Coord2D &scrollDelta,Bool &doExtraRender)
{
	IDirect3DTexture8 * tex =	W3DShaderManager::endRenderToTexture();
	DEBUG_ASSERTCRASH(tex, ("Require rendered texture."));
	if (!tex) return false;
	if (!set(mode)) return false;

	LPDIRECT3DDEVICE8 pDev=DX8Wrapper::_Get_D3D_Device8();

	struct _TRANS_LIT_TEX_VERTEX {
		D3DXVECTOR4 p;
		DWORD color;   // diffuse color    
		float	u;
		float	v;
	} v[4];

	Int xpos, ypos, width, height;

// ?_Get_D3D_Device8@DX8Wrapper@@SAPAUIDirect3DDevice8@@XZ present-unmatched
	DX8Wrapper::_Get_D3D_Device8()->SetTexture(0,tex);	//previously rendered frame inside this texture
	TheTacticalView->getOrigin(&xpos,&ypos);
	width=TheTacticalView->getWidth();
	height=TheTacticalView->getHeight();

	//bottom right
	v[0].p = D3DXVECTOR4( xpos+width-0.5f, ypos+height-0.5f, 0.0f, 1.0f );
	v[0].u = (Real)(xpos+width)/(Real)TheDisplay->getWidth();	v[0].v = (Real)(ypos+height)/(Real)TheDisplay->getHeight();
	//top right
	v[1].p = D3DXVECTOR4( xpos+width-0.5f, ypos-0.5f, 0.0f, 1.0f );
	v[1].u = (Real)(xpos+width)/(Real)TheDisplay->getWidth();	v[1].v = (Real)(ypos)/(Real)TheDisplay->getHeight();
	//bottom left
	v[2].p = D3DXVECTOR4(  xpos-0.5f, ypos+height-0.5f, 0.0f, 1.0f );
	v[2].u = (Real)(xpos)/(Real)TheDisplay->getWidth();	v[2].v = (Real)(ypos+height)/(Real)TheDisplay->getHeight();
	//top left
	v[3].p = D3DXVECTOR4(  xpos-0.5f,  ypos-0.5f, 0.0f, 1.0f );
	v[3].u = (Real)(xpos)/(Real)TheDisplay->getWidth();	v[3].v = (Real)(ypos)/(Real)TheDisplay->getHeight();
	v[0].color = 0xffffffff;
	v[1].color = 0xffffffff;
	v[2].color = 0xffffffff;
	v[3].color = 0xffffffff;

	//draw polygons like this is very inefficient but for only 2 triangles, it's
	//not worth bothering with index/vertex buffers.
	pDev->SetVertexShader(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	pDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(_TRANS_LIT_TEX_VERTEX));

	reset();
	return true;
}

// ?set@ScreenBWFilter@@MAEHW4FilterModes@@@Z present-unmatched
Int ScreenBWFilter::set(enum FilterModes mode)
{
	HRESULT hr;

	if (mode > FM_NULL_MODE)
	{	//rendering a quad with redirected rendering surface tinted by pixel shader

		if (m_fadeDirection > 0)
		{	//turning effect on
			m_curFadeFrame++;
			Int fade = m_curFadeFrame;

			if (fade<m_fadeFrames)
			{
				m_curFadeValue = (Real)fade/(Real)m_fadeFrames;
			}
			else
			{
				m_curFadeFrame = 0;
				m_curFadeValue = 1.0f;
				m_fadeDirection = 0;
			}
		}
		else
		if (m_fadeDirection < 0)
		{	//turning effect off
			m_curFadeFrame++;
			Int fade = m_curFadeFrame;
			if (fade<m_fadeFrames)
			{
				m_curFadeValue = 1.0f - (Real)fade/(Real)m_fadeFrames;
			}
			else
			{	m_curFadeValue = 0.0f;
				TheTacticalView->setViewFilterMode(FM_NULL_MODE);
				TheTacticalView->setViewFilter(FT_NULL_FILTER);
				m_curFadeFrame = 0;
				m_fadeDirection = 0;
			}
		}

		VertexMaterialClass *vmat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
		DX8Wrapper::Set_Material(vmat);
		REF_PTR_RELEASE(vmat);	//no need to keep a reference since it's a preset.
		DX8Wrapper::Set_Shader(ShaderClass::_PresetOpaqueShader);
		DX8Wrapper::Set_Texture(0,NULL);
// ?Apply_Render_State_Changes@DX8Wrapper@@ present-unmatched
		DX8Wrapper::Apply_Render_State_Changes();	//force update of view and projection matrices

		DX8Wrapper::Set_DX8_Render_State(D3DRS_ZFUNC,D3DCMP_ALWAYS);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_ZWRITEENABLE,FALSE);
// ?Apply_Render_State_Changes@DX8Wrapper@@ present-unmatched
		DX8Wrapper::Apply_Render_State_Changes();	//force update of view and projection matrices

		hr=DX8Wrapper::_Get_D3D_Device8()->SetPixelShader(m_dwBWPixelShader);
		D3DXVECTOR4 c0(0.3f, 0.59f, 0.11f, 1.0f); DX8Wrapper::_Get_D3D_Device8()->SetPixelShaderConstant(0, &c0, 1);

		D3DXVECTOR4	color(1.0f,1.0f,1.0f,1.0f);	//multiply color

		if (mode == FM_VIEW_BW_BLACK_AND_WHITE)
		{	//back & white mode
			color.x=1.0f;
			color.y=1.0f;
			color.z=1.0f;
		}
		if (mode == FM_VIEW_BW_RED_AND_WHITE)
		{	//red is on
			color.x = 1.0f;
			color.y = 0.0f;
			color.z = 0.0f;
			//inverse red is on
			//red is on
//			color.x = 0.0f;
//			color.y = 1.0f;
//			color.z = 1.0f;
		}
		if (mode == FM_VIEW_BW_GREEN_AND_WHITE)
		{
			color.x = 0.0f;
			color.y = 1.0f;
			color.z = 0.0f;
		}

		DX8Wrapper::_Get_D3D_Device8()->SetPixelShaderConstant(1, &color, 1);
		D3DXVECTOR4 c2(m_curFadeValue, m_curFadeValue, m_curFadeValue, 1.0f); DX8Wrapper::_Get_D3D_Device8()->SetPixelShaderConstant(2, &c2, 1);
/*		DX8Wrapper::_Get_D3D_Device8()->SetPixelShaderConstant(2,   D3DXVECTOR4(150.0f/255.0f, 150.0f/255.0f, 150.0f/255.0f, 0.0f), 1);
		DX8Wrapper::_Get_D3D_Device8()->SetPixelShaderConstant(3,   D3DXVECTOR4((765.0f/450.0f)/3, (765.0f/450.0f)/3, (765.0f/450.0f)/3, 1.0f), 1);
		DX8Wrapper::_Get_D3D_Device8()->SetPixelShaderConstant(4,   D3DXVECTOR4(0.5f, 0.5f, 0.5f, 0), 1);
		DX8Wrapper::_Get_D3D_Device8()->SetPixelShaderConstant(5,   D3DXVECTOR4((60.0f)/255.0f, (60.0f)/255.0f, (60.0f)/255.0f, 0), 1);
		DX8Wrapper::_Get_D3D_Device8()->SetPixelShaderConstant(6,   D3DXVECTOR4((157.0f)/255.0f, (157.0f)/255.0f, (157.0f)/255.0f, 0), 1);
		DX8Wrapper::_Get_D3D_Device8()->SetPixelShaderConstant(7,   D3DXVECTOR4((30.0f)/255.0f, (30.0f)/255.0f, (30.0f)/255.0f, 0), 1);
*/
		return true;
	}
	return false;
}

void ScreenBWFilter::reset(void)
{
	bfmeSetTexture(0,NULL);	//previously rendered frame inside this texture
	bfmeSetPixelShader(0);	//turn off pixel shader
	DX8Wrapper::Invalidate_Cached_Render_States();
}

// ?shutdown@ScreenBWFilter@@UAEHXZ present-unmatched
Int ScreenBWFilter::shutdown(void)
{
	if (m_dwBWPixelShader)
		DX8Wrapper::_Get_D3D_Device8()->DeletePixelShader(m_dwBWPixelShader);

	m_dwBWPixelShader=NULL;

	return TRUE;
}

/**Alternate version of the above filter which does not require pixel shaders - good for older cards*/
// ?init@ScreenBWFilterDOT3@@UAEHXZ present-unmatched
Int ScreenBWFilterDOT3::init(void)
{
	Int res;

	m_curFadeFrame = 0;

	if (!W3DShaderManager::canRenderToTexture()) {
		// Have to be able to render to texture.
		return false;
	}

	if ((res=W3DShaderManager::getChipset()) != 0)
	{
			W3DFilters[FT_VIEW_BW_FILTER]=&screenBWFilterDOT3;
			return TRUE;
	}
	return FALSE;
}

Bool ScreenBWFilterDOT3::preRender(Bool &skipRender, CustomScenePassModes &scenePassMode)
{
	skipRender = false;
	W3DShaderManager::startRenderToTexture();
	return true;
}

// ?postRender@ScreenBWFilterDOT3@@ present-unmatched
Bool ScreenBWFilterDOT3::postRender(enum FilterModes mode, Coord2D &scrollDelta,Bool &doExtraRender)
{
	IDirect3DTexture8 * tex =	W3DShaderManager::endRenderToTexture();
	DEBUG_ASSERTCRASH(tex, ("Require rendered texture."));
	if (!tex) return false;
	if (!set(mode)) return false;

	LPDIRECT3DDEVICE8 pDev=DX8Wrapper::_Get_D3D_Device8();

	struct _TRANS_LIT_TEX_VERTEX {
		D3DXVECTOR4 p;
		DWORD color;   // diffuse color    
		float	u;
		float	v;
	} v[4];

	Int xpos, ypos, width, height;

	TheTacticalView->getOrigin(&xpos,&ypos);
	width=TheTacticalView->getWidth();
	height=TheTacticalView->getHeight();

	//bottom right
	v[0].p = D3DXVECTOR4( xpos+width-0.5f, ypos+height-0.5f, 0.0f, 1.0f );
	v[0].u = (Real)(xpos+width)/(Real)TheDisplay->getWidth();	v[0].v = (Real)(ypos+height)/(Real)TheDisplay->getHeight();
	//top right
	v[1].p = D3DXVECTOR4( xpos+width-0.5f, ypos-0.5f, 0.0f, 1.0f );
	v[1].u = (Real)(xpos+width)/(Real)TheDisplay->getWidth();	v[1].v = (Real)(ypos)/(Real)TheDisplay->getHeight();
	//bottom left
	v[2].p = D3DXVECTOR4(  xpos-0.5f, ypos+height-0.5f, 0.0f, 1.0f );
	v[2].u = (Real)(xpos)/(Real)TheDisplay->getWidth();	v[2].v = (Real)(ypos+height)/(Real)TheDisplay->getHeight();
	//top left
	v[3].p = D3DXVECTOR4(  xpos-0.5f,  ypos-0.5f, 0.0f, 1.0f );
	v[3].u = (Real)(xpos)/(Real)TheDisplay->getWidth();	v[3].v = (Real)(ypos)/(Real)TheDisplay->getHeight();
	
	DWORD currentFade=(((Int)((1.0f-m_curFadeValue) * 255.0f))<<24) | 0x00ffffff;	//store alpha value

	v[0].color = currentFade;
	v[1].color = currentFade;
	v[2].color = currentFade;
	v[3].color = currentFade;

	//draw polygons like this is very inefficient but for only 2 triangles, it's
	//not worth bothering with index/vertex buffers.
	pDev->SetVertexShader(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	//Draw B&W version first
	if (DX8Wrapper::Get_Current_Caps()->Support_Dot3())
	{	//Override W3D states with customizations for grayscale
		DX8Wrapper::Set_DX8_Render_State(D3DRS_TEXTUREFACTOR, 0x80A5CA8E);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLORARG0, D3DTA_TFACTOR | D3DTA_ALPHAREPLICATE);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLORARG2, D3DTA_TFACTOR | D3DTA_ALPHAREPLICATE);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLOROP, D3DTOP_MULTIPLYADD);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_COLORARG1, D3DTA_CURRENT);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_COLORARG2, D3DTA_TFACTOR);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_COLOROP, D3DTOP_DOTPRODUCT3);
	}
	else
	{	//doesn't have DOT3 blend mode so fake it another way.
		DX8Wrapper::Set_DX8_Render_State(D3DRS_TEXTUREFACTOR, 0x60606060);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLORARG2, D3DTA_TFACTOR);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	}

// ?_Get_D3D_Device8@DX8Wrapper@@SAPAUIDirect3DDevice8@@XZ present-unmatched
	DX8Wrapper::_Get_D3D_Device8()->SetTexture(0,tex);	//previously rendered frame inside this texture

	pDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(_TRANS_LIT_TEX_VERTEX));

	//Draw normal view blended by current fade level
// ?Invalidate@ShaderClass@@SAXXZ present-unmatched
	ShaderClass::Invalidate();	//reset DOT3 blend from above.
	ShaderClass shader=ShaderClass::_PresetAlphaShader;
	shader.Set_Depth_Compare(ShaderClass::PASS_ALWAYS);
	DX8Wrapper::Set_Shader(shader);
// ?Apply_Render_State_Changes@DX8Wrapper@@ present-unmatched
	DX8Wrapper::Apply_Render_State_Changes();	//force update of view and projection matrices
	//replace texture alpha with vertex alpha
	DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);

	pDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(_TRANS_LIT_TEX_VERTEX));

	reset();
	return true;
}

// ?set@ScreenBWFilterDOT3@@MAEHW4FilterModes@@@Z present-unmatched
Int ScreenBWFilterDOT3::set(enum FilterModes mode)
{
	if (mode > FM_NULL_MODE)
	{	//rendering a quad with redirected rendering surface tinted by pixel shader

		if (m_fadeDirection > 0)
		{	//turning effect on
			m_curFadeFrame++;
			Int fade = m_curFadeFrame;

			if (fade<m_fadeFrames)
			{
				m_curFadeValue = (Real)fade/(Real)m_fadeFrames;
			}
			else
			{
				m_curFadeFrame = 0;
				m_curFadeValue = 1.0f;
				m_fadeDirection = 0;
			}
		}
		else
		if (m_fadeDirection < 0)
		{	//turning effect off
			m_curFadeFrame++;
			Int fade = m_curFadeFrame;
			if (fade<m_fadeFrames)
			{
				m_curFadeValue = 1.0f - (Real)fade/(Real)m_fadeFrames;
			}
			else
			{	m_curFadeValue = 0.0f;
				TheTacticalView->setViewFilterMode(FM_NULL_MODE);
				TheTacticalView->setViewFilter(FT_NULL_FILTER);
				m_curFadeFrame = 0;
				m_fadeDirection = 0;
			}
		}

		VertexMaterialClass *vmat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
		DX8Wrapper::Set_Material(vmat);
		REF_PTR_RELEASE(vmat);	//no need to keep a reference since it's a preset.
		DX8Wrapper::Set_Shader(ShaderClass::_PresetOpaqueShader);
		DX8Wrapper::Set_Texture(0,NULL);
// ?Apply_Render_State_Changes@DX8Wrapper@@ present-unmatched
		DX8Wrapper::Apply_Render_State_Changes();	//force update of view and projection matrices

		DX8Wrapper::Set_DX8_Render_State(D3DRS_ZFUNC,D3DCMP_ALWAYS);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_ZWRITEENABLE,FALSE);
// ?Apply_Render_State_Changes@DX8Wrapper@@ present-unmatched
		DX8Wrapper::Apply_Render_State_Changes();	//force update of view and projection matrices

		return true;
	}
	return false;
}

// ?reset@ScreenBWFilterDOT3@@MAEXXZ present-unmatched
void ScreenBWFilterDOT3::reset(void)
{
// ?_Get_D3D_Device8@DX8Wrapper@@SAPAUIDirect3DDevice8@@XZ present-unmatched
	DX8Wrapper::_Get_D3D_Device8()->SetTexture(0,NULL);	//previously rendered frame inside this texture
	DX8Wrapper::Invalidate_Cached_Render_States();
}

// ?shutdown@ScreenBWFilterDOT3@@UAEHXZ present-unmatched
Int ScreenBWFilterDOT3::shutdown(void)
{
	return TRUE;
}

/*=========  ScreenCrossFadeFilter	=============================================================*/
///Fades screen between 2 different views of the scene with both being visible at once.

Int ScreenCrossFadeFilter::m_fadeFrames;
Int ScreenCrossFadeFilter::m_curFadeFrame;
Real ScreenCrossFadeFilter::m_curFadeValue;
Int ScreenCrossFadeFilter::m_fadeDirection;
TextureClass *ScreenCrossFadeFilter::m_fadePatternTexture=NULL;
Bool ScreenCrossFadeFilter::m_skipRender = FALSE;

ScreenCrossFadeFilter screenCrossFadeFilter;

///List of different BW shader implementations in order of preference
///@todo: Add a version that doesn't require pixel shader
W3DFilterInterface *ScreenCrossFadeFilterList[]=
{
	&screenCrossFadeFilter,
	NULL
};

// byte-exact reconstruction: game/GameEngine/Source/Common/ScreenCrossFadeFilter_initMethodThunk.cpp
// ?init@ScreenCrossFadeFilter@@UAEHXZ present-unmatched
Int ScreenCrossFadeFilter::init(void)
{
	if (!TheDisplay)
		return FALSE;	//effect is useless without a view so no point initializing for the WB, etc.

	m_curFadeFrame = 0;

	if (!W3DShaderManager::canRenderToTexture())
		// Have to be able to render to texture.
		return FALSE;

	//Load an alpha mask texture that will mix foreground/background views.
	m_fadePatternTexture=WW3DAssetManager::Get_Instance()->Get_Texture("exmask_g.tga");
	if (!m_fadePatternTexture)
		return FALSE;
	m_fadePatternTexture->Get_Filter().Set_U_Addr_Mode(TextureFilterClass::TEXTURE_ADDRESS_CLAMP);
	m_fadePatternTexture->Get_Filter().Set_V_Addr_Mode(TextureFilterClass::TEXTURE_ADDRESS_CLAMP);
	m_fadePatternTexture->Get_Filter().Set_Mip_Mapping(TextureFilterClass::FILTER_TYPE_NONE);

	W3DFilters[FT_VIEW_CROSSFADE]=&screenCrossFadeFilter;

	return TRUE;
}

// The byte-verified updateFadeLevel definition belongs to
// ScreenCrossFadeFilterUpdateFadeLevelThunk.cpp.

Bool ScreenCrossFadeFilter::preRender(Bool &skipRender, CustomScenePassModes &scenePassMode)
{
	if (updateFadeLevel())
	{	//if fade has not completed
		W3DShaderManager::startRenderToTexture();
		scenePassMode=SCENE_PASS_ALPHA_MASK;
		skipRender = false;
		m_skipRender=true;	//tell the postRender function not to draw into framebuffer yet.
		return true;
	}
	//fade must have completed
	return true;
}

// ?postRender@ScreenCrossFadeFilter@@ present-unmatched
Bool ScreenCrossFadeFilter::postRender(enum FilterModes mode, Coord2D &scrollDelta,Bool &doExtraRender)
{
	IDirect3DTexture8 * tex;

	if (m_skipRender)
	{
		//don't render anything to frame buffer because we still need to draw the new scene
		//that we're fading into.  Okay to render on the next call.
		m_skipRender = false;
		doExtraRender = TRUE;
		tex =	W3DShaderManager::endRenderToTexture();
		return true;	
	}

	tex=W3DShaderManager::getRenderTexture();

	DEBUG_ASSERTCRASH(tex, ("Require last rendered texture."));
	if (!tex) return false;
	if (!set(mode)) return false;

	LPDIRECT3DDEVICE8 pDev=DX8Wrapper::_Get_D3D_Device8();

	struct _TRANS_LIT_TEX_VERTEX {
		D3DXVECTOR4 p;
		DWORD color;   // diffuse color    
		float	u;
		float	v;
		float	u1;
		float	v1;
	} v[4];

	Int xpos, ypos, width, height;
	Real radius = 0.0f;

// ?_Get_D3D_Device8@DX8Wrapper@@SAPAUIDirect3DDevice8@@XZ present-unmatched
	DX8Wrapper::_Get_D3D_Device8()->SetTexture(0,tex);	//previously rendered frame inside this texture
	if (mode == FM_VIEW_CROSSFADE_CIRCLE)
	{	DX8Wrapper::_Get_D3D_Device8()->SetTexture(1,m_fadePatternTexture->Peek_D3D_Texture());
		//Use the current fade level to scale the mask texture, for other modes the texture
		//comes pre-scaled so doesn't require uv scaling.
		radius = (1.0f-m_curFadeValue)*2.0f;
		if (radius <= 0)
			radius = 0.01f;
		radius = 0.5f/radius;
	}

	TheTacticalView->getOrigin(&xpos,&ypos);
	width=TheTacticalView->getWidth();
	height=TheTacticalView->getHeight();

/*	Real radius = (1.0f-m_curFadeValue);
	if (radius <= 0)
		radius = 0.01f;
	radius = 25.0f-radius*24.75f;
*/
	//bottom right
	v[0].p = D3DXVECTOR4( xpos+width-0.5f, ypos+height-0.5f, 0.0f, 1.0f );
	v[0].u = (Real)(xpos+width)/(Real)TheDisplay->getWidth();	v[0].v = (Real)(ypos+height)/(Real)TheDisplay->getHeight();
	v[0].u1 = 0.5f+radius;	v[0].v1 = 0.5f+radius;
	//top right
	v[1].p = D3DXVECTOR4( xpos+width-0.5f, ypos-0.5f, 0.0f, 1.0f );
	v[1].u = (Real)(xpos+width)/(Real)TheDisplay->getWidth();	v[1].v = (Real)(ypos)/(Real)TheDisplay->getHeight();
	v[1].u1 = 0.5f+radius;	v[1].v1 = 0.5f-radius;
	//bottom left
	v[2].p = D3DXVECTOR4(  xpos-0.5f, ypos+height-0.5f, 0.0f, 1.0f );
	v[2].u = (Real)(xpos)/(Real)TheDisplay->getWidth();	v[2].v = (Real)(ypos+height)/(Real)TheDisplay->getHeight();
	v[2].u1 = 0.5f-radius;	v[2].v1 = 0.5f+radius;
	//top left
	v[3].p = D3DXVECTOR4(  xpos-0.5f,  ypos-0.5f, 0.0f, 1.0f );
	v[3].u = (Real)(xpos)/(Real)TheDisplay->getWidth();	v[3].v = (Real)(ypos)/(Real)TheDisplay->getHeight();
	v[3].u1 = 0.5f-radius;	v[3].v1 = 0.5f-radius;

	DWORD diffuse = 0xffffffff;//((Int)((m_curFadeValue) * 255.0f) << 24) | 0x00ffffff;	//store alpha value in vertex diffuse

	v[0].color = diffuse;
	v[1].color = diffuse;
	v[2].color = diffuse;
	v[3].color = diffuse;

	//draw polygons like this is very inefficient but for only 2 triangles, it's
	//not worth bothering with index/vertex buffers.
	pDev->SetVertexShader(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX2);

//		m_pDev->SetTextureStageState(0,D3DTSS_MAGFILTER,D3DTEXF_POINT); 
//		m_pDev->SetTextureStageState(0,D3DTSS_MINFILTER,D3DTEXF_POINT); 

	pDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(_TRANS_LIT_TEX_VERTEX));

	reset();
	return true;
}

// ?set@ScreenCrossFadeFilter@@MAEHW4FilterModes@@@Z present-unmatched
Int ScreenCrossFadeFilter::set(enum FilterModes mode)
{
	if (mode > FM_NULL_MODE)
	{	//rendering a quad with redirected rendering surface
		VertexMaterialClass *vmat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
		DX8Wrapper::Set_Material(vmat);
		REF_PTR_RELEASE(vmat);	//no need to keep a reference since it's a preset.
		DX8Wrapper::Set_Shader(ShaderClass::_PresetAlphaShader);
		DX8Wrapper::Set_Texture(0,NULL);
		DX8Wrapper::Set_Texture(1,NULL);
// ?Apply_Render_State_Changes@DX8Wrapper@@ present-unmatched
		DX8Wrapper::Apply_Render_State_Changes();	//force update of view and projection matrices

		DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);

		if (mode == FM_VIEW_CROSSFADE_CIRCLE)
		{	//cross-fading using circle mask stored in stage 1
			DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_COLORARG1, D3DTA_TEXTURE );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_COLORARG2, D3DTA_CURRENT );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_COLOROP,   D3DTOP_MODULATE );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_ALPHAARG2, D3DTA_CURRENT );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_ALPHAOP,   D3DTOP_MODULATE );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_TEXCOORDINDEX, 1 );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
			DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
			DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_MIPFILTER, D3DTEXF_NONE);
		}

		DX8Wrapper::Set_DX8_Render_State(D3DRS_ZFUNC,D3DCMP_ALWAYS);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_ZWRITEENABLE,FALSE);

		return true;
	}
	return false;
}

void ScreenCrossFadeFilter::reset(void)
{
	DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_COLOROP,   D3DTOP_DISABLE );
	DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
	bfmeSetTexture(0,NULL);	//previously rendered frame inside this texture
	DX8Wrapper::Invalidate_Cached_Render_States();
}

// ?shutdown@ScreenCrossFadeFilter@@UAEHXZ present-unmatched
Int ScreenCrossFadeFilter::shutdown(void)
{
	REF_PTR_RELEASE(m_fadePatternTexture);

	return TRUE;
}

/*=========  ScreenMotionBlurFilter	=============================================================*/
///applies motion blur to viewport.

ScreenMotionBlurFilter screenMotionBlurFilter;

Coord3D ScreenMotionBlurFilter::m_zoomToPos;
Bool ScreenMotionBlurFilter::m_zoomToValid = false;

// ScreenMotionBlurFilter::ScreenMotionBlurFilter (retail 0x007D8880) lives in
// ScreenMotionBlurFilterConstructor.cpp.
///List of different motion blur implementations in order of preference
W3DFilterInterface *ScreenMotionBlurFilterList[]=
{
	&screenMotionBlurFilter,
	NULL
};

Int ScreenMotionBlurFilter::init(void)
{
	if (!W3DShaderManager::canRenderToTexture()) {
		// Have to be able to render to texture.
		return false;
	}
	W3DFilters[FT_VIEW_MOTION_BLUR_FILTER]=this;
	return true;
}

Bool ScreenMotionBlurFilter::preRender(Bool &skipRender, CustomScenePassModes &scenePassMode)
{
	skipRender = m_skipRender;
	W3DShaderManager::startRenderToTexture();
	return true;
}

// ?postRender@ScreenMotionBlurFilter@@ present-unmatched
Bool ScreenMotionBlurFilter::postRender(enum FilterModes mode, Coord2D &scrollDelta,Bool &doExtraRender)
{
	IDirect3DTexture8 * tex =	W3DShaderManager::endRenderToTexture();
	DEBUG_ASSERTCRASH(tex, ("Require rendered texture."));
	if (!tex) return false;
	if (!set(mode)) return false;

	LPDIRECT3DDEVICE8 pDev=DX8Wrapper::_Get_D3D_Device8();

	Bool continueEffect = true;
	struct _TRANS_LIT_TEX_VERTEX {
		D3DXVECTOR4 p;
		DWORD color;   // diffuse color    
		float	u;
		float	v;
	} v[4];

	Int xpos, ypos, width, height;

// ?_Get_D3D_Device8@DX8Wrapper@@SAPAUIDirect3DDevice8@@XZ present-unmatched
	DX8Wrapper::_Get_D3D_Device8()->SetTexture(0,tex);	//previously rendered frame inside this texture
	TheTacticalView->getOrigin(&xpos,&ypos);
	width=TheTacticalView->getWidth();
	height=TheTacticalView->getHeight();

	//bottom right
	v[0].p = D3DXVECTOR4( xpos+width-0.5f, ypos+height-0.5f, 0.0f, 1.0f );
	v[0].u = (Real)(xpos+width)/(Real)TheDisplay->getWidth();	v[0].v = (Real)(ypos+height)/(Real)TheDisplay->getHeight();
	//top right
	v[1].p = D3DXVECTOR4( xpos+width-0.5f, ypos-0.5f, 0.0f, 1.0f );
	v[1].u = (Real)(xpos+width)/(Real)TheDisplay->getWidth();	v[1].v = (Real)(ypos)/(Real)TheDisplay->getHeight();
	//bottom left
	v[2].p = D3DXVECTOR4(  xpos-0.5f, ypos+height-0.5f, 0.0f, 1.0f );
	v[2].u = (Real)(xpos)/(Real)TheDisplay->getWidth();	v[2].v = (Real)(ypos+height)/(Real)TheDisplay->getHeight();
	//top left
	v[3].p = D3DXVECTOR4(  xpos-0.5f,  ypos-0.5f, 0.0f, 1.0f );
	v[3].u = (Real)(xpos)/(Real)TheDisplay->getWidth();	v[3].v = (Real)(ypos)/(Real)TheDisplay->getHeight();
	v[0].color = 0xffffffff;
	v[1].color = 0xffffffff;
	v[2].color = 0xffffffff;
	v[3].color = 0xffffffff;


	if (m_additive) {
		DX8Wrapper::Set_DX8_Render_State(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_DESTBLEND,D3DBLEND_ONE);
	} else { 
		DX8Wrapper::Set_DX8_Render_State(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	}
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHABLENDENABLE,false);
	//draw polygons like this is very inefficient but for only 2 triangles, it's
	//not worth bothering with index/vertex buffers.
	DX8Wrapper::Apply_Render_State_Changes();
	pDev->SetVertexShader(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	Coord2D center;
	center.x = 0.5f;
	center.y = 0.5f;
	Bool pan = false;
	if (mode>=FM_VIEW_MB_PAN_ALPHA) {
		Real len = sqrt(scrollDelta.x*scrollDelta.x + scrollDelta.y*scrollDelta.y);
		//center.x += 0.5f * (scrollDelta.x/len);
		center.y -= 0.5f; // * (scrollDelta.y/len);
		m_decrement = false;
		m_maxCount = (len*200*m_panFactor/(Real)DEFAULT_PAN_FACTOR);
		if (m_maxCount<m_panFactor/2) 
			m_maxCount = m_panFactor/2;
		if (m_maxCount>m_panFactor) 
			m_maxCount=m_panFactor;
		pan = true;
		m_priorDelta = scrollDelta;
	} else if (mode == FM_VIEW_MB_END_PAN_ALPHA) {
		Real len = sqrt(m_priorDelta.x*m_priorDelta.x + m_priorDelta.y*m_priorDelta.y);
		center.x += 0.5f * (m_priorDelta.x/len);
		center.y -= 0.5f * (m_priorDelta.y/len);
		m_decrement = false;
		m_maxCount--;
		if (m_maxCount<2) {
			continueEffect = false;
		}
		pan = true;
	}


	m_skipRender = false;
	if (!pan && m_lastFrame != TheGameLogic->getFrame()) {
		if (m_decrement) {
			m_maxCount-=COUNT_STEP;
			if (m_maxCount<1) {
				m_decrement = false;
				continueEffect = false;
			}	else {
				m_skipRender = true;
			}
		} else {
			m_maxCount+=COUNT_STEP;
			if (m_maxCount>=MAX_COUNT) {
				m_decrement = true;
				if (m_doZoomTo && m_zoomToValid) {
					TheTacticalView->lookAt(&m_zoomToPos);
				} else {
					continueEffect = false;
				}
			}	else {
				m_skipRender = true;
			}
		}
	}
	Int	 i, j;
	if (!pan) {
		for (i=0; i<4; i++) {
			Real factor = 1.0f - (m_maxCount/(Real)MAX_COUNT)*0.90f;
			factor = sqrt(factor);
			v[i].u = ((v[i].u-center.x)*factor) + center.x;
			v[i].v = ((v[i].v-center.y)*factor) + center.y;
		}
	}
	pDev->SetTextureStageState(0,D3DTSS_ALPHAARG1, D3DTA_CURRENT);
	pDev->SetTextureStageState(0,D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
	pDev->SetTextureStageState(0,D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	pDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(_TRANS_LIT_TEX_VERTEX));
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHABLENDENABLE,true);

	DX8Wrapper::Apply_Render_State_Changes();
	{
		Int limit = m_maxCount;
		if (m_maxCount>30) limit = 30;
		for (j=0; j<limit; j++) {
			for (i=0; i<4; i++) {
				Real factor = 0.99f;
				if (m_additive) factor = 0.98f;
				Int alpha = 0x15;
				if (m_additive) {
					alpha = 0x09;
					if (m_maxCount>limit) {
						alpha += (m_maxCount-limit)/5;
					}
					if (m_maxCount==MAX_COUNT) alpha += 60;
				}
				v[i].color = (alpha<<24)|0x00ffffff; // 
				if (pan) {
					v[i].u = ((v[i].u-center.x)*(factor+.006)) + center.x;
					v[i].v = ((v[i].v-center.y)*factor) + center.y;
				} else {
					v[i].u = ((v[i].u-center.x)*factor) + center.x;
					v[i].v = ((v[i].v-center.y)*factor) + center.y;
				}
			}
			pDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(_TRANS_LIT_TEX_VERTEX));

		}
	}
	m_lastFrame = TheGameLogic->getFrame();
	if (pan){
		m_skipRender = false;
	}
	reset();
	if (!continueEffect) {
		m_zoomToValid = false;
	}
	return continueEffect;
}

Bool ScreenMotionBlurFilter::setup(enum FilterModes mode)
{

	m_additive = false;

	// BFME inserts extra FilterModes values vs ZH; retail immediates:
	// IN_AND_OUT_ALPHA=7, IN_AND_OUT_SATURATE=8, OUT_ALPHA=10,
	// IN_SATURATE=11, OUT_SATURATE=12, END_PAN_ALPHA=13, PAN_ALPHA=16.
	if (mode == (FilterModes)8 ||
			mode == (FilterModes)11 ||
			mode == (FilterModes)12) {
		m_additive = true;
	}

	m_doZoomTo = false;
	if (mode == (FilterModes)8 ||
			mode == (FilterModes)7 ) {
		m_doZoomTo = true;
	}
	if (mode >= (FilterModes)16)	{
		m_panFactor = (int)mode - 16;
		if (m_panFactor<1) m_panFactor = DEFAULT_PAN_FACTOR;
	}
	m_skipRender = false;
	if (mode != (FilterModes)13) 
		m_maxCount = 0;
	m_decrement = false;
	m_skipRender = false;
	switch (mode) {
		case (FilterModes)12:
		case (FilterModes)10:
			m_maxCount = MAX_COUNT;
			m_decrement = TRUE;
			break;
	}
	return true;
}

// ?set@ScreenMotionBlurFilter@@UAEHW4FilterModes@@@Z present-unmatched
Int ScreenMotionBlurFilter::set(enum FilterModes mode)
{
	if (mode > FM_NULL_MODE)
	{	//rendering a quad with redirected rendering surface motion blurred

		VertexMaterialClass *vmat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
		DX8Wrapper::Set_Material(vmat);
		REF_PTR_RELEASE(vmat);	//no need to keep a reference since it's a preset.
		DX8Wrapper::Set_Shader(ShaderClass::_PresetOpaqueShader);
		DX8Wrapper::Set_Texture(0,NULL);
		DX8Wrapper::Set_Texture(1,NULL);
// ?Apply_Render_State_Changes@DX8Wrapper@@ present-unmatched
		DX8Wrapper::Apply_Render_State_Changes();	//force update of view and projection matrices

		DX8Wrapper::Set_DX8_Render_State(D3DRS_ZFUNC,D3DCMP_ALWAYS);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_ZWRITEENABLE,FALSE);
// ?Apply_Render_State_Changes@DX8Wrapper@@ present-unmatched
		DX8Wrapper::Apply_Render_State_Changes();	//force update of view and projection matrices
	}
	return TRUE;
}

void ScreenMotionBlurFilter::reset(void)
{
	bfmeSetTexture(0,NULL);	//previously rendered frame inside this texture
	DX8Wrapper::Invalidate_Cached_Render_States();
}

// ?shutdown@ScreenMotionBlurFilter@@UAEHXZ is owned by ScreenMotionBlurFilterShutdown.cpp.

/*===========================================================================================*/
/*=========      Shroud Shaders	=============================================================*/
/*===========================================================================================*/

///Shroud layer rendering shader
class ShroudTextureShader : public W3DShaderInterface
{
	virtual Int set(Int pass);		///<setup shader for the specified rendering pass.
	virtual Int init(void);			///<perform any one time initialization and validation
	virtual void reset(void);		///<do any custom resetting necessary to bring W3D in sync.
	Int m_stageOfSet;
} shroudTextureShader;

///List of different shroud shader implementations in order of preference
W3DShaderInterface *ShroudShaderList[]=
{
	&shroudTextureShader,
	NULL
};

//#define SHROUD_STRETCH_FACTOR	(1.0f/MAP_XY_FACTOR)	//1 texel per heightmap cell width

// ?init@ShroudTextureShader@@EAEHXZ present-unmatched
Int ShroudTextureShader::init(void)
{
	W3DShaders[W3DShaderManager::ST_SHROUD_TEXTURE]=&shroudTextureShader;
	W3DShadersPassCount[W3DShaderManager::ST_SHROUD_TEXTURE]=1;

	return TRUE;
}

//Setup a texture projection in the given stage that applies our shroud.
// ShroudTextureShader::set is defined in ShroudTextureShaderSet.cpp.

// ?reset@ShroudTextureShader@@EAEXXZ present-unmatched
void ShroudTextureShader::reset(void)
{
	{
		StageTextureRef texture;
		BoxSetTexture(m_stageOfSet,texture);
	}
	BFME_SET_RS(D3DRS_ZFUNC,D3DCMP_LESSEQUAL);
	BFME_SET_TSS(m_stageOfSet,  D3DTSS_TEXCOORDINDEX, m_stageOfSet);
	BFME_SET_TSS(m_stageOfSet,  D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
}

///Shroud layer rendering shader
class FlatShroudTextureShader : public W3DShaderInterface
{
	virtual Int set(Int pass);		///<setup shader for the specified rendering pass.
	virtual Int init(void);			///<perform any one time initialization and validation
	virtual void reset(void);		///<do any custom resetting necessary to bring W3D in sync.
	Int m_stageOfSet;
} flatShroudTextureShader;

///List of different shroud shader implementations in order of preference
W3DShaderInterface *FlatShroudShaderList[]=
{
	&flatShroudTextureShader,
	NULL
};

//#define SHROUD_STRETCH_FACTOR	(1.0f/MAP_XY_FACTOR)	//1 texel per heightmap cell width

// ?init@FlatShroudTextureShader@@EAEHXZ present-unmatched
Int FlatShroudTextureShader::init(void)
{
	W3DShaders[W3DShaderManager::ST_FLAT_SHROUD_TEXTURE]=&flatShroudTextureShader;
	W3DShadersPassCount[W3DShaderManager::ST_FLAT_SHROUD_TEXTURE]=1;

	return TRUE;
}

//Setup a texture projection in the given stage that applies our shroud.
Int FlatShroudTextureShader::set(Int stage)
{
	//force WW3D2 system to set it's states so it won't later overwrite our custom settings.
	if (stage < 2)
	{
		BoxSetTexture(stage, (TextureBaseClass *&)bfmeGet(stage));
	}
	else	//stages larger than 1 are not supported by W3D so set them directly
	{
		bfmeSetDX8Texture(stage,
			((TextureBaseClass &)bfmeGet(stage)).Peek_D3D_Base_Texture());
	}

	BFME_SET_TSS(stage, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	BFME_SET_TSS(stage, D3DTSS_COLORARG2, D3DTA_CURRENT);
	BFME_SET_TSS(stage, D3DTSS_COLOROP, D3DTOP_MODULATE);
	BFME_SET_TSS_LATE(stage, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	BFME_SET_TSS_LATE(stage, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
	BFME_SET_TSS_LATE(stage, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
	//DX8Wrapper::Apply_Render_State_Changes();

	//We need to scale so shroud texel stretches over one full terrain cell.  Each texel
	//is 1/128 the size of full texture. (assuming 128x128 vid-mem texture).
	W3DShroud *shroud = *(W3DShroud **)((char *)TheTerrainRenderObject + 0x30b8);
	if (shroud != 0)
	{	///@todo: All this code really only need to be done once per camera/view.  Find a way to optimize it out.
		D3DXMATRIX inv;
		float det;

		Matrix4x4 curView;
		DX8Wrapper::_Get_DX8_Transform(D3DTS_VIEW, curView);

		D3DXMatrixInverse(&inv, &det, (D3DXMATRIX*)&curView);

		D3DXMATRIX scale,offset;

		//We need to make all world coordinates be relative to the heightmap data origin since that
		//is where the shroud begins.

		float xoffset = 0;
		float yoffset = 0;
		Real width=*(Real *)((char *)shroud + 0x10);
		Real height=*(Real *)((char *)shroud + 0x14);

		if (*(void **)((char *)TheTerrainRenderObject + 0x2ff4))
		{	//subtract origin position from all coordinates.  Origin is shifted by 1 cell width/height to allow for unused border texels.
			xoffset = -(float)*(Real *)((char *)shroud + 0x2c) + width;
			yoffset = -(float)*(Real *)((char *)shroud + 0x30) + height;
		}

		D3DXMatrixTranslation(&offset, xoffset, yoffset,0);

		width = 1.0f/(width* *(Int *)((char *)shroud + 0x20));
		height = 1.0f/(height* *(Int *)((char *)shroud + 0x24));
		D3DXMatrixScaling(&scale, width, height, 1);
		D3DXMATRIX first;
		D3DXMatrixMultiply(&first, &inv, &offset);
		D3DXMATRIX second=first;
		D3DXMATRIX third;
		D3DXMatrixMultiply(&third, &second, &scale);
		DX8Wrapper::matrix_changes++;
		*((D3DXMATRIX *)&curView)=third;
		DX8CALL(SetTransform((D3DTRANSFORMSTATETYPE)(D3DTS_TEXTURE0+stage),
			(D3DMATRIX *)&curView));
	}
	m_stageOfSet=stage;
	return TRUE;
}

// ?reset@FlatShroudTextureShader@@EAEXXZ present-unmatched
void FlatShroudTextureShader::reset(void)
{
	if (m_stageOfSet < MAX_TEXTURE_STAGES)
	{
		StageTextureRef texture;
		BoxSetTexture(m_stageOfSet,texture);
	}
	BFME_SET_RS(D3DRS_ZFUNC,D3DCMP_LESSEQUAL);
	BFME_SET_TSS(m_stageOfSet,  D3DTSS_TEXCOORDINDEX, m_stageOfSet);
	BFME_SET_TSS(m_stageOfSet,  D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
}

///Mask layer rendering shader
class MaskTextureShader : public W3DShaderInterface
{
	virtual Int set(Int pass);		///<setup shader for the specified rendering pass.
	virtual Int init(void);			///<perform any one time initialization and validation
	virtual void reset(void);		///<do any custom resetting necessary to bring W3D in sync.
} maskTextureShader;

///List of different shroud shader implementations in order of preference
W3DShaderInterface *MaskShaderList[]=
{
	&maskTextureShader,
	NULL
};

// ?init@MaskTextureShader@@EAEHXZ present-unmatched
Int MaskTextureShader::init(void)
{
	W3DShaders[W3DShaderManager::ST_MASK_TEXTURE]=&maskTextureShader;
	W3DShadersPassCount[W3DShaderManager::ST_MASK_TEXTURE]=1;

	return TRUE;
}

// BFME View slots witnessed by this body; reuse the canonical View type.
template<class T> __forceinline T &maskRetailMethod(View *view, unsigned slot)
{ return *(T *)&(*(void ***)view)[slot]; }
class ScreenCrossFadeFilterUpdateFadeLevelShim
{
	static Real m_curFadeValue;
public:
	__forceinline static Real valueRva01307200() { return m_curFadeValue; }
};
typedef void (View::*MaskOriginFn)(Int *, Int *);
typedef Int (View::*MaskDimensionFn)();
typedef Bool (View::*MaskScreenToTerrainFn)(const ICoord2D *, Coord3D *, Bool);
BfmeHandleCX __cdecl bfmeCurrent();
namespace {
__forceinline void bfmeFlatSetTransform(D3DTRANSFORMSTATETYPE type, const Matrix4x4 &m);
__forceinline D3DXMATRIX bfmeFlatMultiply(const D3DXMATRIX &a, const D3DXMATRIX &b);
}
Int MaskTextureShader::set(Int pass)
{
	Real fadeLevel=ScreenCrossFadeFilterUpdateFadeLevelShim::valueRva01307200();

	//Use the current fade level to scale the mask texture
	Real radius = (1.0f-fadeLevel)*2.0f;
	if (radius <= 0)
		radius = 0.01f;
	radius = 0.5f/radius;

	//force WW3D2 system to set it's states so it won't later overwrite our custom settings.
	VertexMaterialClass *vmat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
	DX8Wrapper::Set_Material(vmat);
	REF_PTR_RELEASE(vmat);	//no need to keep a reference since it's a preset.

	//For now we're always going to project the texture coming from the crossfade effect
	BoxSetTexture(0, bfmeCurrent());
	ShaderClass shader=ShaderClass::_PresetOpaqueShader;
	shader.Set_Primary_Gradient(ShaderClass::GRADIENT_DISABLE);
	DX8Wrapper::Set_Shader(shader);
	DX8Wrapper::Apply_Render_State_Changes();
	Matrix4x4 curView;
	DX8Wrapper::_Get_DX8_Transform(D3DTS_VIEW, curView);

	BFME_SET_TSS_LATE(0,  D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
	BFME_SET_TSS_LATE(0,  D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);

	D3DXMATRIX inv;
	float det;

	//Get inverse view matrix so we can transform camera space points back to world space
	D3DXMatrixInverse(&inv, &det, (D3DXMATRIX*)&curView);

	D3DXMATRIX scale,offset,offsetTextureCenter;
	Coord3D centerPos;

	//Find center of projection (this should be returned from some other filter, etc. but
	//for now assume terrain location at center of screen.
	if (TheTacticalView)
	{	Int xpos,ypos;

		(TheTacticalView->*maskRetailMethod<MaskOriginFn>(TheTacticalView,0x4c/4))(&xpos, &ypos);

		ICoord2D screenPos;
		screenPos.x=(Real)(TheTacticalView->*maskRetailMethod<MaskDimensionFn>(TheTacticalView,0x3c/4))()*0.5f;
		screenPos.y=(Real)(TheTacticalView->*maskRetailMethod<MaskDimensionFn>(TheTacticalView,0x44/4))()*0.5f;
		(TheTacticalView->*maskRetailMethod<MaskScreenToTerrainFn>(TheTacticalView,0x164/4))(&screenPos, &centerPos, 0);
	}

	D3DXMatrixTranslation(&offset, -centerPos.x, -centerPos.y,0);

	D3DXMatrixTranslation(&offsetTextureCenter, 0.5f, 0.5f, 0);	//shift coordinates so center of projection falls at uv 0.5,0.5

	Real worldTexelWidth=(1.0f-fadeLevel)*25.0f;	//9 worked well for circle but weird shape requires more stretch to cover.
	Real worldTexelHeight=(1.0f-fadeLevel)*25.0f;

	///@todo: Fix this to work with non 128x128 textures.
	if (worldTexelWidth != 0 && worldTexelHeight != 0)
	{	Real widthScale = 1.0f/(worldTexelWidth*128.0f);
		Real heightScale = 1.0f/(worldTexelHeight*128.0f);
		D3DXMatrixScaling(&scale, widthScale, heightScale, 1);
		*((D3DXMATRIX *)&curView) = bfmeFlatMultiply(bfmeFlatMultiply(bfmeFlatMultiply(inv, offset), scale), offsetTextureCenter);
	}
	else
	{	D3DXMatrixScaling(&scale, 0, 0, 1);	//scaling by 0 will set uv coordinates to 0,0
		*((D3DXMATRIX *)&curView) = bfmeFlatMultiply(bfmeFlatMultiply(inv, offset), scale);
	}

	bfmeFlatSetTransform(D3DTS_TEXTURE0, *((Matrix4x4*)&curView));

	return TRUE;
}

void MaskTextureShader::reset(void)
{
	{
		StageTextureRef texture;
		BoxSetTexture(0,texture);
	}
	BFME_SET_TSS(0,  D3DTSS_TEXCOORDINDEX, 0);
	BFME_SET_TSS(0,  D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
}

/*===========================================================================================*/
/*=========      Terrain Shaders	=========================================================*/
/*===========================================================================================*/

///regular terrain shader that should work on all multi-texture video cards (slowest version)
class TerrainShader2Stage : public W3DShaderInterface
{
public:
	float m_xSlidePerSecond ;	 ///< How far the clouds move per second.
	float m_ySlidePerSecond ;	 ///< How far the clouds move per second.
	int	  m_curTick;
	float m_xOffset;
	float m_yOffset;
	virtual Int set(Int pass);		///<setup shader for the specified rendering pass.
	virtual Int init(void);			///<perform any one time initialization and validation
	virtual void reset(void);		///<do any custom resetting necessary to bring W3D in sync.
	void updateNoise1 (D3DXMATRIX *destMatrix,D3DXMATRIX *curViewInverse, Bool doUpdate=true);	///<generate the uv coordinates for Noise1 (i.e clouds)
	void updateNoise2 (D3DXMATRIX *destMatrix,D3DXMATRIX *curViewInverse, Bool doUpdate=true);	///<generate the uv coordinates for Noise2 (i.e lightmap)
} terrainShader2Stage;

///regular terrain shader that should work on all multi-texture video cards (slowest version)
class FlatTerrainShader2Stage : public W3DShaderInterface
{
public:
	virtual Int set(Int pass);		///<setup shader for the specified rendering pass.
	virtual Int init(void);			///<perform any one time initialization and validation
	virtual void reset(void);		///<do any custom resetting necessary to bring W3D in sync.
} flatTerrainShader2Stage;

///regular terrain shader that should work on all multi-texture video cards (slowest version)
class FlatTerrainShaderPixelShader : public W3DShaderInterface
{
public:
	DWORD					m_dwBasePixelShader;	///<handle to terrain D3D pixel shader
	DWORD					m_dwBaseNoise1PixelShader;	///<handle to terrain/single noise D3D pixel shader
	DWORD					m_dwBaseNoise2PixelShader;	///<handle to terrain/double noise D3D pixel shader
	DWORD					m_dwBase0PixelShader;	///<handle to terrain only pixel shader
	DWORD					m_dwTaintPixelShader;	///<BFME-only; retail this+0x18
	DWORD					m_dwTaint2PixelShader;	///<BFME-only; retail this+0x1C
	virtual Int set(Int pass);		///<setup shader for the specified rendering pass.
	virtual Int init(void);			///<perform any one time initialization and validation
	virtual void reset(void);		///<do any custom resetting necessary to bring W3D in sync.
	virtual Int shutdown(void);			///<release resources used by shader
} flatTerrainShaderPixelShader;

///8 stage terrain shader which only works on certain Nvidia cards.
class TerrainShader8Stage : public W3DShaderInterface
{
	virtual Int set(Int pass);		///<setup shader for the specified rendering pass.
	virtual void reset(void);		///<do any custom resetting necessary to bring W3D in sync.
	virtual Int init(void);			///<perform any one time initialization and validation
} terrainShader8Stage;

//Offsets into constant register pool used by vertex shader
#define CV_WORLDVIEWPROJ_0	0	//4 vectors for transform of world->clip space.

///Pixel shader based terrain shader - fastest method for the newest cards.
class TerrainShaderPixelShader : public W3DShaderInterface
{
	DWORD					m_dwBasePixelShader;	///<handle to terrain D3D pixel shader
	DWORD					m_dwBaseNoise1PixelShader;	///<handle to terrain/single noise D3D pixel shader
	DWORD					m_dwBaseNoise2PixelShader;	///<handle to terrain/double noise D3D pixel shader

	virtual Int set(Int pass);		///<setup shader for the specified rendering pass.
	virtual void reset(void);		///<do any custom resetting necessary to bring W3D in sync.
	virtual Int init(void);			///<perform any one time initialization and validation
	virtual Int shutdown(void);			///<release resources used by shader
} terrainShaderPixelShader;

///List of different terrain shader implementations in order of preference
W3DShaderInterface *TerrainShaderList[]=
{
	&terrainShaderPixelShader,
	&terrainShader8Stage,
	&terrainShader2Stage,
	NULL
};

///List of different terrain shader implementations in order of preference
W3DShaderInterface *FlatTerrainShaderList[]=
{
	&flatTerrainShaderPixelShader,
	&flatTerrainShader2Stage,
	NULL
};

Int TerrainShader2Stage::init( void )
{
	//initialize settings for uv animated clouds
	// BFME drifts the cloud shadows at -0.012 per second, not the reference's -0.02
	m_xSlidePerSecond = -0.012f;	 
	m_ySlidePerSecond =  1.50f * m_xSlidePerSecond;
	m_curTick = 0;
	m_curTick = WW3D::Get_Sync_Time();//::GetTickCount();
	m_xOffset = 0;
	m_yOffset = 0;

	//no special device validation needed - anything in our min spec should handle this.

	W3DShaders[W3DShaderManager::ST_TERRAIN_BASE]=&terrainShader2Stage;
	W3DShadersPassCount[W3DShaderManager::ST_TERRAIN_BASE]=2;
	W3DShaders[W3DShaderManager::ST_TERRAIN_BASE_NOISE1]=&terrainShader2Stage;
	W3DShadersPassCount[W3DShaderManager::ST_TERRAIN_BASE_NOISE1]=3;
	W3DShaders[W3DShaderManager::ST_TERRAIN_BASE_NOISE2]=&terrainShader2Stage;
	W3DShadersPassCount[W3DShaderManager::ST_TERRAIN_BASE_NOISE2]=3;
	W3DShaders[W3DShaderManager::ST_TERRAIN_BASE_NOISE12]=&terrainShader2Stage;
	W3DShadersPassCount[W3DShaderManager::ST_TERRAIN_BASE_NOISE12]=3;

	return TRUE;
}

void TerrainShader2Stage::reset(void)
{
	ShaderClass::Invalidate();

	//Free references to textures
	bfmeSetTexture(0, NULL);
	bfmeSetTexture(1, NULL);

	DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
	DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_PASSTHRU|0);

	DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
	DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_PASSTHRU|1);
}

extern const Real g_bfmeK1266B;
extern Real g_millisecondsToSeconds;

#define BFME_DEFAULT_BU (1.0f)
#define BFME_SHADOW_SCALE (-1.0f)

struct Rva007DCCE0GlobalData
{
	unsigned char m_pad00[0x48];
	volatile Real m_field48;
};

void TerrainShader2Stage::updateNoise1(D3DXMATRIX *destMatrix,D3DXMATRIX *curViewInverse, Bool doUpdate)
{
	D3DXMATRIX scale;
	D3DXMatrixScaling(&scale, 0.0015151514671742916f,
		0.0015151514671742916f, 1.0f);
	D3DXMATRIX result;
	D3DXMatrixMultiply(&result, curViewInverse, &scale);
	*destMatrix = result;

	D3DXMATRIX offset;

	Int delta;
	__asm {
		mov ecx, dword ptr [WW3D::SyncTime]
		mov eax, dword ptr [ebx+0x10]
		mov edx, ecx
		sub edx, eax
		mov dword ptr [ebx+0x10], ecx
	}
	Rva007DCCE0GlobalData *globalData =
		(Rva007DCCE0GlobalData *)TheWritableGlobalData;
	__asm {
		mov delta, edx
	}
	m_xOffset += (float)delta *
		(globalData->m_field48 *
			g_bfmeK1266B + BFME_DEFAULT_BU) * m_xSlidePerSecond *
		g_millisecondsToSeconds;
	m_yOffset += (float)delta *
		(((Rva007DCCE0GlobalData *)TheWritableGlobalData)->m_field48 *
			g_bfmeK1266B + BFME_DEFAULT_BU) * m_ySlidePerSecond *
		g_millisecondsToSeconds;

	while (m_xOffset > 1) m_xOffset -= 1;
	while (m_yOffset > 1) m_yOffset -= 1;
	while (m_xOffset < -1) m_xOffset += 1;
	while (m_yOffset < -1) m_yOffset += 1;

	D3DXMatrixTranslation(&offset, m_xOffset, m_yOffset,0);
	D3DXMatrixMultiply(destMatrix, destMatrix, &offset);
}

#undef BFME_DEFAULT_BU
#undef BFME_SHADOW_SCALE

// ?updateNoise2@TerrainShader2Stage@@QAEXPAU_D3DXMATRIX@@0_N@Z present-unmatched
void TerrainShader2Stage::updateNoise2(D3DXMATRIX *destMatrix,D3DXMATRIX *curViewInverse, Bool doUpdate)
{
	#define STRETCH_FACTOR ((float)(1/(63.0*MAP_XY_FACTOR/2)))

	D3DXMATRIX scale;

	D3DXMatrixScaling(&scale, STRETCH_FACTOR, STRETCH_FACTOR,1);
	*destMatrix = *curViewInverse * scale;
}

// ?set@TerrainShader2Stage@@UAEHH@Z present-unmatched
Int TerrainShader2Stage::set(Int pass)																											  
{
	//force WW3D2 system to set it's states so it won't later overwrite our custom settings.
	DX8Wrapper::Apply_Render_State_Changes();

	if (TheGlobalData && TheGlobalData->m_bilinearTerrainTex || TheGlobalData->m_trilinearTerrainTex) {
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
	} else {
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_MINFILTER, D3DTEXF_POINT);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_MAGFILTER, D3DTEXF_POINT);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MINFILTER, D3DTEXF_POINT);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MAGFILTER, D3DTEXF_POINT);
	}
	if (TheGlobalData && TheGlobalData->m_trilinearTerrainTex) {
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
	} else {
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_MIPFILTER, D3DTEXF_POINT);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
	}

	switch (pass)
	{
		case 0:
			DX8Wrapper::_Get_D3D_Device8()->SetTexture(0, W3DShaderManager::getShaderTexture(0)->Peek_D3D_Texture());
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);

			// Modulate the diffuse color with the texture as lighting comes from diffuse.
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_COLOROP,   D3DTOP_DISABLE );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_TEXCOORDINDEX, 0 );
			DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHABLENDENABLE,false);
			break;
		case 1:
			DX8Wrapper::_Get_D3D_Device8()->SetTexture(0, W3DShaderManager::getShaderTexture(1)->Peek_D3D_Texture());
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);

			// Modulate the diffuse color with the texture as lighting comes from diffuse.
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_TEXCOORDINDEX, 1 );
			// Blend the result using the alpha. (came from diffuse mod texture)
			DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHABLENDENABLE,true);
			DX8Wrapper::Set_DX8_Render_State(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
			DX8Wrapper::Set_DX8_Render_State(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
			// Disable stage 2.
			DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_COLOROP,   D3DTOP_DISABLE );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
			break;
		case 2:
			// Noise/cloud pass
			Matrix4x4 curView;
			DX8Wrapper::_Get_DX8_Transform(D3DTS_VIEW, curView);

			//these states apply to all noise/cloud combination passes
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1 );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );

			DX8Wrapper::Set_DX8_Texture_Stage_State(0,  D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
			// Two output coordinates are used.
			DX8Wrapper::Set_DX8_Texture_Stage_State(0,  D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);	
			DX8Wrapper::Set_DX8_Texture_Stage_State(0,  D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
			DX8Wrapper::Set_DX8_Texture_Stage_State(0,  D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);

			//blend into frame buffer
			DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHABLENDENABLE,true);
			DX8Wrapper::Set_DX8_Render_State(D3DRS_SRCBLEND,D3DBLEND_DESTCOLOR);
			DX8Wrapper::Set_DX8_Render_State(D3DRS_DESTBLEND,D3DBLEND_ZERO);

			
			D3DXMATRIX inv;
			float det;

			D3DXMatrixInverse(&inv, &det, (D3DXMATRIX*)&curView);

			if (W3DShaderManager::getCurrentShader() == W3DShaderManager::ST_TERRAIN_BASE_NOISE12)
			{
				//setup cloud pass
				DX8Wrapper::_Get_D3D_Device8()->SetTexture(0, W3DShaderManager::getShaderTexture(2)->Peek_D3D_Texture());

				updateNoise1(((D3DXMATRIX*)&curView),&inv);	//update curView with texture matrix
				DX8Wrapper::_Set_DX8_Transform(D3DTS_TEXTURE0, curView);
				//clouds always need bilinear filtering
				DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
				DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);

				//setup noise pass
				DX8Wrapper::_Get_D3D_Device8()->SetTexture(1, W3DShaderManager::getShaderTexture(3)->Peek_D3D_Texture());

				updateNoise2(((D3DXMATRIX*)&curView),&inv);
				DX8Wrapper::_Set_DX8_Transform(D3DTS_TEXTURE1, curView);
				//noise always needs point/linear filtering.  Why point!?
				DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MINFILTER, D3DTEXF_POINT);
				DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);

				DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_COLORARG1, D3DTA_TEXTURE );
				DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_COLORARG2, D3DTA_CURRENT );
				DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_COLOROP,   D3DTOP_MODULATE );
				DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
				DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
				// Two output coordinates are used.
				DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);	

				DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
				DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
			} //ST_TERRAIN_BASE_NOISE12
			else
			{	//only 1 noise or cloud texture
				// Now setup the texture pipeline.
				if (W3DShaderManager::getCurrentShader() == W3DShaderManager::ST_TERRAIN_BASE_NOISE1)
				{	//setup cloud pass
					DX8Wrapper::_Get_D3D_Device8()->SetTexture(0, W3DShaderManager::getShaderTexture(2)->Peek_D3D_Texture());
					updateNoise1(((D3DXMATRIX*)&curView),&inv);	//update curView with texture matrix
					DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
					DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
				}
				else
				{
					//setup noise pass
					DX8Wrapper::_Get_D3D_Device8()->SetTexture(0, W3DShaderManager::getShaderTexture(3)->Peek_D3D_Texture());
					updateNoise2(((D3DXMATRIX*)&curView),&inv);	//update curView with texture matrix
					DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MINFILTER, D3DTEXF_POINT);
					DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
				}

				DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_COLOROP,   D3DTOP_DISABLE );
				DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
				DX8Wrapper::_Set_DX8_Transform(D3DTS_TEXTURE0, *((Matrix4x4*)&curView));
			}
			break;
	}

	return TRUE;
}

Int TerrainShader8Stage::init( void )
{	
	ChipsetType res;

	//this shader will also use the 2Stage shader for some of the passes so initialize it too.
	if (terrainShader2Stage.init() && (res=W3DShaderManager::getChipset()) <= (ChipsetType)1)
	{
		W3DShaders[W3DShaderManager::ST_TERRAIN_BASE]=&terrainShader8Stage;
		W3DShadersPassCount[W3DShaderManager::ST_TERRAIN_BASE]=1;
		W3DShaders[W3DShaderManager::ST_TERRAIN_BASE_NOISE1]=&terrainShader8Stage;
		W3DShadersPassCount[W3DShaderManager::ST_TERRAIN_BASE_NOISE1]=2;
		W3DShaders[W3DShaderManager::ST_TERRAIN_BASE_NOISE2]=&terrainShader8Stage;
		W3DShadersPassCount[W3DShaderManager::ST_TERRAIN_BASE_NOISE2]=2;
		W3DShaders[W3DShaderManager::ST_TERRAIN_BASE_NOISE12]=&terrainShader8Stage;
		W3DShadersPassCount[W3DShaderManager::ST_TERRAIN_BASE_NOISE12]=2;
		return TRUE;
	}

	return FALSE;
}

// ?set@TerrainShader8Stage@@EAEHH@Z present-unmatched
Int TerrainShader8Stage::set(Int pass)
{
	if (pass == 0)
	{
		//force WW3D2 system to set it's states so it won't later overwrite our custom settings.
		DX8Wrapper::Apply_Render_State_Changes();

		DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);

		if (TheGlobalData && TheGlobalData->m_bilinearTerrainTex || TheGlobalData->m_trilinearTerrainTex) {
			DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
			DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
			DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
			DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		} else {
			DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_MINFILTER, D3DTEXF_POINT);
			DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_MAGFILTER, D3DTEXF_POINT);
			DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MINFILTER, D3DTEXF_POINT);
			DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MAGFILTER, D3DTEXF_POINT);
		}
		if (TheGlobalData && TheGlobalData->m_trilinearTerrainTex) {
			DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
			DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
		} else {
			DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_MIPFILTER, D3DTEXF_POINT);
			DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
		}
		
		DX8Wrapper::_Get_D3D_Device8()->SetTexture(0, W3DShaderManager::getShaderTexture(0)->Peek_D3D_Texture());
		DX8Wrapper::_Get_D3D_Device8()->SetTexture(1, W3DShaderManager::getShaderTexture(1)->Peek_D3D_Texture());

		DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_TEXCOORDINDEX, 0);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

		DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_COLOROP, D3DTOP_ADD);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_TEXCOORDINDEX, 1);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_COLORARG1, D3DTA_DIFFUSE | D3DTA_COMPLEMENT | D3DTA_ALPHAREPLICATE);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_ALPHAOP,   D3DTOP_ADD);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_ALPHAARG1, D3DTA_TFACTOR | D3DTA_COMPLEMENT);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_ALPHAARG2, D3DTA_TFACTOR);

		DX8Wrapper::Set_DX8_Texture(2, NULL);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 2, D3DTSS_COLOROP, D3DTOP_MODULATE);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 2, D3DTSS_TEXCOORDINDEX, 2);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 2, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 2, D3DTSS_COLORARG2, D3DTA_TEXTURE);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 2, D3DTSS_ALPHAOP,   D3DTOP_MODULATE);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 2, D3DTSS_ALPHAARG1, D3DTA_TFACTOR);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 2, D3DTSS_ALPHAARG2, D3DTA_TFACTOR);

		DX8Wrapper::Set_DX8_Texture(3, NULL);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 3, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 3, D3DTSS_TEXCOORDINDEX, 3);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 3, D3DTSS_COLORARG1, D3DTA_DIFFUSE | 0 | D3DTA_ALPHAREPLICATE);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 3, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 3, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 3, D3DTSS_ALPHAARG1, D3DTA_TFACTOR);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 3, D3DTSS_ALPHAARG2, D3DTA_TFACTOR);

		DX8Wrapper::Set_DX8_Texture(4, NULL);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 4, D3DTSS_COLOROP, D3DTOP_MODULATE);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 4, D3DTSS_TEXCOORDINDEX, 4);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 4, D3DTSS_COLORARG1, D3DTA_CURRENT);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 4, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 4, D3DTSS_ALPHAOP,   D3DTOP_MODULATE);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 4, D3DTSS_ALPHAARG1, D3DTA_CURRENT);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 4, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

		DX8Wrapper::Set_DX8_Texture(5, NULL);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 5, D3DTSS_COLOROP, D3DTOP_ADD);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 5, D3DTSS_TEXCOORDINDEX, 5);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 5, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 5, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 5, D3DTSS_ALPHAOP,   D3DTOP_ADD);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 5, D3DTSS_ALPHAARG1, D3DTA_TFACTOR | D3DTA_COMPLEMENT);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 5, D3DTSS_ALPHAARG2, D3DTA_TFACTOR);

		DX8Wrapper::Set_DX8_Texture(6, NULL);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 6, D3DTSS_COLOROP, D3DTOP_MODULATE);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 6, D3DTSS_TEXCOORDINDEX, 6);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 6, D3DTSS_COLORARG1, D3DTA_TFACTOR);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 6, D3DTSS_COLORARG2, D3DTA_TFACTOR);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 6, D3DTSS_ALPHAOP,   D3DTOP_MODULATE);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 6, D3DTSS_ALPHAARG1, D3DTA_TFACTOR);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 6, D3DTSS_ALPHAARG2, D3DTA_TFACTOR);

		DX8Wrapper::Set_DX8_Texture(7, NULL);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 7, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 7, D3DTSS_TEXCOORDINDEX, 7);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 7, D3DTSS_COLORARG1, D3DTA_TFACTOR);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 7, D3DTSS_COLORARG2, D3DTA_TFACTOR);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 7, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 7, D3DTSS_ALPHAARG1, D3DTA_TFACTOR);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 7, D3DTSS_ALPHAARG2, D3DTA_TFACTOR);
	}
	else
	{	//setup cloud noise/pass
		DX8Wrapper::Set_DX8_Texture_Stage_State( 2, D3DTSS_COLOROP, D3DTOP_DISABLE);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 2, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 3, D3DTSS_COLOROP, D3DTOP_DISABLE);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 3, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
		DX8Wrapper::Invalidate_Cached_Render_States();

		terrainShader2Stage.set(2);
	}
	return TRUE;
}

// ?reset@TerrainShader8Stage@@EAEXXZ present-unmatched
void TerrainShader8Stage::reset(void)
{
	DX8Wrapper::Set_DX8_Texture_Stage_State( 2, D3DTSS_COLOROP, D3DTOP_DISABLE);
	DX8Wrapper::Set_DX8_Texture_Stage_State( 2, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	DX8Wrapper::Set_DX8_Texture_Stage_State( 3, D3DTSS_COLOROP, D3DTOP_DISABLE);
	DX8Wrapper::Set_DX8_Texture_Stage_State( 3, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	DX8Wrapper::Set_DX8_Texture_Stage_State( 4, D3DTSS_COLOROP, D3DTOP_DISABLE);
	DX8Wrapper::Set_DX8_Texture_Stage_State( 4, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

	DX8Wrapper::_Get_D3D_Device8()->SetTexture(0, NULL);
	DX8Wrapper::_Get_D3D_Device8()->SetTexture(1, NULL);
	DX8Wrapper::Invalidate_Cached_Render_States();
}

// ?shutdown@TerrainShaderPixelShader@@EAEHXZ present-unmatched
Int TerrainShaderPixelShader::shutdown(void)
{
	if (m_dwBasePixelShader)
		DX8Wrapper::_Get_D3D_Device8()->DeletePixelShader(m_dwBasePixelShader);

	if (m_dwBaseNoise1PixelShader)
		DX8Wrapper::_Get_D3D_Device8()->DeletePixelShader(m_dwBaseNoise1PixelShader);

	if (m_dwBaseNoise2PixelShader)
		DX8Wrapper::_Get_D3D_Device8()->DeletePixelShader(m_dwBaseNoise2PixelShader);

	m_dwBasePixelShader=NULL;
	m_dwBaseNoise1PixelShader=NULL;
	m_dwBaseNoise2PixelShader=NULL;

	return TRUE;
}

Int TerrainShaderPixelShader::init( void )
{	
	Int res;
#ifdef DISABLE_PIXEL_SHADERS
	return false;
#endif
	//this shader will also use the 2Stage shader for some of the passes so initialize it too.
	if (terrainShader2Stage.init() && (res=W3DShaderManager::getChipset()) >= BFME_DC_GENERIC_PIXEL_SHADER_1_1)
	{
		if (res >= BFME_DC_GENERIC_PIXEL_SHADER_1_1)
		{
			//base version which doesn't apply any noise textures.
			HRESULT hr = BfmeShaderLoader::LoadAndCreateD3DShader("shaders\\terrain.pso", &m_dwBasePixelShader);
			if (FAILED(hr))
				return FALSE;

			//version which blends 1 noise texture.
			hr = BfmeShaderLoader::LoadAndCreateD3DShader("shaders\\terrainnoise.pso", &m_dwBaseNoise1PixelShader);
			if (FAILED(hr))
				return FALSE;

			//version which blends 2 noise textures.
			hr = BfmeShaderLoader::LoadAndCreateD3DShader("shaders\\terrainnoise2.pso", &m_dwBaseNoise2PixelShader);
			if (FAILED(hr))
				return FALSE;

			W3DShaders[W3DShaderManager::ST_TERRAIN_BASE]=&terrainShaderPixelShader;
			W3DShaders[W3DShaderManager::ST_TERRAIN_BASE_NOISE1]=&terrainShaderPixelShader;
			W3DShaders[W3DShaderManager::ST_TERRAIN_BASE_NOISE2]=&terrainShaderPixelShader;
			W3DShaders[W3DShaderManager::ST_TERRAIN_BASE_NOISE12]=&terrainShaderPixelShader;
			W3DShadersPassCount[W3DShaderManager::ST_TERRAIN_BASE]=1;
			W3DShadersPassCount[W3DShaderManager::ST_TERRAIN_BASE_NOISE1]=1;
			W3DShadersPassCount[W3DShaderManager::ST_TERRAIN_BASE_NOISE2]=1;
			W3DShadersPassCount[W3DShaderManager::ST_TERRAIN_BASE_NOISE12]=1;
			return TRUE;
		}
	}
	return FALSE;
}

// Shared with FlatTerrainShader2Stage below; moved here for both callers.
struct Rva007DCF00Matrix;
class Rva007DCF00TextureMatrix {
public:
    void build(Rva007DCF00Matrix *, Rva007DCF00Matrix *, bool);
};

// 0x007E2180: TerrainShaderPixelShader::set, ZH twin and table 0x01128D00.
// Slot 2 loads terrain.pso / terrainnoise.pso / terrainnoise2.pso into +8/+C/+10.
// BFME device ABI uses D3D9 slots; keep this view local to this recovered body.
class Rva007E2180InlineString
{
	TCHAR *m_Buffer;

public:
	__forceinline Rva007E2180InlineString(int initial_len, bool hint_temporary)
		: m_Buffer(StringClass::m_EmptyString)
	{
		((StringClass *)this)->Get_String(initial_len, hint_temporary);
		TCHAR null_char = g_bfmeCh1035;
		TCHAR *buffer = m_Buffer;
		*buffer = null_char;
	}

	~Rva007E2180InlineString()
	{
		((StringClass *)this)->Free_String();
	}
};

class Rva007E2180OrderedString
{
	TCHAR *m_Buffer;

public:
	__forceinline Rva007E2180OrderedString(int initial_len, bool hint_temporary)
		: m_Buffer(StringClass::m_EmptyString)
	{
		((StringClass *)this)->Get_String(initial_len, hint_temporary);
		TCHAR *buffer = *(TCHAR *volatile *)&m_Buffer;
		TCHAR null_char = *(volatile TCHAR *)&g_bfmeCh1035;
		*buffer = null_char;
	}

	~Rva007E2180OrderedString()
	{
		((StringClass *)this)->Free_String();
	}
};

#define RVA007E2180_SET_TSS(stage_, state_, value_)                                                 \
	if ((unsigned)(stage_) >= MAX_TEXTURE_STAGES) {                                          \
		IDirect3DDevice8 *tss_raw_ = DX8Wrapper::_Get_D3D_Device8();                         \
		(*(BFMESetTSSFn **)tss_raw_)[BFME_SET_TSS_SLOT](tss_raw_,                            \
			(stage_), (state_), (value_));                                                   \
		number_of_DX8_calls++;                                                               \
	} else if (DX8Wrapper::TextureStageStates[stage_][state_] != (unsigned)(value_)) {       \
		if (WW3D::Is_Snapshot_Activated()) {                                                 \
			Rva007E2180InlineString value_name(0, true);                                               \
			DX8Wrapper::Get_DX8_Texture_Stage_State_Value_Name(*(StringClass *)&value_name, \
				(D3DTEXTURESTAGESTATETYPE)(state_), (value_));                               \
			SNAPSHOT_SAY(("DX8 - SetTextureStageState(stage: %d, state: %s, value: %s)\n", \
				(stage_), DX8Wrapper::Get_DX8_Texture_Stage_State_Name(                    \
					(D3DTEXTURESTAGESTATETYPE)(state_)), value_name));                         \
		}                                                                                    \
		DX8Wrapper::TextureStageStates[stage_][state_] = (value_);                           \
		IDirect3DDevice8 *tss_device_ = DX8Wrapper::_Get_D3D_Device8();                      \
		(*(BFMESetTSSFn **)tss_device_)[BFME_SET_TSS_SLOT](tss_device_,                      \
			(stage_), (state_), (value_));                                                   \
		number_of_DX8_calls++;                                                               \
		DX8Wrapper::texture_stage_state_changes++;                                           \
	}

#define RVA007E2180_SET_TSS_ORDERED(stage_, state_, value_)                                                 \
	if ((unsigned)(stage_) >= MAX_TEXTURE_STAGES) {                                          \
		IDirect3DDevice8 *tss_raw_ = DX8Wrapper::_Get_D3D_Device8();                         \
		(*(BFMESetTSSFn **)tss_raw_)[BFME_SET_TSS_SLOT](tss_raw_,                            \
			(stage_), (state_), (value_));                                                   \
		number_of_DX8_calls++;                                                               \
	} else if (DX8Wrapper::TextureStageStates[stage_][state_] != (unsigned)(value_)) {       \
		if (WW3D::Is_Snapshot_Activated()) {                                                 \
			Rva007E2180OrderedString value_name(0, true);                                               \
			DX8Wrapper::Get_DX8_Texture_Stage_State_Value_Name(*(StringClass *)&value_name, \
				(D3DTEXTURESTAGESTATETYPE)(state_), (value_));                               \
			SNAPSHOT_SAY(("DX8 - SetTextureStageState(stage: %d, state: %s, value: %s)\n", \
				(stage_), DX8Wrapper::Get_DX8_Texture_Stage_State_Name(                    \
					(D3DTEXTURESTAGESTATETYPE)(state_)), value_name));                         \
		}                                                                                    \
		DX8Wrapper::TextureStageStates[stage_][state_] = (value_);                           \
		IDirect3DDevice8 *tss_device_ = DX8Wrapper::_Get_D3D_Device8();                      \
		(*(BFMESetTSSFn **)tss_device_)[BFME_SET_TSS_SLOT](tss_device_,                      \
			(stage_), (state_), (value_));                                                   \
		number_of_DX8_calls++;                                                               \
		DX8Wrapper::texture_stage_state_changes++;                                           \
	}

struct Rva007E2180Device {
virtual void __stdcall unused0() = 0;
virtual void __stdcall unused1() = 0;
virtual void __stdcall unused2() = 0;
virtual void __stdcall unused3() = 0;
virtual void __stdcall unused4() = 0;
virtual void __stdcall unused5() = 0;
virtual void __stdcall unused6() = 0;
virtual void __stdcall unused7() = 0;
virtual void __stdcall unused8() = 0;
virtual void __stdcall unused9() = 0;
virtual void __stdcall unused10() = 0;
virtual void __stdcall unused11() = 0;
virtual void __stdcall unused12() = 0;
virtual void __stdcall unused13() = 0;
virtual void __stdcall unused14() = 0;
virtual void __stdcall unused15() = 0;
virtual void __stdcall unused16() = 0;
virtual void __stdcall unused17() = 0;
virtual void __stdcall unused18() = 0;
virtual void __stdcall unused19() = 0;
virtual void __stdcall unused20() = 0;
virtual void __stdcall unused21() = 0;
virtual void __stdcall unused22() = 0;
virtual void __stdcall unused23() = 0;
virtual void __stdcall unused24() = 0;
virtual void __stdcall unused25() = 0;
virtual void __stdcall unused26() = 0;
virtual void __stdcall unused27() = 0;
virtual void __stdcall unused28() = 0;
virtual void __stdcall unused29() = 0;
virtual void __stdcall unused30() = 0;
virtual void __stdcall unused31() = 0;
virtual void __stdcall unused32() = 0;
virtual void __stdcall unused33() = 0;
virtual void __stdcall unused34() = 0;
virtual void __stdcall unused35() = 0;
virtual void __stdcall unused36() = 0;
virtual void __stdcall unused37() = 0;
virtual void __stdcall unused38() = 0;
virtual void __stdcall unused39() = 0;
virtual void __stdcall unused40() = 0;
virtual void __stdcall unused41() = 0;
virtual void __stdcall unused42() = 0;
virtual void __stdcall unused43() = 0;
virtual HRESULT __stdcall SetTransform(DWORD, const void *) = 0;
virtual HRESULT __stdcall GetTransform(DWORD, void *) = 0;
virtual void __stdcall unused46() = 0;
virtual void __stdcall unused47() = 0;
virtual void __stdcall unused48() = 0;
virtual void __stdcall unused49() = 0;
virtual void __stdcall unused50() = 0;
virtual void __stdcall unused51() = 0;
virtual void __stdcall unused52() = 0;
virtual void __stdcall unused53() = 0;
virtual void __stdcall unused54() = 0;
virtual void __stdcall unused55() = 0;
virtual void __stdcall unused56() = 0;
virtual void __stdcall unused57() = 0;
virtual void __stdcall unused58() = 0;
virtual void __stdcall unused59() = 0;
virtual void __stdcall unused60() = 0;
virtual void __stdcall unused61() = 0;
virtual void __stdcall unused62() = 0;
virtual void __stdcall unused63() = 0;
virtual void __stdcall unused64() = 0;
virtual HRESULT __stdcall SetTexture(DWORD, IDirect3DBaseTexture8 *) = 0;
virtual void __stdcall unused66() = 0;
virtual void __stdcall unused67() = 0;
virtual void __stdcall unused68() = 0;
virtual void __stdcall unused69() = 0;
virtual void __stdcall unused70() = 0;
virtual void __stdcall unused71() = 0;
virtual void __stdcall unused72() = 0;
virtual void __stdcall unused73() = 0;
virtual void __stdcall unused74() = 0;
virtual void __stdcall unused75() = 0;
virtual void __stdcall unused76() = 0;
virtual void __stdcall unused77() = 0;
virtual void __stdcall unused78() = 0;
virtual void __stdcall unused79() = 0;
virtual void __stdcall unused80() = 0;
virtual void __stdcall unused81() = 0;
virtual void __stdcall unused82() = 0;
virtual void __stdcall unused83() = 0;
virtual void __stdcall unused84() = 0;
virtual void __stdcall unused85() = 0;
virtual void __stdcall unused86() = 0;
virtual void __stdcall unused87() = 0;
virtual void __stdcall unused88() = 0;
virtual void __stdcall unused89() = 0;
virtual void __stdcall unused90() = 0;
virtual void __stdcall unused91() = 0;
virtual void __stdcall unused92() = 0;
virtual void __stdcall unused93() = 0;
virtual void __stdcall unused94() = 0;
virtual void __stdcall unused95() = 0;
virtual void __stdcall unused96() = 0;
virtual void __stdcall unused97() = 0;
virtual void __stdcall unused98() = 0;
virtual void __stdcall unused99() = 0;
virtual void __stdcall unused100() = 0;
virtual void __stdcall unused101() = 0;
virtual void __stdcall unused102() = 0;
virtual void __stdcall unused103() = 0;
virtual void __stdcall unused104() = 0;
virtual void __stdcall unused105() = 0;
virtual void __stdcall unused106() = 0;
virtual HRESULT __stdcall SetPixelShader(DWORD) = 0;
virtual void __stdcall unused108() = 0;
virtual HRESULT __stdcall SetPixelShaderConstant(DWORD, const void *, DWORD) = 0;
};
// Local helpers spell the independently decoded BFME device ABI.
__forceinline void rva007E2180GetTransform(DWORD state, Matrix4x4 &matrix) {
    IDirect3DDevice8 *device = DX8Wrapper::_Get_D3D_Device8();
    ((Rva007E2180Device *)device)->GetTransform(state, &matrix);
    number_of_DX8_calls++;
}
__forceinline void rva007E2180SetTransform(DWORD state, const Matrix4x4 &matrix) {
    DX8Wrapper::matrix_changes++;
    IDirect3DDevice8 *device = DX8Wrapper::_Get_D3D_Device8();
    ((Rva007E2180Device *)device)->SetTransform(state, &matrix);
    number_of_DX8_calls++;
}
__forceinline void rva007E2180SetConstant(int reg, const void *data, int count) {
    int size = count * sizeof(Vector4);
    if (memcmp(data, &DX8Wrapper::Pixel_Shader_Constants[reg], size) == 0) return;
    memcpy(&DX8Wrapper::Pixel_Shader_Constants[reg], data, size);
    IDirect3DDevice8 *device = DX8Wrapper::_Get_D3D_Device8();
    ((Rva007E2180Device *)device)->SetPixelShaderConstant(reg, data, count);
    number_of_DX8_calls++;
}
#define RVA007E2180_BIND_TEXTURE(stage, index) ((Rva007E2180Device *)DX8Wrapper::_Get_D3D_Device8())->SetTexture(stage, ((TextureBaseClass &)bfmeGet(index)).Peek_D3D_Base_Texture())
Int TerrainShaderPixelShader::set(Int pass)
{
	//force WW3D2 system to set it's states so it won't later overwrite our custom settings.
	DX8Wrapper::Apply_Render_State_Changes();

	//setup base pass
	RVA007E2180_BIND_TEXTURE(0, 0);
	RVA007E2180_BIND_TEXTURE(1, 1);

	BFME_SET_SAMP(0, BFME_SAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	BFME_SET_SAMP(0, BFME_SAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	BFME_SET_SAMP(1, BFME_SAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	BFME_SET_SAMP(1, BFME_SAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	//tell pixel shader which UV set to use for each stage
	RVA007E2180_SET_TSS( 0, D3DTSS_TEXCOORDINDEX, 0 );
	RVA007E2180_SET_TSS( 1, D3DTSS_TEXCOORDINDEX, 1 );

	setTerrainTextureFilters(0);
	setTerrainTextureFilters(1);

	if (W3DShaderManager::getCurrentShader() >= W3DShaderManager::ST_TERRAIN_BASE_NOISE1)
	{
		Matrix4x4 curView;
		rva007E2180GetTransform(D3DTS_VIEW, curView);

		D3DXMATRIX inv;
		float det;
		D3DXMatrixInverse(&inv, &det, (D3DXMATRIX*)&curView);

		RVA007E2180_SET_TSS(2,  D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
		// Two output coordinates are used.
		RVA007E2180_SET_TSS(2,  D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);

		BFME_SET_SAMP(2, BFME_SAMP_ADDRESSU, D3DTADDRESS_WRAP);
		BFME_SET_SAMP(2, BFME_SAMP_ADDRESSV, D3DTADDRESS_WRAP);

		if (W3DShaderManager::getCurrentShader() == W3DShaderManager::ST_TERRAIN_BASE_NOISE12)
		{	//full shader
			BFME_SET_SAMP(3, BFME_SAMP_ADDRESSU, D3DTADDRESS_WRAP);
			BFME_SET_SAMP(3, BFME_SAMP_ADDRESSV, D3DTADDRESS_WRAP);
			RVA007E2180_BIND_TEXTURE(2, 2);
			RVA007E2180_BIND_TEXTURE(3, 3);
			((Rva007E2180Device *)DX8Wrapper::_Get_D3D_Device8())->SetPixelShader(m_dwBaseNoise2PixelShader);
            float value = 0.0f;
            if (TheWritableGlobalData) value = *(float *)((char *)TheWritableGlobalData + 0x48);
            Vector4 constant(value, value, value, value);
            rva007E2180SetConstant(0, &constant, 1);

			BFME_SET_SAMP(2, BFME_SAMP_MINFILTER, D3DTEXF_LINEAR);
			BFME_SET_SAMP(2, BFME_SAMP_MAGFILTER, D3DTEXF_LINEAR);

			BFME_SET_SAMP(3, BFME_SAMP_MINFILTER, D3DTEXF_POINT);
			BFME_SET_SAMP(3, BFME_SAMP_MAGFILTER, D3DTEXF_LINEAR);

			terrainShader2Stage.updateNoise1(((D3DXMATRIX*)&curView),&inv);	//update curView with texture matrix
			rva007E2180SetTransform(D3DTS_TEXTURE2, curView);

			((Rva007DCF00TextureMatrix *)&terrainShader2Stage)->build(
                (Rva007DCF00Matrix *)&curView, (Rva007DCF00Matrix *)&inv, true);	//update curView with texture matrix
			rva007E2180SetTransform(D3DTS_TEXTURE3, curView);

			RVA007E2180_SET_TSS_ORDERED(3,  D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
			// Two output coordinates are used.
			RVA007E2180_SET_TSS(3,  D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
		}
		else
		{	//single noise texture shader
			((Rva007E2180Device *)DX8Wrapper::_Get_D3D_Device8())->SetPixelShader(m_dwBaseNoise1PixelShader);

			if (W3DShaderManager::getCurrentShader() == W3DShaderManager::ST_TERRAIN_BASE_NOISE1)
			{	//cloud map
				RVA007E2180_BIND_TEXTURE(2, 2);
				terrainShader2Stage.updateNoise1(((D3DXMATRIX*)&curView),&inv);	//update curView with texture matrix
				BFME_SET_SAMP(2, BFME_SAMP_MINFILTER, D3DTEXF_LINEAR);
				BFME_SET_SAMP(2, BFME_SAMP_MAGFILTER, D3DTEXF_LINEAR);
			}
			else
			{	//light map
				RVA007E2180_BIND_TEXTURE(2, 3);
				((Rva007DCF00TextureMatrix *)&terrainShader2Stage)->build(
                (Rva007DCF00Matrix *)&curView, (Rva007DCF00Matrix *)&inv, true);	//update curView with texture matrix
				BFME_SET_SAMP(2, BFME_SAMP_MINFILTER, D3DTEXF_POINT);
				BFME_SET_SAMP(2, BFME_SAMP_MAGFILTER, D3DTEXF_LINEAR);
			}
			rva007E2180SetTransform(D3DTS_TEXTURE2, curView);
		}
	}
	else
	{	//just base texturing
		((Rva007E2180Device *)DX8Wrapper::_Get_D3D_Device8())->SetPixelShader(m_dwBasePixelShader);
	}

	return TRUE;
}

#undef RVA007E2180_BIND_TEXTURE
#undef RVA007E2180_SET_TSS
#undef RVA007E2180_SET_TSS_ORDERED

void TerrainShaderPixelShader::reset(void)
{
	bfmeSetTexture(2,NULL);	//release reference to any texture
	bfmeSetTexture(3,NULL);	//release reference to any texture

	bfmeSetPixelShader(0);	//turn off pixel shader

	bfmeSetTexture(0, NULL);
	bfmeSetTexture(1, NULL);

	DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
	DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_PASSTHRU|0);

	DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
	DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_PASSTHRU|1);

	DX8Wrapper::Set_DX8_Texture_Stage_State( 2, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
	DX8Wrapper::Set_DX8_Texture_Stage_State( 2, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_PASSTHRU|2);

	DX8Wrapper::Set_DX8_Texture_Stage_State( 3, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
	DX8Wrapper::Set_DX8_Texture_Stage_State( 3, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_PASSTHRU|3);


	DX8Wrapper::Invalidate_Cached_Render_States();
}




///Cloud layer rendering shader - used for objects similar to terrain which only need the cloud layer.
class CloudTextureShader : public W3DShaderInterface
{
	virtual Int set(Int stage);		///<setup shader for the specified rendering pass.
	virtual Int init(void);			///<perform any one time initialization and validation
	virtual void reset(void);		///<do any custom resetting necessary to bring W3D in sync.
	Int m_stageOfSet;
} cloudTextureShader;

///List of different cloud shader implementations in order of preference
W3DShaderInterface *CloudShaderList[]=
{
	&cloudTextureShader,
	NULL
};

// ?init@CloudTextureShader@@EAEHXZ present-unmatched
Int CloudTextureShader::init(void)
{
	W3DShaders[W3DShaderManager::ST_CLOUD_TEXTURE]=&cloudTextureShader;
	W3DShadersPassCount[W3DShaderManager::ST_CLOUD_TEXTURE]=1;

	return TRUE;
}

/**Setup a certain texture stage to project our cloud texture*/
// ?set@CloudTextureShader@@EAEHH@Z present-unmatched
Int CloudTextureShader::set(Int stage)
{
	Matrix4x4 curView;
	DX8Wrapper::_Get_DX8_Transform(D3DTS_VIEW, curView);

	D3DXMATRIX inv;
	float det;

	D3DXMatrixInverse(&inv, &det, (D3DXMATRIX*)&curView);

	//Get a texture matrix that applies the current cloud position
	terrainShader2Stage.updateNoise1(((D3DXMATRIX*)&curView),&inv,false);	//update curView with texture matrix

	DX8Wrapper::Set_DX8_Texture_Stage_State(stage,  D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
	DX8Wrapper::Set_DX8_Texture_Stage_State(stage,  D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);	
	DX8Wrapper::_Set_DX8_Transform((D3DTRANSFORMSTATETYPE )(D3DTS_TEXTURE0+stage), curView);
	DX8Wrapper::Set_DX8_Texture_Stage_State(stage, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
	DX8Wrapper::Set_DX8_Texture_Stage_State(stage, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
	DX8Wrapper::Set_DX8_Texture_Stage_State(stage, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
	DX8Wrapper::Set_DX8_Texture_Stage_State(stage, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);

	DX8Wrapper::Set_DX8_Texture_Stage_State( stage, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	DX8Wrapper::Set_DX8_Texture_Stage_State( stage, D3DTSS_COLORARG2, D3DTA_CURRENT );
	DX8Wrapper::Set_DX8_Texture_Stage_State( stage, D3DTSS_COLOROP,   D3DTOP_MODULATE );
	DX8Wrapper::Set_DX8_Texture_Stage_State( stage, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
	DX8Wrapper::Set_DX8_Texture_Stage_State( stage, D3DTSS_ALPHAARG2, D3DTA_CURRENT );
	DX8Wrapper::Set_DX8_Texture_Stage_State( stage, D3DTSS_ALPHAOP,   D3DTOP_MODULATE );

	DX8Wrapper::_Get_D3D_Device8()->SetTexture(stage, W3DShaderManager::getShaderTexture(stage)->Peek_D3D_Texture());

	m_stageOfSet=stage;
	return TRUE;
}

void CloudTextureShader::reset(void)
{
	//Free reference to texture
	bfmeSetTexture(m_stageOfSet, NULL);
	//Turn off texture projection
	DX8Wrapper::Set_DX8_Texture_Stage_State( m_stageOfSet, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
	DX8Wrapper::Set_DX8_Texture_Stage_State( m_stageOfSet, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_PASSTHRU|m_stageOfSet);

	DX8Wrapper::Set_DX8_Texture_Stage_State( m_stageOfSet, D3DTSS_COLOROP,   D3DTOP_DISABLE );
	DX8Wrapper::Set_DX8_Texture_Stage_State( m_stageOfSet, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
}

/*===========================================================================================*/
/*=========      Road Shaders	=========================================================*/
/*===========================================================================================*/
class RoadShaderPixelShader : public W3DShaderInterface
{
	DWORD					m_dwBaseNoise2PixelShader;	///<handle to road/double noise D3D pixel shader

	virtual Int set(Int pass);		///<setup shader for the specified rendering pass.
	virtual void reset(void);		///<do any custom resetting necessary to bring W3D in sync.
	virtual Int init(void);			///<perform any one time initialization and validation
	virtual Int shutdown(void);			///<release resources used by shader
} roadShaderPixelShader;

class RoadShader2Stage : public W3DShaderInterface
{	friend class RoadShaderPixelShader;	//pixel shader version uses some of the same features.

	virtual Int set(Int pass);		///<setup shader for the specified rendering pass.
	virtual Int init(void);			///<perform any one time initialization and validation
	virtual void reset(void);
} roadShader2Stage;

///List of different terrain shader implementations in order of preference
W3DShaderInterface *RoadShaderList[]=
{
	&roadShaderPixelShader,
	&roadShader2Stage,
	NULL
};

// ?shutdown@RoadShaderPixelShader@@EAEHXZ present-unmatched
Int RoadShaderPixelShader::shutdown(void)
{
	if (m_dwBaseNoise2PixelShader)
		DX8Wrapper::_Get_D3D_Device8()->DeletePixelShader(m_dwBaseNoise2PixelShader);

	m_dwBaseNoise2PixelShader=NULL;

	return TRUE;
}

// byte-exact reconstruction: game/GameEngineDevice/Source/W3DDevice/GameClient/RoadShaderPixelShader_init.cpp
// ?init@RoadShaderPixelShader@@EAEHXZ present-unmatched
Int RoadShaderPixelShader::init( void )
{	
	Int res;

	//this shader will also use the 2Stage shader for some of the passes so initialize it too.
	if (roadShader2Stage.init() && (res=W3DShaderManager::getChipset()) >= DC_GENERIC_PIXEL_SHADER_1_1)
	{
		if (res >= DC_GENERIC_PIXEL_SHADER_1_1)
		{
			//this shader needs some assets that need to be loaded
			//shader decleration
			DWORD Declaration[]=
			{
				(D3DVSD_STREAM(0)),
				(D3DVSD_REG(0, D3DVSDT_FLOAT3)), // Position
				(D3DVSD_REG(1, D3DVSDT_D3DCOLOR)), // Diffuse
				(D3DVSD_REG(2, D3DVSDT_FLOAT2)), //  Texture Coordinates
				(D3DVSD_END())
			};

			//version which blends 2 noise textures.
			HRESULT hr = W3DShaderManager::LoadAndCreateD3DShader("shaders\\roadnoise2.pso", &Declaration[0], 0, false, &m_dwBaseNoise2PixelShader);
			if (FAILED(hr))
				return FALSE;

			//Only set this shader for use in dual noise mode.  The 2Stage shader will take care of
			//all the other modes.
			W3DShaders[W3DShaderManager::ST_ROAD_BASE_NOISE12]=&roadShaderPixelShader;
			W3DShadersPassCount[W3DShaderManager::ST_ROAD_BASE_NOISE12]=1;
			return TRUE;
		}
	}
	return FALSE;
}

// ?set@RoadShaderPixelShader@@EAEHH@Z present-unmatched
Int RoadShaderPixelShader::set(Int pass)
{
	DX8Wrapper::Set_Texture(0,W3DShaderManager::getShaderTexture(0));
	//force WW3D2 system to set it's states so it won't later overwrite our custom settings.
	DX8Wrapper::Apply_Render_State_Changes();

	//tell pixel shader which UV set to use for each stage
	DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_TEXCOORDINDEX, 0 );

	DX8Wrapper::Set_DX8_Render_State(D3DRS_ZFUNC,D3DCMP_LESSEQUAL);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ZWRITEENABLE,FALSE);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_LIGHTING, FALSE);

// byte-exact reconstruction: game/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWater.cpp
// ?Set_DX8_Render_State@DX8Wrapper@@SAXKI@Z present-unmatched
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHABLENDENABLE,true);	//blend roads into terrain
	DX8Wrapper::Set_DX8_Render_State(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	Matrix4x4 curView;
	DX8Wrapper::_Get_DX8_Transform(D3DTS_VIEW, curView);

	D3DXMATRIX inv;
	float det;
	D3DXMatrixInverse(&inv, &det, (D3DXMATRIX*)&curView);

	if (TheGlobalData && TheGlobalData->m_trilinearTerrainTex)
	{	DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
	}
	else
	{	DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_MIPFILTER, D3DTEXF_POINT);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MIPFILTER, D3DTEXF_POINT);
	}

	DX8Wrapper::Set_DX8_Texture_Stage_State(1,  D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
	// Two output coordinates are used.
	DX8Wrapper::Set_DX8_Texture_Stage_State(1,  D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);	

	DX8Wrapper::Set_DX8_Texture_Stage_State(1,  D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
	DX8Wrapper::Set_DX8_Texture_Stage_State(1,  D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
	
	DX8Wrapper::Set_DX8_Texture_Stage_State(2,  D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
	DX8Wrapper::Set_DX8_Texture_Stage_State(2,  D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);

	DX8Wrapper::Set_Texture(1,W3DShaderManager::getShaderTexture(1));
	DX8Wrapper::Set_Texture(2,W3DShaderManager::getShaderTexture(2));

	DX8Wrapper::_Get_D3D_Device8()->SetPixelShader(m_dwBaseNoise2PixelShader);

	DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
	DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);

	DX8Wrapper::Set_DX8_Texture_Stage_State(2, D3DTSS_MINFILTER, D3DTEXF_POINT);
	DX8Wrapper::Set_DX8_Texture_Stage_State(2, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);

	terrainShader2Stage.updateNoise1(((D3DXMATRIX*)&curView),&inv, false);	//get texture projection matrix
	DX8Wrapper::_Set_DX8_Transform(D3DTS_TEXTURE1, curView);

	terrainShader2Stage.updateNoise2(((D3DXMATRIX*)&curView),&inv, false);	//get texture projection matrix
	DX8Wrapper::_Set_DX8_Transform(D3DTS_TEXTURE2, curView);

	DX8Wrapper::Set_DX8_Texture_Stage_State(2,  D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
	// Two output coordinates are used.
	DX8Wrapper::Set_DX8_Texture_Stage_State(2,  D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);	

	return TRUE;
}

void RoadShaderPixelShader::reset(void)
{

	bfmeSetTexture(2,NULL);	//release reference to any texture
	bfmeSetTexture(3,NULL);	//release reference to any texture

	bfmeSetPixelShader(0);	//turn off pixel shader

	bfmeSetTexture(0, NULL);
	bfmeSetTexture(1, NULL);

	DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
	DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_PASSTHRU|0);

	DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
	DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_PASSTHRU|1);

	DX8Wrapper::Set_DX8_Texture_Stage_State( 2, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
	DX8Wrapper::Set_DX8_Texture_Stage_State( 2, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_PASSTHRU|2);

	DX8Wrapper::Set_DX8_Texture_Stage_State( 3, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
	DX8Wrapper::Set_DX8_Texture_Stage_State( 3, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_PASSTHRU|3);


	DX8Wrapper::Invalidate_Cached_Render_States();
}

// ?init@RoadShader2Stage@@EAEHXZ present-unmatched
Int RoadShader2Stage::init( void )
{
	//no special device validation needed - anything in our min spec should handle this.
	W3DShaders[W3DShaderManager::ST_ROAD_BASE]=&roadShader2Stage;
	W3DShadersPassCount[W3DShaderManager::ST_ROAD_BASE]=1;
	W3DShaders[W3DShaderManager::ST_ROAD_BASE_NOISE1]=&roadShader2Stage;
	W3DShadersPassCount[W3DShaderManager::ST_ROAD_BASE_NOISE1]=1;
	W3DShaders[W3DShaderManager::ST_ROAD_BASE_NOISE2]=&roadShader2Stage;
	W3DShadersPassCount[W3DShaderManager::ST_ROAD_BASE_NOISE2]=1;
	W3DShaders[W3DShaderManager::ST_ROAD_BASE_NOISE12]=&roadShader2Stage;
	W3DShadersPassCount[W3DShaderManager::ST_ROAD_BASE_NOISE12]=2;

	return TRUE;
}

// ?set@RoadShader2Stage@@EAEHH@Z present-unmatched
Int RoadShader2Stage::set(Int pass)																											  
{
	//First stage always contains base texture.
	DX8Wrapper::Set_Texture(0,W3DShaderManager::getShaderTexture(0));
	//Force system to apply world/view transforms.
	DX8Wrapper::Apply_Render_State_Changes();

	DX8Wrapper::Set_DX8_Render_State(D3DRS_ZFUNC,D3DCMP_LESSEQUAL);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ZWRITEENABLE,FALSE);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_LIGHTING, FALSE);

	// Modulate the diffuse color with the texture as lighting comes from diffuse.
	DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
	DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
	DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
	DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
	DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE );

	DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_TEXCOORDINDEX, 0 );
// byte-exact reconstruction: game/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWater.cpp
// ?Set_DX8_Render_State@DX8Wrapper@@SAXKI@Z present-unmatched
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHABLENDENABLE,true);	//blend roads into terrain

	if (pass == 0)
	{	
		DX8Wrapper::Set_DX8_Render_State(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

		if (W3DShaderManager::getCurrentShader() >= W3DShaderManager::ST_ROAD_BASE_NOISE1)
		{	//second texture unit will contain a noise pass
			Matrix4x4 curView;
			DX8Wrapper::_Get_DX8_Transform(D3DTS_VIEW, curView);

			D3DXMATRIX inv;
			float det;
			D3DXMatrixInverse(&inv, &det, (D3DXMATRIX*)&curView);

			if (TheGlobalData && TheGlobalData->m_trilinearTerrainTex)
				DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
			else
				DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MIPFILTER, D3DTEXF_POINT);

			DX8Wrapper::Set_DX8_Texture_Stage_State(1,  D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
			// Two output coordinates are used.
			DX8Wrapper::Set_DX8_Texture_Stage_State(1,  D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);	

			DX8Wrapper::Set_DX8_Texture_Stage_State(1,  D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
			DX8Wrapper::Set_DX8_Texture_Stage_State(1,  D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);

			DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_COLORARG1, D3DTA_TEXTURE );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_COLORARG2, D3DTA_CURRENT );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_COLOROP,   D3DTOP_MODULATE );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_ALPHAARG2, D3DTA_CURRENT );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_ALPHAOP,   D3DTOP_MODULATE );

			if (W3DShaderManager::getCurrentShader() == W3DShaderManager::ST_ROAD_BASE_NOISE12)
			{	//full shader, apply noise 1 in pass 0.
				DX8Wrapper::Set_Texture(1,W3DShaderManager::getShaderTexture(1));
				DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
				DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);

				terrainShader2Stage.updateNoise1(((D3DXMATRIX*)&curView),&inv, false);	//get texture projection matrix
				DX8Wrapper::_Set_DX8_Transform(D3DTS_TEXTURE1, curView);
			}
			else
			{	//single noise texture shader
				if (W3DShaderManager::getCurrentShader() == W3DShaderManager::ST_ROAD_BASE_NOISE1)
				{	//cloud map
					DX8Wrapper::Set_Texture(1,W3DShaderManager::getShaderTexture(1));
					terrainShader2Stage.updateNoise1(((D3DXMATRIX*)&curView),&inv, false);	//update curView with texture matrix
					DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
					DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
				}
				else
				{	//light map
					DX8Wrapper::Set_Texture(1,W3DShaderManager::getShaderTexture(2));
					terrainShader2Stage.updateNoise2(((D3DXMATRIX*)&curView),&inv, false);	//update curView with texture matrix
					DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MINFILTER, D3DTEXF_POINT);
					DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
				}
				DX8Wrapper::_Set_DX8_Transform(D3DTS_TEXTURE1, curView);
			}
		}
		else
		{	//just base texturing
			DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_COLOROP,   D3DTOP_DISABLE );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
		}
	}	//pass 0
	else
	{	//pass 1, apply additional noise pass
		Matrix4x4 curView;
		DX8Wrapper::_Get_DX8_Transform(D3DTS_VIEW, curView);

		D3DXMATRIX inv;
		float det;
		D3DXMatrixInverse(&inv, &det, (D3DXMATRIX*)&curView);

		if (TheGlobalData && TheGlobalData->m_trilinearTerrainTex)
			DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
		else
			DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MIPFILTER, D3DTEXF_POINT);

		DX8Wrapper::Set_Texture(1,W3DShaderManager::getShaderTexture(2));

		terrainShader2Stage.updateNoise2(((D3DXMATRIX*)&curView),&inv, false);	//update curView with texture matrix
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MINFILTER, D3DTEXF_POINT);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);

		DX8Wrapper::Set_DX8_Texture_Stage_State(1,  D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
		// Two output coordinates are used.
		DX8Wrapper::Set_DX8_Texture_Stage_State(1,  D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);	

		DX8Wrapper::Set_DX8_Texture_Stage_State(1,  D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1,  D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);

		//Copy alpha channel into stage 1 but mask out color channel by replacing with white.
		DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		//Force color channel to white by copying the alpha into RGB
		DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE|D3DTA_ALPHAREPLICATE);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG2);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
		DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
		DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1 );

		DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_COLORARG2, D3DTA_CURRENT );
		DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_COLOROP,   D3DTOP_BLENDCURRENTALPHA);
		DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
		DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_ALPHAARG2, D3DTA_CURRENT );
		DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );

		//Modulate into existing roads with clouds applied. - only apply where roads are transparent by
		//using road texture as a mask.
		DX8Wrapper::Set_DX8_Render_State(D3DRS_SRCBLEND,D3DBLEND_ZERO);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_DESTBLEND,D3DBLEND_SRCCOLOR);

		DX8Wrapper::_Set_DX8_Transform(D3DTS_TEXTURE0, curView);
	}

	return TRUE;
}

void RoadShader2Stage::reset(void)
{
	ShaderClass::Invalidate();

	//Free references to textures
	bfmeSetTexture(0, NULL);
	bfmeSetTexture(1, NULL);

	DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
	DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_PASSTHRU|0);

	DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
	DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_PASSTHRU|1);
}

/** List of all custom shader lists - each list in this list contains variations of the same
	shader to allow it to work on different hardware configurations.
*/
W3DShaderInterface **MasterShaderList[]=
{
	TerrainShaderList,
	ShroudShaderList,
	FlatShroudShaderList,
	RoadShaderList,
	MaskShaderList,
	CloudShaderList,
	FlatTerrainShaderList,
	NULL
};

/** List of all custom filter lists - each list in this list contains variations of the same
	filter to allow it to work on different hardware configurations.
*/
W3DFilterInterface **MasterFilterList[]=
{
	ScreenDefaultFilterList,
	ScreenBWFilterList,
	ScreenMotionBlurFilterList,
	ScreenCrossFadeFilterList,
	NULL
};

// W3DShaderManager::W3DShaderManager =========================================
/** Constructor - just clears some variables */
//=============================================================================
W3DShaderManager::W3DShaderManager(void)
{
	m_currentShader = ST_INVALID;
	m_currentFilter = FT_NULL_FILTER;
	m_oldRenderSurface = NULL;
	m_renderTexture = NULL;
	m_newRenderSurface = NULL;
	m_oldDepthSurface = NULL;
	m_renderingToTexture = false;
	__identifier("?m_resource012F9D14@W3DShaderManager@@1PAUShaderComResource@@A") = NULL;
	__identifier("?m_resource012F9D18@W3DShaderManager@@1PAUShaderComResource@@A") = NULL;
	ShaderQuadBuffer = NULL;
	ShaderQuadIndex = 0;
	Int i;
	for (i=0; i<W3DShaderManager::ST_MAX; i++)
	{	W3DShaders[i]=NULL;
		W3DShadersPassCount[i]=0;
	}
	for (i=0; i<10; i++)
	{	W3DFilters[i]=NULL;
	}
	m_currentShader=(W3DShaderManager::ShaderTypes)-1;
}

class BfmeChipsetDetector
{
public:
	static void detect();
};

extern void j_0000cf8b();

extern ShaderComResource *__identifier("?m_resource012F9D24@W3DShaderManager@@1PAUShaderComResource@@A");

class BfmeVertexShaderLoader
{
public:
	static HRESULT LoadAndCreateD3DShader(const char *filename, DWORD *shader);
};

struct BfmeVertexElement
{
	unsigned short stream;
	unsigned short offset;
	unsigned char type;
	unsigned char method;
	unsigned char usage;
	unsigned char usageIndex;
};

class BfmeShaderD3DDevice
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3c();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4c();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5c();
	virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6c();
	virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7c();
	virtual void slot80(); virtual void slot84(); virtual void slot88(); virtual void slot8c();
	virtual void slot90(); virtual void slot94(); virtual void slot98(); virtual void slot9c();
	virtual void slota0(); virtual void slota4(); virtual void slota8(); virtual void slotac();
	virtual void slotb0(); virtual void slotb4(); virtual void slotb8(); virtual void slotbc();
	virtual void slotc0(); virtual void slotc4(); virtual void slotc8(); virtual void slotcc();
	virtual void slotd0(); virtual void slotd4(); virtual void slotd8(); virtual void slotdc();
	virtual void slote0(); virtual void slote4(); virtual void slote8(); virtual void slotec();
	virtual void slotf0(); virtual void slotf4(); virtual void slotf8(); virtual void slotfc();
	virtual void slot100(); virtual void slot104(); virtual void slot108(); virtual void slot10c();
	virtual void slot110(); virtual void slot114(); virtual void slot118(); virtual void slot11c();
	virtual void slot120(); virtual void slot124(); virtual void slot128(); virtual void slot12c();
	virtual void slot130(); virtual void slot134(); virtual void slot138(); virtual void slot13c();
	virtual void slot140(); virtual void slot144(); virtual void slot148(); virtual void slot14c();
	virtual void slot150(); virtual void slot154();
	virtual HRESULT __stdcall CreateVertexShader(
		const BfmeVertexElement *declaration, DWORD *shader);
};

typedef W3DShaderInterface **BfmeMasterShaderEntry;
typedef W3DFilterInterface **BfmeMasterFilterEntry;
typedef BfmeMasterShaderEntry BfmeMasterShaderList[100];
typedef BfmeMasterFilterEntry BfmeMasterFilterList[100];

#define BFME_MASTER_SHADER_LIST MasterShaderList
#define BFME_MASTER_FILTER_LIST MasterFilterList
#define BFME_GLOW_VERTEX_DECLARATION ((*reinterpret_cast<DWORD *>(&__identifier("?m_resource012F9D24@W3DShaderManager@@1PAUShaderComResource@@A"))))
#define BFME_GLOW_VERTEX_SHADER ((*reinterpret_cast<DWORD *>(&__identifier("?m_resource012F9D18@W3DShaderManager@@1PAUShaderComResource@@A"))))
#define BFME_GLOW_PIXEL_SHADER ((*reinterpret_cast<DWORD *>(&__identifier("?m_resource012F9D14@W3DShaderManager@@1PAUShaderComResource@@A"))))

// W3DShaderManager::init =======================================================
void W3DShaderManager::init(void)
{
	BfmeChipsetDetector::detect();
	j_0000cf8b();

	W3DShaderInterface **shaders;
	for (Int i = 0; BFME_MASTER_SHADER_LIST[i] != 0; ++i) {
		shaders = BFME_MASTER_SHADER_LIST[i];
		for (Int j = 0; shaders[j] != 0; ++j) {
			if (shaders[j]->init())
				break;
		}
	}

	W3DFilterInterface **filters;
	for (Int i = 0; BFME_MASTER_FILTER_LIST[i] != 0; ++i) {
		filters = BFME_MASTER_FILTER_LIST[i];
		for (Int j = 0; filters[j] != 0; ++j) {
			if (filters[j]->init())
				break;
		}
	}

	if (*(unsigned char *)((char *)TheWritableGlobalData + 0x28) == 0 &&
		m_currentChipset >= BFME_DC_GENERIC_PIXEL_SHADER_1_1) {
		BfmeVertexElement declaration[] = {
			{ 0, 0, 3, 0, 0, 0 },
			{ 0, 0x10, 4, 0, 0x0a, 0 },
			{ 0, 0x14, 1, 0, 5, 0 },
			{ 0xff, 0, 0x11, 0, 0, 0 }
		};
		if ((*reinterpret_cast<DWORD *>(&__identifier("?m_resource012F9D24@W3DShaderManager@@1PAUShaderComResource@@A"))) == 0) {
			BfmeShaderD3DDevice *device = (BfmeShaderD3DDevice *)DX8Wrapper::_Get_D3D_Device8();
			if (device->CreateVertexShader(
				declaration, &(*reinterpret_cast<DWORD *>(&__identifier("?m_resource012F9D24@W3DShaderManager@@1PAUShaderComResource@@A")))) < 0)
				(*reinterpret_cast<DWORD *>(&__identifier("?m_resource012F9D24@W3DShaderManager@@1PAUShaderComResource@@A"))) = 0;
		}

		if (BfmeVertexShaderLoader::LoadAndCreateD3DShader(
			"shaders\\Glow.vso", &BFME_GLOW_VERTEX_SHADER) < 0)
			BFME_GLOW_VERTEX_SHADER = 0;

		if (BfmeShaderLoader::LoadAndCreateD3DShader(
			"shaders\\Glow.pso", &BFME_GLOW_PIXEL_SHADER) < 0)
			BFME_GLOW_PIXEL_SHADER = 0;
	}
}

// W3DShaderManager::shutdown: retail 0x00717DA0, W3DShaderManagerShutdown.cpp.

// W3DShaderManager::getShaderPasses =======================================================
/** Return number of renderig passes required in perform the desired shader on current
	hardware.  App will need to re-render the polygons this many times to complete the
	effect.
 */
//=============================================================================
// ?getShaderPasses@W3DShaderManager@@SAHW4ShaderTypes@1@@Z present-unmatched
Int W3DShaderManager::getShaderPasses(ShaderTypes shader)
{
	return W3DShadersPassCount[shader];
}

// W3DShaderManager::setShader =======================================================
/** Must call this method before each rendering pass in order to perform proper D3D
	setup for each shader.
 */
//=============================================================================
Int W3DShaderManager::setShader(ShaderTypes shader, Int pass)
{
	if (shader == m_currentShader && pass == m_currentShaderPass)
		return TRUE;	//shader is already set
	m_currentShader=shader;
	m_currentShaderPass = pass;
	if (W3DShaders[shader])
		return W3DShaders[shader]->set(pass);
	return FALSE;
}

// W3DShaderManager::resetShader =======================================================
/** Must call this method after all polygons and rendering passes have been submitted.
	This method allows D3D to reset itself to a default state that doesn't conflict
	with the WW3D2 Shader system.
 */
//=============================================================================
void W3DShaderManager::resetShader(ShaderTypes shader)
{	
	if (m_currentShader == ST_INVALID)
		return;	//last shader is already reset.
	if (W3DShaders[shader])
		W3DShaders[shader]->reset();
	m_currentShader = ST_INVALID;
}
// W3DShaderManager::filterPreRender =======================================================
/** Call to view filter shaders before rendering starts.
 */
//=============================================================================
Bool W3DShaderManager::filterPreRender(FilterTypes filter, Bool &skipRender, CustomScenePassModes &scenePassMode)
{
	if (W3DFilters[filter])
	{	Bool result=W3DFilters[filter]->preRender(skipRender,scenePassMode);
		if (result)
			m_currentFilter = filter;
		return result;
	}
	return FALSE;
}

// W3DShaderManager::filterPostRender =======================================================
/** Call to view filter shaders after rendering is complete.
 */
//=============================================================================
// byte-exact reconstruction: game/GameEngine/Source/Common/W3DShaderManagerFilterPostRender.cpp
// ?filterPostRender@W3DShaderManager@@SA_NW4FilterTypes@@W4FilterModes@@AAUCoord2D@@AA_N@Z present-unmatched
Bool W3DShaderManager::filterPostRender(FilterTypes filter, enum FilterModes mode, Coord2D &scrollDelta, Bool &doExtraRender)
{
	if (W3DFilters[filter])
		return W3DFilters[filter]->postRender(mode, scrollDelta,doExtraRender);

	m_currentFilter = FT_NULL_FILTER;
	return FALSE;
}

// W3DShaderManager::filterPostRender =======================================================
/** Call to view filter shaders after rendering is complete.
 */
//=============================================================================
	static Bool filterSetup(FilterTypes filter, enum FilterModes mode);
Bool W3DShaderManager::filterSetup(FilterTypes filter, enum FilterModes mode)
{
	if (W3DFilters[filter])
		return W3DFilters[filter]->setup(mode);
	return FALSE;
}

/*Draws 2 triangles covering the viewport given the current render states*/
// ?drawViewport@W3DShaderManager@@ present-unmatched
void W3DShaderManager::drawViewport(Int color)
{
	LPDIRECT3DDEVICE8 pDev=DX8Wrapper::_Get_D3D_Device8();

	struct _TRANS_LIT_TEX_VERTEX {
		D3DXVECTOR4 p;
		DWORD color;   // diffuse color    
		float	u;
		float	v;
	} v[4];

	Int xpos, ypos, width, height;

	TheTacticalView->getOrigin(&xpos,&ypos);
	width=TheTacticalView->getWidth();
	height=TheTacticalView->getHeight();

	//bottom right
	v[0].p = D3DXVECTOR4( xpos+width-0.5f, ypos+height-0.5f, 0.0f, 1.0f );
	v[0].u = (Real)(xpos+width)/(Real)TheDisplay->getWidth();	v[0].v = (Real)(ypos+height)/(Real)TheDisplay->getHeight();
	//top right
	v[1].p = D3DXVECTOR4( xpos+width-0.5f, ypos-0.5f, 0.0f, 1.0f );
	v[1].u = (Real)(xpos+width)/(Real)TheDisplay->getWidth();	v[1].v = (Real)(ypos)/(Real)TheDisplay->getHeight();
	//bottom left
	v[2].p = D3DXVECTOR4(  xpos-0.5f, ypos+height-0.5f, 0.0f, 1.0f );
	v[2].u = (Real)(xpos)/(Real)TheDisplay->getWidth();	v[2].v = (Real)(ypos+height)/(Real)TheDisplay->getHeight();
	//top left
	v[3].p = D3DXVECTOR4(  xpos-0.5f,  ypos-0.5f, 0.0f, 1.0f );
	v[3].u = (Real)(xpos)/(Real)TheDisplay->getWidth();	v[3].v = (Real)(ypos)/(Real)TheDisplay->getHeight();
	v[0].color = color;
	v[1].color = color;
	v[2].color = color;
	v[3].color = color;

	//draw polygons like this is very inefficient but for only 2 triangles, it's
	//not worth bothering with index/vertex buffers.
	pDev->SetVertexShader(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	pDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(_TRANS_LIT_TEX_VERTEX));
}

// W3DShaderManager::startRenderToTexture =======================================================
/** Starts rendering to a texture.
 */
//=============================================================================
// byte-exact reconstruction: game/GameEngine/Source/Common/ExactStaticThunks.cpp
// ?startRenderToTexture@W3DShaderManager@@SAXXZ present-unmatched
void W3DShaderManager::startRenderToTexture(void)
{	
	DEBUG_ASSERTCRASH(!m_renderingToTexture, ("Already rendering to texture - cannot nest calls."));

	if (m_renderingToTexture || m_newRenderSurface==NULL || m_oldDepthSurface==NULL) return;
	HRESULT hr = DX8Wrapper::_Get_D3D_Device8()->SetRenderTarget(m_newRenderSurface,m_oldDepthSurface);
	DEBUG_ASSERTCRASH(hr==S_OK, ("Set target failed unexpectedly."));
	if (hr != S_OK)
		return;
	m_renderingToTexture = true;
	if (TheGlobalData->m_showSoftWaterEdge)
	{	//Soft water edges use frame buffer destination alpha so we must clear it to a known value.
		if (m_currentFilter == FT_VIEW_MOTION_BLUR_FILTER || m_currentFilter == FT_VIEW_CROSSFADE)
		{	//these filters rely on the previous frame being visible so we must be careful about clearing
			//frame buffer.  Only clear the alpha channel
// byte-exact reconstruction: game/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWater.cpp
// ?Set_DX8_Render_State@DX8Wrapper@@SAXKI@Z present-unmatched
			DX8Wrapper::Set_DX8_Render_State(D3DRS_COLORWRITEENABLE,D3DCOLORWRITEENABLE_ALPHA);	//only clear alpha
			ShaderClass shader=ShaderClass::_PresetOpaqueSolidShader;
			shader.Set_Depth_Compare(ShaderClass::PASS_ALWAYS);
			shader.Set_Depth_Mask(ShaderClass::DEPTH_WRITE_DISABLE);
			DX8Wrapper::Set_Shader(shader);

			VertexMaterialClass *vmat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
			DX8Wrapper::Set_Material(vmat);
			REF_PTR_RELEASE(vmat);	//no need to keep a reference since it's a preset.
		
			drawViewport(0x00ffffff | (((Int)(TheWaterTransparency->m_minWaterOpacity*255.0f)) <<24));
// byte-exact reconstruction: game/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWater.cpp
// ?Set_DX8_Render_State@DX8Wrapper@@SAXKI@Z present-unmatched
			DX8Wrapper::Set_DX8_Render_State(D3DRS_COLORWRITEENABLE,D3DCOLORWRITEENABLE_RED|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_BLUE);	//disable writes to alpha
		}
		else	//normal clear that overwrites everything.
			DX8Wrapper::Clear(true, false, Vector3( 0.0f, 0.0f, 0.0f ), TheWaterTransparency->m_minWaterOpacity);
	}
}

// W3DShaderManager::startRenderToTexture =======================================================
/** Ends rendering to a texture.
 */
//=============================================================================
// endRenderToTexture: retail body matched in W3DShaderManagerEndRenderToTexture.cpp.

/**Returns texture containing the image that was last rendered using any of the effects requiring render target
textures.  Used mostly for cross-fading effects that need an unmodified version of the view before the effect
was applied.  NOTE: This texture does not survive device reset.. so quit effect on reset!*/
// ?getRenderTexture@W3DShaderManager@@SAPAUIDirect3DTexture8@@XZ present-unmatched
IDirect3DTexture8 *W3DShaderManager::getRenderTexture(void)
{
	return m_renderTexture;
}

enum GraphicsVenderID
{
	DC_NVIDIA_VENDOR_ID	= 0x10DE,
	DC_3DFX_VENDOR_ID	= 0x121A,
	DC_ATI_VENDOR_ID	= 0x1002
};

// W3DShaderManager::ChipsetType =======================================================
/** Returns the chipset used by the currently active rendering device.  Can be useful
	for coding around specific driver bugs.
 */
//=============================================================================
#if 0
ChipsetType W3DShaderManager::getChipset( void )
{
	//check if globaldata has an override for current chipset
	if (TheGlobalData && TheGlobalData->m_chipSetType != DC_UNKNOWN)
		return (ChipsetType)TheGlobalData->m_chipSetType;

	ChipsetType chip=DC_UNKNOWN;
	IDirect3D8* d3d8Interface=DX8Wrapper::_Get_D3D8();

	if (d3d8Interface && DX8Wrapper::_Get_D3D_Device8())
	{

		D3DADAPTER_IDENTIFIER8 did;
		::ZeroMemory(&did, sizeof(D3DADAPTER_IDENTIFIER8));
	/*	HRESULT res = */ d3d8Interface->GetAdapterIdentifier(0,D3DENUM_NO_WHQL_LEVEL,&did);
		*((LARGE_INTEGER*)&m_driverVersion) = did.DriverVersion;

		if(did.VendorId == DC_NVIDIA_VENDOR_ID)
		{
			m_currentVendor = DC_NVIDIA_VENDOR_ID;

			if (did.DeviceId == 0x20)
				return DC_TNT;
   
			if (did.DeviceId >= 0x28 && did.DeviceId < 0x100)
				return DC_TNT2;

			if ( (did.DeviceId >= 0x100 && did.DeviceId <= 0x103) ||	//GeForce
				 (did.DeviceId >= 0x110 && did.DeviceId <= 0x113) ||	//GeForce2 MX
						 (did.DeviceId >= 0x150 && did.DeviceId <= 0x153) )	//GeForce2
           		return DC_GEFORCE2;

			if (did.DeviceId >= 0x200 && did.DeviceId < 0x250)
				return DC_GEFORCE3;

			if (did.DeviceId >= 0x250)
				return DC_GEFORCE4;
		}
		else
		if(did.VendorId == DC_3DFX_VENDOR_ID)
		{
			m_currentVendor = DC_3DFX_VENDOR_ID;

			if (did.DeviceId == 0x0002)
				return DC_VOODOO2;
			if (did.DeviceId == 0x0005)
				return DC_VOODOO3;
			if (did.DeviceId == 0x0008)	///@todo: Just guessing on this one - find actual Voodoo4 deviceID.
				return DC_VOODOO4;
			if (did.DeviceId == 0x0009)
				return DC_VOODOO5;
		}
		else
		if(did.VendorId == DC_ATI_VENDOR_ID)
		{
			m_currentVendor = DC_ATI_VENDOR_ID;

			if (did.DeviceId == 0x5144)
				return DC_RADEON;
			if (did.DeviceId == 0x514C)
				return DC_RADEON_8500;
			if (did.DeviceId == 0x4e44)
				return DC_RADEON_9700;
		}

		//None of the vendor specific ID's matched so use generic means to classify the card
		Int maxTextures=DX8Wrapper::Get_Current_Caps()->Get_Max_Simultaneous_Textures();
		Real pixelShaderVersion;

		char buf[256];

		//Convert version to Real
		sprintf(buf,"%d.%d",DX8Wrapper::Get_Current_Caps()->Get_Pixel_Shader_Major_Version(),DX8Wrapper::Get_Current_Caps()->Get_Pixel_Shader_Minor_Version());
		sscanf(buf,"%f",&pixelShaderVersion);

		if (maxTextures >= 4)
		{	if (pixelShaderVersion >= 1.1f)
				chip=DC_GENERIC_PIXEL_SHADER_1_1;
			if (pixelShaderVersion >= 1.4f)
				chip=DC_GENERIC_PIXEL_SHADER_1_4;
			if (maxTextures >= 8 && pixelShaderVersion >= 2.0f)
				chip=DC_GENERIC_PIXEL_SHADER_2_0;
		}
	}	//D3D8 interface and device exist. 
	
	return chip;
}
#endif

// Retail's active implementation is the compact global override accessor.
__declspec(noinline) ChipsetType W3DShaderManager::getChipset( void )
{
	if (*(volatile unsigned char *)((char *)TheGlobalData + 0x28)
		&& m_currentChipset >= BFME_DC_GENERIC_PIXEL_SHADER_1_1)
		return (ChipsetType)2;

	return m_currentChipset;
}

// The BFME GPU-index body inlines this compact chipset query. Keep the
// protected static behind a derived view so the source remains ordinary C++
// while preserving the retail's BFME chipset thresholds (1 and 3).
class BfmeGpuChipsetQuery : public W3DShaderManager
{
public:
	static __forceinline ChipsetType query(void)
	{
		if (*(volatile unsigned char *)((char *)TheGlobalData + 0x28)
			&& m_currentChipset >= BFME_DC_GENERIC_PIXEL_SHADER_1_1)
			return (ChipsetType)2;
		return m_currentChipset;
	}
};

//=============================================================================
// WaterRenderObjClass::LoadAndCreateShader
//=============================================================================
/** Loads and creates a D3D pixel or vertex shader.*/
//=============================================================================
// ?LoadAndCreateD3DShader@W3DShaderManager@@SAJPADPBKK_NPAK@Z present-unmatched
HRESULT W3DShaderManager::LoadAndCreateD3DShader(char* strFilePath, const DWORD* pDeclaration, DWORD Usage, Bool ShaderType, DWORD* pHandle)
{
	if (getChipset() < DC_GENERIC_PIXEL_SHADER_1_1)
		return E_FAIL;	//don't allow loading any shaders if hardware can't handle it.
	
	try
	{
		File *file = NULL;
		HRESULT hr;

		file = TheFileSystem->openFile(strFilePath, File::READ | File::BINARY);
		if (file == NULL)
		{
			OutputDebugString("Could not find file \n" );
			return E_FAIL;
		}

		FileInfo fileInfo;
		TheFileSystem->getFileInfo(AsciiString(strFilePath), &fileInfo);
		DWORD dwFileSize = fileInfo.sizeLow;

		const DWORD* pShader = (DWORD*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwFileSize);
		if (!pShader)
		{
			OutputDebugString( "Failed to allocate memory to load shader\n " );
			return E_FAIL;
		}

		file->read((void *)pShader, dwFileSize);

		file->close();
		file = NULL;

		if (ShaderType == TRUE)//SHADERTYPE_VERTEX)
		{
			hr = DX8Wrapper::_Get_D3D_Device8()->CreateVertexShader(pDeclaration, pShader, pHandle, Usage);
		}
		else if (ShaderType == FALSE)//SHADERTYPE_PIXEL)
		{
			hr = DX8Wrapper::_Get_D3D_Device8()->CreatePixelShader(pShader, pHandle);
		}

		HeapFree(GetProcessHeap(), 0, (void*)pShader);

		if (FAILED(hr))
		{
			OutputDebugString( "Failed to create shader\n "); 
			return E_FAIL;
		}
	}
	catch(...)
	{
		OutputDebugString( "Error opening file \n" );
		return E_FAIL;
	}

	return S_OK;
}

//For the MP test, we're enforcing high min-spec requirements that need to be verified.
#define MIN_INTEL_CPU_FREQ	1300
#define MIN_AMD_CPU_FREQ	1100
#define MIN_ACCEPTED_FREQUENCY	1300
#define MIN_ACCEPTED_MEMORY	(1024*1024*256)	//256 MB
#define MIN_ACCEPTED_TEXTURE_MEMORY	(1024*1024*30)	//30 MB

/**Hack to give gameengine access to this function*/
Bool testMinimumRequirements(ChipsetType *videoChipType, CpuType *cpuType, Int *cpuFreq, Int *numRAM, Real *intBenchIndex, Real *floatBenchIndex, Real *memBenchIndex)
{
	return W3DShaderManager::testMinimumRequirements(videoChipType,cpuType,cpuFreq,numRAM,intBenchIndex,floatBenchIndex,memBenchIndex);
}

// byte-exact reconstruction: game/GameEngine/Source/Common/W3DShaderManagerMinimumRequirements.cpp
// ?testMinimumRequirements@W3DShaderManager@@SA_NPAW4ChipsetType@@PAW4CpuType@@PAH2PAM33@Z present-unmatched
Bool W3DShaderManager::testMinimumRequirements(ChipsetType *videoChipType, CpuType *cpuType, Int *cpuFreq, Int *numRAM, Real *intBenchIndex, Real *floatBenchIndex, Real *memBenchIndex)
{
	if (videoChipType)
		*videoChipType = getChipset();

	if (cpuType)
	{
		*cpuType = XX;	//unknown

		//Check if it's an Athlon
		if (CPUDetectClass::Get_Processor_Manufacturer() == CPUDetectClass::MANUFACTURER_AMD &&
// ?Get_AMD_Processor@CPUDetectClass@@SA?AW4AMDProcessorType@1@XZ present-unmatched
				CPUDetectClass::Get_AMD_Processor() >= CPUDetectClass::AMD_PROCESSOR_ATHLON_025)
				*cpuType = K7;

		//Check if it's a P3
		if (CPUDetectClass::Get_Processor_Manufacturer() == CPUDetectClass::MANUFACTURER_INTEL &&
// ?Get_Intel_Processor@CPUDetectClass@@SA?AW4IntelProcessorType@1@XZ present-unmatched
				CPUDetectClass::Get_Intel_Processor() >= CPUDetectClass::INTEL_PROCESSOR_PENTIUM_III_MODEL_7)
				*cpuType = P3;
		//Check if it's a P4
		if (CPUDetectClass::Get_Processor_Manufacturer() == CPUDetectClass::MANUFACTURER_INTEL &&
// ?Get_Intel_Processor@CPUDetectClass@@SA?AW4IntelProcessorType@1@XZ present-unmatched
				CPUDetectClass::Get_Intel_Processor() >= CPUDetectClass::INTEL_PROCESSOR_PENTIUM4)
				*cpuType = P4;
	}

	if (cpuFreq)
		*cpuFreq=CPUDetectClass::Get_Processor_Speed();

	if (numRAM)
		*numRAM=CPUDetectClass::Get_Total_Physical_Memory();

	if (intBenchIndex && floatBenchIndex && memBenchIndex)
	{
		RunBenchmark(0, NULL, floatBenchIndex, intBenchIndex, memBenchIndex);
	}

	return TRUE;
}

/**Try to guess how well the video card will handle the game assuming very fast CPU*/
StaticGameLODLevel W3DShaderManager::getGPUPerformanceIndex(void)
{
	StaticGameLODLevel detailSetting=(StaticGameLODLevel)1;
	ChipsetType chipType=BfmeGpuChipsetQuery::query();

	if (chipType)
	{
		if (chipType >= BFME_DC_GEFORCE2)
			detailSetting=(StaticGameLODLevel)1;
		if (chipType >= BFME_DC_GENERIC_PIXEL_SHADER_1_1)
			detailSetting=(StaticGameLODLevel)3;
	}

	return detailSetting;
}

/**We need a hardware independent method to compare different CPU's.  For lack of anything better, we'll
use time to calculate PIE using a slow random number algorithm.*/

/**Used to test function call overhead*/
void add(float *sum,float *addend)
{
	*sum = *sum + *addend;
}

/**Returns seconds needed to run the test*/
Real W3DShaderManager::GetCPUBenchTime(void)
{
	float ztot, yran, ymult, ymod, x, y, z, pi, prod;
    long int low, ixran, itot, j, iprod;

  	__int64 endTime64,freq64,startTime64;
	QueryPerformanceFrequency((LARGE_INTEGER *)&freq64);
	QueryPerformanceCounter((LARGE_INTEGER *)&startTime64);

    ztot = 0.0;
    low = 1;
    ixran = 1907;
    yran = 5813.0;
    ymult = 1307.0;
    ymod = 5471.0;
    itot = 560000;	//total iterations. This value ends up running at ~30 fps on our P4-2.2Ghz.

    for(j=1; j<=itot; j++)
    {
		iprod = 27611 * ixran;
		ixran = iprod - 74383*(long int)(iprod/74383);
		x = (float)ixran / 74383.0;
		prod = ymult * yran;
		yran = (prod - ymod*(long int)(prod/ymod));
		y = yran / ymod;
		z = x*x + y*y;
		add(&ztot,&z);
		if ( z <= 1.0 )
		{
		  low = low + 1;
		}
	}
	pi = 4.0 * (float)low/(float)itot;

	QueryPerformanceCounter((LARGE_INTEGER *)&endTime64);
	return ((double)(endTime64-startTime64)/(double)(freq64));
}


// W3DShaderManager::setShroudTex =======================================================
/** Puts the shroud texture into a texture stage.
 */
//=============================================================================
// ?setShroudTex@W3DShaderManager@@SAHH@Z present-unmatched
Int W3DShaderManager::setShroudTex(Int stage)
{
	//We need to scale so shroud texel stretches over one full terrain cell.  Each texel
	//is 1/128 the size of full texture. (assuming 128x128 vid-mem texture).
	W3DShroud *shroud;
	if ((shroud=TheTerrainRenderObject->getShroud()) != 0)
	{	 
		DX8Wrapper::Set_Texture(stage, shroud->getShroudTexture());

		DX8Wrapper::Set_DX8_Texture_Stage_State(stage,  D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
		DX8Wrapper::Set_DX8_Texture_Stage_State(stage,  D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);	
		DX8Wrapper::Set_DX8_Texture_Stage_State( stage, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		DX8Wrapper::Set_DX8_Texture_Stage_State( stage, D3DTSS_COLORARG2, D3DTA_CURRENT );
		DX8Wrapper::Set_DX8_Texture_Stage_State( stage, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
		DX8Wrapper::Set_DX8_Texture_Stage_State( stage, D3DTSS_ALPHAARG2, D3DTA_CURRENT );
		DX8Wrapper::Set_DX8_Texture_Stage_State( stage, D3DTSS_COLOROP,   D3DTOP_MODULATE );
		DX8Wrapper::Set_DX8_Texture_Stage_State( stage, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG2 );
		D3DXMATRIX inv;
		float det;

		Matrix4x4 curView;
		DX8Wrapper::_Get_DX8_Transform(D3DTS_VIEW, curView);

		D3DXMatrixInverse(&inv, &det, (D3DXMATRIX*)&curView);

		D3DXMATRIX scale,offset;

		//We need to make all world coordinates be relative to the heightmap data origin since that
		//is where the shroud begins.

		float xoffset = 0;
		float yoffset = 0;
		Real width=shroud->getCellWidth();
		Real height=shroud->getCellHeight();

		if (TheTerrainRenderObject->getMap())
		{	//subtract origin position from all coordinates.  Origin is shifted by 1 cell width/height to allow for unused border texels.
			xoffset = -(float)shroud->getDrawOriginX() + width;
			yoffset = -(float)shroud->getDrawOriginY() + height;
		}

		D3DXMatrixTranslation(&offset, xoffset, yoffset,0);

		width = 1.0f/(width*shroud->getTextureWidth());
		height = 1.0f/(height*shroud->getTextureHeight());
		D3DXMatrixScaling(&scale, width, height, 1);
		*((D3DXMATRIX *)&curView) = (inv * offset) * scale;
		DX8Wrapper::_Set_DX8_Transform((D3DTRANSFORMSTATETYPE )(D3DTS_TEXTURE0+stage), *((Matrix4x4*)&curView));
		return TRUE;
	}
	return FALSE;
}



Int FlatTerrainShader2Stage::init( void )
{
	//no special device validation needed - anything in our min spec should handle this.

	W3DShaders[W3DShaderManager::ST_FLAT_TERRAIN_BASE]=&flatTerrainShader2Stage;
	W3DShadersPassCount[W3DShaderManager::ST_FLAT_TERRAIN_BASE]=1;
	W3DShaders[W3DShaderManager::ST_FLAT_TERRAIN_BASE_NOISE1]=&flatTerrainShader2Stage;
	W3DShadersPassCount[W3DShaderManager::ST_FLAT_TERRAIN_BASE_NOISE1]=2;
	W3DShaders[W3DShaderManager::ST_FLAT_TERRAIN_BASE_NOISE2]=&flatTerrainShader2Stage;
	W3DShadersPassCount[W3DShaderManager::ST_FLAT_TERRAIN_BASE_NOISE2]=2;
	W3DShaders[W3DShaderManager::ST_FLAT_TERRAIN_BASE_NOISE12]=&flatTerrainShader2Stage;
	W3DShadersPassCount[W3DShaderManager::ST_FLAT_TERRAIN_BASE_NOISE12]=2;

	return TRUE;
}

void FlatTerrainShader2Stage::reset(void)
{
	ShaderClass::Invalidate();

	//Free references to textures
	bfmeSetTexture(0, NULL);
	bfmeSetTexture(1, NULL);

	DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
	DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_PASSTHRU|0);

	DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
	DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_PASSTHRU|1);
}


// Retail RVA 0x007C5690, 7909 bytes. Vtable VA 0x011287A0 slot 0 routes
// through ILT 0x0003517F to this body; slots 1/2 route to the matched
// FlatTerrainShader2Stage::reset/init. The ZH twin supplies the shader identity.
// The device slots and shroud offsets below are independently read from retail.
// GlobalData +0xcf5/+0xdbc and terrain +0x30bc remain unnamed: no layout witness.
// Preserve separate branch-local matrices, the handle comparison before cleanup,
// and the state helper's early exit: they determine the retail EH/allocator shape.
// The second matrix helper is already owned by TerrainTextureMatrix.cpp.
// Retail calls ILT 0x000051FF -> 0x007DCF00; reuse that established name and
// its thiscall(matrix* destination, matrix* inverse, bool) / ret 12 ABI.
namespace {
struct FlatTerrainDeviceRva01340534 {
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual HRESULT __stdcall SetTransform(DWORD, const void*) = 0;
	virtual HRESULT __stdcall GetTransform(DWORD, void*) = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual HRESULT __stdcall SetRenderState(DWORD, DWORD) = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;
	virtual void slot63() = 0;
	virtual void slot64() = 0;
	virtual HRESULT __stdcall SetTexture(DWORD, IDirect3DBaseTexture8*) = 0;
	virtual void slot66() = 0;
	virtual HRESULT __stdcall SetTextureStageState(DWORD, DWORD, DWORD) = 0;
	virtual void slot68() = 0;
	virtual HRESULT __stdcall SetSamplerState(DWORD, DWORD, DWORD) = 0;
};
// Four-byte StringClass storage. Preserve the witnessed null-byte read order;
// the original qualifier is unknown, so this view uses a volatile byte load.
class FlatTerrainValueNameRva007C5690
{
	TCHAR *m_Buffer;

public:
	__forceinline FlatTerrainValueNameRva007C5690(int initial_len, bool hint_temporary)
		: m_Buffer(StringClass::m_EmptyString)
	{
		((StringClass *)this)->Get_String(initial_len, hint_temporary);
		m_Buffer[0] = *(volatile TCHAR *)&g_bfmeCh1035;
	}

	~FlatTerrainValueNameRva007C5690()
	{
		((StringClass *)this)->Free_String();
	}
};
__forceinline void bfmeFlatSetTransform(D3DTRANSFORMSTATETYPE type, const Matrix4x4 &m)
{
    DX8Wrapper::matrix_changes++;
    DX8Wrapper::_Get_D3D_Device8()->SetTransform(type, (const D3DMATRIX *)&m);
    number_of_DX8_calls++;
}
__forceinline D3DXMATRIX bfmeFlatMultiply(const D3DXMATRIX &a, const D3DXMATRIX &b)
{
    D3DXMATRIX result;
    D3DXMatrixMultiply(&result, &a, &b);
    return result;
}
#define BFME_FLAT_TEXTURE(stage, texture) ((FlatTerrainDeviceRva01340534 *)DX8Wrapper::_Get_D3D_Device8())->SetTexture(stage, texture)
// These BFME offsets differ from the ZH texture/origin layout. Accessor return
// boundaries also preserve retail scalar temporaries in the matrix calculation.
__forceinline float flatShroudCellWidth(W3DShroud *shroud) { return *(float *)((char *)shroud + 0x10); }
__forceinline float flatShroudCellHeight(W3DShroud *shroud) { return *(float *)((char *)shroud + 0x14); }
__forceinline int flatShroudTextureWidth(W3DShroud *shroud) { return *(int *)((char *)shroud + 0x20); }
__forceinline int flatShroudTextureHeight(W3DShroud *shroud) { return *(int *)((char *)shroud + 0x24); }
__forceinline float flatShroudDrawOriginX(W3DShroud *shroud) { return *(float *)((char *)shroud + 0x2c); }
__forceinline float flatShroudDrawOriginY(W3DShroud *shroud) { return *(float *)((char *)shroud + 0x30); }

} // namespace

#define FLAT_SET_TSS(stage_, state_, value_) do { \
    if (DX8Wrapper::TextureStageStates[stage_][state_] == (unsigned)(value_)) break; \
    if (WW3D::Is_Snapshot_Activated()) { \
        FlatTerrainValueNameRva007C5690 value_name(0, true); \
        DX8Wrapper::Get_DX8_Texture_Stage_State_Value_Name(*(StringClass *)&value_name, (D3DTEXTURESTAGESTATETYPE)(state_), (value_)); \
    } \
    DX8Wrapper::TextureStageStates[stage_][state_] = (value_); \
    FlatTerrainDeviceRva01340534 *device = (FlatTerrainDeviceRva01340534 *)DX8Wrapper::_Get_D3D_Device8(); \
    device->SetTextureStageState((stage_), (state_), (value_)); \
    number_of_DX8_calls++; \
    DX8Wrapper::texture_stage_state_changes++; \
} while (0)
#define FLAT_SET_RS(state_, value_) \
	if (DX8Wrapper::RenderStates[state_] != (unsigned)(value_)) { \
		if (WW3D::Is_Snapshot_Activated()) { \
			FlatTerrainValueNameRva007C5690 value_name(0, true); \
			DX8Wrapper::Get_DX8_Render_State_Value_Name(*(StringClass *)&value_name, \
				(D3DRENDERSTATETYPE)(state_), (value_)); \
		} \
		DX8Wrapper::RenderStates[state_] = (value_); \
		IDirect3DDevice8 *rs_device_ = DX8Wrapper::_Get_D3D_Device8(); \
		(*(BFMESetRSFn **)rs_device_)[BFME_SET_RS_SLOT](rs_device_, (state_), (value_)); \
		number_of_DX8_calls++; \
		DX8Wrapper::render_state_changes++; \
	}


Int FlatTerrainShader2Stage::set(Int pass)
{
	DX8Wrapper::Apply_Render_State_Changes();

	setTerrainTextureFilters(0);
	setTerrainTextureFilters(1);

	switch (pass)
	{
		case 0:
			BFME_SET_SAMP(0, BFME_SAMP_ADDRESSU, D3DTADDRESS_CLAMP);
			BFME_SET_SAMP(0, BFME_SAMP_ADDRESSV, D3DTADDRESS_CLAMP);
			FLAT_SET_TSS(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
			FLAT_SET_TSS(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
			FLAT_SET_TSS(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
			FLAT_SET_TSS(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
			FLAT_SET_TSS(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
			if ((TextureBaseClass *&)bfmeGet(0) != NULL) {
				FLAT_SET_TSS(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
				FLAT_SET_TSS(0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
				FLAT_SET_TSS(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
				if (*(bool *)((char *)TheWritableGlobalData + 0xcf5)) {
					BFME_FLAT_TEXTURE(0, ((TextureBaseClass &)bfmeGet(4)).Peek_D3D_Base_Texture());
					W3DShroud *shroud;
					if ((shroud=*(W3DShroud **)((char *)TheTerrainRenderObject + 0x30bc)) != 0)
					{
						D3DXMATRIX inv;
						float det;
						Matrix4x4 curView;
						DX8Wrapper::_Get_DX8_Transform(D3DTS_VIEW, curView);
						D3DXMatrixInverse(&inv, &det, (D3DXMATRIX*)&curView);
						D3DXMATRIX scale,offset;
						float xoffset = 0;
						float yoffset = 0;
						Real width=flatShroudCellWidth(shroud);
						Real height=flatShroudCellHeight(shroud);
						if (*(WorldHeightMap **)((char *)TheTerrainRenderObject + 0x2ff4))
						{
							xoffset = -(float)flatShroudDrawOriginX(shroud) + width;
							yoffset = -(float)flatShroudDrawOriginY(shroud) + height;
						}
						D3DXMatrixTranslation(&offset, xoffset, yoffset,0);
						width = 1.0f/(width*flatShroudTextureWidth(shroud));
						height = 1.0f/(height*flatShroudTextureHeight(shroud));
						D3DXMatrixScaling(&scale, width, height, 1);
						*((D3DXMATRIX *)&curView) = bfmeFlatMultiply(bfmeFlatMultiply(inv, offset), scale);
						bfmeFlatSetTransform((D3DTRANSFORMSTATETYPE )(D3DTS_TEXTURE0), *((Matrix4x4*)&curView));
					}
				} else {
					BFME_FLAT_TEXTURE(0, ((TextureBaseClass &)bfmeGet(0)).Peek_D3D_Base_Texture());
					W3DShroud *shroud;
					if ((shroud=*(W3DShroud **)((char *)TheTerrainRenderObject + 0x30b8)) != 0)
					{
						D3DXMATRIX inv;
						float det;
						Matrix4x4 curView;
						DX8Wrapper::_Get_DX8_Transform(D3DTS_VIEW, curView);
						D3DXMatrixInverse(&inv, &det, (D3DXMATRIX*)&curView);
						D3DXMATRIX scale,offset;
						float xoffset = 0;
						float yoffset = 0;
						Real width=flatShroudCellWidth(shroud);
						Real height=flatShroudCellHeight(shroud);
						if (*(WorldHeightMap **)((char *)TheTerrainRenderObject + 0x2ff4))
						{
							xoffset = -(float)flatShroudDrawOriginX(shroud) + width;
							yoffset = -(float)flatShroudDrawOriginY(shroud) + height;
						}
						D3DXMatrixTranslation(&offset, xoffset, yoffset,0);
						width = 1.0f/(width*flatShroudTextureWidth(shroud));
						height = 1.0f/(height*flatShroudTextureHeight(shroud));
						D3DXMatrixScaling(&scale, width, height, 1);
						*((D3DXMATRIX *)&curView) = bfmeFlatMultiply(bfmeFlatMultiply(inv, offset), scale);
						bfmeFlatSetTransform((D3DTRANSFORMSTATETYPE )(D3DTS_TEXTURE0), *((Matrix4x4*)&curView));
					}
				}
			} else {
				FLAT_SET_TSS(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
				FLAT_SET_TSS(0, D3DTSS_TEXCOORDINDEX, 0);
			}
			BFME_SET_SAMP(1, BFME_SAMP_ADDRESSU, D3DTADDRESS_CLAMP);
			BFME_SET_SAMP(1, BFME_SAMP_ADDRESSV, D3DTADDRESS_CLAMP);
			FLAT_SET_TSS(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
			FLAT_SET_TSS(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
			if (TheWritableGlobalData && *(bool *)((char *)TheWritableGlobalData + 0xdbc)) {
				FLAT_SET_TSS(1, D3DTSS_COLOROP, D3DTOP_MODULATE2X);
			} else {
				FLAT_SET_TSS(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
			}
			FLAT_SET_TSS(1, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
			FLAT_SET_TSS(1, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
			FLAT_SET_TSS(1, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
			FLAT_SET_TSS(1, D3DTSS_TEXCOORDINDEX, 0);
			FLAT_SET_TSS(1, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
			FLAT_SET_TSS(1, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_PASSTHRU|0);
			FLAT_SET_RS(D3DRS_ALPHABLENDENABLE, false);
			break;
		case 1:
			FLAT_SET_TSS(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
			FLAT_SET_TSS(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
			FLAT_SET_TSS(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
			FLAT_SET_TSS(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
			FLAT_SET_TSS(0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
			FLAT_SET_TSS(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
			BFME_SET_SAMP(0, BFME_SAMP_ADDRESSU, D3DTADDRESS_WRAP);
			BFME_SET_SAMP(0, BFME_SAMP_ADDRESSV, D3DTADDRESS_WRAP);
			FLAT_SET_RS(D3DRS_ALPHABLENDENABLE, true);
			FLAT_SET_RS(D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR);
			FLAT_SET_RS(D3DRS_DESTBLEND, D3DBLEND_ZERO);
			if (W3DShaderManager::getCurrentShader() == W3DShaderManager::ST_FLAT_TERRAIN_BASE_NOISE12)
			{
				Matrix4x4 curView;
				DX8Wrapper::_Get_DX8_Transform(D3DTS_VIEW, curView);
				D3DXMATRIX inv;
				float det;
				D3DXMatrixInverse(&inv, &det, (D3DXMATRIX*)&curView);
				terrainShader2Stage.updateNoise1(((D3DXMATRIX*)&curView),&inv);
				bfmeFlatSetTransform(D3DTS_TEXTURE0, curView);
				BFME_SET_SAMP(0, BFME_SAMP_MINFILTER, D3DTEXF_LINEAR);
				BFME_SET_SAMP(0, BFME_SAMP_MAGFILTER, D3DTEXF_LINEAR);
				BFME_FLAT_TEXTURE(0, ((TextureBaseClass &)bfmeGet(2)).Peek_D3D_Base_Texture());
				((Rva007DCF00TextureMatrix *)&terrainShader2Stage)->build((Rva007DCF00Matrix *)&curView, (Rva007DCF00Matrix *)&inv, true);
				bfmeFlatSetTransform(D3DTS_TEXTURE1, curView);
				BFME_SET_SAMP(1, BFME_SAMP_MINFILTER, D3DTEXF_POINT);
				BFME_SET_SAMP(1, BFME_SAMP_MAGFILTER, D3DTEXF_LINEAR);
				FLAT_SET_TSS(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
				FLAT_SET_TSS(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
				FLAT_SET_TSS(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
				FLAT_SET_TSS(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
				FLAT_SET_TSS(1, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
				FLAT_SET_TSS(1, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
				BFME_SET_SAMP(1, BFME_SAMP_ADDRESSU, D3DTADDRESS_WRAP);
				BFME_SET_SAMP(1, BFME_SAMP_ADDRESSV, D3DTADDRESS_MIRROR);
				BFME_FLAT_TEXTURE(1, ((TextureBaseClass &)bfmeGet(3)).Peek_D3D_Base_Texture());
			}
			else
			{
				Matrix4x4 curView;
				DX8Wrapper::_Get_DX8_Transform(D3DTS_VIEW, curView);
				D3DXMATRIX inv;
				float det;
				D3DXMatrixInverse(&inv, &det, (D3DXMATRIX*)&curView);
				if (W3DShaderManager::getCurrentShader() == W3DShaderManager::ST_FLAT_TERRAIN_BASE_NOISE1)
				{
					BFME_FLAT_TEXTURE(0, ((TextureBaseClass &)bfmeGet(2)).Peek_D3D_Base_Texture());
					terrainShader2Stage.updateNoise1(((D3DXMATRIX*)&curView),&inv);
					BFME_SET_SAMP(0, BFME_SAMP_MINFILTER, D3DTEXF_LINEAR);
					BFME_SET_SAMP(0, BFME_SAMP_MAGFILTER, D3DTEXF_LINEAR);
				}
				else
				{
					BFME_FLAT_TEXTURE(0, ((TextureBaseClass &)bfmeGet(3)).Peek_D3D_Base_Texture());
					((Rva007DCF00TextureMatrix *)&terrainShader2Stage)->build((Rva007DCF00Matrix *)&curView, (Rva007DCF00Matrix *)&inv, true);
					BFME_SET_SAMP(0, BFME_SAMP_MINFILTER, D3DTEXF_POINT);
					BFME_SET_SAMP(0, BFME_SAMP_MAGFILTER, D3DTEXF_LINEAR);
				}
				FLAT_SET_TSS(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
				FLAT_SET_TSS(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
				bfmeFlatSetTransform(D3DTS_TEXTURE0, *((Matrix4x4*)&curView));
			}
			break;
	}
	return TRUE;
}
#undef FLAT_SET_TSS
#undef FLAT_SET_RS
#undef BFME_FLAT_TEXTURE







// ?shutdown@FlatTerrainShaderPixelShader@@UAEHXZ present-unmatched
Int FlatTerrainShaderPixelShader::shutdown(void)
{
	if (m_dwBasePixelShader)
		DX8Wrapper::_Get_D3D_Device8()->DeletePixelShader(m_dwBasePixelShader);

	if (m_dwBase0PixelShader)
		DX8Wrapper::_Get_D3D_Device8()->DeletePixelShader(m_dwBase0PixelShader);

	if (m_dwBaseNoise1PixelShader)
		DX8Wrapper::_Get_D3D_Device8()->DeletePixelShader(m_dwBaseNoise1PixelShader);

	if (m_dwBaseNoise2PixelShader)
		DX8Wrapper::_Get_D3D_Device8()->DeletePixelShader(m_dwBaseNoise2PixelShader);

	m_dwBasePixelShader=NULL;
	m_dwBase0PixelShader=NULL;
	m_dwBaseNoise1PixelShader=NULL;
	m_dwBaseNoise2PixelShader=NULL;

	return TRUE;
}

Int FlatTerrainShaderPixelShader::init( void )
{	
	Int res;

#ifdef DISABLE_PIXEL_SHADERS
	return false;
#endif

	//this shader will also use the 2Stage shader for some of the passes so initialize it too.
	if ((res=W3DShaderManager::getChipset()) >= BFME_DC_GENERIC_PIXEL_SHADER_1_1)
	{
		if (res >= BFME_DC_GENERIC_PIXEL_SHADER_1_1)
		{
			//base version which doesn't apply any noise textures.
			HRESULT hr = BfmeShaderLoader::LoadAndCreateD3DShader("shaders\\fterrain.pso", &m_dwBasePixelShader);
			if (FAILED(hr))
				return FALSE;

			//BFME-only: the terrain taint shaders, loaded before fterrain0.
			hr = BfmeShaderLoader::LoadAndCreateD3DShader("shaders\\terraintaint.pso", &m_dwTaintPixelShader);
			if (FAILED(hr))
				return FALSE;

			hr = BfmeShaderLoader::LoadAndCreateD3DShader("shaders\\terraintaint2.pso", &m_dwTaint2PixelShader);
			if (FAILED(hr))
				return FALSE;

			//base version which doesn't apply any shroud textures.
			hr = BfmeShaderLoader::LoadAndCreateD3DShader("shaders\\fterrain0.pso", &m_dwBase0PixelShader);
			if (FAILED(hr))
				return FALSE;

			//version which blends 1 noise texture.
			hr = BfmeShaderLoader::LoadAndCreateD3DShader("shaders\\fterrainnoise.pso", &m_dwBaseNoise1PixelShader);
			if (FAILED(hr))
				return FALSE;

			//version which blends 2 noise textures.
			hr = BfmeShaderLoader::LoadAndCreateD3DShader("shaders\\fterrainnoise2.pso", &m_dwBaseNoise2PixelShader);
			if (FAILED(hr))
				return FALSE;

			W3DShaders[W3DShaderManager::ST_FLAT_TERRAIN_BASE]=&flatTerrainShaderPixelShader;
			W3DShaders[W3DShaderManager::ST_FLAT_TERRAIN_BASE_NOISE1]=&flatTerrainShaderPixelShader;
			W3DShaders[W3DShaderManager::ST_FLAT_TERRAIN_BASE_NOISE2]=&flatTerrainShaderPixelShader;
			W3DShaders[W3DShaderManager::ST_FLAT_TERRAIN_BASE_NOISE12]=&flatTerrainShaderPixelShader;
			W3DShadersPassCount[W3DShaderManager::ST_FLAT_TERRAIN_BASE]=2;
			W3DShadersPassCount[W3DShaderManager::ST_FLAT_TERRAIN_BASE_NOISE1]=2;
			W3DShadersPassCount[W3DShaderManager::ST_FLAT_TERRAIN_BASE_NOISE2]=2;
			W3DShadersPassCount[W3DShaderManager::ST_FLAT_TERRAIN_BASE_NOISE12]=2;
			return TRUE;
		}
	}
	return FALSE;
}

// ?set@FlatTerrainShaderPixelShader@@UAEHH@Z present-unmatched
Int FlatTerrainShaderPixelShader::set(Int pass)
{
	//setup base pass
	Int curStage = 1;
	// setup terrain [3/31/2003]

	DX8Wrapper::Set_DX8_Texture_Stage_State(0,  D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0,  D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
	DX8Wrapper::Set_Texture(0, W3DShaderManager::getShaderTexture(2));
	DX8Wrapper::Set_Texture(1, W3DShaderManager::getShaderTexture(2));
	//force WW3D2 system to set it's states so it won't later overwrite our custom settings.
	DX8Wrapper::Apply_Render_State_Changes();




	DX8Wrapper::Set_DX8_Texture_Stage_State( curStage, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
	DX8Wrapper::Set_DX8_Texture_Stage_State( curStage, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
	//tell pixel shader which UV set to use for each stage
	DX8Wrapper::Set_DX8_Texture_Stage_State( curStage, D3DTSS_TEXCOORDINDEX, 0 );
	DX8Wrapper::Set_DX8_Texture_Stage_State(curStage,  D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);	

	if (TheGlobalData && TheGlobalData->m_bilinearTerrainTex || TheGlobalData->m_trilinearTerrainTex) {
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
	} else {
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage, D3DTSS_MINFILTER, D3DTEXF_POINT);
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage, D3DTSS_MAGFILTER, D3DTEXF_POINT);
	}
	if (TheGlobalData && TheGlobalData->m_trilinearTerrainTex) {
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
	} else {
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage, D3DTSS_MIPFILTER, D3DTEXF_POINT);
	}

	curStage = 0;

	W3DShroud *shroud = TheTerrainRenderObject->getShroud();
	if (shroud) {

		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage,  D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage,  D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);	

		//We need to scale so shroud texel stretches over one full terrain cell.  Each texel
		//is 1/128 the size of full texture. (assuming 128x128 vid-mem texture).
		{	
			D3DXMATRIX inv;
			float det;

			Matrix4x4 curView;
			DX8Wrapper::_Get_DX8_Transform(D3DTS_VIEW, curView);

			D3DXMatrixInverse(&inv, &det, (D3DXMATRIX*)&curView);

			D3DXMATRIX scale,offset;

			//We need to make all world coordinates be relative to the heightmap data origin since that
			//is where the shroud begins.

			float xoffset = 0;
			float yoffset = 0;
			Real width=shroud->getCellWidth();
			Real height=shroud->getCellHeight();

			if (TheTerrainRenderObject->getMap())
			{	//subtract origin position from all coordinates.  Origin is shifted by 1 cell width/height to allow for unused border texels.
				xoffset = -(float)shroud->getDrawOriginX() + width;
				yoffset = -(float)shroud->getDrawOriginY() + height;
			}

			D3DXMatrixTranslation(&offset, xoffset, yoffset,0);

			width = 1.0f/(width*shroud->getTextureWidth());
			height = 1.0f/(height*shroud->getTextureHeight());
			D3DXMatrixScaling(&scale, width, height, 1);
			*((D3DXMATRIX *)&curView) = (inv * offset) * scale;
			DX8Wrapper::_Set_DX8_Transform((D3DTRANSFORMSTATETYPE )(D3DTS_TEXTURE0+curStage), *((Matrix4x4*)&curView));
		}
		DX8Wrapper::Set_DX8_Texture_Stage_State( curStage, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
		DX8Wrapper::Set_DX8_Texture_Stage_State( curStage, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
		DX8Wrapper::Set_DX8_Texture_Stage_State( curStage, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		DX8Wrapper::Set_DX8_Texture_Stage_State( curStage, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		DX8Wrapper::_Get_D3D_Device8()->SetTexture(curStage, shroud->getShroudTexture()->Peek_D3D_Texture());
		curStage++;
		if (curStage==1) curStage++;
	}

	Bool doNoise1 = (W3DShaderManager::getCurrentShader() == W3DShaderManager::ST_FLAT_TERRAIN_BASE_NOISE1 ||
						W3DShaderManager::getCurrentShader() == W3DShaderManager::ST_FLAT_TERRAIN_BASE_NOISE12);
	if (doNoise1) {	 // Cloud pass.
		Matrix4x4 curView;
		DX8Wrapper::_Get_DX8_Transform(D3DTS_VIEW, curView);

		D3DXMATRIX inv;
		float det;
		D3DXMatrixInverse(&inv, &det, (D3DXMATRIX*)&curView);

		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage,  D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
		// Two output coordinates are used.
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage,  D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);	

		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage,  D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage,  D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
		DX8Wrapper::_Get_D3D_Device8()->SetTexture(curStage, W3DShaderManager::getShaderTexture(2)->Peek_D3D_Texture());
		terrainShader2Stage.updateNoise1(((D3DXMATRIX*)&curView),&inv);	//update curView with texture matrix
		DX8Wrapper::_Set_DX8_Transform((D3DTRANSFORMSTATETYPE )(D3DTS_TEXTURE0+curStage), *((Matrix4x4*)&curView));
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		
		curStage++;
		if (curStage==1) curStage++;
	}

	Bool doNoise2 = (W3DShaderManager::getCurrentShader() == W3DShaderManager::ST_FLAT_TERRAIN_BASE_NOISE2 ||
						W3DShaderManager::getCurrentShader() == W3DShaderManager::ST_FLAT_TERRAIN_BASE_NOISE12);
	if (doNoise2)
	{	
		Matrix4x4 curView;
		DX8Wrapper::_Get_DX8_Transform(D3DTS_VIEW, curView);

		D3DXMATRIX inv;
		float det;
		D3DXMatrixInverse(&inv, &det, (D3DXMATRIX*)&curView);

		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage,  D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
		// Two output coordinates are used.
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage,  D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);	

		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage,  D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage,  D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
		DX8Wrapper::_Get_D3D_Device8()->SetTexture(curStage, W3DShaderManager::getShaderTexture(3)->Peek_D3D_Texture());
		terrainShader2Stage.updateNoise2(((D3DXMATRIX*)&curView),&inv);	//update curView with texture matrix
		DX8Wrapper::_Set_DX8_Transform((D3DTRANSFORMSTATETYPE )(D3DTS_TEXTURE0+curStage), *((Matrix4x4*)&curView));
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		
		curStage++;
		if (curStage==1) curStage++;
	}
	if (curStage<2) {
		DX8Wrapper::_Get_D3D_Device8()->SetPixelShader(m_dwBase0PixelShader);
	}	else if (curStage==2) {
		DX8Wrapper::_Get_D3D_Device8()->SetPixelShader(m_dwBasePixelShader);
	}	else if (curStage==3) {
		DX8Wrapper::_Get_D3D_Device8()->SetPixelShader(m_dwBaseNoise1PixelShader);
	}else if (curStage==4) {
		DX8Wrapper::_Get_D3D_Device8()->SetPixelShader(m_dwBaseNoise2PixelShader);
	}
	DX8Wrapper::_Get_D3D_Device8()->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	DX8Wrapper::Apply_Render_State_Changes();
	DX8Wrapper::_Get_D3D_Device8()->SetTexture(curStage, W3DShaderManager::getShaderTexture(3)->Peek_D3D_Texture());
	return TRUE;
}

void FlatTerrainShaderPixelShader::reset(void)
{
	bfmeSetTexture(2,NULL);	//release reference to any texture
	bfmeSetTexture(3,NULL);	//release reference to any texture

	bfmeSetPixelShader(0);	//turn off pixel shader

	bfmeSetTexture(0, NULL);
	bfmeSetTexture(1, NULL);

	DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
	DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_PASSTHRU|0);

	DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
	DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_PASSTHRU|1);

	DX8Wrapper::Set_DX8_Texture_Stage_State( 2, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
	DX8Wrapper::Set_DX8_Texture_Stage_State( 2, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_PASSTHRU|2);

	DX8Wrapper::Set_DX8_Texture_Stage_State( 3, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
	DX8Wrapper::Set_DX8_Texture_Stage_State( 3, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_PASSTHRU|3);


	DX8Wrapper::Invalidate_Cached_Render_States();
}


#include "matpass.h"
// Native derived owner is unproven; its constructor and virtual role are witnessed.
class Rva007CBB30 : public MaterialPassClass
{
public:
    virtual void Install_Materials() const;
    unsigned methodRva007CBB70();
    int m_at38;
    float m_at3c;
    int m_at40;
    float m_at44;
};
typedef char MaterialPassExtentRva007CBB30[sizeof(MaterialPassClass)==0x38 ? 1 : -1];
class BfmeRefEAX;
extern BfmeRefEAX *g_bfmeAEAX;
extern BfmeRefEAX *g_bfmeBEAX;
typedef HRESULT (__stdcall *MaterialCreateDeclarationFn)(IDirect3DDevice8 *, const BfmeVertexElement *, BfmeRefEAX **);
typedef HRESULT (__stdcall *MaterialSetObjectFn)(IDirect3DDevice8 *, BfmeRefEAX *);
typedef HRESULT (__stdcall *MaterialSetConstantFn)(IDirect3DDevice8 *, unsigned, const void *, unsigned);
#define MATERIAL_SET_OBJECT(slot_, value_) \
    { IDirect3DDevice8 *device_ = DX8Wrapper::_Get_D3D_Device8(); \
      (*(MaterialSetObjectFn **)device_)[(slot_)/4](device_, value_); number_of_DX8_calls++; }
#define MATERIAL_SET_CONSTANT(reg_, data_, count_) \
    { if(memcmp(data_, &DX8Wrapper::Vertex_Shader_Constants[reg_],sizeof(Vector4)*(count_))!=0) { \
      memcpy(&DX8Wrapper::Vertex_Shader_Constants[reg_],data_,sizeof(Vector4)*(count_)); \
      IDirect3DDevice8 *device_ = DX8Wrapper::_Get_D3D_Device8(); \
      (*(MaterialSetConstantFn **)device_)[0x178/4](device_,reg_,data_,count_); number_of_DX8_calls++; } }
extern __declspec(align(4)) unsigned char Rva013071A0[4];
extern unsigned Rva013071A4;
extern Vector4 Rva0130718C;
typedef char ShaderExtentRva007CBD90[sizeof(ShaderClass)==4 ? 1 : -1];
void Rva007CBB30::Install_Materials() const
{
    if (g_bfmeBEAX == 0) {
        BfmeVertexElement declaration[] = {
            {0,0,2,0,0,0}, {0,12,2,0,3,0}, {0xff,0,17,0,0,0}
        };
        IDirect3DDevice8 *device = DX8Wrapper::_Get_D3D_Device8();
        (*(MaterialCreateDeclarationFn **)device)[0x158/4](device,declaration,&g_bfmeBEAX);
        BfmeVertexShaderLoader::LoadAndCreateD3DShader("shaders\\unlitnormalextrusion.vso",(DWORD *)&g_bfmeAEAX);
    }
    if (!(Rva013071A4 & 1)) {
        Rva013071A4 |= 1;
        new (Rva013071A0) ShaderClass(0x105833);
    }
    unsigned color = const_cast<Rva007CBB30 *>(this)->methodRva007CBB70();
    DX8Wrapper::Set_Shader(*(ShaderClass *)Rva013071A0);
    DX8Wrapper::Apply_Render_State_Changes();
    BFME_SET_TSS(0,D3DTSS_COLORARG1,3);
    BFME_SET_TSS_LATE(0,D3DTSS_COLOROP,2);
    BFME_SET_RS(D3DRS_TEXTUREFACTOR,color);
    MATERIAL_SET_OBJECT(0x15c,g_bfmeBEAX);
    MATERIAL_SET_OBJECT(0x170,g_bfmeAEAX);
    D3DXMATRIX world,view,projection,result;
    DX8Wrapper::_Get_DX8_Transform(D3DTS_WORLD,*(Matrix4x4 *)&world);
    DX8Wrapper::_Get_DX8_Transform(D3DTS_VIEW,*(Matrix4x4 *)&view);
    DX8Wrapper::_Get_DX8_Transform(D3DTS_PROJECTION,*(Matrix4x4 *)&projection);
    D3DXMatrixMultiply(&result,&view,&projection);
    D3DXMatrixMultiply(&result,&world,&result);
    D3DXMatrixTranspose(&result,&result);
    MATERIAL_SET_CONSTANT(4,&result,4);
    Rva0130718C.X = m_at3c;
    MATERIAL_SET_CONSTANT(8,&Rva0130718C,1);
}
#undef MATERIAL_SET_OBJECT
#undef MATERIAL_SET_CONSTANT
