// ?renderShadows@W3DVolumetricShadowManager@@QAEX_N@Z
// partial score=1.0 date=2026-09-23
// cl: /ICode/Libraries/Source/WWVegas/WW3D2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DBFME_VOLUMETRIC_DELETE_LAYOUT /Ireference/shims/volumetricshadow /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// readable body of ?Fabs@WWMath@@: Code/Libraries/Source/WWVegas/WW3D2/coltest.cpp
#define Matrix4x4 Matrix4  // BFME renamed it
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

// FILE: W3DVolumetricShadow.cpp ///////////////////////////////////////////////////////////
//
// Real time shadow volume representations
//
// Author: Colin Day, January 2001
// Adapted for W3D: Mark Wilczynski October 2001
//
//
///////////////////////////////////////////////////////////////////////////////
///@todo: Must cap shadow volumes if we ever allow camera inside the volumes.
///@todo: Find better way to determine when shadow volumes need updating - lights move, objects move.

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include <assert.h>

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "always.h"
#include "GameClient/View.h"
#include "WW3D2/Camera.h"
#include "WW3D2/Light.h"
#define MESH_RENDER_SNAPSHOT_ENABLED
#include "dx8wrapper.h"
#undef MESH_RENDER_SNAPSHOT_ENABLED
#include "WW3D2/DX8Wrapper.h"
#include "WW3D2/HLod.h"
#include "WW3D2/mesh.h"
#include "WW3D2/meshmdl.h"
#include "Lib/BaseType.h"
#include "W3DDevice/GameClient/W3DGranny.h"
#include "W3DDevice/GameClient/Heightmap.h"
#include "D3dx8math.h"
#include "common/GlobalData.h"
#include "common/drawmodule.h"
#include "W3DDevice/GameClient/W3DVolumetricShadow.h"
#include "W3DDevice/GameClient/W3DShadow.h"
#include "WW3D2/statistics.h"
#include "GameLogic/TerrainLogic.h"
#include "WW3D2/DX8Caps.h"
#include "GameClient/Drawable.h"
#include "wwshade/shdmesh.h"
#include "wwshade/shdsubmesh.h"


struct SHADOW_STATIC_VOLUME_VERTEX	//vertex structure passed to D3D
{
		float x,y,z;
}; 
#define SHADOW_STATIC_VOLUME_FVF	D3DFVF_XYZ

#ifdef SV_DEBUG	//in debug mode, dynamic shadows are rendered with random diffuse color
	struct SHADOW_DYNAMIC_VOLUME_VERTEX	//vertex structure passed to D3D
	{
			float x,y,z;
			DWORD diffuse;
	}; 
	#define SHADOW_DYNAMIC_VOLUME_FVF	D3DFVF_XYZ|D3DFVF_DIFFUSE
#else
	typedef struct SHADOW_STATIC_VOLUME_VERTEX	SHADOW_DYNAMIC_VOLUME_VERTEX;
	#define SHADOW_DYNAMIC_VOLUME_FVF	D3DFVF_XYZ
#endif

LPDIRECT3DVERTEXBUFFER8 shadowVertexBufferD3D=NULL;		///<D3D vertex buffer
LPDIRECT3DINDEXBUFFER8	shadowIndexBufferD3D=NULL;	///<D3D index buffer
int nShadowVertsInBuf=0;	//model vetices in vertex buffer
int nShadowStartBatchVertex=0;
int nShadowIndicesInBuf=0;	//model vetices in vertex buffer
int nShadowStartBatchIndex=0;
int SHADOW_VERTEX_SIZE=4096;
int SHADOW_INDEX_SIZE=8192;

//Rough bounding box around visible portion of the terrain
//useful for quick culling
static Real bcX;
static Real bcY;
static Real bcZ;
static Real beX;
static Real beY;
static Real beZ;

static LPDIRECT3DVERTEXBUFFER8 lastActiveVertexBuffer=NULL;


extern const FrustumClass *shadowCameraFrustum;
extern void BoxSetTexture(unsigned, TextureBaseClass*&);
class Rva007C2CD0Receiver { public: void invoke(); };
extern Rva007C2CD0Receiver* Rva01307178;
class Rva007BF7D0Receiver { public: void invoke(bool); };

struct Rva007BFB90TextureRef {
    TextureClass* texture;
    Rva007BFB90TextureRef():texture(0){}
    __forceinline ~Rva007BFB90TextureRef(){if(texture) texture->Release_Ref();}
};
// BFME retail device-interface slots, witnessed by the calls in this body.
class Rva007BFB90Device { public:
    virtual void rva_slot_000() = 0;
    virtual void rva_slot_004() = 0;
    virtual void rva_slot_008() = 0;
    virtual void rva_slot_00c() = 0;
    virtual void rva_slot_010() = 0;
    virtual void rva_slot_014() = 0;
    virtual void rva_slot_018() = 0;
    virtual void rva_slot_01c() = 0;
    virtual void rva_slot_020() = 0;
    virtual void rva_slot_024() = 0;
    virtual void rva_slot_028() = 0;
    virtual void rva_slot_02c() = 0;
    virtual void rva_slot_030() = 0;
    virtual void rva_slot_034() = 0;
    virtual void rva_slot_038() = 0;
    virtual void rva_slot_03c() = 0;
    virtual void rva_slot_040() = 0;
    virtual void rva_slot_044() = 0;
    virtual void rva_slot_048() = 0;
    virtual void rva_slot_04c() = 0;
    virtual void rva_slot_050() = 0;
    virtual void rva_slot_054() = 0;
    virtual void rva_slot_058() = 0;
    virtual void rva_slot_05c() = 0;
    virtual void rva_slot_060() = 0;
    virtual void rva_slot_064() = 0;
    virtual void rva_slot_068() = 0;
    virtual void rva_slot_06c() = 0;
    virtual void rva_slot_070() = 0;
    virtual void rva_slot_074() = 0;
    virtual void rva_slot_078() = 0;
    virtual void rva_slot_07c() = 0;
    virtual void rva_slot_080() = 0;
    virtual void rva_slot_084() = 0;
    virtual void rva_slot_088() = 0;
    virtual void rva_slot_08c() = 0;
    virtual void rva_slot_090() = 0;
    virtual void rva_slot_094() = 0;
    virtual void rva_slot_098() = 0;
    virtual void rva_slot_09c() = 0;
    virtual void rva_slot_0a0() = 0;
    virtual void rva_slot_0a4() = 0;
    virtual void rva_slot_0a8() = 0;
    virtual void rva_slot_0ac() = 0;
    virtual void rva_slot_0b0() = 0;
    virtual void rva_slot_0b4() = 0;
    virtual void rva_slot_0b8() = 0;
    virtual void rva_slot_0bc() = 0;
    virtual void rva_slot_0c0() = 0;
    virtual void rva_slot_0c4() = 0;
    virtual void rva_slot_0c8() = 0;
    virtual void rva_slot_0cc() = 0;
    virtual void rva_slot_0d0() = 0;
    virtual void rva_slot_0d4() = 0;
    virtual void rva_slot_0d8() = 0;
    virtual void rva_slot_0dc() = 0;
    virtual void rva_slot_0e0() = 0;
    virtual long __stdcall SetRenderState(D3DRENDERSTATETYPE,unsigned) = 0;
    virtual long __stdcall GetRenderState(D3DRENDERSTATETYPE,unsigned long*) = 0;
    virtual void rva_slot_0ec() = 0;
    virtual void rva_slot_0f0() = 0;
    virtual void rva_slot_0f4() = 0;
    virtual void rva_slot_0f8() = 0;
    virtual void rva_slot_0fc() = 0;
    virtual void rva_slot_100() = 0;
    virtual long __stdcall SetTexture(unsigned,IDirect3DBaseTexture8*) = 0;
    virtual void rva_slot_108() = 0;
    virtual long __stdcall SetTextureStageState(unsigned,D3DTEXTURESTAGESTATETYPE,unsigned) = 0;
    virtual void rva_slot_110() = 0;
    virtual void rva_slot_114() = 0;
    virtual void rva_slot_118() = 0;
    virtual void rva_slot_11c() = 0;
    virtual void rva_slot_120() = 0;
    virtual void rva_slot_124() = 0;
    virtual void rva_slot_128() = 0;
    virtual void rva_slot_12c() = 0;
    virtual void rva_slot_130() = 0;
    virtual void rva_slot_134() = 0;
    virtual void rva_slot_138() = 0;
    virtual void rva_slot_13c() = 0;
    virtual void rva_slot_140() = 0;
    virtual void rva_slot_144() = 0;
    virtual void rva_slot_148() = 0;
    virtual void rva_slot_14c() = 0;
    virtual void rva_slot_150() = 0;
    virtual void rva_slot_154() = 0;
    virtual void rva_slot_158() = 0;
    virtual void rva_slot_15c() = 0;
    virtual void rva_slot_160() = 0;
    virtual long __stdcall SetVertexShader(unsigned) = 0;
    virtual void rva_slot_168() = 0;
    virtual void rva_slot_16c() = 0;
    virtual long __stdcall SetPixelShader(unsigned) = 0;
};
static __forceinline W3DBufferManager::W3DVertexBuffer* Rva007BFB90NextVB(W3DBufferManager::W3DVertexBuffer* previous)
{
    return previous ? *(W3DBufferManager::W3DVertexBuffer**)((char*)previous+0x10)
                    : *(W3DBufferManager::W3DVertexBuffer**)((char*)TheW3DBufferManager+0x9000);
}

extern int Rva007AD820Lookup(int); // landed 12-byte table lookup, retail ILT 0x0001AFF0

void W3DVolumetricShadowManager::renderShadows( Bool forceStencilFill )
{
	W3DVolumetricShadow *shadow;
	Int numRenderedShadows = 0;

 	AABoxClass bbox;
	SphereClass bsphere;
 
 	//Get a bounding box around our visible universe.  Bounded by terrain and the sky
 	//so much tighter fitting volume than what's actually visible.  This will cull
 	//particles falling under the ground.
 
 	TheTerrainRenderObject->getMaximumVisibleBox(*shadowCameraFrustum, &bbox, TRUE);
 
 	bcX = bbox.Center.X;
 	bcY = bbox.Center.Y;
 	bcZ = bbox.Center.Z;
 	beX = bbox.Extent.X;
 	beY = bbox.Extent.Y;
 	beZ = bbox.Extent.Z;

	if (Rva01307178) Rva01307178->invoke();

	if (m_shadowList && *(const Bool*)((const char*)TheGlobalData+0x64))
	{

		Rva007BFB90Device* m_pDev=(Rva007BFB90Device*)DX8Wrapper::_Get_D3D_Device8();

		if (!m_pDev)
			return;	//need device to render anything.

 		//According to Nvidia there's a D3D bug that happens if you don't start with a
 		//new dynamic VB each frame - so we force a DISCARD by overflowing the counter.
 		nShadowIndicesInBuf = 0xffff;
 		nShadowVertsInBuf = 0xffff;

		//Set W3D to some known state
		VertexMaterialClass *vmat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
		DX8Wrapper::Set_Material(vmat);
		REF_PTR_RELEASE(vmat);

		DX8Wrapper::Set_Shader(ShaderClass::_PresetOpaqueShader);
// ?Set_Texture@DX8Wrapper@@SAXIPAVTextureBaseClass@@@Z present-unmatched
		{ Rva007BFB90TextureRef tex; BoxSetTexture(0, (TextureBaseClass*&)tex.texture); }	//turn off textures
// ?Set_Texture@DX8Wrapper@@SAXIPAVTextureBaseClass@@@Z present-unmatched
		{ Rva007BFB90TextureRef tex; BoxSetTexture(1, (TextureBaseClass*&)tex.texture); }	//turn off textures
// ?Apply_Render_State_Changes@DX8Wrapper@@ present-unmatched
		DX8Wrapper::Apply_Render_State_Changes();	//force update of view and projection matrices

		// turn off z writing
		m_pDev->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	  m_pDev->SetRenderState( D3DRS_ZENABLE,          TRUE );
		m_pDev->SetRenderState(D3DRS_ZWRITEENABLE , FALSE);
		m_pDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		m_pDev->SetRenderState(D3DRS_FOGENABLE, FALSE);


		// setup the TMU to default
		m_pDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
		m_pDev->SetRenderState(D3DRS_LIGHTING, FALSE);
		m_pDev->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		m_pDev->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
		m_pDev->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG2);
		m_pDev->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
		m_pDev->SetTextureStageState( 0, D3DTSS_TEXCOORDINDEX, 0 );

		m_pDev->SetTextureStageState( 1, D3DTSS_COLOROP,   D3DTOP_DISABLE);
		m_pDev->SetTextureStageState( 1, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
		m_pDev->SetTextureStageState( 1, D3DTSS_TEXCOORDINDEX, 1 );
		m_pDev->SetTexture(0,NULL);
		m_pDev->SetTexture(1,NULL);

		DWORD oldColorWriteEnable=0x12345678;

	#ifdef SV_DEBUG
		m_pDev->SetRenderState(D3DRS_ALPHABLENDENABLE , TRUE);
		m_pDev->SetRenderState( D3DRS_STENCILENABLE, FALSE );
		m_pDev->SetRenderState( D3DRS_SRCBLEND, /*D3DBLEND_DESTCOLOR*/D3DBLEND_ONE );
		m_pDev->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ZERO );
		m_pDev->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	#else
		//disable writes to color buffer
		if (DX8Wrapper::Get_Current_Caps()->Get_DX8_Caps().PrimitiveMiscCaps & D3DPMISCCAPS_COLORWRITEENABLE)
		{	((Rva007BFB90Device*)DX8Wrapper::_Get_D3D_Device8())->GetRenderState(D3DRS_COLORWRITEENABLE, &oldColorWriteEnable);
			DX8Wrapper::Set_DX8_Render_State(D3DRS_COLORWRITEENABLE,0);
		}
		else
		{	//device does not support disabling writes to color buffer so fake it through alpha blending
			m_pDev->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_ZERO );
			m_pDev->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
			m_pDev->SetRenderState(D3DRS_ALPHABLENDENABLE , TRUE);
		}
		m_pDev->SetRenderState( D3DRS_STENCILENABLE, TRUE );
	#endif
		//Any pixels with stencil already set to 128 contains a potential occluder.  If this pixels also has any of the player
		//color stencil bits also set, it means that it's an occluded player color and we need to NOT render shadows here.  We
		//do this determination by comparing the value in the combined bits against a value containing only a potential occluder.
		//If the value of just the potential occluder bit is >= than the combined bits, then we know none of the player color
		//bits were set and it's okay to render shadow.
		if (TheW3DShadowManager->getStencilShadowMask() == 0x80808080)
			m_pDev->SetRenderState( D3DRS_STENCILFUNC,     D3DCMP_GREATER );	//in this mode, MSB indicates occluded player pixels.
		else
			m_pDev->SetRenderState( D3DRS_STENCILFUNC,     D3DCMP_GREATEREQUAL );	//in this mode, multiple bits indicate occluded player pixels.
		m_pDev->SetRenderState( D3DRS_STENCILREF,      0x80808080 );			//isolate MSB, it's used to indicate pixels containing potential occluders.
		m_pDev->SetRenderState( D3DRS_STENCILMASK,     TheW3DShadowManager->getStencilShadowMask());	//isolate upper bits containing PotentialOccluderBit|PlayerColorBits
		m_pDev->SetRenderState( D3DRS_STENCILWRITEMASK,0xffffffff );
		m_pDev->SetRenderState( D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP );
		m_pDev->SetRenderState( D3DRS_STENCILFAIL,  D3DSTENCILOP_KEEP );
		m_pDev->SetRenderState( D3DRS_STENCILPASS,  D3DSTENCILOP_INCR );
		
		m_pDev->SetPixelShader(0);
		m_pDev->SetVertexShader(SHADOW_DYNAMIC_VOLUME_FVF);

		m_pDev->SetRenderState(D3DRS_CULLMODE,D3DCULL_CW);
//		m_pDev->SetRenderState(D3DRS_ZBIAS,1);	///@todo: See if this helps or makes things worse.
		//m_pDev->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);


		lastActiveVertexBuffer=NULL;	//reset

		m_dynamicShadowVolumesToRender=NULL;	//clear list of pending dynamic shadows
		W3DVolumetricShadowRenderTask *shadowDynamicTasksStart,*shadowDynamicTask;
		
		// step through each of our shadows and render
		for( shadow = m_shadowList; shadow; shadow = *(W3DVolumetricShadow**)((char*)shadow+0x68) )
		{
			if (shadow->m_isEnabled && !shadow->m_isInvisibleEnabled)
			{
				//Record last added task
				shadowDynamicTasksStart=m_dynamicShadowVolumesToRender;
				reinterpret_cast<Rva007BF7D0Receiver*>(shadow)->invoke(false);
				shadowDynamicTask=m_dynamicShadowVolumesToRender;
				while (shadowDynamicTask != shadowDynamicTasksStart)
				{	//update() added a dynamic shadow
					//dynamic shadow columes don't need to wait in queue since they
					//all use the same vertex buffer.  Flush them ASAP.
					shadow->RenderVolume(shadowDynamicTask->m_meshIndex,shadowDynamicTask->m_lightIndex);
					//move to next dynamic task
					shadowDynamicTask=(W3DVolumetricShadowRenderTask *)shadowDynamicTask->m_nextTask;
					numRenderedShadows++;
				}
			}
		}  // end for

		// Set vertex format to that used by static shadow volumes
		m_pDev->SetVertexShader(Rva007AD820Lookup(0));

		//Empty queue of static shadow volumes to render.
		W3DBufferManager::W3DVertexBuffer *nextVb;
		W3DVolumetricShadowRenderTask *nextTask;
		for (nextVb=Rva007BFB90NextVB(NULL);nextVb != NULL; nextVb=Rva007BFB90NextVB(nextVb))
		{
			nextTask=(W3DVolumetricShadowRenderTask *)nextVb->m_renderTaskList;
			while (nextTask)
			{
				nextTask->m_parentShadow->RenderVolume(nextTask->m_meshIndex,nextTask->m_lightIndex);
				nextTask=(W3DVolumetricShadowRenderTask *)nextTask->m_nextTask;
				numRenderedShadows++;
			}
		}

		// change the stencil op to decrement
		m_pDev->SetRenderState( D3DRS_STENCILPASS,  D3DSTENCILOP_DECRSAT);

		//
		// invert normals of shadow volumes so we can decrement in the
		// stencil buffer and render
		//

		m_pDev->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);

		for (nextVb=Rva007BFB90NextVB(NULL);nextVb != NULL; nextVb=Rva007BFB90NextVB(nextVb))
		{
			nextTask=(W3DVolumetricShadowRenderTask *)nextVb->m_renderTaskList;
			while (nextTask)
			{
				nextTask->m_parentShadow->RenderVolume(nextTask->m_meshIndex,nextTask->m_lightIndex);
				nextTask=(W3DVolumetricShadowRenderTask *)nextTask->m_nextTask;
			}
		}

		m_pDev->SetVertexShader(SHADOW_DYNAMIC_VOLUME_FVF);
		//flush any dynamic shadow volumes
		shadowDynamicTask=m_dynamicShadowVolumesToRender;
		while (shadowDynamicTask)
		{	//dynamic shadow columes don't need to wait in queue since they
			//all use the same vertex buffer.  Flush them ASAP.
			shadowDynamicTask->m_parentShadow->RenderVolume(shadowDynamicTask->m_meshIndex,shadowDynamicTask->m_lightIndex);
			shadowDynamicTask=(W3DVolumetricShadowRenderTask *)shadowDynamicTask->m_nextTask;
		}

		//Reset all render tasks for next frame.
		for (nextVb=Rva007BFB90NextVB(NULL);nextVb != NULL; nextVb=Rva007BFB90NextVB(nextVb))
		{
			nextVb->m_renderTaskList=NULL;
		}

		m_pDev->SetRenderState(D3DRS_CULLMODE,D3DCULL_CW);
//		m_pDev->SetRenderState(D3DRS_ZBIAS,0);	///@todo: See if this helps or makes things worse.
		//m_pDev->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);


		if (oldColorWriteEnable != 0x12345678)
			DX8Wrapper::Set_DX8_Render_State(D3DRS_COLORWRITEENABLE,oldColorWriteEnable);

		//
		// render the big transparent square of shadows in the stencil buffer
		// to the screen
		//
///@todo: Put this check back in after water is fixed so it doesn't require shadow rendering to fix alpha.
//		if (numRenderedShadows)
			renderStencilShadows();

		m_pDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
		m_pDev->SetRenderState(D3DRS_ALPHABLENDENABLE , FALSE);
		m_pDev->SetRenderState(D3DRS_LIGHTING, FALSE);

		DX8Wrapper::Invalidate_Cached_Render_States();
	}
	else
	if (forceStencilFill)
	{	//no shadows to render, but still need to fill stencil buffer
		//for other effects.

		//Set W3D to some known state
		VertexMaterialClass *vmat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
		DX8Wrapper::Set_Material(vmat);
		REF_PTR_RELEASE(vmat);
		DX8Wrapper::Set_Shader(ShaderClass::_PresetOpaqueShader);
		{ Rva007BFB90TextureRef tex; BoxSetTexture(0, (TextureBaseClass*&)tex.texture); }
// ?Apply_Render_State_Changes@DX8Wrapper@@ present-unmatched
		DX8Wrapper::Apply_Render_State_Changes();	//force update of view and projection matrices

		renderStencilShadows();

		DX8Wrapper::Invalidate_Cached_Render_States();
	}

}
