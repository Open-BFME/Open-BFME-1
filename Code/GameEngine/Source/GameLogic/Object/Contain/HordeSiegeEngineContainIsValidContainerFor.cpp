// Open-BFME: HordeSiegeEngineContain::isValidContainerFor at retail 0x0024A840.
// The method occupies slot 33 in the class vtable installed at object offset
// +0x20. The module-data filter and capacity sit at +0x224 and +0x228.

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

class HordeSiegeEngineContainModuleData
{
public:
	unsigned char m_unmodelled_000[0x224];
	Rva2225E0Filter m_containFilter;
	Int m_slotCapacity;
};

class TransportContain
{
public:
	virtual Bool isValidContainerFor(const Object *object, Bool checkCapacity) const;
};

class HordeTransportContain : public TransportContain
{
public:
	virtual Bool isValidContainerFor(const Object *object, Bool checkCapacity) const;
};

class HordeSiegeEngineContain : public HordeTransportContain
{
public:
	virtual Bool isValidContainerFor(const Object *object, Bool checkCapacity) const;

	HordeSiegeEngineContainModuleData *getModuleData() const
	{
		return *(HordeSiegeEngineContainModuleData *const *)((const char *)this - 0x1c);
	}

	Object *getObject() const
	{
		return *(Object *const *)((const char *)this - 0x18);
	}
};

#pragma comment(linker, "/alternatename:?getControllingPlayer@Object@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ")

// ?isValidContainerFor@HordeSiegeEngineContain@@UBE_NPBVObject@@_N@Z
Bool HordeSiegeEngineContain::isValidContainerFor(const Object *object,
	Bool checkCapacity) const
{
	register Object *rider = (Object *)object;
	if (rider->isKindOf(0x20000000))
		return false;

	const Object *owner = getObject();
	HordeSiegeEngineContainModuleData *data = getModuleData();
	if (data->m_containFilter.accepts(rider,
		owner->getControllingPlayer()))
	{
		Int containMax = data->m_slotCapacity;
		if (containMax > 0)
		{
			switch (checkCapacity)
			{
			case false:
				goto sameOwner;
			default:
				if (*(const unsigned int *)((const char *)this + 0xd0) <
					(unsigned int)containMax)
					goto sameOwner;
			}

			return TransportContain::isValidContainerFor(rider, checkCapacity);

		sameOwner:
			Player *ownerPlayer = getObject()->getControllingPlayer();
			if (rider->getControllingPlayer() != ownerPlayer)
				return TransportContain::isValidContainerFor(rider, checkCapacity);
			return true;
		}
	}

	return HordeTransportContain::isValidContainerFor(rider, checkCapacity);
}
