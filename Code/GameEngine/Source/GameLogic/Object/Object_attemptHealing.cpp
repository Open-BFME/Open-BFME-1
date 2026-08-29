// cl: /DNDEBUG /MD /EHsc
// readable body of ?attemptHealing@Object@@QAEXMPBV1@@Z: Code/GameEngine/Source/GameLogic/Object/Object.cpp

typedef unsigned int ObjectID;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
class DamageInfo
{
public:
	DamageInfo();

	unsigned char m_00[0x08];
	ObjectID m_sourceID;
	unsigned char m_0C[0x04];
	int m_damageType;
	unsigned char m_14[0x04];
	int m_deathType;
	float m_amount;
	unsigned char m_20[0x3C];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h
class BodyModuleInterface
{
public:
	virtual void bodyAnchor();
	virtual void attemptHealing(DamageInfo *damageInfo);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void attemptHealing(float amount, const Object *source);
	ObjectID getID() const
	{
		return *reinterpret_cast<const ObjectID *>(reinterpret_cast<const char *>(this) + 0x74);
	}

private:
	unsigned char m_000[0x200];
	BodyModuleInterface *m_body;
};

void Object::attemptHealing(float amount, const Object *source)
{
	BodyModuleInterface *body = m_body;
	if (body)
	{
		DamageInfo damageInfo;
		damageInfo.m_damageType = 7;
		damageInfo.m_deathType = 1;
		damageInfo.m_sourceID = source ? source->getID() : 0;
		damageInfo.m_amount = amount;
		body->attemptHealing(&damageInfo);
	}
}
