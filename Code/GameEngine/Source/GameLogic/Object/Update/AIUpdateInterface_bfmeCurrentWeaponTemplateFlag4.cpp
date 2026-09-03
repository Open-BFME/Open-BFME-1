// cl: /DNDEBUG /MD
//
// Retail 0x00278790: AIUpdateInterface query. Object status 0x400000 at +0x90,
// then Object::getCurrentWeapon(0) and bit 4 of WeaponTemplate +0x4D4.

typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class WeaponTemplate
{
public:
	unsigned char m_unmodelled_00[0x4D4];
	unsigned char m_bit0 : 1;
	unsigned char m_bit1 : 1;
	unsigned char m_bit2 : 1;
	unsigned char m_bit3 : 1;
	unsigned char m_bit4 : 1;
};

class BfmeXCLE
{
public:
	const WeaponTemplate *getTemplate() const { return m_template; }

private:
	void *m_vtable;
	const WeaponTemplate *m_template;
};

class BfmeSubCLE
{
public:
	BfmeXCLE *bfmeAskCLE(int);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public BfmeSubCLE
{
public:
	unsigned char m_unmodelled_00[0x90];
	unsigned int m_status;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	virtual Bool bfmeCurrentWeaponTemplateFlag4() const;

private:
	unsigned char m_unmodelled_04[4];
	Object *m_object;
};

Bool AIUpdateInterface::bfmeCurrentWeaponTemplateFlag4() const
{
	Object *obj = m_object;
	if ((obj->m_status & 0x400000) == 0)
		return false;
	else
	{
		BfmeXCLE *weapon = obj->bfmeAskCLE(0);
		if (!weapon)
			return false;
		return weapon->getTemplate()->m_bit4;
	}
}
