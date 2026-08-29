// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned int ObjectID;

struct DamageInfo
{
	unsigned char m_prefix[8];
	ObjectID m_sourceID;
};

class BfmeDamageRedirect
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34();
	virtual Bool getRecentDamageSource(ObjectID *sourceID, UnsignedInt frames) const;
};

class ContainModuleInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	virtual BfmeDamageRedirect *getDamageRedirect() const;
};

class BodyModuleInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual const DamageInfo *getLastDamageInfo() const;
	virtual UnsignedInt getLastDamageTimestamp() const;
};

class GameLogic
{
public:
	unsigned char m_prefix[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

class Object
{
public:
	Bool bfmeGetRecentDamageSource(ObjectID *sourceID, UnsignedInt seconds) const;

private:
	unsigned char m_prefix[0x1fc];
	ContainModuleInterface *m_contain;
	BodyModuleInterface *m_body;
};

Bool Object::bfmeGetRecentDamageSource(ObjectID *sourceID, UnsignedInt seconds) const
{
	ContainModuleInterface *contain = m_contain;
	const UnsignedInt frames = seconds * 5;
	if (contain)
	{
		BfmeDamageRedirect *redirect = contain->getDamageRedirect();
		if (redirect)
			return redirect->getRecentDamageSource(sourceID, frames);
	}

	BodyModuleInterface *body = m_body;
	if (body)
	{
		const UnsignedInt lastDamageFrame = body->getLastDamageTimestamp();
		if (lastDamageFrame != static_cast<UnsignedInt>(-1) &&
			lastDamageFrame + frames >= TheGameLogic->m_frame)
		{
			const DamageInfo *info = body->getLastDamageInfo();
			if (info)
				*sourceID = info->m_sourceID;
			return true;
		}
	}

	return false;
}
