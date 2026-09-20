// cl: /DNDEBUG /MD /EHsc
// ProductionSpeedBonus::doSpecialPower at retail 0x002645D0, 144 bytes.
//
// The constructor installs the ProductionSpeedBonus vtables immediately before
// this body.  Slot 11 of its SpecialPowerModuleInterface vtable reaches this
// RVA, while slot 13 reaches doSpecialPowerAtLocation.  The module-data ctor
// independently fixes the fields at +0x210/+0x214/+0x218, and Object's layout
// witness fixes m_disabledMask at +0x1A4.

typedef unsigned int UnsignedInt;

class AsciiString { private: void *m_data; };

class Rva00010A23Target
{
public:
	void rva00010a23( void *key, float value1, int value2 );
};

class Player;

class Object
{
public:
	Player *getControllingPlayer() const;

	unsigned char m_pad00[ 0x38 ];
	float m_position[ 3 ];
	unsigned char m_pad44[ 0x160 ];
	UnsignedInt m_disabledMask;
};

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

extern const double g_bfmeSubB3;
extern const double Rva002645D0NegativeOne;

void ProductionSpeedBonus::doSpecialPower( UnsignedInt commandOptions )
{
	const char *self = reinterpret_cast<const char *>( this );
	Object *object = *reinterpret_cast<Object *const *>( self - 8 );
	ProductionSpeedBonusModuleData *data =
		*reinterpret_cast<ProductionSpeedBonusModuleData *const *>( self - 12 );
	Rva00010A23Target *player = reinterpret_cast<Rva00010A23Target *>(
		object->getControllingPlayer() );

	for( AsciiString *it = data->m_upgradeTypesBegin;
		it != data->m_upgradeTypesEnd; ++it )
	{
		player->rva00010a23( it,
			static_cast<float>(
				( static_cast<double>( data->m_duration ) - g_bfmeSubB3 ) /
				( static_cast<double>( data->m_duration ) * Rva002645D0NegativeOne ) ),
			data->m_bonusPercent );
	}

	if( object->m_disabledMask == 0 )
		doSpecialPowerAtLocation( object->m_position, commandOptions );
}
