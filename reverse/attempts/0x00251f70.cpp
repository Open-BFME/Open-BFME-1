// ?parseOclEntry@Rva00251F70@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.93 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini_noinline /Ireference/shims/iniexception /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// ================= BANKED ATTEMPT NOTE (2026-09-10) =================
// This is the whole ported translation unit, not a standalone body. It is the
// stash for the three INI field parsers 0x00251ED0 (fxlist), 0x00251F70 (ocl)
// and 0x00252010 (psys) and for the shared helper at 0x00251CF0.
//
// WHAT THIS BANK ESTABLISHES, and it replaces the earlier standalone stash:
//
// 1. The helper at 0x00251CF0 is NOT a TransitionDamageFX constructor. The
//    retail body throws INIException(3, "parseFXLocInfo: Bone name not
//    followed by RandomBone specifier.") at 0x010B2470, so the function names
//    itself: it is the file-static parseFXLocInfo of this TU. The ledger row
//    ??0TransitionDamageFX@@ at 0x00251CF0 carries a wrong identity and the
//    __emit lift at TransitionDamageFXCtorThunk.cpp has to go.
//
// 2. There is a real donor. Zero Hour's
//    GeneralsMD/.../GameLogic/Object/Damage/TransitionDamageFX.cpp contains
//    parseFXLocInfo and all three parsers, and the already-ported
//    Code/GameEngine/Source/GameLogic/Object/Damage/TransitionDamageFX.cpp in
//    this repository holds them as present-unmatched bodies. No new TU is
//    needed. The retail string pool confirms the shape: "bone" 0x010B24CC,
//    "randombone" 0x010B24BC, "loc" 0x010B246C, "'loc' or 'bone' expected"
//    0x010B244C, "X"/"Y"/"Z" for the three sub-tokens.
//
// 3. BFME differs from Zero Hour in exactly two ways here, both applied below.
//    Every "throw INI_INVALID_DATA" is a "throw INIException(3, <message>)"
//    against the literal at the address the retail body pushes, and the
//    DEBUG_CRASH before the RandomBone throw is absent from retail.
//
// 4. The INI class layout is the one in reference/shims/ini_noinline, where
//    m_seps sits at +0x414 and getSepsColon() therefore compiles to
//    [ini+0x41C], which is what retail loads. reference/shims/ini_bfme is the
//    WRONG shim for this TU: it puts m_sepsColon at +0x20. The unmodified
//    Zero Hour header puts it at +0x2428. The cl: line below adds
//    /Ireference/shims/ini_noinline and /Ireference/shims/iniexception ahead
//    of /Ireference/shims/sweep, and the TU includes Common/INIException.h.
//
// RESULT. ?parseObjectCreationList@TransitionDamageFXModuleData@@ compiles to
// 118 bytes against retail's 117, with the first 18 bytes byte-identical
// (sub esp,8 / push ebx / mov ebx,[esp+0x14] / push esi / push edi) and the
// whole tail in retail's instruction order including the INIException throw
// path, the g_lookup stricmp import and the four-argument tail call. The
// earlier standalone stash reached 114 bytes but did so with a hand-written
// INI class and a hand-written parser body, so it could never grow the helper.
//
// THE REMAINING GAP is one instruction and one register swap:
//   retail  lea ecx,[edi+4] ; push ebx ; call parseFXLocInfo ; ... add esp,4
//   ours    lea eax,[esi+4] ; push eax ; push ebx ; call ... ; add esp,8
// MSVC 7.1 does give the file-static helper a private register convention -
// this bank REFUTES nothing about that theory and in fact confirms it, since
// ini is passed in a callee-saved register with no stack slot. What it does
// not yet reproduce is WHICH values go in registers: retail passes locInfo in
// ecx and ini in esi with instance alone on the stack, while ours passes ini
// in a register and both locInfo and instance on the stack. That also flips
// the esi/edi roles in the caller prologue (retail esi=ini edi=store, ours
// esi=store edi=ini), which is the same one decision seen twice.
//
// RULED OUT here, on top of the earlier list (__fastcall varargs on a member
// and on a free function, ellipsis thiscall, __asm at the call site, local
// definition order and hoisted separator variants):
//   - reference/shims/ini_bfme as the INI layout for this TU (+0x20, wrong).
//   - Reordering parseFXLocInfo's parameters to (locInfo, ini, instance) so
//     that locInfo is the first argument. Byte-identical outcome at 118: the
//     private convention's register choice does not follow parameter order.
//
// NEXT LEVER TO TRY, in this order: change parseFXLocInfo's own body so its
// allocation puts locInfo in ecx - it currently keeps locInfo live across
// every call, which is why the compiler spilled it. Candidates are making the
// AsciiString temporary a named local in its own nested scope, and writing
// locInfo->locType before the boneName assignment as retail does
// (mov byte ptr [edi],0 lands AFTER releaseBuffer in retail).
// Do NOT fake the call with a TU-local stub.
//
// The four bodies land together once the helper's convention lands, in one
// tools/add_match_batch.py pass, and TransitionDamageFXCtorThunk.cpp must be
// deleted in the same commit.
// ===================================================================
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

// FILE: TransitionDamageFX.cpp ///////////////////////////////////////////////////////////////////
// Author: Colin Day, March 2002
// Desc:   Damage module capable of launching various effects on damage transitions
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/Xfer.h"
#include "GameClient/Drawable.h"
#include "GameClient/FXList.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/ObjectCreationList.h"
#include "GameLogic/Module/TransitionDamageFX.h"
#include "Common/INIException.h"

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/TransitionDamageFXModuleData_ctor_Thunk.cpp
// ??0TransitionDamageFXModuleData@@ present-unmatched
TransitionDamageFXModuleData::TransitionDamageFXModuleData( void )
{
	Int i, j;

	for( i = 0; i < BODYDAMAGETYPE_COUNT; i++ )
	{

		for( j = 0; j < DAMAGE_MODULE_MAX_FX; j++ )
		{

			m_fxList[ i ][ j ].fx = NULL;
			m_fxList[ i ][ j ].locInfo.loc.x = 0.0f;
			m_fxList[ i ][ j ].locInfo.loc.y = 0.0f;
			m_fxList[ i ][ j ].locInfo.loc.z = 0.0f;
			m_fxList[ i ][ j ].locInfo.locType = FX_DAMAGE_LOC_TYPE_COORD;
			m_fxList[ i ][ j ].locInfo.randomBone = FALSE;
			m_OCL[ i ][ j ].ocl = NULL;
			m_OCL[ i ][ j ].locInfo.loc.x = 0.0f;
			m_OCL[ i ][ j ].locInfo.loc.y = 0.0f;
			m_OCL[ i ][ j ].locInfo.loc.z = 0.0f;
			m_OCL[ i ][ j ].locInfo.locType = FX_DAMAGE_LOC_TYPE_COORD;
			m_OCL[ i ][ j ].locInfo.randomBone = FALSE;
			m_particleSystem[ i ][ j ].particleSysTemplate = NULL;
			m_particleSystem[ i ][ j ].locInfo.loc.x = 0.0f;
			m_particleSystem[ i ][ j ].locInfo.loc.y = 0.0f;
			m_particleSystem[ i ][ j ].locInfo.loc.z = 0.0f;
			m_particleSystem[ i ][ j ].locInfo.locType = FX_DAMAGE_LOC_TYPE_COORD;
			m_particleSystem[ i ][ j ].locInfo.randomBone = FALSE;

		}  // end for j

	}  // end for i

	m_damageFXTypes = DAMAGE_TYPE_FLAGS_NONE;
	m_damageFXTypes.flip();
	m_damageOCLTypes = DAMAGE_TYPE_FLAGS_NONE;
	m_damageOCLTypes.flip();
	m_damageParticleTypes = DAMAGE_TYPE_FLAGS_NONE;
	m_damageParticleTypes.flip();

}  // end TransitionDamageFXModuleData

//-------------------------------------------------------------------------------------------------
/** Parse fx location info ... that is a named bone or a coord3d position */
//-------------------------------------------------------------------------------------------------
static void parseFXLocInfo( FXLocInfo *locInfo, INI *ini, void *instance )
{
	const char *token = ini->getNextToken( ini->getSepsColon() );

	if( stricmp( token, "bone" ) == 0 )
	{

		// save bone name and location type
		locInfo->boneName = AsciiString( ini->getNextToken() );
		locInfo->locType = FX_DAMAGE_LOC_TYPE_BONE;

		//
		// bones are followed by RandomBone:<Yes|No>, if random bone is yes, the bone name is
		// assumed to be a "base bone name" and we will find all the bones with that prefix
		// when picking an effect position.  If it's no, the bone name is assumed to be explicit
		//
		token = ini->getNextToken( ini->getSepsColon() );
		if( stricmp( token, "randombone" ) != 0 )
		{

			throw INIException( 3, "parseFXLocInfo: Bone name not followed by RandomBone specifier." );

		}  // end if

		// parse the Bool definition
		ini->parseBool( ini, instance, &locInfo->randomBone, NULL );

	}  // end if
	else if( stricmp( token, "loc" ) == 0 )
	{

		// save location and location type
		locInfo->loc.x = ini->scanReal( ini->getNextSubToken("X") );
		locInfo->loc.y = ini->scanReal( ini->getNextSubToken("Y") );
		locInfo->loc.z = ini->scanReal( ini->getNextSubToken("Z") );
		locInfo->locType = FX_DAMAGE_LOC_TYPE_COORD;

	}  // end else
	else
	{

		// error
		throw INIException( 3, "'loc' or 'bone' expected" );

	}  // end else

}  // end parseFXLocInfo

//-------------------------------------------------------------------------------------------------
/** In the form of:
	* FXListSlot = <<Bone:BoneName BoneRandom:<Yes|No>> | <Loc: X:x Y:y Z:z>> FXList:FXListName */
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/RTS/TransitionDamageFXModuleDataParseFXListThunk.cpp
// ?parseFXList@TransitionDamageFXModuleData@@ present-unmatched
void TransitionDamageFXModuleData::parseFXList( INI *ini, void *instance, 
																								void *store, const void *userData )
{
	const char *token;
	FXDamageFXListInfo *info = (FXDamageFXListInfo *)store;

	// parse the location bone or location
	parseFXLocInfo( &info->locInfo, ini, instance );

	// make sure we have an "FXList:" token
	token = ini->getNextToken( ini->getSepsColon() );
	if( stricmp( token, "fxlist" ) != 0 )
	{

		// error
		throw INIException( 3, "'fxlist' expected" );

	}  // end if

	// parse the fx list name
	ini->parseFXList( ini, instance, &info->fx, NULL );

}  // end parseFXList

//-------------------------------------------------------------------------------------------------
/** In the form of:
	* OCLSlot = <<Bone:BoneName BoneRandom:<Yes|No>> | <Loc: X:x Y:y Z:z>> OCL:OCLName */
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/RTS/TransitionDamageFXModuleDataParseObjectCreationListThunk.cpp
// ?parseObjectCreationList@TransitionDamageFXModuleData@@ present-unmatched
void TransitionDamageFXModuleData::parseObjectCreationList( INI *ini, void *instance, 
																														void *store, const void *userData )
{
	const char *token;
	FXDamageOCLInfo *info = (FXDamageOCLInfo *)store;

	// parse the location bone or location
	parseFXLocInfo( &info->locInfo, ini, instance );

	// make sure we have an "OCL:" token
	token = ini->getNextToken( ini->getSepsColon() );
	if( stricmp( token, "ocl" ) != 0 )
	{

		// error
		throw INIException( 3, "'ocl' expected" );

	}  // end if

	// parse the ocl name
	ini->parseObjectCreationList( ini, instance, store, &info->ocl );

}  // end parseObjectCreationList

//-------------------------------------------------------------------------------------------------
/** In the form of:
	* ParticleSlot = <<Bone:BoneName BoneRandom:<Yes|No>> | <Loc: X:x Y:y Z:z>> PSys:PSysName */
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/RTS/FXModuleDataParseParticleSystemThunks.cpp
// ?parseParticleSystem@TransitionDamageFXModuleData@@ present-unmatched
void TransitionDamageFXModuleData::parseParticleSystem( INI *ini, void *instance, 
																												void *store, const void *userData )
{
	const char *token;
	FXDamageParticleSystemInfo *info = (FXDamageParticleSystemInfo *)store;

	// parse the location bone or location
	parseFXLocInfo( &info->locInfo, ini, instance );

	// make sure we have an "PSys:" token
	token = ini->getNextToken( ini->getSepsColon() );
	if( stricmp( token, "psys" ) != 0 )
	{

		// error
		throw INIException( 3, "'psys' expected" );

	}  // end if

	// parse the particle system name
	ini->parseParticleSystemTemplate( ini, instance, store, &info->particleSysTemplate );

}  // end parseParticleSystem

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??0TransitionDamageFX@@ present-unmatched
TransitionDamageFX::TransitionDamageFX( Thing *thing, const ModuleData* moduleData ) 
																		  : DamageModule( thing, moduleData )
{
	Int i, j;

	for( i = 0; i < BODYDAMAGETYPE_COUNT; i++ )
		for( j = 0; j < DAMAGE_MODULE_MAX_FX; j++ )
			m_particleSystemID[ i ][ j ] = INVALID_PARTICLE_SYSTEM_ID;

}  // end TransitionDamageFX

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??1TransitionDamageFX@@ present-unmatched
TransitionDamageFX::~TransitionDamageFX( void )
{

}  // end ~TransitionDamageFX

/*
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?onDelete@TransitionDamageFX@@ present-unmatched
void TransitionDamageFX::onDelete( void )
{

	//
	// we would in theory delete any particle systems we have created and attached, but the
	// particle system will automatically delete itself when the object is destroyed
	//

}  // end onDelete
*/

//-------------------------------------------------------------------------------------------------
/** Given an FXLoc info struct, return the effect position that we are supposed to use. 
	* The position is local to to the object */
//-------------------------------------------------------------------------------------------------
static Coord3D getLocalEffectPos( const FXLocInfo *locInfo, Drawable *draw )
{

	DEBUG_ASSERTCRASH( locInfo, ("getLocalEffectPos: locInfo is NULL\n") );

	if( locInfo->locType == FX_DAMAGE_LOC_TYPE_BONE && draw )
	{

		if( locInfo->randomBone == FALSE )
		{
			Coord3D pos;
		
			// get the bone position
			Int count = draw->getPristineBonePositions( locInfo->boneName.str(), 0, &pos, NULL, 1 );

			// sanity, if bone not found revert back to location defined in struct (which is 0,0,0)
			if( count == 0 )
				return locInfo->loc;

			// return the position retrieved
			return pos;

		}  // end if
		else
		{
		  const Int MAX_BONES = 32;
			Coord3D positions[ MAX_BONES ];

			// get the bone positions
			Int boneCount;
			boneCount = draw->getPristineBonePositions( locInfo->boneName.str(), 1, positions, NULL, MAX_BONES );

			// sanity, if bone not found revert back to location defined in struct (which is 0,0,0)
			if( boneCount == 0 )
				return locInfo->loc;

			// pick one of the bone positions
			Int pick = GameLogicRandomValue( 0, boneCount - 1 );
			return positions[ pick ];

		}  // end else

	}  // end if
	else
		return locInfo->loc;

}  // end getLocalEffectPos

//-------------------------------------------------------------------------------------------------
/** Switching damage states */
//-------------------------------------------------------------------------------------------------
// ?onBodyDamageStateChange@TransitionDamageFX@@ present-unmatched
void TransitionDamageFX::onBodyDamageStateChange( const DamageInfo* damageInfo, 
																									BodyDamageType oldState, 
																									BodyDamageType newState )
{
	Object *damageSource = NULL;
	Int i;
	Drawable *draw = getObject()->getDrawable();
	const TransitionDamageFXModuleData *modData = getTransitionDamageFXModuleData();

	// get the source of the damage if present
	if( damageInfo )
		damageSource = TheGameLogic->findObjectByID( damageInfo->in.m_sourceID );
	
	// remove any particle systems that might be emitting from our old state
	for( i = 0; i < DAMAGE_MODULE_MAX_FX; i++ )
	{

		if( m_particleSystemID[ oldState ][ i ] != INVALID_PARTICLE_SYSTEM_ID )
		{

			TheParticleSystemManager->destroyParticleSystemByID( m_particleSystemID[ oldState ][ i ] );
			m_particleSystemID[ oldState ][ i ] = INVALID_PARTICLE_SYSTEM_ID;

		}  // end if

	}  // end for i

	//
	// when we are transitioning to a "worse" state we will play a set of effects for that
	// new state to make the transition
	//
	if( IS_CONDITION_WORSE( newState, oldState ) )
	{
		const ParticleSystemTemplate *pSystemT;
		Coord3D pos;

		// if we are restricted by the damage type executing effect, bail out of here
		const DamageInfo *lastDamageInfo = getObject()->getBodyModule()->getLastDamageInfo();

		for( i = 0; i < DAMAGE_MODULE_MAX_FX; i++ )
		{

			// play fx list for our new state
			if( modData->m_fxList[ newState ][ i ].fx )
			{

				if( lastDamageInfo == NULL || 
						getDamageTypeFlag( modData->m_damageFXTypes, lastDamageInfo->in.m_damageType ) )
				{

					pos = getLocalEffectPos( &modData->m_fxList[ newState ][ i ].locInfo, draw );
					getObject()->convertBonePosToWorldPos( &pos, NULL, &pos, NULL );
					FXList::doFXPos( modData->m_fxList[ newState ][ i ].fx, &pos );

				}  // end if

			}  // end if
					
			// do any object creation list for our new state
			if( modData->m_OCL[ newState ][ i ].ocl )
			{

				if( lastDamageInfo == NULL || 
						getDamageTypeFlag( modData->m_damageOCLTypes, lastDamageInfo->in.m_damageType ) )
				{

					pos = getLocalEffectPos( &modData->m_OCL[ newState ][ i ].locInfo, draw );
					getObject()->convertBonePosToWorldPos( &pos, NULL, &pos, NULL );
// ?create@ObjectCreationList@@ present-unmatched
					ObjectCreationList::create( modData->m_OCL[ newState ][ i ].ocl, 
																			getObject(), &pos, damageSource->getPosition(), INVALID_ANGLE );

				}  // end if

			}  // end if

			// get the template of the system to create
			pSystemT = modData->m_particleSystem[ newState ][ i ].particleSysTemplate;
			if( pSystemT )
			{

				if( lastDamageInfo == NULL || 
						getDamageTypeFlag( modData->m_damageParticleTypes, lastDamageInfo->in.m_damageType ) )
				{

					// create a new particle system based on the template provided
					ParticleSystem* pSystem = TheParticleSystemManager->createParticleSystem( pSystemT );
					if( pSystem )
					{
			
						// get the what is the position we're going to playe the effect at
						pos = getLocalEffectPos( &modData->m_particleSystem[ newState ][ i ].locInfo, draw );

						//
						// set position on system given any bone position provided, the bone position is
						// local to the object and that's what we want for the particle system ... the
						// transormation into world space using the object position is taken care of in
						// the particle system attachToObject method
						//
						pSystem->setPosition( &pos );

						// attach to object
						pSystem->attachToObject( getObject() );

						// save the id of this particle system so we can remove it later if it still exists
						m_particleSystemID[ newState ][ i ] = pSystem->getSystemID();

					}  // end if

				}  // end if

			}  // end if
						
		}  // end for i

	}  // end if
			
}  // end onBodyDamageStateChange

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@TransitionDamageFX@@ present-unmatched
void TransitionDamageFX::crc( Xfer *xfer )
{

	// extend base class
	DamageModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@TransitionDamageFX@@ present-unmatched
void TransitionDamageFX::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	DamageModule::xfer( xfer );

	// particle systems ids
	xfer->xferUser( m_particleSystemID, sizeof( ParticleSystemID ) * BODYDAMAGETYPE_COUNT * DAMAGE_MODULE_MAX_FX );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@TransitionDamageFX@@ present-unmatched
void TransitionDamageFX::loadPostProcess( void )
{

	// extend base class
	DamageModule::loadPostProcess();

}  // end loadPostProcess
