// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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
//=============================================================================
// W3DBridge constructor.
//=============================================================================
/** Initializes pointers & values.  */
//=============================================================================
// ??0W3DBridge@@QAE@XZ present-unmatched
W3DBridge::W3DBridge() :
m_bridgeTexture(NULL),
m_leftMesh(NULL),
m_sectionMesh(NULL),
m_rightMesh(NULL),
m_visible(false),
m_curDamageState(BODY_PRISTINE),
m_scale(1.0)
{
}

//=============================================================================
// W3DBridge destructor.
//=============================================================================
/** Frees objects.  */
//=============================================================================
// ??1W3DBridge@@QAE@XZ present-unmatched
W3DBridge::~W3DBridge(void)
{
	clearBridge();
}

//=============================================================================
// W3DBridge::renderBridge
//=============================================================================
/** Renders the bride.  It is assumed that the shared vertex and index buffers
are already set.  */
//=============================================================================
// ?renderBridge@W3DBridge@@QAEX_N@Z present-unmatched
void W3DBridge::renderBridge(Bool wireframe)
{
	if (m_visible && m_numPolygons && m_numVertex) {
		if (!wireframe) DX8Wrapper::Set_Texture(0,m_bridgeTexture);
		// Draw all the bridges.
		DX8Wrapper::Draw_Triangles(	m_firstIndex, m_numPolygons, m_firstVertex,	m_numVertex);
	}
}

//=============================================================================
// W3DBridge::clearBridge
//=============================================================================
/** Frees all bridge objects (meshes & texture).  */
//=============================================================================
// ?clearBridge@W3DBridge@@QAEXXZ present-unmatched
void W3DBridge::clearBridge(void)
{
	m_visible = false;
	REF_PTR_RELEASE(m_bridgeTexture);
	REF_PTR_RELEASE(m_leftMesh);
	REF_PTR_RELEASE(m_sectionMesh);
	REF_PTR_RELEASE(m_rightMesh);
}

//=============================================================================
// W3DBridge::cullBridge
//=============================================================================
/** Culls bridge to camera.  */
//=============================================================================
Bool W3DBridge::cullBridge(CameraClass * camera)
{
	///@todo - cull bridges. 
	Bool wasVisible = m_visible;

	m_visible = true;

	return(wasVisible != m_visible);

}

#define BRIDGE_FLOAT_AMT (0.25f)

//=============================================================================
// W3DBridge::init
//=============================================================================
/** Inits a bridges location & type so it can be load'ed.  */
//=============================================================================
// ?init@W3DBridge@@QAEXVVector3@@0VAsciiString@@@Z present-unmatched
void W3DBridge::init(Vector3 fromLoc, Vector3 toLoc, AsciiString bridgeTemplateName)
{
	m_start = fromLoc;
	m_end = toLoc;
	m_templateName = bridgeTemplateName;
	m_enabled = true;
}

//=============================================================================
// W3DBridge::init
//=============================================================================
/** Loads a bridge model(if not already loaded) and gets meshes for use at 
specified location.  */
//=============================================================================
__declspec(naked) Bool W3DBridge::load(enum BodyDamageType curDamageState)
{
	__asm {
	__emit 0x6a;
	__emit 0xff;
	__emit 0x64;
	__emit 0xa1;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x68;
	__emit 0x7b;
	__emit 0xab;
	__emit 0x04;
	__emit 0x01;
	__emit 0x50;
	__emit 0x64;
	__emit 0x89;
	__emit 0x25;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x81;
	__emit 0xec;
	__emit 0x80;
	__emit 0x05;
	__emit 0x00;
	__emit 0x00;
	__emit 0x53;
	__emit 0x55;
	__emit 0x56;
	__emit 0x8b;
	__emit 0xf1;
	__emit 0x8b;
	__emit 0x4e;
	__emit 0x34;
	__emit 0x33;
	__emit 0xed;
	__emit 0x3b;
	__emit 0xcd;
	__emit 0x57;
	__emit 0x74;
	__emit 0x08;
	__emit 0xe8;
	__emit 0x61;
	__emit 0x2b;
	__emit 0x31;
	__emit 0x00;
	__emit 0x89;
	__emit 0x6e;
	__emit 0x34;
	__emit 0x8b;
	__emit 0x4e;
	__emit 0x38;
	__emit 0x3b;
	__emit 0xcd;
	__emit 0x74;
	__emit 0x0c;
	__emit 0xff;
	__emit 0x49;
	__emit 0x04;
	__emit 0x75;
	__emit 0x04;
	__emit 0x8b;
	__emit 0x01;
	__emit 0xff;
	__emit 0x10;
	__emit 0x89;
	__emit 0x6e;
	__emit 0x38;
	__emit 0x8b;
	__emit 0x4e;
	__emit 0x7c;
	__emit 0x3b;
	__emit 0xcd;
	__emit 0x74;
	__emit 0x0c;
	__emit 0xff;
	__emit 0x49;
	__emit 0x04;
	__emit 0x75;
	__emit 0x04;
	__emit 0x8b;
	__emit 0x11;
	__emit 0xff;
	__emit 0x12;
	__emit 0x89;
	__emit 0x6e;
	__emit 0x7c;
	__emit 0x8b;
	__emit 0x8e;
	__emit 0xb8;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x3b;
	__emit 0xcd;
	__emit 0x74;
	__emit 0x0f;
	__emit 0xff;
	__emit 0x49;
	__emit 0x04;
	__emit 0x75;
	__emit 0x04;
	__emit 0x8b;
	__emit 0x01;
	__emit 0xff;
	__emit 0x10;
	__emit 0x89;
	__emit 0xae;
	__emit 0xb8;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0x14;
	__emit 0xe1;
	__emit 0x11;
	__emit 0x01;
	__emit 0x66;
	__emit 0xa1;
	__emit 0x1c;
	__emit 0xe1;
	__emit 0x11;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x15;
	__emit 0x18;
	__emit 0xe1;
	__emit 0x11;
	__emit 0x01;
	__emit 0x89;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x80;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8a;
	__emit 0x0d;
	__emit 0x1e;
	__emit 0xe1;
	__emit 0x11;
	__emit 0x01;
	__emit 0x88;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x8a;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0x66;
	__emit 0x89;
	__emit 0x84;
	__emit 0x24;
	__emit 0x88;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0x33;
	__emit 0xc0;
	__emit 0x89;
	__emit 0x94;
	__emit 0x24;
	__emit 0x84;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x15;
	__emit 0x00;
	__emit 0xe1;
	__emit 0x11;
	__emit 0x01;
	__emit 0xb9;
	__emit 0x3e;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8d;
	__emit 0xbc;
	__emit 0x24;
	__emit 0x8b;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0xf3;
	__emit 0xab;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0x08;
	__emit 0xe1;
	__emit 0x11;
	__emit 0x01;
	__emit 0xaa;
	__emit 0xa1;
	__emit 0x04;
	__emit 0xe1;
	__emit 0x11;
	__emit 0x01;
	__emit 0x89;
	__emit 0x54;
	__emit 0x24;
	__emit 0x7c;
	__emit 0x8b;
	__emit 0x15;
	__emit 0x0c;
	__emit 0xe1;
	__emit 0x11;
	__emit 0x01;
	__emit 0x89;
	__emit 0x84;
	__emit 0x24;
	__emit 0x80;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x84;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x33;
	__emit 0xc0;
	__emit 0x89;
	__emit 0x94;
	__emit 0x24;
	__emit 0x88;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xb9;
	__emit 0x3d;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8d;
	__emit 0xbc;
	__emit 0x24;
	__emit 0x8c;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xf3;
	__emit 0xab;
	__emit 0x51;
	__emit 0x8d;
	__emit 0x86;
	__emit 0x08;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0x64;
	__emit 0x24;
	__emit 0x58;
	__emit 0x8b;
	__emit 0xcc;
	__emit 0x50;
	__emit 0xe8;
	__emit 0x46;
	__emit 0xee;
	__emit 0x1a;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0x08;
	__emit 0x70;
	__emit 0x2f;
	__emit 0x01;
	__emit 0xe8;
	__emit 0x68;
	__emit 0xc0;
	__emit 0x95;
	__emit 0xff;
	__emit 0x8b;
	__emit 0xf8;
	__emit 0x3b;
	__emit 0xfd;
	__emit 0x0f;
	__emit 0x84;
	__emit 0xf4;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x84;
	__emit 0x24;
	__emit 0xa0;
	__emit 0x05;
	__emit 0x00;
	__emit 0x00;
	__emit 0x83;
	__emit 0xf8;
	__emit 0x03;
	__emit 0x8b;
	__emit 0x4f;
	__emit 0x1c;
	__emit 0x89;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x54;
	__emit 0x0f;
	__emit 0x87;
	__emit 0xdd;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0xff;
	__emit 0x24;
	__emit 0x85;
	__emit 0x14;
	__emit 0x97;
	__emit 0xad;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x54;
	__emit 0x24;
	__emit 0x10;
	__emit 0x52;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0xe8;
	__emit 0xb0;
	__emit 0xfc;
	__emit 0x96;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x00;
	__emit 0x3b;
	__emit 0xc5;
	__emit 0x8d;
	__emit 0x48;
	__emit 0x08;
	__emit 0x75;
	__emit 0x05;
	__emit 0xb9;
	__emit 0x8b;
	__emit 0x38;
	__emit 0x07;
	__emit 0x01;
	__emit 0x8d;
	__emit 0x94;
	__emit 0x24;
	__emit 0x80;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0xff;
	__emit 0x8a;
	__emit 0x01;
	__emit 0x41;
	__emit 0x88;
	__emit 0x02;
	__emit 0x42;
	__emit 0x84;
	__emit 0xc0;
	__emit 0x75;
	__emit 0xf6;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x10;
	__emit 0xe8;
	__emit 0xbd;
	__emit 0xeb;
	__emit 0x1a;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x44;
	__emit 0x24;
	__emit 0x78;
	__emit 0x50;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0xe8;
	__emit 0xcc;
	__emit 0xbe;
	__emit 0x96;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x00;
	__emit 0x3b;
	__emit 0xc5;
	__emit 0x8d;
	__emit 0x48;
	__emit 0x08;
	__emit 0x75;
	__emit 0x05;
	__emit 0xb9;
	__emit 0x8b;
	__emit 0x38;
	__emit 0x07;
	__emit 0x01;
	__emit 0x8d;
	__emit 0x54;
	__emit 0x24;
	__emit 0x7c;
	__emit 0x8a;
	__emit 0x01;
	__emit 0x41;
	__emit 0x88;
	__emit 0x02;
	__emit 0x42;
	__emit 0x84;
	__emit 0xc0;
	__emit 0x75;
	__emit 0xf6;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x78;
	__emit 0xe9;
	__emit 0x2d;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x74;
	__emit 0x51;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0xe8;
	__emit 0x81;
	__emit 0x85;
	__emit 0x94;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x00;
	__emit 0x3b;
	__emit 0xc5;
	__emit 0x8d;
	__emit 0x48;
	__emit 0x08;
	__emit 0x75;
	__emit 0x05;
	__emit 0xb9;
	__emit 0x8b;
	__emit 0x38;
	__emit 0x07;
	__emit 0x01;
	__emit 0x8d;
	__emit 0x94;
	__emit 0x24;
	__emit 0x80;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8a;
	__emit 0x01;
	__emit 0x41;
	__emit 0x88;
	__emit 0x02;
	__emit 0x42;
	__emit 0x84;
	__emit 0xc0;
	__emit 0x75;
	__emit 0xf6;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x74;
	__emit 0xe8;
	__emit 0x58;
	__emit 0xeb;
	__emit 0x1a;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x54;
	__emit 0x24;
	__emit 0x64;
	__emit 0x52;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0xe8;
	__emit 0x08;
	__emit 0x6e;
	__emit 0x96;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x00;
	__emit 0x3b;
	__emit 0xc5;
	__emit 0x8d;
	__emit 0x48;
	__emit 0x08;
	__emit 0x75;
	__emit 0x05;
	__emit 0xb9;
	__emit 0x8b;
	__emit 0x38;
	__emit 0x07;
	__emit 0x01;
	__emit 0x8d;
	__emit 0x54;
	__emit 0x24;
	__emit 0x7c;
	__emit 0x8a;
	__emit 0x01;
	__emit 0x41;
	__emit 0x88;
	__emit 0x02;
	__emit 0x42;
	__emit 0x84;
	__emit 0xc0;
	__emit 0x75;
	__emit 0xf6;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x64;
	__emit 0xe9;
	__emit 0xc8;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x44;
	__emit 0x24;
	__emit 0x68;
	__emit 0x50;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0xe8;
	__emit 0xaf;
	__emit 0xb9;
	__emit 0x95;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x00;
	__emit 0x3b;
	__emit 0xc5;
	__emit 0x8d;
	__emit 0x48;
	__emit 0x08;
	__emit 0x75;
	__emit 0x05;
	__emit 0xb9;
	__emit 0x8b;
	__emit 0x38;
	__emit 0x07;
	__emit 0x01;
	__emit 0x8d;
	__emit 0x94;
	__emit 0x24;
	__emit 0x80;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x9b;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8a;
	__emit 0x01;
	__emit 0x41;
	__emit 0x88;
	__emit 0x02;
	__emit 0x42;
	__emit 0x84;
	__emit 0xc0;
	__emit 0x75;
	__emit 0xf6;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x68;
	__emit 0xe8;
	__emit 0xed;
	__emit 0xea;
	__emit 0x1a;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x70;
	__emit 0x51;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0xe8;
	__emit 0xf1;
	__emit 0xce;
	__emit 0x95;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x00;
	__emit 0x3b;
	__emit 0xc5;
	__emit 0x8d;
	__emit 0x48;
	__emit 0x08;
	__emit 0x75;
	__emit 0x05;
	__emit 0xb9;
	__emit 0x8b;
	__emit 0x38;
	__emit 0x07;
	__emit 0x01;
	__emit 0x8d;
	__emit 0x54;
	__emit 0x24;
	__emit 0x7c;
	__emit 0x8a;
	__emit 0x01;
	__emit 0x41;
	__emit 0x88;
	__emit 0x02;
	__emit 0x42;
	__emit 0x84;
	__emit 0xc0;
	__emit 0x75;
	__emit 0xf6;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x70;
	__emit 0xeb;
	__emit 0x60;
	__emit 0x8d;
	__emit 0x54;
	__emit 0x24;
	__emit 0x6c;
	__emit 0x52;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0xe8;
	__emit 0x2c;
	__emit 0x4f;
	__emit 0x93;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x00;
	__emit 0x3b;
	__emit 0xc5;
	__emit 0x8d;
	__emit 0x48;
	__emit 0x08;
	__emit 0x75;
	__emit 0x05;
	__emit 0xb9;
	__emit 0x8b;
	__emit 0x38;
	__emit 0x07;
	__emit 0x01;
	__emit 0x8d;
	__emit 0x94;
	__emit 0x24;
	__emit 0x80;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8a;
	__emit 0x01;
	__emit 0x41;
	__emit 0x88;
	__emit 0x02;
	__emit 0x42;
	__emit 0x84;
	__emit 0xc0;
	__emit 0x75;
	__emit 0xf6;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x6c;
	__emit 0xe8;
	__emit 0x8b;
	__emit 0xea;
	__emit 0x1a;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x44;
	__emit 0x24;
	__emit 0x14;
	__emit 0x50;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0xe8;
	__emit 0x3f;
	__emit 0xe3;
	__emit 0x94;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x00;
	__emit 0x3b;
	__emit 0xc5;
	__emit 0x8d;
	__emit 0x48;
	__emit 0x08;
	__emit 0x75;
	__emit 0x05;
	__emit 0xb9;
	__emit 0x8b;
	__emit 0x38;
	__emit 0x07;
	__emit 0x01;
	__emit 0x8d;
	__emit 0x54;
	__emit 0x24;
	__emit 0x7c;
	__emit 0x8a;
	__emit 0x01;
	__emit 0x41;
	__emit 0x88;
	__emit 0x02;
	__emit 0x42;
	__emit 0x84;
	__emit 0xc0;
	__emit 0x75;
	__emit 0xf6;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x14;
	__emit 0xe8;
	__emit 0x5a;
	__emit 0xea;
	__emit 0x1a;
	__emit 0x00;
	__emit 0x33;
	__emit 0xc0;
	__emit 0xeb;
	__emit 0x06;
	__emit 0x8d;
	__emit 0x9b;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8a;
	__emit 0x4c;
	__emit 0x04;
	__emit 0x7c;
	__emit 0x88;
	__emit 0x8c;
	__emit 0x04;
	__emit 0x84;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x40;
	__emit 0x84;
	__emit 0xc9;
	__emit 0x75;
	__emit 0xf0;
	__emit 0x8d;
	__emit 0xbc;
	__emit 0x24;
	__emit 0x84;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x4f;
	__emit 0x8a;
	__emit 0x47;
	__emit 0x01;
	__emit 0x47;
	__emit 0x84;
	__emit 0xc0;
	__emit 0x75;
	__emit 0xf8;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0xf0;
	__emit 0xe0;
	__emit 0x11;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x15;
	__emit 0xf4;
	__emit 0xe0;
	__emit 0x11;
	__emit 0x01;
	__emit 0xa1;
	__emit 0xf8;
	__emit 0xe0;
	__emit 0x11;
	__emit 0x01;
	__emit 0x89;
	__emit 0x0f;
	__emit 0x8a;
	__emit 0x0d;
	__emit 0xfc;
	__emit 0xe0;
	__emit 0x11;
	__emit 0x01;
	__emit 0x89;
	__emit 0x57;
	__emit 0x04;
	__emit 0x89;
	__emit 0x47;
	__emit 0x08;
	__emit 0x88;
	__emit 0x4f;
	__emit 0x0c;
	__emit 0x33;
	__emit 0xc0;
	__emit 0x8a;
	__emit 0x4c;
	__emit 0x04;
	__emit 0x7c;
	__emit 0x88;
	__emit 0x8c;
	__emit 0x04;
	__emit 0x88;
	__emit 0x03;
	__emit 0x00;
	__emit 0x00;
	__emit 0x40;
	__emit 0x84;
	__emit 0xc9;
	__emit 0x75;
	__emit 0xf0;
	__emit 0x8d;
	__emit 0xbc;
	__emit 0x24;
	__emit 0x88;
	__emit 0x03;
	__emit 0x00;
	__emit 0x00;
	__emit 0x4f;
	__emit 0x8d;
	__emit 0x64;
	__emit 0x24;
	__emit 0x00;
	__emit 0x8a;
	__emit 0x47;
	__emit 0x01;
	__emit 0x47;
	__emit 0x84;
	__emit 0xc0;
	__emit 0x75;
	__emit 0xf8;
	__emit 0x8b;
	__emit 0x15;
	__emit 0xe0;
	__emit 0xe0;
	__emit 0x11;
	__emit 0x01;
	__emit 0xa1;
	__emit 0xe4;
	__emit 0xe0;
	__emit 0x11;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0xe8;
	__emit 0xe0;
	__emit 0x11;
	__emit 0x01;
	__emit 0x89;
	__emit 0x17;
	__emit 0x8a;
	__emit 0x15;
	__emit 0xec;
	__emit 0xe0;
	__emit 0x11;
	__emit 0x01;
	__emit 0x89;
	__emit 0x47;
	__emit 0x04;
	__emit 0x89;
	__emit 0x4f;
	__emit 0x08;
	__emit 0x88;
	__emit 0x57;
	__emit 0x0c;
	__emit 0x33;
	__emit 0xc0;
	__emit 0x8d;
	__emit 0x64;
	__emit 0x24;
	__emit 0x00;
	__emit 0x8a;
	__emit 0x4c;
	__emit 0x04;
	__emit 0x7c;
	__emit 0x88;
	__emit 0x8c;
	__emit 0x04;
	__emit 0x8c;
	__emit 0x04;
	__emit 0x00;
	__emit 0x00;
	__emit 0x40;
	__emit 0x84;
	__emit 0xc9;
	__emit 0x75;
	__emit 0xf0;
	__emit 0x8d;
	__emit 0xbc;
	__emit 0x24;
	__emit 0x8c;
	__emit 0x04;
	__emit 0x00;
	__emit 0x00;
	__emit 0x4f;
	__emit 0x8a;
	__emit 0x47;
	__emit 0x01;
	__emit 0x47;
	__emit 0x84;
	__emit 0xc0;
	__emit 0x75;
	__emit 0xf8;
	__emit 0xa1;
	__emit 0xd0;
	__emit 0xe0;
	__emit 0x11;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0xd4;
	__emit 0xe0;
	__emit 0x11;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x15;
	__emit 0xd8;
	__emit 0xe0;
	__emit 0x11;
	__emit 0x01;
	__emit 0x89;
	__emit 0x07;
	__emit 0x66;
	__emit 0xa1;
	__emit 0xdc;
	__emit 0xe0;
	__emit 0x11;
	__emit 0x01;
	__emit 0x89;
	__emit 0x4f;
	__emit 0x04;
	__emit 0x55;
	__emit 0x89;
	__emit 0x57;
	__emit 0x08;
	__emit 0x6a;
	__emit 0x03;
	__emit 0x8d;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x88;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0x51;
	__emit 0x8d;
	__emit 0x54;
	__emit 0x24;
	__emit 0x20;
	__emit 0x52;
	__emit 0x66;
	__emit 0x89;
	__emit 0x47;
	__emit 0x0c;
	__emit 0xe8;
	__emit 0x38;
	__emit 0x59;
	__emit 0x23;
	__emit 0x00;
	__emit 0x83;
	__emit 0xc4;
	__emit 0x10;
	__emit 0x8b;
	__emit 0xf8;
	__emit 0x8b;
	__emit 0x07;
	__emit 0x3b;
	__emit 0xc5;
	__emit 0x89;
	__emit 0xac;
	__emit 0x24;
	__emit 0x98;
	__emit 0x05;
	__emit 0x00;
	__emit 0x00;
	__emit 0x74;
	__emit 0x04;
	__emit 0x66;
	__emit 0xff;
	__emit 0x40;
	__emit 0x04;
	__emit 0x8b;
	__emit 0x4e;
	__emit 0x34;
	__emit 0x3b;
	__emit 0xcd;
	__emit 0x74;
	__emit 0x05;
	__emit 0xe8;
	__emit 0xa6;
	__emit 0x27;
	__emit 0x31;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x14;
	__emit 0x3b;
	__emit 0xcd;
	__emit 0x8b;
	__emit 0x07;
	__emit 0x89;
	__emit 0x46;
	__emit 0x34;
	__emit 0xc7;
	__emit 0x84;
	__emit 0x24;
	__emit 0x98;
	__emit 0x05;
	__emit 0x00;
	__emit 0x00;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0x74;
	__emit 0x05;
	__emit 0xe8;
	__emit 0x89;
	__emit 0x27;
	__emit 0x31;
	__emit 0x00;
	__emit 0x89;
	__emit 0x6e;
	__emit 0x40;
	__emit 0x89;
	__emit 0x6e;
	__emit 0x44;
	__emit 0x89;
	__emit 0x6e;
	__emit 0x48;
	__emit 0xb8;
	__emit 0x00;
	__emit 0x00;
	__emit 0x80;
	__emit 0x3f;
	__emit 0x89;
	__emit 0x46;
	__emit 0x3c;
	__emit 0x89;
	__emit 0x6e;
	__emit 0x4c;
	__emit 0x89;
	__emit 0x46;
	__emit 0x50;
	__emit 0x89;
	__emit 0x6e;
	__emit 0x54;
	__emit 0x89;
	__emit 0x6e;
	__emit 0x58;
	__emit 0x89;
	__emit 0x6e;
	__emit 0x5c;
	__emit 0x89;
	__emit 0x6e;
	__emit 0x60;
	__emit 0x89;
	__emit 0x46;
	__emit 0x64;
	__emit 0x89;
	__emit 0x6e;
	__emit 0x68;
	__emit 0x89;
	__emit 0x86;
	__emit 0xbc;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0xae;
	__emit 0xc0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0xae;
	__emit 0xc4;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0xae;
	__emit 0xc8;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0xae;
	__emit 0xcc;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0x86;
	__emit 0xd0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0xae;
	__emit 0xd4;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0xae;
	__emit 0xd8;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0xae;
	__emit 0xdc;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0xae;
	__emit 0xe0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0x86;
	__emit 0xe4;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0xae;
	__emit 0xe8;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0x86;
	__emit 0x80;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0xae;
	__emit 0x84;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0xae;
	__emit 0x88;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0xae;
	__emit 0x8c;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0xae;
	__emit 0x90;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0x86;
	__emit 0x94;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0xae;
	__emit 0x98;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0xae;
	__emit 0x9c;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x7c;
	__emit 0x51;
	__emit 0x89;
	__emit 0xae;
	__emit 0xa0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0xae;
	__emit 0xa4;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0x86;
	__emit 0xa8;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0xae;
	__emit 0xac;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0xb6;
	__emit 0x61;
	__emit 0x22;
	__emit 0x00;
	__emit 0x8b;
	__emit 0xd8;
	__emit 0x83;
	__emit 0xc4;
	__emit 0x04;
	__emit 0x3b;
	__emit 0xdd;
	__emit 0x0f;
	__emit 0x84;
	__emit 0x3c;
	__emit 0x03;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x13;
	__emit 0x8b;
	__emit 0xcb;
	__emit 0x89;
	__emit 0x6c;
	__emit 0x24;
	__emit 0x10;
	__emit 0xff;
	__emit 0x52;
	__emit 0x6c;
	__emit 0x85;
	__emit 0xc0;
	__emit 0x0f;
	__emit 0x8e;
	__emit 0xb6;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x2d;
	__emit 0x48;
	__emit 0x93;
	__emit 0x35;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x10;
	__emit 0x8b;
	__emit 0x03;
	__emit 0x51;
	__emit 0x8b;
	__emit 0xcb;
	__emit 0xff;
	__emit 0x50;
	__emit 0x74;
	__emit 0x8b;
	__emit 0xf8;
	__emit 0x8b;
	__emit 0x17;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0xff;
	__emit 0x52;
	__emit 0x50;
	__emit 0x8b;
	__emit 0x47;
	__emit 0x18;
	__emit 0x8b;
	__emit 0x57;
	__emit 0x20;
	__emit 0x8b;
	__emit 0x4f;
	__emit 0x1c;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x18;
	__emit 0x8b;
	__emit 0x47;
	__emit 0x24;
	__emit 0x89;
	__emit 0x54;
	__emit 0x24;
	__emit 0x20;
	__emit 0x8b;
	__emit 0x57;
	__emit 0x2c;
	__emit 0x89;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x1c;
	__emit 0x8b;
	__emit 0x4f;
	__emit 0x28;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x24;
	__emit 0x8b;
	__emit 0x47;
	__emit 0x30;
	__emit 0x89;
	__emit 0x54;
	__emit 0x24;
	__emit 0x2c;
	__emit 0x8b;
	__emit 0x57;
	__emit 0x38;
	__emit 0x89;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x28;
	__emit 0x8b;
	__emit 0x4f;
	__emit 0x34;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x30;
	__emit 0x8b;
	__emit 0x47;
	__emit 0x3c;
	__emit 0x89;
	__emit 0x54;
	__emit 0x24;
	__emit 0x38;
	__emit 0x8b;
	__emit 0x57;
	__emit 0x44;
	__emit 0x89;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x34;
	__emit 0x8b;
	__emit 0x4f;
	__emit 0x40;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x3c;
	__emit 0x8d;
	__emit 0x84;
	__emit 0x24;
	__emit 0x84;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0x54;
	__emit 0x24;
	__emit 0x44;
	__emit 0x89;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x40;
	__emit 0x8d;
	__emit 0x50;
	__emit 0x01;
	__emit 0x8a;
	__emit 0x08;
	__emit 0x40;
	__emit 0x84;
	__emit 0xc9;
	__emit 0x75;
	__emit 0xf9;
	__emit 0x2b;
	__emit 0xc2;
	__emit 0x50;
	__emit 0x8b;
	__emit 0x07;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0xff;
	__emit 0x50;
	__emit 0x18;
	__emit 0x50;
	__emit 0x8d;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x8c;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x51;
	__emit 0xff;
	__emit 0xd5;
	__emit 0x83;
	__emit 0xc4;
	__emit 0x0c;
	__emit 0x85;
	__emit 0xc0;
	__emit 0x75;
	__emit 0x6c;
	__emit 0x8b;
	__emit 0x54;
	__emit 0x24;
	__emit 0x18;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x1c;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x20;
	__emit 0x89;
	__emit 0x56;
	__emit 0x3c;
	__emit 0x8b;
	__emit 0x54;
	__emit 0x24;
	__emit 0x24;
	__emit 0x89;
	__emit 0x46;
	__emit 0x40;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x28;
	__emit 0x89;
	__emit 0x4e;
	__emit 0x44;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x2c;
	__emit 0x89;
	__emit 0x56;
	__emit 0x48;
	__emit 0x8b;
	__emit 0x54;
	__emit 0x24;
	__emit 0x30;
	__emit 0x89;
	__emit 0x46;
	__emit 0x4c;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x34;
	__emit 0x89;
	__emit 0x4e;
	__emit 0x50;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x38;
	__emit 0x89;
	__emit 0x56;
	__emit 0x54;
	__emit 0x8b;
	__emit 0x54;
	__emit 0x24;
	__emit 0x3c;
	__emit 0x89;
	__emit 0x46;
	__emit 0x58;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x40;
	__emit 0x89;
	__emit 0x4e;
	__emit 0x5c;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x44;
	__emit 0x89;
	__emit 0x4e;
	__emit 0x68;
	__emit 0x89;
	__emit 0x56;
	__emit 0x60;
	__emit 0x89;
	__emit 0x46;
	__emit 0x64;
	__emit 0x8b;
	__emit 0x17;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0xff;
	__emit 0x52;
	__emit 0x18;
	__emit 0x8d;
	__emit 0x94;
	__emit 0x24;
	__emit 0x84;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8a;
	__emit 0x08;
	__emit 0x40;
	__emit 0x88;
	__emit 0x0a;
	__emit 0x42;
	__emit 0x84;
	__emit 0xc9;
	__emit 0x75;
	__emit 0xf6;
	__emit 0x8d;
	__emit 0x84;
	__emit 0x24;
	__emit 0x88;
	__emit 0x03;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x50;
	__emit 0x01;
	__emit 0x8d;
	__emit 0x64;
	__emit 0x24;
	__emit 0x00;
	__emit 0x8a;
	__emit 0x08;
	__emit 0x40;
	__emit 0x84;
	__emit 0xc9;
	__emit 0x75;
	__emit 0xf9;
	__emit 0x2b;
	__emit 0xc2;
	__emit 0x50;
	__emit 0x8b;
	__emit 0x07;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0xff;
	__emit 0x50;
	__emit 0x18;
	__emit 0x50;
	__emit 0x8d;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x90;
	__emit 0x03;
	__emit 0x00;
	__emit 0x00;
	__emit 0x51;
	__emit 0xff;
	__emit 0xd5;
	__emit 0x83;
	__emit 0xc4;
	__emit 0x0c;
	__emit 0x85;
	__emit 0xc0;
	__emit 0x0f;
	__emit 0x85;
	__emit 0x93;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x54;
	__emit 0x24;
	__emit 0x18;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x1c;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x20;
	__emit 0x89;
	__emit 0x96;
	__emit 0x80;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x54;
	__emit 0x24;
	__emit 0x24;
	__emit 0x89;
	__emit 0x86;
	__emit 0x84;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x28;
	__emit 0x89;
	__emit 0x8e;
	__emit 0x88;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x2c;
	__emit 0x89;
	__emit 0x96;
	__emit 0x8c;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x54;
	__emit 0x24;
	__emit 0x30;
	__emit 0x89;
	__emit 0x86;
	__emit 0x90;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x34;
	__emit 0x89;
	__emit 0x8e;
	__emit 0x94;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x38;
	__emit 0x89;
	__emit 0x96;
	__emit 0x98;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x54;
	__emit 0x24;
	__emit 0x3c;
	__emit 0x89;
	__emit 0x86;
	__emit 0x9c;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x40;
	__emit 0x89;
	__emit 0x8e;
	__emit 0xa0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x44;
	__emit 0x89;
	__emit 0x8e;
	__emit 0xac;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0x96;
	__emit 0xa4;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0x86;
	__emit 0xa8;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x17;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0xff;
	__emit 0x52;
	__emit 0x18;
	__emit 0x8d;
	__emit 0x94;
	__emit 0x24;
	__emit 0x88;
	__emit 0x03;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x49;
	__emit 0x00;
	__emit 0x8a;
	__emit 0x08;
	__emit 0x40;
	__emit 0x88;
	__emit 0x0a;
	__emit 0x42;
	__emit 0x84;
	__emit 0xc9;
	__emit 0x75;
	__emit 0xf6;
	__emit 0x8d;
	__emit 0x84;
	__emit 0x24;
	__emit 0x8c;
	__emit 0x04;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x50;
	__emit 0x01;
	__emit 0x8a;
	__emit 0x08;
	__emit 0x40;
	__emit 0x84;
	__emit 0xc9;
	__emit 0x75;
	__emit 0xf9;
	__emit 0x2b;
	__emit 0xc2;
	__emit 0x50;
	__emit 0x8b;
	__emit 0x07;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0xff;
	__emit 0x50;
	__emit 0x18;
	__emit 0x50;
	__emit 0x8d;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x94;
	__emit 0x04;
	__emit 0x00;
	__emit 0x00;
	__emit 0x51;
	__emit 0xff;
	__emit 0xd5;
	__emit 0x83;
	__emit 0xc4;
	__emit 0x0c;
	__emit 0x85;
	__emit 0xc0;
	__emit 0x0f;
	__emit 0x85;
	__emit 0x90;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x54;
	__emit 0x24;
	__emit 0x18;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x1c;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x20;
	__emit 0x89;
	__emit 0x96;
	__emit 0xbc;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x54;
	__emit 0x24;
	__emit 0x24;
	__emit 0x89;
	__emit 0x86;
	__emit 0xc0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x28;
	__emit 0x89;
	__emit 0x8e;
	__emit 0xc4;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x2c;
	__emit 0x89;
	__emit 0x96;
	__emit 0xc8;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x54;
	__emit 0x24;
	__emit 0x30;
	__emit 0x89;
	__emit 0x86;
	__emit 0xcc;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x34;
	__emit 0x89;
	__emit 0x8e;
	__emit 0xd0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x38;
	__emit 0x89;
	__emit 0x96;
	__emit 0xd4;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x54;
	__emit 0x24;
	__emit 0x3c;
	__emit 0x89;
	__emit 0x86;
	__emit 0xd8;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x40;
	__emit 0x89;
	__emit 0x8e;
	__emit 0xdc;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x44;
	__emit 0x89;
	__emit 0x8e;
	__emit 0xe8;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0x96;
	__emit 0xe0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0x86;
	__emit 0xe4;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x17;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0xff;
	__emit 0x52;
	__emit 0x18;
	__emit 0x8d;
	__emit 0x94;
	__emit 0x24;
	__emit 0x8c;
	__emit 0x04;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8a;
	__emit 0x08;
	__emit 0x40;
	__emit 0x88;
	__emit 0x0a;
	__emit 0x42;
	__emit 0x84;
	__emit 0xc9;
	__emit 0x75;
	__emit 0xf6;
	__emit 0xff;
	__emit 0x4f;
	__emit 0x04;
	__emit 0x75;
	__emit 0x06;
	__emit 0x8b;
	__emit 0x07;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0xff;
	__emit 0x10;
	__emit 0x8b;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x10;
	__emit 0x8b;
	__emit 0x13;
	__emit 0x47;
	__emit 0x8b;
	__emit 0xcb;
	__emit 0x89;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x10;
	__emit 0xff;
	__emit 0x52;
	__emit 0x6c;
	__emit 0x3b;
	__emit 0xf8;
	__emit 0x0f;
	__emit 0x8c;
	__emit 0x52;
	__emit 0xfd;
	__emit 0xff;
	__emit 0xff;
	__emit 0x33;
	__emit 0xed;
	__emit 0xff;
	__emit 0x4b;
	__emit 0x04;
	__emit 0x75;
	__emit 0x06;
	__emit 0x8b;
	__emit 0x03;
	__emit 0x8b;
	__emit 0xcb;
	__emit 0xff;
	__emit 0x10;
	__emit 0x8d;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x84;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x51;
	__emit 0xe8;
	__emit 0xc8;
	__emit 0x5e;
	__emit 0x22;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x10;
	__emit 0x83;
	__emit 0xc4;
	__emit 0x04;
	__emit 0x8b;
	__emit 0xc8;
	__emit 0xff;
	__emit 0x52;
	__emit 0x14;
	__emit 0x89;
	__emit 0x46;
	__emit 0x38;
	__emit 0x8d;
	__emit 0x84;
	__emit 0x24;
	__emit 0x88;
	__emit 0x03;
	__emit 0x00;
	__emit 0x00;
	__emit 0x50;
	__emit 0xe8;
	__emit 0xae;
	__emit 0x5e;
	__emit 0x22;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x10;
	__emit 0x83;
	__emit 0xc4;
	__emit 0x04;
	__emit 0x8b;
	__emit 0xc8;
	__emit 0xff;
	__emit 0x52;
	__emit 0x14;
	__emit 0x89;
	__emit 0x46;
	__emit 0x7c;
	__emit 0x8d;
	__emit 0x84;
	__emit 0x24;
	__emit 0x8c;
	__emit 0x04;
	__emit 0x00;
	__emit 0x00;
	__emit 0x50;
	__emit 0xe8;
	__emit 0x94;
	__emit 0x5e;
	__emit 0x22;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x10;
	__emit 0x83;
	__emit 0xc4;
	__emit 0x04;
	__emit 0x8b;
	__emit 0xc8;
	__emit 0xff;
	__emit 0x52;
	__emit 0x14;
	__emit 0x8b;
	__emit 0xd8;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x54;
	__emit 0x89;
	__emit 0x46;
	__emit 0x18;
	__emit 0x8b;
	__emit 0x46;
	__emit 0x38;
	__emit 0x3b;
	__emit 0xc5;
	__emit 0x89;
	__emit 0x9e;
	__emit 0xb8;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x75;
	__emit 0x24;
	__emit 0x8b;
	__emit 0xce;
	__emit 0xe8;
	__emit 0xd3;
	__emit 0x2d;
	__emit 0x95;
	__emit 0xff;
	__emit 0x32;
	__emit 0xc0;
	__emit 0x8b;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x90;
	__emit 0x05;
	__emit 0x00;
	__emit 0x00;
	__emit 0x5f;
	__emit 0x5e;
	__emit 0x5d;
	__emit 0x64;
	__emit 0x89;
	__emit 0x0d;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x5b;
	__emit 0x81;
	__emit 0xc4;
	__emit 0x8c;
	__emit 0x05;
	__emit 0x00;
	__emit 0x00;
	__emit 0xc2;
	__emit 0x04;
	__emit 0x00;
	__emit 0x3b;
	__emit 0xdd;
	__emit 0xc7;
	__emit 0x46;
	__emit 0x20;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x74;
	__emit 0x05;
	__emit 0x39;
	__emit 0x6e;
	__emit 0x7c;
	__emit 0x75;
	__emit 0x03;
	__emit 0x89;
	__emit 0x6e;
	__emit 0x20;
	__emit 0x8b;
	__emit 0x80;
	__emit 0xc8;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x48;
	__emit 0x28;
	__emit 0x85;
	__emit 0xc9;
	__emit 0x8b;
	__emit 0x50;
	__emit 0x30;
	__emit 0x8b;
	__emit 0x52;
	__emit 0x0c;
	__emit 0xbd;
	__emit 0xff;
	__emit 0xff;
	__emit 0x7f;
	__emit 0x7f;
	__emit 0xbf;
	__emit 0xff;
	__emit 0xff;
	__emit 0x7f;
	__emit 0xff;
	__emit 0x89;
	__emit 0x6e;
	__emit 0x74;
	__emit 0x89;
	__emit 0x7e;
	__emit 0x78;
	__emit 0x89;
	__emit 0x6e;
	__emit 0x6c;
	__emit 0x89;
	__emit 0x7e;
	__emit 0x70;
	__emit 0x0f;
	__emit 0x8e;
	__emit 0xaa;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x44;
	__emit 0x24;
	__emit 0x58;
	__emit 0x3b;
	__emit 0xc2;
	__emit 0x75;
	__emit 0x1a;
	__emit 0x8b;
	__emit 0x02;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x48;
	__emit 0x8b;
	__emit 0x42;
	__emit 0x04;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x4c;
	__emit 0x8b;
	__emit 0x42;
	__emit 0x08;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x50;
	__emit 0x8d;
	__emit 0x44;
	__emit 0x24;
	__emit 0x48;
	__emit 0xeb;
	__emit 0x02;
	__emit 0x8b;
	__emit 0xc2;
	__emit 0xd9;
	__emit 0x46;
	__emit 0x44;
	__emit 0xd8;
	__emit 0x48;
	__emit 0x08;
	__emit 0xd9;
	__emit 0x46;
	__emit 0x40;
	__emit 0xd8;
	__emit 0x48;
	__emit 0x04;
	__emit 0xde;
	__emit 0xc1;
	__emit 0xd9;
	__emit 0x00;
	__emit 0xd8;
	__emit 0x4e;
	__emit 0x3c;
	__emit 0xde;
	__emit 0xc1;
	__emit 0xd8;
	__emit 0x46;
	__emit 0x48;
	__emit 0xd9;
	__emit 0x46;
	__emit 0x54;
	__emit 0xd8;
	__emit 0x48;
	__emit 0x08;
	__emit 0xd9;
	__emit 0x46;
	__emit 0x4c;
	__emit 0xd8;
	__emit 0x08;
	__emit 0xde;
	__emit 0xc1;
	__emit 0xd9;
	__emit 0x46;
	__emit 0x50;
	__emit 0xd8;
	__emit 0x48;
	__emit 0x04;
	__emit 0xde;
	__emit 0xc1;
	__emit 0xd8;
	__emit 0x46;
	__emit 0x58;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x5c;
	__emit 0xd8;
	__emit 0x56;
	__emit 0x74;
	__emit 0xdf;
	__emit 0xe0;
	__emit 0xf6;
	__emit 0xc4;
	__emit 0x05;
	__emit 0x7a;
	__emit 0x03;
	__emit 0xd9;
	__emit 0x56;
	__emit 0x74;
	__emit 0xd9;
	__emit 0x46;
	__emit 0x6c;
	__emit 0xd8;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x5c;
	__emit 0xdf;
	__emit 0xe0;
	__emit 0xf6;
	__emit 0xc4;
	__emit 0x41;
	__emit 0x75;
	__emit 0x07;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x5c;
	__emit 0x89;
	__emit 0x46;
	__emit 0x6c;
	__emit 0xd8;
	__emit 0x56;
	__emit 0x78;
	__emit 0xdf;
	__emit 0xe0;
	__emit 0xf6;
	__emit 0xc4;
	__emit 0x41;
	__emit 0x75;
	__emit 0x05;
	__emit 0xd9;
	__emit 0x5e;
	__emit 0x78;
	__emit 0xeb;
	__emit 0x02;
	__emit 0xdd;
	__emit 0xd8;
	__emit 0xd9;
	__emit 0x44;
	__emit 0x24;
	__emit 0x5c;
	__emit 0xd8;
	__emit 0x5e;
	__emit 0x70;
	__emit 0xdf;
	__emit 0xe0;
	__emit 0xf6;
	__emit 0xc4;
	__emit 0x41;
	__emit 0x75;
	__emit 0x07;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x5c;
	__emit 0x89;
	__emit 0x46;
	__emit 0x70;
	__emit 0x83;
	__emit 0xc2;
	__emit 0x0c;
	__emit 0x49;
	__emit 0x0f;
	__emit 0x85;
	__emit 0x56;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0x83;
	__emit 0x7e;
	__emit 0x20;
	__emit 0x01;
	__emit 0x0f;
	__emit 0x85;
	__emit 0x46;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x4e;
	__emit 0x7c;
	__emit 0x8b;
	__emit 0x81;
	__emit 0xc8;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x50;
	__emit 0x28;
	__emit 0x85;
	__emit 0xd2;
	__emit 0x8b;
	__emit 0x40;
	__emit 0x30;
	__emit 0x8b;
	__emit 0x48;
	__emit 0x0c;
	__emit 0x89;
	__emit 0xae;
	__emit 0xb0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0xbe;
	__emit 0xb4;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x0f;
	__emit 0x8e;
	__emit 0x7e;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x9b;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x44;
	__emit 0x24;
	__emit 0x58;
	__emit 0x3b;
	__emit 0xc1;
	__emit 0x75;
	__emit 0x1a;
	__emit 0x8b;
	__emit 0x01;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x48;
	__emit 0x8b;
	__emit 0x41;
	__emit 0x04;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x4c;
	__emit 0x8b;
	__emit 0x41;
	__emit 0x08;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x50;
	__emit 0x8d;
	__emit 0x44;
	__emit 0x24;
	__emit 0x48;
	__emit 0xeb;
	__emit 0x02;
	__emit 0x8b;
	__emit 0xc1;
	__emit 0xd9;
	__emit 0x40;
	__emit 0x08;
	__emit 0xd8;
	__emit 0x8e;
	__emit 0x88;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xd9;
	__emit 0x40;
	__emit 0x04;
	__emit 0xd8;
	__emit 0x8e;
	__emit 0x84;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xde;
	__emit 0xc1;
	__emit 0xd9;
	__emit 0x86;
	__emit 0x80;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xd8;
	__emit 0x08;
	__emit 0xde;
	__emit 0xc1;
	__emit 0xd8;
	__emit 0x86;
	__emit 0x8c;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xd8;
	__emit 0x96;
	__emit 0xb0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xdf;
	__emit 0xe0;
	__emit 0xf6;
	__emit 0xc4;
	__emit 0x05;
	__emit 0x7a;
	__emit 0x06;
	__emit 0xd9;
	__emit 0x96;
	__emit 0xb0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xd8;
	__emit 0x96;
	__emit 0xb4;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xdf;
	__emit 0xe0;
	__emit 0xf6;
	__emit 0xc4;
	__emit 0x41;
	__emit 0x75;
	__emit 0x08;
	__emit 0xd9;
	__emit 0x9e;
	__emit 0xb4;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xeb;
	__emit 0x02;
	__emit 0xdd;
	__emit 0xd8;
	__emit 0x83;
	__emit 0xc1;
	__emit 0x0c;
	__emit 0x4a;
	__emit 0x75;
	__emit 0x88;
	__emit 0x8b;
	__emit 0x83;
	__emit 0xc8;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x50;
	__emit 0x28;
	__emit 0x85;
	__emit 0xd2;
	__emit 0x8b;
	__emit 0x48;
	__emit 0x30;
	__emit 0x8b;
	__emit 0x49;
	__emit 0x0c;
	__emit 0x89;
	__emit 0xae;
	__emit 0xec;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0xbe;
	__emit 0xf0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x0f;
	__emit 0x8e;
	__emit 0x9e;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xeb;
	__emit 0x03;
	__emit 0x8d;
	__emit 0x49;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x44;
	__emit 0x24;
	__emit 0x58;
	__emit 0x3b;
	__emit 0xc1;
	__emit 0x75;
	__emit 0x1a;
	__emit 0x8b;
	__emit 0x01;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x48;
	__emit 0x8b;
	__emit 0x41;
	__emit 0x04;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x4c;
	__emit 0x8b;
	__emit 0x41;
	__emit 0x08;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x50;
	__emit 0x8d;
	__emit 0x44;
	__emit 0x24;
	__emit 0x48;
	__emit 0xeb;
	__emit 0x02;
	__emit 0x8b;
	__emit 0xc1;
	__emit 0xd9;
	__emit 0x40;
	__emit 0x08;
	__emit 0xd8;
	__emit 0x8e;
	__emit 0xc4;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xd9;
	__emit 0x40;
	__emit 0x04;
	__emit 0xd8;
	__emit 0x8e;
	__emit 0xc0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xde;
	__emit 0xc1;
	__emit 0xd9;
	__emit 0x86;
	__emit 0xbc;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xd8;
	__emit 0x08;
	__emit 0xde;
	__emit 0xc1;
	__emit 0xd8;
	__emit 0x86;
	__emit 0xc8;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xd8;
	__emit 0x96;
	__emit 0xec;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xdf;
	__emit 0xe0;
	__emit 0xf6;
	__emit 0xc4;
	__emit 0x05;
	__emit 0x7a;
	__emit 0x06;
	__emit 0xd9;
	__emit 0x96;
	__emit 0xec;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xd8;
	__emit 0x96;
	__emit 0xf0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xdf;
	__emit 0xe0;
	__emit 0xf6;
	__emit 0xc4;
	__emit 0x41;
	__emit 0x75;
	__emit 0x08;
	__emit 0xd9;
	__emit 0x9e;
	__emit 0xf0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xeb;
	__emit 0x02;
	__emit 0xdd;
	__emit 0xd8;
	__emit 0x83;
	__emit 0xc1;
	__emit 0x0c;
	__emit 0x4a;
	__emit 0x75;
	__emit 0x88;
	__emit 0xeb;
	__emit 0x1f;
	__emit 0x8b;
	__emit 0x4e;
	__emit 0x78;
	__emit 0x8b;
	__emit 0xd1;
	__emit 0x8b;
	__emit 0xc1;
	__emit 0x89;
	__emit 0x8e;
	__emit 0xb0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0x96;
	__emit 0xb4;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0x86;
	__emit 0xec;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0x8e;
	__emit 0xf0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xd9;
	__emit 0x86;
	__emit 0xf0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xd8;
	__emit 0x66;
	__emit 0x74;
	__emit 0xd8;
	__emit 0x15;
	__emit 0x34;
	__emit 0x53;
	__emit 0x07;
	__emit 0x01;
	__emit 0xdf;
	__emit 0xe0;
	__emit 0xf6;
	__emit 0xc4;
	__emit 0x05;
	__emit 0x7a;
	__emit 0x08;
	__emit 0xdd;
	__emit 0xd8;
	__emit 0xd9;
	__emit 0x05;
	__emit 0x34;
	__emit 0x53;
	__emit 0x07;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x46;
	__emit 0x20;
	__emit 0xd9;
	__emit 0x56;
	__emit 0x1c;
	__emit 0x83;
	__emit 0xf8;
	__emit 0x01;
	__emit 0x75;
	__emit 0x46;
	__emit 0xd8;
	__emit 0x0d;
	__emit 0x70;
	__emit 0xa6;
	__emit 0x0b;
	__emit 0x01;
	__emit 0xd9;
	__emit 0xc0;
	__emit 0xd8;
	__emit 0x86;
	__emit 0xb0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xd8;
	__emit 0x5e;
	__emit 0x78;
	__emit 0xdf;
	__emit 0xe0;
	__emit 0xf6;
	__emit 0xc4;
	__emit 0x05;
	__emit 0x7a;
	__emit 0x07;
	__emit 0xc7;
	__emit 0x46;
	__emit 0x20;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xd9;
	__emit 0x86;
	__emit 0xb4;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xd8;
	__emit 0xe1;
	__emit 0xd9;
	__emit 0x86;
	__emit 0xec;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xde;
	__emit 0xd9;
	__emit 0xdf;
	__emit 0xe0;
	__emit 0xdd;
	__emit 0xd8;
	__emit 0xf6;
	__emit 0xc4;
	__emit 0x05;
	__emit 0x7a;
	__emit 0x10;
	__emit 0xc7;
	__emit 0x46;
	__emit 0x20;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xb0;
	__emit 0x01;
	__emit 0xe9;
	__emit 0x1d;
	__emit 0xfd;
	__emit 0xff;
	__emit 0xff;
	__emit 0xdd;
	__emit 0xd8;
	__emit 0xb0;
	__emit 0x01;
	__emit 0xe9;
	__emit 0x14;
	__emit 0xfd;
	__emit 0xff;
	__emit 0xff;
	__emit 0x8d;
	__emit 0x49;
	__emit 0x00;
	__emit 0x4d;
	__emit 0x8d;
	__emit 0xad;
	__emit 0x00;
	__emit 0xb4;
	__emit 0x8d;
	__emit 0xad;
	__emit 0x00;
	__emit 0x19;
	__emit 0x8e;
	__emit 0xad;
	__emit 0x00;
	__emit 0x81;
	__emit 0x8e;
	__emit 0xad;
	__emit 0x00;
	}
#if 0
	REF_PTR_RELEASE(m_bridgeTexture);
	REF_PTR_RELEASE(m_leftMesh);
	REF_PTR_RELEASE(m_sectionMesh);
	REF_PTR_RELEASE(m_rightMesh);

	Real scale, width, length;
	char textureFile[_MAX_PATH] = "No Texture";
	char modelName[_MAX_PATH] = "BRIDGESECTIONAL";

	/// @todo, should these be defaults in INI??? CBD
	scale = 0.7f;
	width = 34;
	length = 170;

	// try to find bridge in INI
	TerrainRoadType *bridge = TheTerrainRoads->findBridge( m_templateName );
	if (!bridge) return false;

	scale = bridge->getBridgeScale();
	switch (curDamageState) {
		default: return false;

		case 	BODY_PRISTINE:
			strcpy( textureFile, bridge->getTexture().str() );
			strcpy( modelName, bridge->getBridgeModel().str() );
			break;
		case BODY_DAMAGED:
			strcpy( textureFile, bridge->getTextureDamaged().str() );
			strcpy( modelName, bridge->getBridgeModelNameDamaged().str() );
			break;
		case BODY_REALLYDAMAGED:
			strcpy( textureFile, bridge->getTextureReallyDamaged().str() );
			strcpy( modelName, bridge->getBridgeModelNameReallyDamaged().str() );
			break;
		case BODY_RUBBLE:
			strcpy( textureFile, bridge->getTextureBroken().str() );
			strcpy( modelName, bridge->getBridgeModelNameBroken().str() );
			break;
	}

	WW3DAssetManager *pMgr = W3DAssetManager::Get_Instance();
	char left[_MAX_PATH];
	char section[_MAX_PATH];
	char right[_MAX_PATH];

	strcpy(left, modelName);
	strcat(left, ".BRIDGE_LEFT");
	strcpy(section, modelName);
	strcat(section, ".BRIDGE_SPAN");
	strcpy(right, modelName);
	strcat(right, ".BRIDGE_RIGHT");

	m_bridgeTexture = pMgr->Get_Texture(textureFile,  MIP_LEVELS_3); 
	m_leftMtx.Make_Identity();
	m_rightMtx.Make_Identity();
	m_sectionMtx.Make_Identity();

	RenderObjClass *pObj = pMgr->Create_Render_Obj(modelName );
	if (!pObj) return false;
	Int i;
	for (i=0; i<pObj->Get_Num_Sub_Objects(); i++) {
		RenderObjClass *pSub = pObj->Get_Sub_Object(i);
		Matrix3D mtx = pSub->Get_Transform();
		if (0==strnicmp(left, pSub->Get_Name(), strlen(left))) {
			m_leftMtx = mtx;
			strcpy(left, pSub->Get_Name());
		}
		if (0==strnicmp(section, pSub->Get_Name(), strlen(section))) {
			m_sectionMtx = mtx;
			strcpy(section, pSub->Get_Name());
		}
		if (0==strnicmp(right, pSub->Get_Name(), strlen(right))) {
			m_rightMtx = mtx;
			strcpy(right, pSub->Get_Name());
		}
		REF_PTR_RELEASE(pSub);
		//DEBUG_LOG(("Sub obj name %s\n", pSub->Get_Name()));
	}

	REF_PTR_RELEASE(pObj);

	m_leftMesh = (MeshClass*)pMgr->Create_Render_Obj(left );
	m_sectionMesh = (MeshClass*)pMgr->Create_Render_Obj(section);
	m_rightMesh = (MeshClass*)pMgr->Create_Render_Obj(right);
	m_scale = scale;


	if (m_leftMesh == NULL) {
		clearBridge();
		return(false);
	}
	m_bridgeType = SECTIONAL_BRIDGE;

	if (m_rightMesh == NULL || m_sectionMesh == NULL) {
		m_bridgeType = FIXED_BRIDGE;
	}

	Int numVertex = m_leftMesh->Peek_Model()->Get_Vertex_Count();
	Vector3 *pVert = m_leftMesh->Peek_Model()->Get_Vertex_Array();
	m_leftMinX = FLT_MAX;
	m_leftMaxX = -FLT_MAX;
	m_minY = FLT_MAX;
	m_maxY = -FLT_MAX;
	for (i=0; i<numVertex; i++) {
		Vector3 vert;
		Matrix3D::Transform_Vector(m_leftMtx, pVert[i], &vert);
		if (m_leftMinX > vert.X) m_leftMinX = vert.X;
		if (m_minY > vert.Y) m_minY = vert.Y;
		if (vert.X > m_leftMaxX) m_leftMaxX = vert.X;
		if (vert.Y > m_maxY) m_maxY = vert.Y;	 // Note - we assume all sections are the same width, so we only do maxY for first section.
	}
	if (m_bridgeType == SECTIONAL_BRIDGE) {
		numVertex = m_sectionMesh->Peek_Model()->Get_Vertex_Count();
		pVert = m_sectionMesh->Peek_Model()->Get_Vertex_Array();
		m_sectionMinX = FLT_MAX;
		m_sectionMaxX = -FLT_MAX;
		for (i=0; i<numVertex; i++) {
			Vector3 vert;
			Matrix3D::Transform_Vector(m_sectionMtx, pVert[i], &vert);
			if (m_sectionMinX > vert.X) m_sectionMinX = vert.X;
			if (vert.X > m_sectionMaxX) m_sectionMaxX = vert.X;
		}

		numVertex = m_rightMesh->Peek_Model()->Get_Vertex_Count();
		pVert = m_rightMesh->Peek_Model()->Get_Vertex_Array();
		m_rightMinX = FLT_MAX;
		m_rightMaxX = -FLT_MAX;
		for (i=0; i<numVertex; i++) {
			Vector3 vert;
			Matrix3D::Transform_Vector(m_rightMtx, pVert[i], &vert);
			if (m_rightMinX > vert.X) m_rightMinX = vert.X;
			if (vert.X > m_rightMaxX) m_rightMaxX = vert.X;
		}
	} else {
		m_sectionMinX = m_leftMaxX;
		m_sectionMaxX = m_leftMaxX;
		m_rightMinX = m_leftMaxX;
		m_rightMaxX = m_leftMaxX;
	}
	length = m_rightMaxX - m_leftMinX;
	if (length < 1) length = 1;
	m_length = length;
	if (m_bridgeType == SECTIONAL_BRIDGE) {
		Real allowableError = 0.05f*length;
		// make sure the sections align.

		if (m_leftMaxX>m_sectionMinX+allowableError) {
			m_bridgeType = FIXED_BRIDGE;
		}

		if (m_rightMinX<m_sectionMaxX-allowableError) {
			m_bridgeType = FIXED_BRIDGE;
		}

	}
	return(true);
#endif
}


//=============================================================================
// W3DBridge::getBridgeInfo
//=============================================================================
/** Gets the location info for the bridge.  */
//=============================================================================
void W3DBridge::getBridgeInfo(BridgeInfo *pInfo)
{

	pInfo->from.x = m_start.X;
	pInfo->from.y = m_start.Y;
	pInfo->from.z = m_start.Z;
	pInfo->to.x = m_end.X;
	pInfo->to.y = m_end.Y;
	pInfo->to.z = m_end.Z;
	pInfo->bridgeWidth = (m_maxY - m_minY) *m_scale;

	Vector3 vec = 	m_end-m_start;
	Vector3 vecNormal(-vec.Y, vec.X, 0);
	vecNormal.Normalize();

	// From left = from + vecNormal*maxY*scale
	pInfo->fromLeft.x = m_start.X + vecNormal.X * m_maxY * m_scale;
	pInfo->fromLeft.y = m_start.Y + vecNormal.Y * m_maxY * m_scale;
	pInfo->fromLeft.z = m_start.Z + vecNormal.Z * m_maxY * m_scale;

	// From right = from + vecNormal*minY*scale
	pInfo->fromRight.x = m_start.X + vecNormal.X * m_minY * m_scale;
	pInfo->fromRight.y = m_start.Y + vecNormal.Y * m_minY * m_scale;
	pInfo->fromRight.z = m_start.Z + vecNormal.Z * m_minY * m_scale;

	// to left = to + vecNormal*maxY*scale
	pInfo->toLeft.x = m_end.X + vecNormal.X * m_maxY * m_scale;
	pInfo->toLeft.y = m_end.Y + vecNormal.Y * m_maxY * m_scale;
	pInfo->toLeft.z = m_end.Z + vecNormal.Z * m_maxY * m_scale;

	// to right = to + vecNormal*minY*scale
	pInfo->toRight.x = m_end.X + vecNormal.X * m_minY * m_scale;
	pInfo->toRight.y = m_end.Y + vecNormal.Y * m_minY * m_scale;
	pInfo->toRight.z = m_end.Z + vecNormal.Z * m_minY * m_scale;

}



//=============================================================================
// W3DBridge::getModelVertices
//=============================================================================
/** Gets the vertex values for a section of a bridge.  */
//=============================================================================
// byte-exact reconstruction: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DBridgeGetModelVerticesThunk.cpp
// ?getModelVertices@W3DBridge@@IAEHPAUVertexFormatXYZNDUV1@@HMAAVVector3@@111ABVMatrix3D@@PAVMeshClass@@PAV?$RefMultiListIterator@VRenderObjClass@@@@@Z present-unmatched
Int W3DBridge::getModelVertices(VertexFormatXYZNDUV1 *destination_vb, Int curVertex, Real xOffset,
																Vector3 &vec, Vector3 &vecNormal, Vector3 &vecZ, Vector3 &offset, 
																const Matrix3D &mtx, 
																MeshClass *pMesh, RefRenderObjListIterator *pLightsIterator)
{
	if (pMesh == NULL) 
		return(0);

	Int i;
	Int numVertex = pMesh->Peek_Model()->Get_Vertex_Count();
	Vector3 *pVert = pMesh->Peek_Model()->Get_Vertex_Array();

	const Vector3 *pNormal = 	pMesh->Peek_Model()->Get_Vertex_Normal_Array();

	// If we happen to have too many bridges, stop.
	if (curVertex+numVertex+2>= W3DBridgeBuffer::MAX_BRIDGE_VERTEX) {
		return(0);
	}

	Vector3 lightRay[MAX_GLOBAL_LIGHTS];
	const Coord3D *lightPos;

	for (Int lightIndex=0; lightIndex < TheGlobalData->m_numGlobalLights; lightIndex++)
	{
		lightPos=&TheGlobalData->m_terrainLightPos[lightIndex];
		lightRay[lightIndex].Set(-lightPos->x,-lightPos->y,	-lightPos->z);
//		__asm {int 3}; //see if it really needs normalization!!
		lightRay[lightIndex].Normalize();
	}

	const Vector2*uvs=pMesh->Peek_Model()->Get_UV_Array_By_Index(0);
	VertexFormatXYZNDUV1 *curVb = destination_vb+curVertex;

	for (i=0; i<numVertex; i++) {
		Vector3 vLoc;
		Vector3 vertex;
		Matrix3D::Transform_Vector(mtx, pVert[i], &vertex);
		vLoc = (vertex.X+xOffset) * vec + vertex.Y*vecNormal + vertex.Z*vecZ;

		vLoc.X += m_start.X;
		vLoc.Y += m_start.Y;
		vLoc.Z += m_start.Z; 

		curVb->x = vLoc.X;
		curVb->y = vLoc.Y;
		curVb->z = vLoc.Z;
		
		VERTEX_FORMAT vb;
		vb.x = vLoc.X;
		vb.y = vLoc.Y;
		vb.z = vLoc.Z;

		Vector3 normal;
		Matrix3D::Rotate_Vector(mtx, pNormal[i], &normal);
#ifdef USE_BRIDGE_NORMALS
		curVb->nx = normal.X;
		curVb->ny = normal.Y;
		curVb->nz = normal.Z;
		curVb->diffuse = 0xFF000000;
#else
		normal = (normal.X) * vec + normal.Y*vecNormal + normal.Z*vecZ;
		normal.Normalize();	
		TheTerrainRenderObject->doTheLight(&vb, lightRay, &normal, NULL, 1.0f);
		curVb->nx = 0;	//will these to keep AGP write buffer happy.
		curVb->ny = 0;
		curVb->nz = 1;
		curVb->diffuse = vb.diffuse | 0xFF000000;
#endif
		curVb->u1 = uvs[i].U;
		curVb->v1 = uvs[i].V;
		curVb++;
	}
	return(numVertex);
}

//=============================================================================
// W3DBridge::getModelVerticesFixed
//=============================================================================
/** Gets the vertex values for a section of a fixed bridge.  */
//=============================================================================
Int W3DBridge::getModelVerticesFixed(VertexFormatXYZNDUV1 *destination_vb, Int curVertex, 
																const Matrix3D &mtx, MeshClass *pMesh, RefRenderObjListIterator *pLightsIterator)
{
	if (pMesh == NULL) 
		return(0);

	Vector3 vec = m_end - m_start;
	if (vec.Length2() < 1.0f) {
		vec.Normalize();
	}
	Vector3 vecNormal(-vec.Y, vec.X, 0);
	vecNormal.Normalize();
	Real deltaZ = m_end.Z - m_start.Z;
	deltaZ /= vec.Length();
	Real deltaX = sqrt(1.0 - deltaZ*deltaZ);
	Vector3 vecZ(-deltaZ, 0, deltaX);
	vec /= m_length;
	vecNormal *= m_scale;
	vecZ *= m_scale;
	Real xOffset = -m_leftMinX;
	return(getModelVertices(destination_vb, curVertex, xOffset, vec, vecNormal, vecZ, m_start, mtx, pMesh, pLightsIterator));
}

//=============================================================================
// W3DBridge::getIndicesNVertices
//=============================================================================
/** Gets the index values and vertex values for a bridge.  */
//=============================================================================
// BFME matches Generals body (no ZH overflow early-returns); floor via CRT not WWLib fast_float_floor.
void W3DBridge::getIndicesNVertices(UnsignedShort *destination_ib, VertexFormatXYZNDUV1 *destination_vb, 
																		Int *curIndexP, Int *curVertexP, RefRenderObjListIterator *pLightsIterator)
{
	Int numI;
	Int numV;
	m_firstVertex = *curVertexP;
	m_firstIndex = *curIndexP;
	m_numVertex = 0;
	m_numPolygons = 0;
	if (m_sectionMesh == NULL) {
		numV = getModelVerticesFixed(destination_vb, *curVertexP, m_leftMtx, m_leftMesh, pLightsIterator);
		numI = getModelIndices( destination_ib, *curIndexP, *curVertexP, m_leftMesh);
		*curIndexP += numI;
		*curVertexP += numV;
		m_numVertex += numV;
		m_numPolygons += numI/3;
		return;
	}

	Vector3 vec = m_end - m_start;
	if (vec.Length2() < 1.0f) {
		vec.Normalize();
	}

	Vector3 vecNormal(-vec.Y, vec.X, 0);
	vecNormal.Normalize();
	vecNormal *= m_scale;

	// Rotate along the y axis to get the appropriate Z height adjustment.
	Real deltaZ = m_end.Z - m_start.Z;
	Real desiredLength = vec.Length();
	deltaZ /= desiredLength;
	Real deltaX = sqrt(1.0 - deltaZ*deltaZ);
	Vector3 vecZ(-deltaZ, 0, deltaX);
	vecZ *= m_scale;

	Real spanLength = m_rightMinX - m_leftMaxX; 
	Int numSpans = 1;
	if (m_bridgeType != FIXED_BRIDGE) {
		Real spannable = desiredLength - (m_length-spanLength);
		numSpans = fast_float2long_round(floorf( (spannable + spanLength/2)/spanLength));
		if (numSpans<0) numSpans = 0;
	}

	Real bridgeLength = m_length + (numSpans-1)*spanLength;
	Real xOffset = -m_leftMinX;
	
	// Draw the left end.
	vec /= bridgeLength;
	numV = getModelVertices(destination_vb, *curVertexP, xOffset, vec, vecNormal, vecZ, m_start, 
		m_leftMtx, m_leftMesh, pLightsIterator);
	numI = getModelIndices( destination_ib, *curIndexP, *curVertexP, m_leftMesh);
	*curIndexP += numI;
	*curVertexP += numV;
	m_numVertex += numV;
	m_numPolygons += numI/3;

	Int i;
	// draw the spans.
	for (i=0; i<numSpans; i++) {
		numV = getModelVertices(destination_vb, *curVertexP, xOffset+i*spanLength, vec, vecNormal, vecZ, m_start, 
			m_sectionMtx, m_sectionMesh, pLightsIterator);
		numI = getModelIndices( destination_ib, *curIndexP, *curVertexP, m_sectionMesh);
		*curIndexP += numI;
		*curVertexP += numV;
		m_numVertex += numV;
		m_numPolygons += numI/3;
	}
		
	// Draw the right end.
	numV = getModelVertices(destination_vb, *curVertexP, xOffset+(numSpans-1)*spanLength, vec, vecNormal, vecZ, m_start,
		m_rightMtx, m_rightMesh, pLightsIterator);
	numI = getModelIndices( destination_ib, *curIndexP, *curVertexP, m_rightMesh);
	*curIndexP += numI;
	*curVertexP += numV;
	m_numVertex += numV;
	m_numPolygons += numI/3;
	return;
}

//=============================================================================
// W3DBridge::getModelIndices
//=============================================================================
/** Gets the index values for a particular mesh section of the bridge.  */
//=============================================================================
Int W3DBridge::getModelIndices(UnsignedShort *destination_ib, Int curIndex, Int vertexOffset, MeshClass *pMesh)
{
	if (pMesh == NULL) 
		return(0);
	Int numPoly = pMesh->Peek_Model()->Get_Polygon_Count();
	const TriIndex *pPoly =pMesh->Peek_Model()->Get_Polygon_Array();
	const Int maxBridgeIndex = 16000;
	if (curIndex+3*numPoly+6 >= maxBridgeIndex) {
		return(0);
	}
	UnsignedShort *curIb = destination_ib+curIndex;
	Int i;
	for (i=0; i<numPoly; i++) {
		*curIb++ = vertexOffset + pPoly[i].I;
		*curIb++ = vertexOffset + pPoly[i].J;
		*curIb++ = vertexOffset + pPoly[i].K;
	}
	return(numPoly*3);
}

//-----------------------------------------------------------------------------
//         Private Functions                                               
//-----------------------------------------------------------------------------

///@todo - Sort bridges by texture for better performance.

//=============================================================================
// W3DBridgeBuffer::cull
//=============================================================================
/** Culls the bridges, marking the visible flag.  If a bridge changes visibility, it sets
m_anythingChanged */
//=============================================================================
void W3DBridgeBuffer::cull(CameraClass * camera)
{
	Int curBridge;

	m_anythingChanged = m_updateVis;

	for (curBridge=0; curBridge<m_numBridges; curBridge++) {
		if (m_bridges[curBridge].cullBridge(camera)) {
			m_anythingChanged = true;
		}
	}
}


//=============================================================================
// W3DBridgeBuffer::loadBridgesInVertexAndIndexBuffers
//=============================================================================
/** Loads the bridges into the vertex buffer for drawing. */
//=============================================================================
// byte-exact reconstruction: Code/GameEngineDevice/Source/W3DDevice/W3DScene/W3DBridgeBufferLoadThunk.cpp
// ?loadBridgesInVertexAndIndexBuffers@W3DBridgeBuffer@@IAEXPAV?$RefMultiListIterator@VRenderObjClass@@@@@Z present-unmatched
void W3DBridgeBuffer::loadBridgesInVertexAndIndexBuffers(RefRenderObjListIterator *pLightsIterator)
{
	if (!m_indexBridge || !m_vertexBridge || !m_initialized) {
		return;
	}
	m_curNumBridgeVertices = 0;
	m_curNumBridgeIndices = 0;
	VertexFormatXYZNDUV1 *vb;
	UnsignedShort *ib;
	// Lock the buffers.
	DX8IndexBufferClass::WriteLockClass lockIdxBuffer(m_indexBridge, D3DLOCK_DISCARD);
	DX8VertexBufferClass::WriteLockClass lockVtxBuffer(m_vertexBridge, D3DLOCK_DISCARD);
	vb=(VertexFormatXYZNDUV1*)lockVtxBuffer.Get_Vertex_Array();
	ib = lockIdxBuffer.Get_Index_Array();

//	UnsignedShort *curIb = ib;

//	VertexFormatXYZNDUV1 *curVb = vb;

	Int curBridge;

	try {
	for (curBridge=0; curBridge<m_numBridges; curBridge++) {
		m_bridges[curBridge].getIndicesNVertices(ib, vb, &m_curNumBridgeIndices, 
			&m_curNumBridgeVertices, pLightsIterator);
	}
	IndexBufferExceptionFunc();
	} catch(...) {
		IndexBufferExceptionFunc();
	}
}

//-----------------------------------------------------------------------------
//         Public Functions                                                
//-----------------------------------------------------------------------------

//=============================================================================
// W3DBridgeBuffer::~W3DBridgeBuffer
//=============================================================================
/** Destructor. Releases w3d assets. */
//=============================================================================
// ??1W3DBridgeBuffer@@QAE@XZ present-unmatched
W3DBridgeBuffer::~W3DBridgeBuffer(void)
{
	freeBridgeBuffers();
}

// The exact retail constructor is emitted by W3DBridgeBufferCtorThunk.cpp.


//=============================================================================
// W3DBridgeBuffer::freeBridgeBuffers
//=============================================================================
/** Frees the index and vertex buffers. */
//=============================================================================
void W3DBridgeBuffer::freeBridgeBuffers(void)
{
	if (m_vertexBridge) {
		m_vertexBridge->Release_Ref();
		m_vertexBridge = NULL;
	}
	if (m_indexBridge) {
		m_indexBridge->Release_Ref();
		m_indexBridge = NULL;
	}
	if (m_vertexMaterial) {
		m_vertexMaterial->Release_Ref();
		m_vertexMaterial = NULL;
	}
}

//=============================================================================
// W3DBridgeBuffer::clearAllBridges
//=============================================================================
/** Removes all bridges. */
//=============================================================================
// ?clearAllBridges@W3DBridgeBuffer@@QAEXXZ present-unmatched
void W3DBridgeBuffer::clearAllBridges(void)
{
	Int curBridge;
	for (curBridge=0; curBridge<m_numBridges; curBridge++) {
		m_bridges[curBridge].clearBridge();
	}
	m_curNumBridgeIndices = 0;
	m_numBridges=0;
}

//=============================================================================
// W3DBridgeBuffer::loadBridges
//=============================================================================
/** loadBridges.  When loaded, tell the terrain logic where the bridge is. */
//=============================================================================
// ?loadBridges@W3DBridgeBuffer@@QAEXPAVW3DTerrainLogic@@_N@Z present-unmatched
void W3DBridgeBuffer::loadBridges(W3DTerrainLogic *pTerrainLogic, Bool saveGame)
{
	clearAllBridges();
	MapObject *pMapObj;
	MapObject *pMapObj2;
	for (pMapObj = MapObject::getFirstMapObject(); pMapObj; pMapObj = pMapObj->getNext()) {
		if (pMapObj->getFlag(FLAG_BRIDGE_POINT1)) {
			pMapObj2 = pMapObj->getNext();
			if ( !pMapObj2 || !pMapObj2->getFlag(FLAG_BRIDGE_POINT2)) {
				DEBUG_LOG(("Missing second bridge point.  Ignoring first.\n"));
			}
			if (pMapObj2==NULL) break;
			if (!pMapObj2->getFlag(FLAG_BRIDGE_POINT2)) continue;
			Vector3 from, to;
			from.Set(pMapObj->getLocation()->x, pMapObj->getLocation()->y, 0);
			from.Z = TheTerrainRenderObject->getHeightMapHeight(from.X, from.Y, NULL) + BRIDGE_FLOAT_AMT;
			to.Set(pMapObj2->getLocation()->x, pMapObj2->getLocation()->y, 0);
			to.Z = TheTerrainRenderObject->getHeightMapHeight(to.X, to.Y, NULL) + BRIDGE_FLOAT_AMT;
			addBridge(from, to, pMapObj->getName(), pTerrainLogic, pMapObj->getProperties());
			pMapObj = pMapObj2;
		} 
	}
	if (pTerrainLogic) {
		pTerrainLogic->updateBridgeDamageStates();
	}
}

//=============================================================================
//=============================================================================
static RenderObjClass* createTower( SimpleSceneClass *scene,
																		W3DAssetManager *assetManager,
																		MapObject *mapObject, 
																	  BridgeTowerType type, 
																	  BridgeInfo *bridgeInfo )
{
	RenderObjClass* tower = NULL;

	// sanity
	if( scene == NULL ||
			assetManager == NULL || 
			mapObject == NULL || 
			bridgeInfo == NULL || 
			type < 0 || type >= BRIDGE_MAX_TOWERS )
		return NULL;

	// get template for this bridge
	DEBUG_ASSERTCRASH( TheTerrainRoads, ("createTower: TheTerrainRoads is NULL\n") );
	TerrainRoadType *bridgeTemplate = TheTerrainRoads->findBridge( mapObject->getName() );
	if( bridgeTemplate == NULL )
		return NULL;

	// given the type of tower (corner position) find the appropriate spot to put the tower
	Coord3D towerPos;
	switch( type )
	{

		case BRIDGE_TOWER_FROM_LEFT:	towerPos = bridgeInfo->fromLeft;		break;
		case BRIDGE_TOWER_FROM_RIGHT: towerPos = bridgeInfo->fromRight;		break;
		case BRIDGE_TOWER_TO_LEFT:		towerPos = bridgeInfo->toLeft;			break;
		case BRIDGE_TOWER_TO_RIGHT:		towerPos = bridgeInfo->toRight;			break;
		default: return NULL;

	}  // end switch

	// set the Z position to that of the terrain
	towerPos.z = TheTerrainRenderObject->getHeightMapHeight( towerPos.x, towerPos.y, NULL);

	// find the thing template for the tower we want to construct
	AsciiString towerTemplateName = bridgeTemplate->getTowerObjectName( type );
	DEBUG_ASSERTCRASH( TheThingFactory, ("createTower: TheThingFactory is NULL\n") );
	const ThingTemplate *towerTemplate = TheThingFactory->findTemplate( towerTemplateName );
	if( towerTemplate == NULL )
		return NULL;
		
	// find the name of the render object to show	
	const ModuleInfo& mi = towerTemplate->getDrawModuleInfo( );
	if( mi.getCount() <= 0 )
		return NULL;
	const ModuleData* mdd = mi.getNthData(0);
	const W3DModelDrawModuleData* md = mdd ? mdd->getAsW3DModelDrawModuleData() : NULL;
	if( md == NULL )
		return NULL;
	ModelConditionFlags state;
	state.clear();
	AsciiString modelName = md->getBestModelNameForWB( state );

	// create the render object
	Int playerColor = 0xFFFFFF;
	tower = assetManager->Create_Render_Obj( modelName.str(), 1.0f, playerColor );

	// tie the render object into the map object
	mapObject->setBridgeRenderObject( type, tower );

	// set the position of the tower render object to the position in the world
	Matrix3D transform;
	transform.Make_Identity();
	transform.Set_X_Translation( towerPos.x );
	transform.Set_Y_Translation( towerPos.y );
	transform.Set_Z_Translation( towerPos.z );
	tower->Set_Transform( transform );

	// set the angle for the tower
	/// @todo --> write me

	// add tower render object to the scene
	scene->Add_Render_Object( tower );

	// return the render object of the tower created
	return tower;

}

//=============================================================================
//=============================================================================
static void updateTowerPos( RenderObjClass* tower, 
														BridgeTowerType type, 
														BridgeInfo* bridgeInfo )
{

	// sanity
	if( tower == NULL || type < 0 || type >= BRIDGE_MAX_TOWERS || bridgeInfo == NULL )
		return;

	//
	// compute the angle of the bridge ... we consider the angle of the bridge to be
	// from 'from' to 'to' in the bridge info ... and so does the game
	//
	Coord2D v;
	v.x = bridgeInfo->toLeft.x - bridgeInfo->fromLeft.x;
	v.y = bridgeInfo->toLeft.y - bridgeInfo->fromLeft.y;
	Real angle = v.toAngle();

	//
	// given the type of tower (corner position) find the appropriate spot to put the tower
	// NOTE that we're also adjusting the angle for the from side to point the
	// opposite way the "bridge is pointing"
	//
	Coord3D towerPos;
	switch( type )
	{

		case BRIDGE_TOWER_FROM_LEFT:	towerPos = bridgeInfo->fromLeft;		angle += PI; break;
		case BRIDGE_TOWER_FROM_RIGHT: towerPos = bridgeInfo->fromRight;		angle += PI; break;
		case BRIDGE_TOWER_TO_LEFT:		towerPos = bridgeInfo->toLeft;			break;
		case BRIDGE_TOWER_TO_RIGHT:		towerPos = bridgeInfo->toRight;			break;
		default: return;

	}  // end switch

	// set the position of the tower render object to the position in the world
	Matrix3D transform;
	transform.Make_Identity();
	transform.Set_X_Translation( towerPos.x );
	transform.Set_Y_Translation( towerPos.y );
	transform.Set_Z_Translation( towerPos.z );
	transform.Rotate_Z( angle );
	tower->Set_Transform( transform );

	// set the angle for the tower
//	tower->setAngle( angle );

}

//=============================================================================
// W3DBridgeBuffer::worldBuilderUpdateBridgeTowers
//=============================================================================
/** loadBridges.  When loaded, tell the terrain logic where the bridge is. */
//=============================================================================
// ?worldBuilderUpdateBridgeTowers@W3DBridgeBuffer@@QAEXPAVW3DAssetManager@@PAVSimpleSceneClass@@@Z present-unmatched
void W3DBridgeBuffer::worldBuilderUpdateBridgeTowers( W3DAssetManager *assetManager,
																											SimpleSceneClass *scene )
{
	MapObject *pMapObj;
	MapObject *pMapObj2;

	for( pMapObj = MapObject::getFirstMapObject(); pMapObj; pMapObj = pMapObj->getNext() ) 
	{

		if( pMapObj->getFlag( FLAG_BRIDGE_POINT1 ) ) 
		{

			pMapObj2 = pMapObj->getNext();
			if( !pMapObj2 || !pMapObj2->getFlag( FLAG_BRIDGE_POINT2 ) ) 
				DEBUG_LOG(("Missing second bridge point.  Ignoring first.\n"));

			if( pMapObj2 == NULL ) 
				break;
			if( !pMapObj2->getFlag( FLAG_BRIDGE_POINT2 ) ) 
				continue;

			//
			// now that we've got the two map objects that are bridge point 1 and 2, get the
			// bridge info that has been stored
			//
			for( Int i = 0; i < m_numBridges; ++i )
			{

				//
				// find the bridge with the matching name and position ... note we're just matching
				// (x,y) here cause name and location (without the additional complication of Z) is
				// really all we have to match bridges.
				/// @todo integrate the editor with the game ... will never happen tho ... 
				//
				if( m_bridges[ i ].getTemplateName() == pMapObj->getName() &&
						m_bridges[ i ].getStart()->X == pMapObj->getLocation()->x &&
						m_bridges[ i ].getStart()->Y == pMapObj->getLocation()->y &&
						m_bridges[ i ].getEnd()->X == pMapObj2->getLocation()->x &&
						m_bridges[ i ].getEnd()->Y == pMapObj2->getLocation()->y )
				{
					RenderObjClass *towerRenderObj;

					// get the bridge info
					BridgeInfo bridgeInfo;
					m_bridges[ i ].getBridgeInfo( &bridgeInfo );

					// go through all bridge tower render objects
					Bool created;
					for( Int j = 0; j < BRIDGE_MAX_TOWERS; ++j )
					{

						// create render object if needed
						created = FALSE;
						towerRenderObj = pMapObj->getBridgeRenderObject( (BridgeTowerType)j );
						if( towerRenderObj == NULL )
						{

							towerRenderObj = createTower( scene, assetManager, pMapObj, (BridgeTowerType)j, &bridgeInfo );
							created = TRUE;

						}  // end if

						// sanity
						DEBUG_ASSERTCRASH( towerRenderObj != NULL, ("worldBuilderUpdateBridgeTowers: unable to create tower for bridge '%s'\n",
															 m_bridges[ i ].getTemplateName().str()) );
															  
						// update the position of the towers
						updateTowerPos( towerRenderObj, (BridgeTowerType)j, &bridgeInfo );

						// release the initial ref count of 1 for a newly created tower
						if( created )
							REF_PTR_RELEASE( towerRenderObj );

					}  // end for j

				}  // end if

			}  // end for i

			// skip the 2nd map object representing the second half of the bridgef
			pMapObj = pMapObj2;

		} 

	}

}

//=============================================================================
// W3DBridgeBuffer::addBridge
//=============================================================================
/** Adds a bridge.  Name is the GDF object name. */
//=============================================================================
// byte-exact reconstruction: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DBridgeBuffer_addBridge_Thunk.cpp
// ?addBridge@W3DBridgeBuffer@@IAEXVVector3@@0VAsciiString@@PAVW3DTerrainLogic@@PAVDict@@@Z present-unmatched
void W3DBridgeBuffer::addBridge(Vector3 fromLoc, Vector3 toLoc, AsciiString name, W3DTerrainLogic *pTerrainLogic, Dict *props)
{
	if (m_numBridges >= MAX_BRIDGES) {
		return;  
	}

	if (!m_initialized) {
		return;  
	}
	m_bridges[m_numBridges].init(fromLoc, toLoc, name);
	if (m_bridges[m_numBridges].load(BODY_PRISTINE)) {
		W3DBridge *pBridge = m_bridges+m_numBridges;
		if (pTerrainLogic) {
			BridgeInfo info;
			pBridge->getBridgeInfo(&info);
			info.bridgeIndex = m_numBridges;
			pTerrainLogic->addBridgeToLogic(&info, props, name);
		}
		m_numBridges++;
	}
}

//=============================================================================
// W3DBridgeBuffer::updateCenter
//=============================================================================
/** Updates the drawing buffer, based on the camera position. */
//=============================================================================
void W3DBridgeBuffer::updateCenter(CameraClass *camera, RefRenderObjListIterator *pLightsIterator)
{
	cull(camera);
	if (m_anythingChanged || m_curNumBridgeIndices == 0) {
		loadBridgesInVertexAndIndexBuffers(pLightsIterator);
	}
	m_updateVis = false;
}

//=============================================================================
// W3DBridgeBuffer::drawBridges
//=============================================================================
/** Draws the bridges. */
//=============================================================================
// ?drawBridges@W3DBridgeBuffer@@QAEXPAVCameraClass@@_NPAVTextureClass@@@Z
// Body in W3DBridgeBuffer_drawBridges.asm (exact 909B retail).
// Keep COMDATs previously only referenced by drawBridges: DX8Wrapper::Set_Shader,
// Bridge::getBridgeInfo, W3DBridge::setEnabled.
void W3DBridgeBuffer_force_drawBridges_deps(ShaderClass *sh, Bridge *br, BridgeInfo *bi, W3DBridge *wb, Bool en)
{
	DX8Wrapper::Set_Shader(*sh);
	br->getBridgeInfo(bi);
	wb->setEnabled(en);
}
