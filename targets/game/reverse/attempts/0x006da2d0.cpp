// ?d_006da2d0@@YAXXZ
// partial score=0.48 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
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

// FILE: W3DBridgeBuffer.cpp ////////////////////////////////////////////////
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
// File name: W3DBridgeBuffer.cpp
//
// Created:   John Ahlquist, May 2001
//
// Desc:      Draw buffer to handle all the bridges in a scene.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//         Includes                                                      
//-----------------------------------------------------------------------------
#include "W3DDevice/GameClient/W3DBridgeBuffer.h"

#include <stdio.h>
#include <string.h>
#include "W3DDevice/GameClient/W3DAssetManager.h"
#include <texture.h>
#include "common/GlobalData.h"
#include "common/RandomValue.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "GameClient/TerrainRoads.h"
#include "GameLogic/Damage.h"
#include "GameLogic/Module/BodyModule.h"
#include "W3DDevice/GameLogic/W3DTerrainLogic.h"
#include "W3DDevice/GameClient/TerrainTex.h"
#include "W3DDevice/GameClient/HeightMap.h"
#include "W3DDevice/GameClient/W3DDynamicLight.h"
#include "W3DDevice/GameClient/Module/W3DModelDraw.h"
#include "W3DDevice/GameClient/W3DShaderManager.h"
#include "W3DDevice/GameClient/W3DShroud.h"
#include "WW3D2/Camera.h"
#include "WW3D2/DX8Wrapper.h"
#include "WW3D2/DX8Renderer.h"
#include "WW3D2/Mesh.h"
#include "WW3D2/MeshMdl.h"
#include "WW3D2/Scene.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-----------------------------------------------------------------------------
//         Private Data                                                     
//-----------------------------------------------------------------------------
// A W3D shader that does alpha, texturing, tests zbuffer, doesn't update zbuffer.
#define SC_ALPHA_DETAIL ( SHADE_CNST(ShaderClass::PASS_LEQUAL, ShaderClass::DEPTH_WRITE_ENABLE, ShaderClass::COLOR_WRITE_ENABLE, ShaderClass::SRCBLEND_SRC_ALPHA, \
	ShaderClass::DSTBLEND_ONE_MINUS_SRC_ALPHA, ShaderClass::FOG_DISABLE, ShaderClass::GRADIENT_MODULATE, ShaderClass::SECONDARY_GRADIENT_DISABLE, ShaderClass::TEXTURING_ENABLE, \
	ShaderClass::ALPHATEST_ENABLE, ShaderClass::CULL_MODE_DISABLE, \
	ShaderClass::DETAILCOLOR_DISABLE, ShaderClass::DETAILALPHA_DISABLE) )

static ShaderClass detailAlphaShader(SC_ALPHA_DETAIL);


#define SC_ALPHA_MIRROR ( SHADE_CNST(ShaderClass::PASS_LEQUAL, ShaderClass::DEPTH_WRITE_ENABLE, ShaderClass::COLOR_WRITE_ENABLE, ShaderClass::SRCBLEND_ONE, \
	ShaderClass::DSTBLEND_ZERO, ShaderClass::FOG_DISABLE, ShaderClass::GRADIENT_MODULATE, ShaderClass::SECONDARY_GRADIENT_DISABLE, ShaderClass::TEXTURING_ENABLE, \
	ShaderClass::ALPHATEST_DISABLE, ShaderClass::CULL_MODE_DISABLE, \
	ShaderClass::DETAILCOLOR_DISABLE, ShaderClass::DETAILALPHA_DISABLE) )

static ShaderClass detailShader(SC_ALPHA_MIRROR);

#define NO_USE_BRIDGE_NORMALS

//-----------------------------------------------------------------------------
//         Private Classes                                               
//-----------------------------------------------------------------------------
// Banked attempt for retail 0x006DA2D0 (1191 B, ret 0xC). Lives in
// game/GameEngineDevice/Source/W3DDevice/GameClient/W3DBridgeBuffer.cpp: the
// renderBridge below replaces that TU's out-of-line ZH body (retail inlines it
// with no polygon/vertex checks). Still missing: the BFME texture handle for
// the third parameter and for getShroudTexture (0x006D2630 via ILT 0x13BBF, sret)
// whose destructor supplies retail's SEH frame, and the refcounted BFME
// W3DShaderManager::setTexture (REF_PTR_SET into m_Textures at 0x012F9D28).

extern void BoxSetTexture(unsigned stage, TextureBaseClass *& texture);
inline void W3DBridge::renderBridge(Bool wireframe)
{
	if (!wireframe) BoxSetTexture(0, (TextureBaseClass *&)m_bridgeTexture);
	// Draw all the bridges.
	DX8Wrapper::Draw_Triangles(	m_firstIndex, m_numPolygons, m_firstVertex,	m_numVertex);
}

// BFME's DX8Wrapper::Set_Shader is the Zero Hour inline with its snapshot
// StringClass compiled in; MSVC 7.1 will not inline a wrapper that builds an
// object with a destructor, so expand it here (TerrainShader2StageSet.cpp
// does the same for the render-state setters).
struct BfmeBridgeDX8Access : public DX8Wrapper
{
	static __forceinline RenderStateStruct &state() { return render_state; }
	static __forceinline unsigned &changed() { return render_state_changed; }
	enum { SHADER_CHANGED_BIT = 1 << 15 };	// DX8Wrapper::SHADER_CHANGED is private
};
struct BfmeBridgeShaderAccess : public ShaderClass
{
	static __forceinline bool &dirty() { return ShaderDirty; }
};
#define BFME_BRIDGE_SET_SHADER(shader_) \
	if (BfmeBridgeShaderAccess::dirty() || (unsigned &)(shader_) != (unsigned &)BfmeBridgeDX8Access::state().shader) { \
		BfmeBridgeDX8Access::state().shader = (shader_); \
		BfmeBridgeDX8Access::changed() |= BfmeBridgeDX8Access::SHADER_CHANGED_BIT; \
		StringClass shader_description; \
	}

// ?drawBridges@W3DBridgeBuffer@@QAEXPAVCameraClass@@_NPAVTextureClass@@@Z present-unmatched
void W3DBridgeBuffer::drawBridges(CameraClass * camera, Bool wireframe, TextureClass *cloudTexture)
{
	Int curBridge;
	if (TheTerrainLogic) {
		for (curBridge=0; curBridge<m_numBridges; curBridge++) {
			m_bridges[curBridge].setEnabled(false);
		}
		Bool changed = false;
		for (Bridge *bridge = TheTerrainLogic->getFirstBridge(); bridge; bridge = bridge->getNext()) {
			BridgeInfo info;
			bridge->getBridgeInfo(&info);
			if (info.bridgeIndex<0 || info.bridgeIndex>=m_numBridges) {
				continue;
			}
			m_bridges[info.bridgeIndex].setEnabled(true);
			if (m_bridges[info.bridgeIndex].getDamageState() != info.curDamageState) {
				changed = true;
				enum BodyDamageType curState = m_bridges[info.bridgeIndex].getDamageState();
				m_bridges[info.bridgeIndex].setDamageState(info.curDamageState);
				if (!m_bridges[info.bridgeIndex].load(info.curDamageState)) {
					m_bridges[info.bridgeIndex].load(curState);
					m_bridges[info.bridgeIndex].setDamageState(info.curDamageState);
				}
			}
		}
		if (changed) {
			loadBridgesInVertexAndIndexBuffers(NULL);
		}
	} else {
		for (curBridge=0; curBridge<m_numBridges; curBridge++) {
			m_bridges[curBridge].setEnabled(true);
		}
	}

	if (m_curNumBridgeIndices == 0) {
		return;
	}

	DX8Wrapper::Set_Material(m_vertexMaterial);
	DX8Wrapper::Set_Index_Buffer(m_indexBridge,0);
	DX8Wrapper::Set_Vertex_Buffer(m_vertexBridge);
	BFME_BRIDGE_SET_SHADER(detailAlphaShader);
	DX8Wrapper::Apply_Render_State_Changes();

	if (!wireframe && cloudTexture) {
		W3DShaderManager::setTexture(1,cloudTexture);
		W3DShaderManager::setShader(W3DShaderManager::ST_CLOUD_TEXTURE,1);
	}

	for (curBridge=0; curBridge<m_numBridges; curBridge++) {
		if (m_bridges[curBridge].isEnabled() && m_bridges[curBridge].isVisible()) {
			m_bridges[curBridge].renderBridge(wireframe);
		}
	}

	if (!wireframe && cloudTexture) {
		W3DShaderManager::resetShader(W3DShaderManager::ST_CLOUD_TEXTURE);
	}

	if (!wireframe && TheTerrainRenderObject->getShroud()) {
		DX8Wrapper::Invalidate_Cached_Render_States();
		BFME_BRIDGE_SET_SHADER(ShaderClass::_PresetOpaqueShader);
		DX8Wrapper::Set_Material(m_vertexMaterial);
		DX8Wrapper::Set_Index_Buffer(m_indexBridge,0);
		DX8Wrapper::Set_Vertex_Buffer(m_vertexBridge);
		DX8Wrapper::Apply_Render_State_Changes();
		W3DShaderManager::setTexture(0,TheTerrainRenderObject->getShroud()->getShroudTexture());
		W3DShaderManager::setShader(W3DShaderManager::ST_SHROUD_TEXTURE, 0);
		for (curBridge=0; curBridge<m_numBridges; curBridge++) {
			if (m_bridges[curBridge].isEnabled() && m_bridges[curBridge].isVisible()) {
				m_bridges[curBridge].renderBridge(TRUE);
			}
		}
		W3DShaderManager::resetShader(W3DShaderManager::ST_SHROUD_TEXTURE);
	}
}
