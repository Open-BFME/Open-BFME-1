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
	__forceinline IDirect3DBaseTexture8 *Peek_D3D_Base_Texture() const { return ((const TextureBaseClass *)this)->Peek_D3D_Base_Texture(); }
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

class BFMEValueName
{
	TCHAR *m_Buffer;

public:
	__forceinline BFMEValueName(int initial_len, bool hint_temporary)
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

namespace {
    typedef HRESULT (__stdcall *BFMESetTSSFn)(IDirect3DDevice8 *, DWORD, DWORD, DWORD);
    typedef HRESULT (__stdcall *BFMESetRSFn)(IDirect3DDevice8 *, DWORD, DWORD);
    enum { BFME_SAMP_ADDRESSU=1, BFME_SAMP_ADDRESSV=2,
           BFME_SAMP_MAGFILTER=5, BFME_SAMP_MINFILTER=6 };
    enum { BFME_SET_TSS_SLOT=67, BFME_SET_RS_SLOT=57, BFME_SET_SAMP_SLOT=69 };
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

#define BFME_SET_RS(state_, value_)                                                          \
	if (DX8Wrapper::RenderStates[state_] != (unsigned)(value_)) {                            \
		if (WW3D::Is_Snapshot_Activated()) {                                                 \
			BFMEValueName value_name(0, true);                                                 \
			DX8Wrapper::Get_DX8_Render_State_Value_Name(*(StringClass *)&value_name,                          \
				(D3DRENDERSTATETYPE)(state_), (value_));                                     \
		}                                                                                    \
		DX8Wrapper::RenderStates[state_] = (value_);                                         \
		IDirect3DDevice8 *rs_device_ = DX8Wrapper::_Get_D3D_Device8();                       \
		(*(BFMESetRSFn **)rs_device_)[BFME_SET_RS_SLOT](rs_device_, (state_), (value_));     \
		number_of_DX8_calls++;                                                               \
		DX8Wrapper::render_state_changes++;                                                  \
	}

// TerrainShader2Stage::set, retail RVA 0x007DD180, 6636 bytes.
// Identity: the matched init/reset at 0x007DCBE0/0x007DCC60 own the
// terrainShader2Stage instance; TerrainShader8Stage::set invokes this pass
// through its ILT route. Layout declarations mirror W3DShaderManager.cpp.
// BFME differs from ZH: uncached transform slot 44, texture slot 65,
// stage-state slot 67 and sampler slot 69. Full-expression texture handles
// are required: six separate EH temporaries account for the 0xA4 frame.
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
};
void j_00019bff();
void j_000051ff();
void Rva006D4690Apply(void *);
typedef HRESULT (__stdcall *TerrainTransformFn)(IDirect3DDevice8 *, DWORD, const Matrix4 *);
__forceinline void terrainSetTransform(DWORD state, const Matrix4 &matrix)
{
    DX8Wrapper::matrix_changes++;
    IDirect3DDevice8 *device = DX8Wrapper::_Get_D3D_Device8();
    (*(TerrainTransformFn **)device)[44](device, state, &matrix);
    number_of_DX8_calls++;
}
class Rva007DD180Device { public:
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
virtual void slot44() = 0;
virtual void slot45() = 0;
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
virtual void slot57() = 0;
virtual void slot58() = 0;
virtual void slot59() = 0;
virtual void slot60() = 0;
virtual void slot61() = 0;
virtual void slot62() = 0;
virtual void slot63() = 0;
virtual void slot64() = 0;
virtual HRESULT __stdcall SetTexture(DWORD stage, IDirect3DBaseTexture8 *texture) = 0;
};
Int TerrainShader2Stage::set(Int pass)
{
	typedef void (TerrainShader2Stage::*TerrainNoiseMatrixFn)(D3DXMATRIX *, D3DXMATRIX *, Bool);
	union TerrainNoiseMatrixCast {
		void (*raw)();
		TerrainNoiseMatrixFn member;
	};
	TerrainNoiseMatrixCast updateNoise1Cast;
	updateNoise1Cast.raw = j_00019bff;
	TerrainNoiseMatrixCast updateNoise2Cast;
	updateNoise2Cast.raw = j_000051ff;

	DX8Wrapper::Apply_Render_State_Changes();
	Rva006D4690Apply((void *)0);
	Rva006D4690Apply((void *)1);

	switch (pass)
	{
	case 0:
		{
			((Rva007DD180Device *)DX8Wrapper::_Get_D3D_Device8())->SetTexture( 0, bfmeGet(0).Peek_D3D_Base_Texture());
		}
		BFME_SET_SAMP(0, BFME_SAMP_ADDRESSU, D3DTADDRESS_CLAMP);
		BFME_SET_SAMP(0, BFME_SAMP_ADDRESSV, D3DTADDRESS_CLAMP);
		BFME_SET_TSS(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		BFME_SET_TSS(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		BFME_SET_TSS(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		BFME_SET_TSS(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
		BFME_SET_TSS(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
		BFME_SET_TSS(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
		BFME_SET_TSS(0, D3DTSS_TEXCOORDINDEX, 0);
		BFME_SET_RS(D3DRS_ALPHABLENDENABLE, false);
		break;
	case 1:
		{
			((Rva007DD180Device *)DX8Wrapper::_Get_D3D_Device8())->SetTexture( 0, bfmeGet(1).Peek_D3D_Base_Texture());
		}
		BFME_SET_SAMP(0, BFME_SAMP_ADDRESSU, D3DTADDRESS_CLAMP);
		BFME_SET_SAMP(0, BFME_SAMP_ADDRESSV, D3DTADDRESS_CLAMP);
		BFME_SET_TSS(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		BFME_SET_TSS(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		BFME_SET_TSS(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		BFME_SET_TSS(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		BFME_SET_TSS(0, D3DTSS_TEXCOORDINDEX, 1);
		BFME_SET_RS(D3DRS_ALPHABLENDENABLE, true);
		BFME_SET_RS(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		BFME_SET_RS(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		BFME_SET_TSS(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
		BFME_SET_TSS(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
		break;
	case 2:
		{
			Matrix4x4 curView;
			DX8Wrapper::_Get_DX8_Transform(D3DTS_VIEW, curView);
			BFME_SET_TSS(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
			BFME_SET_TSS(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
			BFME_SET_TSS(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
			BFME_SET_TSS(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
			BFME_SET_TSS(0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
			BFME_SET_TSS(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
			BFME_SET_SAMP(0, BFME_SAMP_ADDRESSU, D3DTADDRESS_WRAP);
			BFME_SET_SAMP(0, BFME_SAMP_ADDRESSV, D3DTADDRESS_WRAP);
			BFME_SET_RS(D3DRS_ALPHABLENDENABLE, true);
			BFME_SET_RS(D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR);
			BFME_SET_RS(D3DRS_DESTBLEND, D3DBLEND_ZERO);
			D3DXMATRIX inv;
			float det;
			D3DXMatrixInverse(&inv, &det, (D3DXMATRIX *)&curView);
			if (W3DShaderManager::getCurrentShader() == W3DShaderManager::ST_TERRAIN_BASE_NOISE12)
			{
				{
					((Rva007DD180Device *)DX8Wrapper::_Get_D3D_Device8())->SetTexture( 0, bfmeGet(2).Peek_D3D_Base_Texture());
				}
				(this->*updateNoise1Cast.member)((D3DXMATRIX *)&curView, &inv, true);
				terrainSetTransform(D3DTS_TEXTURE0, curView);
				BFME_SET_SAMP(0, BFME_SAMP_MINFILTER, D3DTEXF_LINEAR);
				BFME_SET_SAMP(0, BFME_SAMP_MAGFILTER, D3DTEXF_LINEAR);
				{
					((Rva007DD180Device *)DX8Wrapper::_Get_D3D_Device8())->SetTexture( 1, bfmeGet(3).Peek_D3D_Base_Texture());
				}
				(this->*updateNoise2Cast.member)((D3DXMATRIX *)&curView, &inv, true);
				terrainSetTransform(D3DTS_TEXTURE1, curView);
				BFME_SET_SAMP(1, BFME_SAMP_MINFILTER, D3DTEXF_POINT);
				BFME_SET_SAMP(1, BFME_SAMP_MAGFILTER, D3DTEXF_LINEAR);
				BFME_SET_TSS(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
				BFME_SET_TSS(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
				BFME_SET_TSS(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
				BFME_SET_TSS(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
				BFME_SET_TSS(1, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
				BFME_SET_TSS(1, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
				BFME_SET_SAMP(1, BFME_SAMP_ADDRESSU, D3DTADDRESS_WRAP);
				BFME_SET_SAMP(1, BFME_SAMP_ADDRESSV, D3DTADDRESS_WRAP);
			}
			else
			{
				if (W3DShaderManager::getCurrentShader() == W3DShaderManager::ST_TERRAIN_BASE_NOISE1)
				{
					((Rva007DD180Device *)DX8Wrapper::_Get_D3D_Device8())->SetTexture( 0, bfmeGet(2).Peek_D3D_Base_Texture());
					(this->*updateNoise1Cast.member)((D3DXMATRIX *)&curView, &inv, true);
					BFME_SET_SAMP(0, BFME_SAMP_MINFILTER, D3DTEXF_LINEAR);
					BFME_SET_SAMP(0, BFME_SAMP_MAGFILTER, D3DTEXF_LINEAR);
				}
				else
				{
					((Rva007DD180Device *)DX8Wrapper::_Get_D3D_Device8())->SetTexture( 0, bfmeGet(3).Peek_D3D_Base_Texture());
					(this->*updateNoise2Cast.member)((D3DXMATRIX *)&curView, &inv, true);
					BFME_SET_SAMP(1, BFME_SAMP_MINFILTER, D3DTEXF_POINT);
					BFME_SET_SAMP(1, BFME_SAMP_MAGFILTER, D3DTEXF_LINEAR);
				}
				BFME_SET_TSS(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
				BFME_SET_TSS(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
				terrainSetTransform(D3DTS_TEXTURE0, *((Matrix4x4 *)&curView));
			}
		}
		break;
	}
	return TRUE;
}
