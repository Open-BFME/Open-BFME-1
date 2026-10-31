// cl: /O2

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#include <math.h>

class Object;

class AsciiString
{
public:
	char *m_text;

	__forceinline Bool isEmpty() const
	{
		return m_text == 0 || *(const unsigned short *)(m_text + 4) == 0;
	}
};

#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

static __forceinline void setCoord3D(Coord3D &value, const Coord3D *other)
{
	value.x = other->x;
	value.y = other->y;
	value.z = other->z;
}

static __forceinline void subCoord3D(Coord3D &value, const Coord3D *other)
{
	value.x -= other->x;
	value.y -= other->y;
	value.z -= other->z;
}

static __forceinline Real coord3DLength(const Coord3D &value)
{
	return (Real)sqrt(value.x * value.x + value.y * value.y + value.z * value.z);
}

class AudioEventRTS
{
public:
	void setObjectID(UnsignedInt objectID);
	void setPlayingHandle(UnsignedInt handle);

	char m_pad00[0x14];
	AsciiString m_eventName;
};

class ResourceGatheringManager
{
public:
	Object *findBestSupplyWarehouse(Object *worker);
};

class Player
{
public:
	char m_pad00[0x228];
	ResourceGatheringManager *m_resourceGatheringManager;
};

class Object
{
public:
	Player *getControllingPlayer() const;

	inline const Coord3D *getPosition() const
	{
		return (const Coord3D *)((const char *)this + 0x38);
	}

	inline UnsignedInt getID() const
	{
		return *(const UnsignedInt *)((const char *)this + 0x74);
	}
};

class AudioManager
{
public:
	virtual void pad00();
	virtual void pad04();
	virtual void pad08();
	virtual void pad0c();
	virtual void pad10();
	virtual void pad14();
	virtual void pad18();
	virtual void pad1c();
	virtual void pad20();
	virtual void pad24();
	virtual void pad28();
	virtual void pad2c();
	virtual void pad30();
	virtual void pad34();
	virtual void pad38();
	virtual void pad3c();
	virtual void pad40();
	virtual UnsignedInt addAudioEvent(const AudioEventRTS *eventToAdd);
};

extern AudioManager *TheAudio;

class BfmeSinkRM
{
public:
	void bfmeSendRM(void *what, Int many);
};

class WorkerAIUpdateModuleData
{
public:
	char m_pad00[0x64];
	Int m_maxBoxesData;
};

class WorkerAIUpdate
{
public:
	virtual void pad00();
	virtual void pad04();
	virtual void pad08();
	virtual void pad0c();
	virtual void pad10();
	virtual void pad14();
	virtual void pad18();
	virtual void pad1c();
	virtual void pad20();
	virtual void pad24();
	virtual Real getWarehouseScanDistance() const;
	virtual Bool gainOneBox(Int remainingStock);

	char m_pad00[0xb4];
	Int m_numberBoxes;
	char m_padc0[0x98];
	AudioEventRTS m_suppliesDepletedVoice;

	inline Object *getObject() const
	{
		return *(Object **)((char *)this - 0x33c);
	}
};

extern void j_00040a52();

Bool WorkerAIUpdate::gainOneBox(Int remainingStock)
{
	WorkerAIUpdateModuleData *moduleData = *(WorkerAIUpdateModuleData **)((char *)this - 0x340);
	if (moduleData && m_numberBoxes >= moduleData->m_maxBoxesData)
		return false;

	++m_numberBoxes;
	if (remainingStock == 0)
	{
		Object *object = getObject();
		Player *player = object->getControllingPlayer();
		ResourceGatheringManager *manager = player->m_resourceGatheringManager;
		Object *bestWarehouse = manager->findBestSupplyWarehouse(object);
		Bool playDepleted = false;
		if (bestWarehouse)
		{
			Coord3D delta;
			setCoord3D(delta, getObject()->getPosition());
			subCoord3D(delta, bestWarehouse->getPosition());
			if (coord3DLength(delta) > getWarehouseScanDistance() / 4)
				playDepleted = true;
		}
		else
			playDepleted = true;

		if (playDepleted && m_suppliesDepletedVoice.m_eventName.isEmpty() == false)
		{
			m_suppliesDepletedVoice.setObjectID(getObject()->getID());
			{
				typedef void (AudioEventRTS::*SetPlayingHandle)(UnsignedInt);
				union
				{
					void (*fn)();
					SetPlayingHandle call;
				} u = { j_00040a52 };
				(m_suppliesDepletedVoice.*u.call)(TheAudio->addAudioEvent(&m_suppliesDepletedVoice));
			}
		}
	}

	((BfmeSinkRM *)*(Object **)((char *)this - 0x33c))->bfmeSendRM(
		(void *)((WorkerAIUpdateModuleData *)*(WorkerAIUpdateModuleData **)((char *)this - 0x340))->m_maxBoxesData,
		m_numberBoxes);
	return true;
}
