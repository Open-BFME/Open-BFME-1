// cl: /DNDEBUG /MD /EHsc
// ElvenWoodSpecialPower::doSpecialPower (0x0025B920, slot 11) and ::doSpecialPowerAtObject
// (0x0025B8E0, slot 12) of the SpecialPowerModuleInterface table 0x010B4A60, which
// ElvenWoodSpecialPower's registered constructor 0x0025B2B0 stores at +0x10. Each body is
// reached only through its ILT stub (0x00030A26, 0x00008242), and each stub's VA
// appears once in the image. Object::doSpecialPower (0x001C3790) and
// Object::doSpecialPowerAtObject (0x001C37F0) call slots 11 and 12.
// Evidence: targets/game/reverse/identity_evidence/specialpower-slot11-12-dospecialpower.md
//
// Moved from BackPointerGuardedDispatch.cpp with its byte notes. this-8 is the
// Object. Each body returns when the Object's +0x1A4 gate is set (Zero Hour's
// isDisabled()), then calls slot 13 on `this` with a position (the Object's
// +0x38..+0x40 triple, copied one field at a time, or the target's +0x38) and
// commandOptions. Slot 13 keeps its placeholder name `apply`; see the evidence
// note's open question.

typedef unsigned int UnsignedInt;

class Object;

class Rva0025B920Owner
{
public:
	char m_leading[ 0x38 ];
	int m_first;
	int m_second;
	int m_third;
	char m_trailing[ 0x1A4 - 0x44 ];
	int m_gate;
};

class Rva0025B920Triple
{
public:
	int m_first;
	int m_second;
	int m_third;
};

class Rva0025B8E0Owner
{
public:
	char m_leading[ 0x1A4 ];
	int m_gate;
};

struct Rva0025B8E0Part
{
	int m_word0;
};

class Rva0025B8E0Subject
{
public:
	char m_leading[ 0x38 ];
	Rva0025B8E0Part m_part;
};

class ElvenWoodSpecialPower
{
public:
	virtual void slot00(); virtual void slot04();
	virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24();
	virtual void slot28();
	virtual void doSpecialPower( UnsignedInt commandOptions );
	virtual void doSpecialPowerAtObject( Object *obj, UnsignedInt commandOptions );
	virtual void apply( void *where, UnsignedInt commandOptions );
};

void ElvenWoodSpecialPower::doSpecialPower( UnsignedInt commandOptions )
{
	Rva0025B920Owner *owner = *(Rva0025B920Owner **)( (char *)this - 8 );
	if ( owner->m_gate != 0 )
	{
		return;
	}
	Rva0025B920Triple triple;
	triple.m_first = owner->m_first;
	triple.m_second = owner->m_second;
	triple.m_third = owner->m_third;
	apply( &triple, commandOptions );
}

void ElvenWoodSpecialPower::doSpecialPowerAtObject( Object *obj, UnsignedInt commandOptions )
{
	Rva0025B8E0Owner *owner = *(Rva0025B8E0Owner **)( (char *)this - 8 );
	if ( owner->m_gate != 0 )
	{
		return;
	}
	if ( obj == 0 )
	{
		return;
	}
	apply( &((Rva0025B8E0Subject *)obj)->m_part, commandOptions );
}
