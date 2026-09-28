// ?tryToIgnite@FlammableUpdate@@QAEXXZ
// partial score=0.985 date=2026-09-28
// ?tryToIgnite@FlammableUpdate@@QAEXXZ
// Candidate only: 962 bytes versus 961; normalized instruction match 0.985.
// Refined native FX wrappers; owner spill and cursor/element slots still differ.
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/GameLogic/Object
// stlport
//
// Retail 0x00293990: FlammableUpdate::tryToIgnite, 961 bytes.
//
// The Zero Hour body (inputs/reference/.../FlammableUpdate.cpp:190) is the
// first third of this one. BFME keeps every step of it -- the AFLAME status
// bit, the body-module setAflame, the MODELCONDITION_AFLAME state, the burning
// sound, the NAMEKEY("FireSpreadUpdate") module lookup, the three end frames,
// the wake frame -- and adds the FireFX list walk, the two affect flags, the
// delayed-Lua-event list handed to the script owner, and the disable window.
//
// Layout evidence, all byte-verified elsewhere in this tree:
//   FlammableUpdate            +0x24 m_status, +0x28/+0x2c/+0x30 the three end
//                             frames, +0x44 the BFME-only frame field
//                             (FlammableUpdateConstructorThunk.cpp)
//   FlammableUpdateModuleData  +0x08 burnedDelay, +0x0c aflameDuration,
//                             +0x10 aflameDamageDelay, +0x24 the FireFX list,
//                             +0x30/+0x32 the two affect flags, +0x48
//                             damageType, +0x4c the disable window
//                             (FlammableUpdateModuleDataCtorThunk.cpp)
//   the FireFX element        { FXList *fx; AsciiString boneName; }
//                             (FlammableUpdateParseFireFXList.cpp, 8-byte
//                             stride read straight off the loop)
//   the model-condition words Object +0x118 and +0x124
//                             (FlameCleanup00293E50.cpp)

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
#include "ascii_string.h"

typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef float Real;
typedef int Int;
typedef bool Bool;

template <>
inline const char *StringBase<char>::str() const
{
	return m_data ? (const char *)m_data + 8 : "";
}

template <>
inline bool StringBase<char>::isNotEmpty() const
{
	return m_data != 0 && m_data->length != 0;
}

template <int N>
class BitFlags
{
public:
	enum Init { kInit };
	BitFlags(Init, int bit) { bits.set(bit); }
	_STL::bitset<N> bits;
};

class Module;
class FXList;
class Drawable;
class Object;
class Rva001BE220Receiver { public: void dispatch(int, unsigned int); };
class Matrix3D;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum NameKeyType { KEY_NONE = 0 };
enum UpdateSleepTime { UPDATE_SLEEP_FOREVER = 0x3FFFFFFF };
enum DisabledType { DISABLED_PLACEHOLDER };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *);
};

extern NameKeyGenerator *TheNameKeyGenerator;

// BodyModuleInterface slot 10 is the Zero Hour setAflame: the first ten slots
// are the pads the retail vtable carries ahead of it.
#define BODY_SLOT( n ) virtual void bodyslot##n();
class BodyModuleInterface
{
public:
	BODY_SLOT( 00 ) BODY_SLOT( 04 ) BODY_SLOT( 08 ) BODY_SLOT( 0c )
	BODY_SLOT( 10 ) BODY_SLOT( 14 ) BODY_SLOT( 18 ) BODY_SLOT( 1c )
	BODY_SLOT( 20 ) BODY_SLOT( 24 )
	virtual void setAflame();
};
#undef BODY_SLOT

class FXList
{
public:
	void doFXPos( const Coord3D *primary, const Matrix3D *primaryMtx,
		Real primarySpeed, const Coord3D *secondary ) const;
	void doFXObj( const Object *primary, const Object *secondary ) const;
	Bool bfmeIsBlocked() const;
 static __forceinline void doFXPos(const FXList *, const Coord3D *, const Matrix3D *, float, const Coord3D *);
 static __forceinline void doFXObj(const FXList *, const Object *, const Object *);
};

#define OBJECT_TU_MEMBERS \
	void setStatus( const BitFlags<86> &status, Bool set ); \
	void notifyModelConditionChanged(); \
	Module *findModule( NameKeyType key ) const; \
	void setDisabledUntil( DisabledType type, UnsignedInt frame ); \
	void setStatusBit( Int bit, Bool value ); \
	void bfmeThunk1DC( Int damageType, UnsignedInt delay );

#include "object.h"

class Drawable
{
public:
	void applyPendingModelConditionFlags( Bool apply );
	Bool getCurrentWorldspaceClientBonePositions( const char *boneName,
		Matrix3D &transform ) const;
};

// Retail's matrix local is 48 bytes with the 1.0 on the diagonal of three
// four-float rows and every fourth component zero, so the translation lives at
// +0x0c/+0x1c/+0x2c -- which is exactly what the body copies out of it.
class BoneRow
{
public:
	void Set( Real x, Real y, Real z, Real w )
	{
		X = x;
		Y = y;
		Z = z;
		W = w;
	}
	Real X, Y, Z, W;
};

class Matrix3D
{
public:
	void Make_Identity( void )
	{
		Row[0].Set( 1.0f, 0.0f, 0.0f, 0.0f );
		Row[1].Set( 0.0f, 1.0f, 0.0f, 0.0f );
		Row[2].Set( 0.0f, 0.0f, 1.0f, 0.0f );
	}
	Real Get_X_Translation( void ) const { return Row[0].W; }
	Real Get_Y_Translation( void ) const { return Row[1].W; }
	Real Get_Z_Translation( void ) const { return Row[2].W; }
	BoneRow Row[3];
};

class FireFXElement
{
public:
	FXList *fx;
	AsciiString boneName;
};

class FlammableUpdateModuleData
{
public:
	unsigned char m_pad00[8];
	UnsignedInt m_burnedDelay;						// +0x08
	UnsignedInt m_aflameDuration;					// +0x0C
	UnsignedInt m_aflameDamageDelay;				// +0x10
	unsigned char m_pad14[0x24 - 0x14];
	FireFXElement *m_fireFXListBegin;				// +0x24
	FireFXElement *m_fireFXListEnd;					// +0x28
	unsigned char m_pad2c[0x30 - 0x2c];
	UnsignedByte m_enabled;							// +0x30
	UnsignedByte m_affectSelf;						// +0x31
	UnsignedByte m_affectAllies;					// +0x32
	unsigned char m_pad33[0x48 - 0x33];
	Int m_damageType;								// +0x48
	UnsignedInt m_extra0;							// +0x4C
};

// The frame the three end frames are stamped from, and the one the disable
// window is measured in. Rva00367E30Logic is the witness the landed
// ObjectSetDisabledUntil.cpp and the banked onDamage body both use.
class Rva00367E30Logic
{
public:
	unsigned char m_pad00[0x3c];
	UnsignedInt m_frame;							// +0x3C
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class BfmeDelayedLuaEvent
{
public:
	BfmeDelayedLuaEvent( void );
	~BfmeDelayedLuaEvent( void );
private:
	char m_bfmeBody[0x18];
};

class BfmeDelayedLuaEventListBase
{
public:
	~BfmeDelayedLuaEventListBase( void );
};

class DelayedLuaEventList : public BfmeDelayedLuaEventListBase
{
public:
	DelayedLuaEventList( void );
	virtual ~DelayedLuaEventList( void );
private:
	BfmeDelayedLuaEvent m_bfmeEvents[3];				// +0x04
};

class BfmeOwnerBR
{
public:
	void bfmeGo939B( Int script, Object *object, DelayedLuaEventList *events );
};

extern BfmeOwnerBR *g_bfmeOwnerBR;

class FireSpreadUpdate
{
public:
	void startFireSpreading();
};

class UpdateModule
{
protected:
	void setWakeFrame( Object *object, UpdateSleepTime sleepTime );

	Object *getObject() const { return m_object; }

	void *m_vptr;									// +0x00
	const void *m_moduleData;						// +0x04
	Object *m_object;								// +0x08
	unsigned char m_pad0c[0x24 - 0x0c];
};

class FlammableUpdate : public UpdateModule
{
public:
	void tryToIgnite();

	UpdateSleepTime bfmeCalcSleepTimeGate();

protected:
	void startBurningSound();

private:
	Int m_status;										// +0x24
	UnsignedInt m_aflameEndFrame;						// +0x28
	UnsignedInt m_burnedEndFrame;						// +0x2C
	UnsignedInt m_damageEndFrame;						// +0x30
	unsigned char m_pad34[0x44 - 0x34];
	UnsignedInt m_field44;								// +0x44
};

// ?tryToIgnite@FlammableUpdate@@QAEXXZ
__forceinline void FXList::doFXPos(const FXList *fx, const Coord3D *pos, const Matrix3D *matrix, float speed, const Coord3D *secondary)
{
    if (fx) { if (!fx->bfmeIsBlocked()) fx->doFXPos(pos,matrix,speed,secondary); }
}
__forceinline void FXList::doFXObj(const FXList *fx, const Object *object, const Object *secondary)
{
    if (fx) { if (!fx->bfmeIsBlocked()) fx->doFXObj(object,secondary); }
}

void FlammableUpdate::tryToIgnite()
{
	if( m_status != 0 )
		return;

	Object *me = m_object;

	me->setStatus( BitFlags<86>( BitFlags<86>::kInit, 10 ), true );
	me->m_body->setAflame();

	if( !( me->m_modelConditionFlags[2] & 0x2000 ) )
	{
		me->m_modelConditionFlags[2] |= 0x2000;
		me->notifyModelConditionChanged();
	}

	startBurningSound();

	static NameKeyType key_FireSpreadUpdate = TheNameKeyGenerator->nameToKey( "FireSpreadUpdate" );
	FireSpreadUpdate *fu = (FireSpreadUpdate *)getObject()->findModule( key_FireSpreadUpdate );
	if( fu != 0 )
		fu->startFireSpreading();

	m_status = 1;

	DelayedLuaEventList events;
	g_bfmeOwnerBR->bfmeGo939B( 10, me, &events );

	const FlammableUpdateModuleData *data = (const FlammableUpdateModuleData *)m_moduleData;
	UnsignedInt now = TheBfmeGameLogic->m_frame;
	if( data->m_aflameDuration > 0 )
	{
		m_aflameEndFrame = now + data->m_aflameDuration;
	}
	else
	{
		m_aflameEndFrame = UPDATE_SLEEP_FOREVER;
	}
	m_burnedEndFrame = data->m_burnedDelay ? now + data->m_burnedDelay : 0;
	m_damageEndFrame = data->m_aflameDamageDelay ? now + data->m_aflameDamageDelay : 0;
	setWakeFrame( getObject(), bfmeCalcSleepTimeGate() );

	if( data->m_enabled )
	{
		if( !( me->m_modelConditionFlags[5] & 0x100000 ) )
		{
			me->m_modelConditionFlags[5] |= 0x100000;
			me->notifyModelConditionChanged();
		}
	}
	if( data->m_affectAllies )
	{
		if( !( me->m_modelConditionFlags[5] & 0x200000 ) )
		{
			me->m_modelConditionFlags[5] |= 0x200000;
			me->notifyModelConditionChanged();
		}
	}
	if( data->m_enabled || data->m_affectAllies )
		me->getDrawable()->applyPendingModelConditionFlags( true );

	for( FireFXElement *e = data->m_fireFXListBegin; e != data->m_fireFXListEnd; )
	{
		FireFXElement elem = *e;
		if( elem.boneName.isNotEmpty() )
		{
			if( getObject()->getDrawable() )
			{
				Matrix3D boneTransform;
				boneTransform.Make_Identity();
				getObject()->getDrawable()->getCurrentWorldspaceClientBonePositions( elem.boneName.str(), boneTransform );

				Coord3D pos;
				pos.x = boneTransform.Get_X_Translation();
				pos.y = boneTransform.Get_Y_Translation();
				pos.z = boneTransform.Get_Z_Translation();

				FXList::doFXPos(elem.fx, &pos, &boneTransform, 0.0f, 0);
                goto next;
			}
		}
		Object *obj = getObject();
        FXList::doFXObj(elem.fx, obj, 0);
	next: ;
		// Retail steps the cursor at +030f, ahead of the element destructor
		// at +0326, so the step is the last statement of the body rather
		// than the for-increment.
		++e;
	}

	if( data->m_extra0 > 0 )
	{
		// The +0x1DC member is a two-argument pointer tail thunk: the call
		// hands it this, and the thunk loads its stored receiver itself.
		reinterpret_cast<Rva001BE220Receiver *>(me)->dispatch( data->m_damageType, data->m_extra0 );
		me->setDisabledUntil( (DisabledType)4, TheBfmeGameLogic->m_frame + data->m_extra0 - 1 );
		m_field44 = TheBfmeGameLogic->m_frame + data->m_extra0;
		me->setStatusBit( 0x51, true );
	}
	else
	{
		m_field44 = TheBfmeGameLogic->m_frame;
	}

	setWakeFrame( getObject(), (UpdateSleepTime)1 );
}
