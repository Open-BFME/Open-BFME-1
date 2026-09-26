// cl: /EHsc-
// Open-BFME: SiegeEngineContain::isValidContainerFor, retail 0x0022BF30.

typedef bool Bool;
typedef int Int;

class Player;

class ObjectStatusMaskType
{
public:
	unsigned int m_words[6];

	Bool test(unsigned int bit) const
	{
		return (m_words[bit >> 5] & (1U << (bit & 31))) != 0;
	}
};

class Object
{
public:
	unsigned char m_unmodelled_000[0x90];
	ObjectStatusMaskType m_status;
	unsigned int isKindOf(unsigned int mask) const
	{
		return m_status.m_words[1] & mask;
	}
	Player *getControllingPlayer() const;
};

class Rva2225E0Filter
{
public:
	Bool accepts(Object *object, Player *player);
};

class SiegeEngineContainModuleData
{
public:
	unsigned char m_unmodelled_000[0x224];
	Rva2225E0Filter m_containFilter;
	Int m_slotCapacity;
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
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual Bool isValidContainerFor(const Object *object, Bool checkCapacity) const = 0;
};

class TransportContain
{
public:
	virtual Bool isValidContainerFor(const Object *object, Bool checkCapacity) const;
};

class SiegeEngineContain : public TransportContain
{
public:
	virtual Bool isValidContainerFor(const Object *object, Bool checkCapacity) const;

	SiegeEngineContainModuleData *getModuleData() const
	{
		return *(SiegeEngineContainModuleData *const *)((const char *)this - 0x1c);
	}

	Object *getObject() const
	{
		return *(Object *const *)((const char *)this - 0x18);
	}

};

// ?isValidContainerFor@SiegeEngineContain@@UBE_NPBVObject@@_N@Z
Bool SiegeEngineContain::isValidContainerFor(const Object *object,
	Bool checkCapacity) const
{
	register Object *rider = (Object *)object;
	if (rider->isKindOf(0x20000000))
		return false;

	const Object *owner = getObject();
	register SiegeEngineContainModuleData *data = getModuleData();
      if (data->m_containFilter.accepts(rider,
          owner->getControllingPlayer()))
      {
		Int containMax = data->m_slotCapacity;
		if (containMax > 0)
		{
			if (checkCapacity &&
				*(const unsigned int *)((const char *)this + 0xc8) >=
				(unsigned int)containMax)
			{
				return TransportContain::isValidContainerFor(rider,
					checkCapacity);
			}

			Player *ownerPlayer = getObject()->getControllingPlayer();
			if (rider->getControllingPlayer() != ownerPlayer)
				return TransportContain::isValidContainerFor(rider,
					checkCapacity);

			return true;
		}
	}

	return TransportContain::isValidContainerFor(rider, checkCapacity);
}
