// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#include <bitset>
#include <list>

typedef bool Bool;
typedef unsigned int UnsignedInt;

class Drawable;
class PickAndPlayInfo;

template <int NUM_BITS>
class BitFlags
{
public:
	BitFlags()
	{
	}

	void set( int condition )
	{
		m_bits.set( condition );
	}

private:
	_STL::bitset<NUM_BITS> m_bits;
};

typedef BitFlags<320> ModelConditionFlags;

class Object
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual Drawable *getDrawable();

	Bool testWeaponBonusCondition( int condition ) const
	{
		return ( ( m_weaponBonusCondition >> condition ) & 1 ) != 0;
	}

	void setWeaponBonusCondition( int condition )
	{
		m_weaponBonusCondition |= 1U << condition;
	}

	void clearWeaponBonusCondition( int condition )
	{
		m_weaponBonusCondition &= ~( 1U << condition );
	}

	void clearAndSetModelConditionFlags( const ModelConditionFlags &clear,
		const ModelConditionFlags &set );

private:
	unsigned char m_unmodelled_004[ 0x29C ];
	UnsignedInt m_weaponBonusCondition;
};

typedef _STL::list<Drawable *> DrawableList;

class GameMessage
{
public:
	enum Type
	{
		MSG_RAPID_FIRE = 0x7DC
	};
};

void pickAndPlayUnitVoiceResponse( const DrawableList *list,
	GameMessage::Type messageType, PickAndPlayInfo *info );

enum WeaponBonusCondition
{
	WEAPONBONUSCONDITION_CONTINUOUS_FIRE_MEAN = 2,
	WEAPONBONUSCONDITION_CONTINUOUS_FIRE_FAST = 3
};

enum ModelCondition
{
	MODELCONDITION_CONTINUOUS_FIRE_SLOW = 108,
	MODELCONDITION_CONTINUOUS_FIRE_MEAN = 109,
	MODELCONDITION_CONTINUOUS_FIRE_FAST = 110
};

class FiringTracker
{
private:
	void speedUp();

	unsigned char m_unmodelled_000[ 8 ];
	Object *m_object;
};

void FiringTracker::speedUp()
{
	ModelConditionFlags clr, set;
	Object *self = m_object;

	if( self->testWeaponBonusCondition( WEAPONBONUSCONDITION_CONTINUOUS_FIRE_FAST ) )
	{
	}
	else if( self->testWeaponBonusCondition( WEAPONBONUSCONDITION_CONTINUOUS_FIRE_MEAN ) )
	{
		DrawableList list;
		list.push_back( self->getDrawable() );
		pickAndPlayUnitVoiceResponse( &list, GameMessage::MSG_RAPID_FIRE, 0 );

		self->setWeaponBonusCondition( WEAPONBONUSCONDITION_CONTINUOUS_FIRE_FAST );
		set.set( MODELCONDITION_CONTINUOUS_FIRE_FAST );

		self->clearWeaponBonusCondition( WEAPONBONUSCONDITION_CONTINUOUS_FIRE_MEAN );
		clr.set( MODELCONDITION_CONTINUOUS_FIRE_MEAN );
		clr.set( MODELCONDITION_CONTINUOUS_FIRE_SLOW );
	}
	else
	{
		self->setWeaponBonusCondition( WEAPONBONUSCONDITION_CONTINUOUS_FIRE_MEAN );
		set.set( MODELCONDITION_CONTINUOUS_FIRE_MEAN );

		self->clearWeaponBonusCondition( WEAPONBONUSCONDITION_CONTINUOUS_FIRE_FAST );
		clr.set( MODELCONDITION_CONTINUOUS_FIRE_FAST );
		clr.set( MODELCONDITION_CONTINUOUS_FIRE_SLOW );
	}

	self->clearAndSetModelConditionFlags( clr, set );
}
