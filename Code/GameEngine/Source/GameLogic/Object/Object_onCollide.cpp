// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/bfmeobjectlayout /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#include "PreRTS.h"
#include "GameLogic/Object.h"

void Object::onCollide( Object *other, const Coord3D *loc, const Coord3D *normal )
{
	struct BFMEObjectOnCollideFields
	{
		unsigned char m_pad000[0x74];
		UnsignedInt m_id;
		unsigned char m_pad078[0x18];
		UnsignedByte m_status90;
		unsigned char m_pad091[0x15f];
		void *const *m_behaviors;
		unsigned char m_pad1f4[0x1ac];
		UnsignedInt m_field3a0;
	};
	struct BFMECollideModuleInterface
	{
		virtual void onCollide( Object *, const Coord3D *, const Coord3D * ) = 0;
	};
	struct BFMEBehaviorModuleInterface
	{
		virtual void slot00() = 0;
		virtual BFMECollideModuleInterface *getCollide() = 0;
	};

	BFMEObjectOnCollideFields *self =
		reinterpret_cast<BFMEObjectOnCollideFields *>( this );
	BFMEObjectOnCollideFields *otherFields =
		reinterpret_cast<BFMEObjectOnCollideFields *>( other );
	if (other == NULL)
		return;
	if (self->m_field3a0 == otherFields->m_id)
		return;
	if (otherFields->m_field3a0 != 0 && self->m_id != 0)
		return;

	for (void *const *m = self->m_behaviors; *m; ++m)
	{
		char *adjusted = reinterpret_cast<char *>( *m ) + 0xc;
		BFMECollideModuleInterface *collide =
			reinterpret_cast<BFMEBehaviorModuleInterface *>( adjusted )->getCollide();
		if (!collide)
			continue;

		if( (self->m_status90 & 0x10) != 0 )
			break;

		collide->onCollide( other, loc, normal );
	}
}
