// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <bitset>

typedef bool Bool;
typedef unsigned int UnsignedInt;

template <int NUMBITS>
class BitFlags
{
	_STL::bitset<NUMBITS> m_bits;
	static const char *s_bitNameList[];

public:
	BitFlags();
	Bool any() const;
	Bool testForAny( const BitFlags &other ) const;
	Bool testForNone( const BitFlags &other ) const;
	Bool testForAll( const BitFlags &other ) const;
};

template <int NUMBITS>
BitFlags<NUMBITS>::BitFlags()
{
}

template <int NUMBITS>
Bool BitFlags<NUMBITS>::any() const
{
	return m_bits.any();
}

template <int NUMBITS>
Bool BitFlags<NUMBITS>::testForAny( const BitFlags &other ) const
{
	return m_bits.any() && other.m_bits.any();
}

template <int NUMBITS>
Bool BitFlags<NUMBITS>::testForNone( const BitFlags &other ) const
{
	return !m_bits.any() || !other.m_bits.any();
}

template <int NUMBITS>
Bool BitFlags<NUMBITS>::testForAll( const BitFlags &other ) const
{
	return m_bits.any() && other.m_bits.any();
}

typedef BitFlags<192> UpgradeMaskType;

class DelayedUpgradeUpdateInterface
{
public:
	virtual Bool isTriggeredBy( const UpgradeMaskType &potentialMask );
	virtual void setDelay( UnsignedInt startingDelay );
};

class BehaviorModuleInterface
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual DelayedUpgradeUpdateInterface *getDelayedUpgradeUpdateInterface();
};

class ModuleData
{
};

class Object;

class ObjectModule
{
public:
	virtual void objectModuleAnchor();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class Object
{
public:
	BehaviorModule **getBehaviorModules() const
	{
		return m_behaviorModules;
	}

private:
	unsigned char m_padding[0x1f0];
	BehaviorModule **m_behaviorModules;
};

class UpgradeMuxView
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void getUpgradeActivationMasks( UpgradeMaskType &activation,
		UpgradeMaskType &conflicting ) const;
};

class DelayedUpgrade
{
protected:
	virtual void upgradeImplementation();
};

// ?upgradeImplementation@DelayedUpgrade@@MAEXXZ
void DelayedUpgrade::upgradeImplementation()
{
	UnsignedInt delay = *reinterpret_cast<UnsignedInt *>(
		*reinterpret_cast<unsigned char **>(reinterpret_cast<unsigned char *>(this) - 0xc) + 0x70);
	DelayedUpgradeUpdateInterface *upgradeUpdate = 0;
	Object *me = *reinterpret_cast<Object **>(reinterpret_cast<unsigned char *>(this) - 8);

	UpgradeMaskType activation, conflicting;
	UpgradeMuxView *mux = reinterpret_cast<UpgradeMuxView *>(this);
	mux->getUpgradeActivationMasks( activation, conflicting );

	for (BehaviorModule **u = me->getBehaviorModules(); *u; ++u)
	{
		if ((upgradeUpdate = (*u)->getDelayedUpgradeUpdateInterface()) != 0)
		{
			if (upgradeUpdate->isTriggeredBy( activation ))
			{
				upgradeUpdate->setDelay( delay );
			}
		}
	}
}
