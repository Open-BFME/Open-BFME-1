// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// ProductionSpeedBonus::doSpecialPower at retail 0x002645D0, 144 bytes.
//
// The constructor installs the ProductionSpeedBonus vtables immediately before
// this body.  Slot 11 of its SpecialPowerModuleInterface vtable reaches this
// RVA, while slot 13 reaches doSpecialPowerAtLocation.  The module-data ctor
// independently fixes the fields at +0x210/+0x214/+0x218, and Object's layout
// witness fixes m_disabledMask at +0x1A4.

typedef unsigned int UnsignedInt;

#include "ascii_string.h"

// ILT 0x00010A23 reaches setMaps at 0x000D9F50; its values are raw dwords.
class BfmeThingEZC
{
public:
	void setMaps( void *key, void *value1, void *value2 );
};

class Player;

#define OBJECT_TU_MEMBERS Player *getControllingPlayer() const;
#include "../object.h"
#undef OBJECT_TU_MEMBERS

struct ProductionSpeedBonusModuleData
{
	unsigned char m_pad00[ 0x210 ];
	UnsignedInt m_bonusPercent;
	float m_duration;
	AsciiString *m_upgradeTypesBegin;
	AsciiString *m_upgradeTypesEnd;
	AsciiString *m_upgradeTypesCapacity;
};

class ProductionSpeedBonus
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot0A() = 0;
	virtual void doSpecialPower( UnsignedInt commandOptions );
	virtual void slot0C() = 0;
	virtual void doSpecialPowerAtLocation( const float *position,
		UnsignedInt commandOptions ) = 0;
};

void ProductionSpeedBonus::doSpecialPower( UnsignedInt commandOptions )
{
	const char *self = reinterpret_cast<const char *>( this );
	Object *object = *reinterpret_cast<Object *const *>( self - 8 );
	ProductionSpeedBonusModuleData *data =
		*reinterpret_cast<ProductionSpeedBonusModuleData *const *>( self - 12 );
	BfmeThingEZC *player = reinterpret_cast<BfmeThingEZC *>(
		object->getControllingPlayer() );

	for( AsciiString *it = data->m_upgradeTypesBegin;
		it != data->m_upgradeTypesEnd; ++it )
	{
		// Preserve the float argument's bits for the pointer-spelled map ABI.
		// The double literals use retail's pooled constants at 0x0107C640/0x01095F18.
		(player->*reinterpret_cast<void (BfmeThingEZC::*)(void *, float, int)>(
			&BfmeThingEZC::setMaps))( it,
			static_cast<float>(
				( static_cast<double>( data->m_duration ) - 1.0 ) /
				( static_cast<double>( data->m_duration ) * -1.0 ) ),
			data->m_bonusPercent );
	}

	if( object->m_disabledMask == 0 )
		doSpecialPowerAtLocation( object->m_cachedPos, commandOptions );
}
