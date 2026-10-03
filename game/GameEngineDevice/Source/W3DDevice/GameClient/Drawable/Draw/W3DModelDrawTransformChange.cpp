// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /MD /EHsc /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/w3dmodeldraw /Iinputs/reference/shims/asciistring8 /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

// FILE: W3DModelDraw.cpp ///////////////////////////////////////////////////////////////////////
// Author: Colin Day, November 2001
// Desc:   Default w3d draw module
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////

#define DEFINE_W3DANIMMODE_NAMES
#define DEFINE_WEAPONSLOTTYPE_NAMES
#define _BFME_RETAIL_TREE_INSERT_LAYOUT

#define NO_DEBUG_CRC

#include "Common/CRC.h"
#include "Common/CRCDebug.h"
#include "Common/GameState.h"
#include "Common/GlobalData.h"
#include "Common/PerfTimer.h"
#include "Common/RandomValue.h"
#include "Common/ThingTemplate.h"
#include "Common/GameLOD.h"
#include "Common/Xfer.h"
#include "Common/GameState.h"
#include "Common/QuickTrig.h"
#include "GameClient/Drawable.h"
#include "GameClient/FXList.h"
#include "GameClient/Shadow.h"
#include "GameLogic/GameLogic.h"		// for real-time frame
#include "GameLogic/Object.h"
#include "GameLogic/WeaponSet.h"
#include "GameLogic/FPUControl.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "W3DDevice/GameClient/Module/W3DModelDraw.h"
#include "W3DDevice/GameClient/W3DAssetManager.h"
#include "W3DDevice/GameClient/W3DDisplay.h"
#include "W3DDevice/GameClient/W3DScene.h"
#include "W3DDevice/GameClient/W3DShadow.h"
#include "W3DDevice/GameClient/W3DTerrainTracks.h"
#include "W3DDevice/GameClient/WorldHeightMap.h"
#include "WW3D2/HAnim.h"
#include "WW3D2/HLod.h"
#include "WW3D2/RendObj.h"
#include "WW3D2/Mesh.h"
#include "WW3D2/MeshMdl.h"
#include "Common/BitFlagsIO.h"

class HeightMapRenderObjClass;
extern HeightMapRenderObjClass *TheTerrainRenderObject;
class BFMERopeDrawableGetPositionShim { public: const Coord3D *get() const; };
class BfmeCalc919G { public: int bfmeCalc919G(); };
// The existing address-named ILT is used because the canonical WorldHeightMap
// header does not yet declare its independently recovered BFME member.
void j_0001b572();
class Rva00763620Map {
public:
    void update(const Coord3D *position, float radius, bool value) {
        typedef void (Rva00763620Map::*Method)(const Coord3D *, float, bool);
        typedef char CheckedMemberPointerWidth[sizeof(Method) == sizeof(&j_0001b572) ? 1 : -1];
        union { void (*entry)(); Method method; } call;
        call.entry = &j_0001b572;
        (this->*call.method)(position, radius, value);
    }
};
class BfmeTrackLikeD62640 { public: void addCapEdgeToTrack(float, float); };
class AttachmentTransform007629F0 { public: void adjust(Matrix3D &); };
// Zero Hour twin and primary W3DModelDraw vtable slot35 (VA01123D38)
// establish this identity; the BFME-only fields remain address-qualified.
// See targets/game/reverse/identity_evidence/00763620-transform-change.md.
void W3DModelDraw::reactToTransformChange(const Matrix3D* oldMtx, const Coord3D* oldPos, Real oldAngle)
{
    Drawable *draw = *(Drawable **)((char *)this + 8);
    const void *data = *(const void **)((char *)this + 4);
    const ThingTemplate *tm = *(const OVERRIDE<ThingTemplate> *)((const char *)draw + 4);
    const Coord3D *pos = ((BFMERopeDrawableGetPositionShim *)draw)->get();
    if (*(const float *)((const char *)tm + 0x3a0) > 1.0f) {
        ((Rva00763620Map *)*(void **)((char *)TheTerrainRenderObject + 0x2ff4))->update(oldPos, *(const float *)((const char *)tm + 0x3a0), true);
        ((Rva00763620Map *)*(void **)((char *)TheTerrainRenderObject + 0x2ff4))->update(pos, *(const float *)((const char *)tm + 0x3a0), false);
    }
    if (*(RenderObjClass **)((char *)this + 0x34)) {
        Matrix3D mtx(true);
        if (*(const bool *)((const char *)data + 0x69))
            mtx.Set_Translation(((const Matrix3D *)((BfmeCalc919G *)*(Drawable **)((char *)this + 8))->bfmeCalc919G())->Get_Translation());
        else
            mtx = *((const Matrix3D *)((BfmeCalc919G *)*(Drawable **)((char *)this + 8))->bfmeCalc919G());
        ((AttachmentTransform007629F0 *)this)->adjust(mtx);
        (*(RenderObjClass **)((char *)this + 0x34))->Set_Transform(mtx);
    }
    TerrainTracksRenderObjClass *track = *(TerrainTracksRenderObjClass **)((char *)this + 0x44);
    if (track) {
        Object *obj = *(Object **)((char *)*(Drawable **)((char *)this + 8) + 0xfc);
        if (*(bool *)((char *)this + 0x2d)) {
            ((BfmeTrackLikeD62640 *)track)->addCapEdgeToTrack(pos->x,pos->y);
        } else {
            if (obj && obj->isSignificantlyAboveTerrain())
                *(bool *)((char *)*(void **)((char *)this + 0x44) + 0x12f8) = true;
            (*(TerrainTracksRenderObjClass **)((char *)this + 0x44))->addEdgeToTrack(pos->x,pos->y);
        }
    }
}

