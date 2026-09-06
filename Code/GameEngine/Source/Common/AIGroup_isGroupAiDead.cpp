// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
// Grok promote from masm_dumps — retail 0x00151390 size 50
// was: Code/masm_dumps/_cache__isGroupAiDead_AIGroup__QBE_NXZ_151390.asm
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Bool isEffectivelyDead() const { return (m_privateStatus & EFFECTIVELY_DEAD) != 0; }

private:
	enum ObjectPrivateStatusBits { EFFECTIVELY_DEAD = (1 << 0) };

	// BFME grew Object past ZH's layout: m_privateStatus sits at +0x344 here, not +0x297.
	unsigned char m_pad_000[0x344];
	unsigned char m_privateStatus;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	Bool isGroupAiDead(void) const;

private:
	unsigned char m_unmodelled_000[4];			// this+0x00, untouched
	_STL::list<Object *> m_memberList;			// this+0x04
};

// ?isGroupAiDead@AIGroup@@QBE_NXZ
Bool AIGroup::isGroupAiDead( void ) const
{
	Bool isDead = true;
	_STL::list<Object *>::const_iterator i;
	for( i = m_memberList.begin(); i != m_memberList.end(); ++i )
	{
		Object *obj = *i;
		if (!obj) {
			continue;
		}

		isDead = (isDead && obj->isEffectivelyDead());
	}

	return isDead;
}
