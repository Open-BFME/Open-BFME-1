// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
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

// FILE: W3DShroud.cpp /////////////////////////////////////////////////////////////////////////////
// Created:   Mark Wilczynski, Jan 2002
// Desc:      Code to support rendering of shrouded units/terrain.
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "Lib/BaseType.h"
#include "camera.h"
#include "simplevec.h"
#include "dx8wrapper.h"
#include "common/MapObject.h"
#include "common/PerfTimer.h"
#include "W3DDevice/GameClient/HeightMap.h"
#include "W3DDevice/GameClient/W3DPoly.h"
#include "W3DDevice/GameClient/W3DShaderManager.h"
#include "assetmgr.h"
#include "W3DDevice/GameClient/W3DShroud.h"
#include "WW3D2/textureloader.h"
#include "common/GlobalData.h"
#include "GameLogic/PartitionManager.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-----------------------------------------------------------------------------

// In Global Data now

//#define SHROUD_COLOR	0x00ffffff //temporary test of gray shroud instead of pure black.
//#define MIN_SHROUD_LEVEL	0		//for gray fog

//Int SHROUD_COLOR=0x00808080; //temporary test of gray shroud instead of pure black.
//Int MIN_SHROUD_LEVEL=50;		//for gray fog

//#define SHROUD_COLOR	0x00eeeebff //temporary test of gray shroud instead of pure black.
//#define MIN_SHROUD_LEVEL	254		//for gray fog

//#define SHROUD_COLOR	0x00bbbbbb //temporary test of gray shroud instead of pure black.
//#define SHROUD_COLOR	0x00004080 //temporary test of blue shroud instead of pure black.

//#define MIN_SHROUD_LEVEL	100		//for black fog

//#define MAX_MAP_SHROUDSIZE	1024	//maximum number of shroud cells across entire map.
//#define MAX_VISIBLE_SHROUDSIZE	(MAX_MAP_SHROUDSIZE+1)	//maximum number of shroud vertices visible at any given time
#define DEFAULT_SHROUD_CELL_SIZE	MAP_XY_FACTOR	//assume shroud at same resolution as terrain cells.
#define DEFAULT_TERRAIN_SIZE 1024 //assumed size of largest terrain possible (in vertices)
#define DEFAULT_VISIBLE_TERRAIN 96	//assumed size of visible terrain cells.

//-----------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShroudConstructor.cpp

//-----------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngineDevice/Source/W3DDevice/GameClient/Gen_0071B3D0_W3DShroudDestructor.cpp

//-----------------------------------------------------------------------------
/**Called to initialize a new shroud for a new map.  Should be done after the map is loaded
   into the terrain object.  worldCellSize is the world-space dimensions of each shroud cell.
   The system will generate enough cells to cover the full map.
*/

//-----------------------------------------------------------------------------
///Called on map reset.

//-----------------------------------------------------------------------------
///Release any resources that can't survive a D3D device reset.
// ?ReleaseResources@W3DShroud@@ present-unmatched
void W3DShroud::ReleaseResources(void)
{
	REF_PTR_RELEASE (m_pDstTexture);
}

//-----------------------------------------------------------------------------
///Restore resources that are lost on D3D device reset.
// byte-exact reconstruction: game/GameEngineDevice/Source/W3DDevice/GameClient/Gen_00719FB0_ReAcquireResources.cpp
// ?ReAcquireResources@W3DShroud@@ present-unmatched
Bool W3DShroud::ReAcquireResources(void)
{
		if (!m_dstTextureWidth)
			return TRUE;	//nothing to reaquire since shroud was never initialized with valid data

		DEBUG_ASSERTCRASH( m_pDstTexture == NULL, ("ReAcquire of existing shroud texture"));
	
		// Create destination texture (stored in video memory).
		// Since we control the video memory copy, we can do partial updates more efficiently. Or do shift blits.
#if defined(_DEBUG) || defined(_INTERNAL)
		if (TheGlobalData && TheGlobalData->m_fogOfWarOn)
			m_pDstTexture = MSGNEW("TextureClass") TextureClass(m_dstTextureWidth,m_dstTextureHeight,WW3D_FORMAT_A4R4G4B4,MIP_LEVELS_1, TextureClass::POOL_DEFAULT);
		else
#endif
			m_pDstTexture = MSGNEW("TextureClass") TextureClass(m_dstTextureWidth,m_dstTextureHeight,WW3D_FORMAT_R5G6B5,MIP_LEVELS_1, TextureClass::POOL_DEFAULT);

		DEBUG_ASSERTCRASH( m_pDstTexture != NULL, ("Failed ReAcquire of shroud texture"));

		if (!m_pDstTexture)
		{	//could not create a valid texture
			m_dstTextureWidth = 0;
			m_dstTextureHeight = 0;
			return FALSE;
		}
		m_pDstTexture->Get_Filter().Set_U_Addr_Mode(TextureFilterClass::TEXTURE_ADDRESS_CLAMP);
		m_pDstTexture->Get_Filter().Set_V_Addr_Mode(TextureFilterClass::TEXTURE_ADDRESS_CLAMP);
		m_pDstTexture->Get_Filter().Set_Mip_Mapping(TextureFilterClass::FILTER_TYPE_NONE);
		m_clearDstTexture = TRUE;	//force clearing of destination texture first time it's used.

		return TRUE;
}

//-----------------------------------------------------------------------------
W3DShroudLevel W3DShroud::getShroudLevel(Int x, Int y)
{
	if (m_shroudData == NULL)
		return 0;

	if (x < m_numCellsX && y < m_numCellsY)
	{
		Int value = (Int)*((volatile UnsignedByte *)((UnsignedByte *)m_shroudData + (x + y * m_numCellsX) * 2));
		value &= 0x0f;
		return (W3DShroudLevel)(value * 17.0f);
	}
	return 0;
}

//-----------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngineDevice/Source/W3DDevice/GameClient/Gen_0071B670_SetShroudLevel.cpp

//-----------------------------------------------------------------------------
///Quickly sets the shroud level of entire map to a single value
// fillShroudData is owned by W3DShroud_fillShroudData.cpp (RVA 0x0071A520).
// The BFME body calls packShroudPixel; the reference donor inlined other packing.

// W3DShroud::fillBorderShroudData: retail body (0x0071A5E0) in
// W3DShroud_fillBorderShroudData.cpp.

//-----------------------------------------------------------------------------
///@todo: remove this
TextureClass *DummyTexture=NULL;

//#define LOAD_DUMMY_SHROUD

//-----------------------------------------------------------------------------
//DECLARE_PERF_TIMER(shroudCopy)

//-----------------------------------------------------------------------------
/** Updates video memory surface with currently visible shroud data */

#define FOG_INTERPOLATION_RATE	(255.0f/1000.0f)	//take one second to go from black to fully lit.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// ?setShroudFilter@W3DShroud@@ present-unmatched
void W3DShroud::setShroudFilter(Bool enable)
{
	if (enable)
		m_shroudFilter=TextureFilterClass::FILTER_TYPE_DEFAULT;
	else
		m_shroudFilter=TextureFilterClass::FILTER_TYPE_NONE;
}

//-----------------------------------------------------------------------------
///Set render states required to draw shroud pass.

//-----------------------------------------------------------------------------
///Restore render states that W3D doesn't know about.
void W3DShroudMaterialPassClass::UnInstall_Materials(void) const
{
	W3DShaderManager::resetShader(W3DShaderManager::ST_SHROUD_TEXTURE);
}

//-----------------------------------------------------------------------------
///Set render states required to draw shroud pass.
void W3DMaskMaterialPassClass::Install_Materials(void) const
{
	W3DShaderManager::setShader(W3DShaderManager::ST_MASK_TEXTURE, 0);
}

//-----------------------------------------------------------------------------
///Restore render states that W3D doesn't know about.
void W3DMaskMaterialPassClass::UnInstall_Materials(void) const
{
	if (m_allowUninstall)
		W3DShaderManager::resetShader(W3DShaderManager::ST_MASK_TEXTURE);
}
