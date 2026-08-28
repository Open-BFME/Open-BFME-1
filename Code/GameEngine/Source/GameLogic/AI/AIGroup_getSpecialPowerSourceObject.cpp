// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AIGroup::getSpecialPowerSourceObject, retail 0x001513D0, 77 bytes.
//
// The reference's body unchanged: look the template up by id, then hand back
// the first member that has a special power module for it.
//
// m_memberList is at this+0x04, the same STLport sentinel walk the two
// groupDoCommandButton loops measured, payload at node+0x08.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef unsigned int UnsignedInt;

class SpecialPowerTemplate;
class SpecialPowerModuleInterface;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *spTemplate) const;	// ILT 0x000401BF
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplateByID(UnsignedInt id);	// ILT 0x000034B8
};

extern SpecialPowerStore *TheSpecialPowerStore;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	Object *getSpecialPowerSourceObject(UnsignedInt specialPowerID);

private:
	unsigned char m_unmodelled_000[4];			// this+0x00, untouched
	_STL::list<Object *> m_memberList;			// this+0x04
};

Object *AIGroup::getSpecialPowerSourceObject( UnsignedInt specialPowerID )
{
	_STL::list<Object *>::iterator i;
	const SpecialPowerTemplate *spTemplate = TheSpecialPowerStore->findSpecialPowerTemplateByID( specialPowerID );
	if( spTemplate )
	{
		for( i = m_memberList.begin(); i != m_memberList.end(); ++i )
		{
			Object *object = (*i);
			SpecialPowerModuleInterface *mod = object->getSpecialPowerModule( spTemplate );
			if( mod )
				return object;
		}
	}
	return 0;
}
