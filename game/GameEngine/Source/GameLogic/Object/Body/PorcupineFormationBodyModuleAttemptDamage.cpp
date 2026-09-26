// cl: /DNDEBUG /MD /EHsc

class DamageInfo;

typedef unsigned char Bool;

class PorcupineDamageCheckResult
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
	virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual void slot39(); virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43(); virtual void slot44();
	virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50();
	virtual void slot51(); virtual void slot52(); virtual void slot53();
	virtual void slot54(); virtual Bool slot55();
};

class PorcupineDamageCheckResultSource
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
	virtual PorcupineDamageCheckResult *getResult();
};

class PorcupineDamageCheck
{
public:
	unsigned char m_data[0x1fc];
	PorcupineDamageCheckResultSource *m_resultSource;
};

class Object
{
public:
	unsigned char m_data[0x214];
	PorcupineDamageCheck *m_damageCheck;
};

class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

protected:
	unsigned int m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class BodyModuleInterface
{
public:
	virtual void attemptDamage(DamageInfo *);
};

class PorcupineFormationBodyModule : public BehaviorModule,
	public BehaviorModuleInterface,
	public BodyModuleInterface
{
public:
	virtual void attemptDamage(DamageInfo *damageInfo);
};

class PorcupineDamageHelper
{
public:
	void apply(DamageInfo *);
};

// ?attemptDamage@PorcupineFormationBodyModule@@UAEXPAVDamageInfo@@@Z
void PorcupineFormationBodyModule::attemptDamage(DamageInfo *damageInfo)
{
	Object *object = m_object;
	PorcupineDamageCheckResult *result = 0;
	if (object != 0)
	{
		PorcupineDamageCheck *check = object->m_damageCheck;
		if (check != 0)
		{
			PorcupineDamageCheckResultSource *source = check->m_resultSource;
			if (source != 0)
				result = source->getResult();
		}
	}

	if (result == 0)
		goto fallback;
	if (!result->slot55())
		goto fallback;
	{
		PorcupineDamageHelper *helper = (PorcupineDamageHelper *)this;
		helper->apply(damageInfo);
		goto finish;
	}
fallback:
	{
		BodyModuleInterface *base = (BodyModuleInterface *)((char *)this + 0x10);
		base->BodyModuleInterface::attemptDamage(damageInfo);
		return;
	}
finish:
	{
		BodyModuleInterface *base = (BodyModuleInterface *)((char *)this + 0x10);
		base->BodyModuleInterface::attemptDamage(damageInfo);
	}
}
