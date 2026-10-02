// cl: /DNDEBUG /MD /EHsc
// OCLSpecialPower::doSpecialPowerAtObject (0x00262D60): slot 12 of the
// SpecialPowerModuleInterface table 0x010B6010, which OCLSpecialPower's registered
// constructor 0x002628E0 stores at +0x10. The body is reached only through ILT
// 0x0001CAEE, whose VA appears once in the image. Object::doSpecialPowerAtObject
// (0x001C37F0) calls slot 12.
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

class Rva00262D60Owner
{
public:
	char m_leading[ 0x1A4 ];
	int m_gate;
};

struct Rva00262D60Part
{
	int m_word0;
};

class Rva00262D60Subject
{
public:
	char m_leading[ 0x38 ];
	Rva00262D60Part m_part;
};

class OCLSpecialPower
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

void OCLSpecialPower::doSpecialPowerAtObject( Object *obj, UnsignedInt commandOptions )
{
	Rva00262D60Owner *owner = *(Rva00262D60Owner **)( (char *)this - 8 );
	if ( owner->m_gate != 0 )
	{
		return;
	}
	if ( obj == 0 )
	{
		return;
	}
	apply( &((Rva00262D60Subject *)obj)->m_part, commandOptions );
}
