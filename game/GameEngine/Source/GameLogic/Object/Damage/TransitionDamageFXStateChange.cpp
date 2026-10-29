// ?onBodyDamageStateChange@TransitionDamageFX@@UAEXPBVDamageInfo@@W4BodyDamageType@@1@Z
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Include /Igame/GameEngine/Source/GameLogic/Object/Damage
// Evidence: targets/game/reverse/identity_evidence/002525e0-damage-transition-retry.md.
#define class struct
#include "coord3d.h"
#undef class
#include "ascii_string.h"
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
inline Coord3D::Coord3D(const Coord3D &other) {x=other.x;y=other.y;z=other.z;}
class Matrix3D;
class Drawable {
public:
 int getPristineBonePositions(const char *,int,Coord3D *,Matrix3D *,int,int) const;
};
int GetGameLogicRandomValue(int,int,char *,int);
struct FXLocInfo {
 char locType;
 AsciiString boneName;
 bool randomBone;
 Coord3D loc;
};
// ?getLocalEffectPos@@YA?AUCoord3D@@PBUFXLocInfo@@PAVDrawable@@@Z
//-------------------------------------------------------------------------------------------------
/** Given an FXLoc info struct, return the effect position that we are supposed to use. 
	* The position is local to to the object */
//-------------------------------------------------------------------------------------------------
static Coord3D getLocalEffectPos( const FXLocInfo *locInfo, Drawable *draw )
{



	if( locInfo->locType == 0 && draw )
	{

		if( !locInfo->randomBone )
		{
			Coord3D pos;
		
			// get the bone position
			int count = draw->getPristineBonePositions( locInfo->boneName.str(), 0, &pos, 0, 1, 0 );

			// sanity, if bone not found revert back to location defined in struct (which is 0,0,0)
			if( count == 0 )
				return locInfo->loc;

			// return the position retrieved
			return pos;

		}  // end if
		else
		{
		  const int MAX_BONES = 32;
			Coord3D positions[ MAX_BONES ];

			// get the bone positions
			int boneCount;
			boneCount = draw->getPristineBonePositions( locInfo->boneName.str(), 1, positions, 0, MAX_BONES, 0 );

			// sanity, if bone not found revert back to location defined in struct (which is 0,0,0)
			if( boneCount == 0 )
				return locInfo->loc;

			// pick one of the bone positions
			int pick = GetGameLogicRandomValue( 0, boneCount - 1, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Damage\\TransitionDamageFX.cpp", 339 );
			return positions[ pick ];

		}  // end else

	}  // end if
	else
		return locInfo->loc;

}  // end getLocalEffectPos


// ??4Coord3D@@QAEAAU0@ABU0@@Z absent-from-retail
inline Coord3D &Coord3D::operator=(const Coord3D &other) { x=other.x; y=other.y; z=other.z; return *this; }
class Matrix3D;
class ParticleSystemTemplate;
enum BodyDamageType { BODY_PRISTINE, BODY_DAMAGED, BODY_REALLYDAMAGED, BODY_RUBBLE };
enum ParticleSystemID { INVALID_PARTICLE_SYSTEM_ID=0 };
class DamageInfo {
public:
 char m_unmodelled00[8];
 int m_sourceID;
 char m_unmodelled0C[4];
 int m_damageType;
};
class BodyModuleInterface {
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
 virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
 virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
 virtual void slot30(); virtual void slot34(); virtual void slot38();
 virtual const DamageInfo *getLastDamageInfo() const;
};
#define BFME_HAVE_COORD3D
#define THING_TU_MEMBERS void convertBonePosToWorldPos(const Coord3D *,const Matrix3D *,Coord3D *,Matrix3D *) const;
#define OBJECT_TU_MEMBERS \
 Drawable *getDrawableInline() const {return (Drawable *)getDrawable();} \
 BodyModuleInterface *getBodyModule() const {return m_body;} \
 const Coord3D *getPosition() const {return &m_cachedPos;} \
 bool rva002525E0Guard() const {return (*(const unsigned char *)((const char *)this+0x118)&0x10)!=0;}
#include "../object.h"
#undef OBJECT_TU_MEMBERS
#undef THING_TU_MEMBERS
class GameLogic {public:Object *findObjectByID(int);};
// Retail 0x012F0898 is ?TheGameLogic@@3PAVGameLogic@@A (data_rows.csv,
// GameLogic.cpp); TheBfmeGameLogic was only a pin nothing defines.
extern GameLogic *TheGameLogic;
#define TheBfmeGameLogic TheGameLogic
class FXList {
public:
 bool bfmeIsBlocked();
 void doFXPos(const Coord3D *,const Matrix3D *,float,const Coord3D *) const;
 static void doFXPos(const FXList *fx,const Coord3D *pos) {
  if(fx && !const_cast<FXList *>(fx)->bfmeIsBlocked()) fx->doFXPos(pos,0,0,0);
 }
};
class BfmeThingFB {public:void bfmeTellFB(void *,void *,void *,void *);};
struct FXDamageFXListInfo {const FXList *fx; FXLocInfo locInfo;};
struct FXDamageOCLInfo {BfmeThingFB *ocl; FXLocInfo locInfo;};
struct FXDamageParticleSystemInfo {const ParticleSystemTemplate *particleSysTemplate; FXLocInfo locInfo;};
class TransitionDamageFXModuleData {
public:
 char m_unmodelled00[8];
 unsigned int m_damageFXTypes;
 FXDamageFXListInfo m_fxList[4][12];
 unsigned int m_damageOCLTypes;
 FXDamageOCLInfo m_OCL[4][12];
 unsigned int m_damageParticleTypes;
 FXDamageParticleSystemInfo m_particleSystem[4][12];
};
class BfmeParticleSystemHandle;
class ParticleSystem {
public:
 char m_unmodelled00[0x98];
 BfmeParticleSystemHandle *m_firstHandle;
 BfmeParticleSystemHandle *m_lastHandle;
 char m_unmodelledA0[0xC];
 ParticleSystemID m_systemID;
 void setPosition(const Coord3D *);
 void attachToObject(const Object *);
 ParticleSystemID getSystemID() const {return m_systemID;}
};
ParticleSystem *Make00001B18();
class BfmeParticleSystemHandle {
public:
 ParticleSystem *m_system;
 BfmeParticleSystemHandle *m_previous;
 BfmeParticleSystemHandle *m_next;
 operator bool() const {return m_system!=0;}
 ParticleSystem *operator->() const {if(!m_system)return Make00001B18();return m_system;}
 ~BfmeParticleSystemHandle() {
  if(m_system) {
   if(m_previous)m_previous->m_next=m_next;else m_system->m_firstHandle=m_next;
   if(m_next)m_next->m_previous=m_previous;else m_system->m_lastHandle=m_previous;
   m_previous=0; m_next=0;
  }
 }
};
class ParticleSystemManager {
public:
 BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate *,bool);
 void destroyParticleSystemByID(ParticleSystemID);
};
extern ParticleSystemManager *TheParticleSystemManager;
class BfmeThingFDE {public:void bfmeUseFDE(int);};
class Rva002525E0ObjectModule {
public:
 virtual void slot00();
 const TransitionDamageFXModuleData *m_moduleData;
 Object *m_object;
};
class Rva002525E0BehaviorInterface {public:virtual void slot00();};
class Rva002525E0DamageInterface {
public:
 virtual void onDamage(DamageInfo *);
 virtual void onHealing(DamageInfo *);
 virtual void onBodyDamageStateChange(const DamageInfo *,BodyDamageType,BodyDamageType)=0;
};
class TransitionDamageFX : public Rva002525E0ObjectModule, public Rva002525E0BehaviorInterface, public Rva002525E0DamageInterface {
public:
 virtual void onBodyDamageStateChange(const DamageInfo *,BodyDamageType,BodyDamageType);
 void rva002523E0(bool);
 Object *getObject() const {return m_object;}
 const TransitionDamageFXModuleData *getTransitionDamageFXModuleData() const {return m_moduleData;}
 ParticleSystemID m_particleSystemID[4][12];
};
inline bool getDamageTypeFlag(unsigned int flags,int type) {return (flags&(1u<<(type-1)))!=0;}
inline bool rva002525E0NeighborStateChanged(BodyDamageType oldState,BodyDamageType newState) {return newState!=oldState && (newState==BODY_RUBBLE || oldState==BODY_RUBBLE);}
//-------------------------------------------------------------------------------------------------
/** Switching damage states */
//-------------------------------------------------------------------------------------------------
// ?onBodyDamageStateChange@TransitionDamageFX@@UAEXPBVDamageInfo@@W4BodyDamageType@@1@Z
void TransitionDamageFX::onBodyDamageStateChange( const DamageInfo* damageInfo, 
																									BodyDamageType oldState, 
																									BodyDamageType newState )
{
	if( getObject()->rva002525E0Guard() )
		return;

	Object *damageSource = 0;
	Int i;
	Drawable *draw = getObject()->getDrawableInline();
	const TransitionDamageFXModuleData *modData = getTransitionDamageFXModuleData();

	// get the source of the damage if present
	if( damageInfo )
		damageSource = TheBfmeGameLogic->findObjectByID( damageInfo->m_sourceID );
	
	// remove any particle systems that might be emitting from our old state
	for( i = 0; i < 12; i++ )
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
	((BfmeThingFDE *)this)->bfmeUseFDE( newState );

	if( newState > oldState )
	{
		const ParticleSystemTemplate *pSystemT;
		Coord3D pos;

		// if we are restricted by the damage type executing effect, bail out of here
		const DamageInfo *lastDamageInfo = getObject()->getBodyModule()->getLastDamageInfo();

		for( i = 0; i < 12; i++ )
		{

			// play fx list for our new state
			if( modData->m_fxList[ newState ][ i ].fx )
			{

				if( lastDamageInfo == 0 || 
						getDamageTypeFlag( modData->m_damageFXTypes, lastDamageInfo->m_damageType ) )
				{

					pos = getLocalEffectPos( &modData->m_fxList[ newState ][ i ].locInfo, draw );
					getObject()->convertBonePosToWorldPos( &pos, 0, &pos, 0 );
					FXList::doFXPos( modData->m_fxList[ newState ][ i ].fx, &pos );

				}  // end if

			}  // end if
					
			// do any object creation list for our new state
			if( modData->m_OCL[ newState ][ i ].ocl )
			{

				if( lastDamageInfo == 0 || 
						getDamageTypeFlag( modData->m_damageOCLTypes, lastDamageInfo->m_damageType ) )
				{

					pos = getLocalEffectPos( &modData->m_OCL[ newState ][ i ].locInfo, draw );
					getObject()->convertBonePosToWorldPos( &pos, 0, &pos, 0 );
					BfmeThingFB *ocl = modData->m_OCL[ newState ][ i ].ocl;
					Object *object = getObject();
					if( ocl ) ocl->bfmeTellFB( object, &pos, (void *)damageSource->getPosition(), 0 );

				}  // end if

			}  // end if

			// get the template of the system to create
			pSystemT = modData->m_particleSystem[ newState ][ i ].particleSysTemplate;
			if( pSystemT )
			{

				if( lastDamageInfo == 0 || 
						getDamageTypeFlag( modData->m_damageParticleTypes, lastDamageInfo->m_damageType ) )
				{

					// create a new particle system based on the template provided
					BfmeParticleSystemHandle pSystem = TheParticleSystemManager->createParticleSystem( pSystemT, true );
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
			
	if( rva002525E0NeighborStateChanged( oldState, newState ) )
		rva002523E0( true );

}  // end onBodyDamageStateChange

