// ?isPendingObjectUnavailable@CastleBehavior@@QBE_NXZ
// partial score=0.99 date=2026-09-02
// ?isPendingObjectUnavailable@CastleBehavior@@QBE_NXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX

typedef bool Bool;
typedef int ObjectID;
typedef unsigned char Byte;

class ModelConditionFlags
{
public:
	char test(int condition) const;
};

union CastleObjectStatus
{
	unsigned int value;
	struct
	{
		unsigned char byte0;
		signed char byte1;
		unsigned char byte2;
		unsigned char byte3;
	};
};

class Object
{
public:
	unsigned char m_unmodelled_000[0x110];
	ModelConditionFlags m_modelConditions;
	unsigned char m_unmodelled_111[0x118 - 0x111];
	unsigned char m_modelConditionByte8;
	unsigned char m_unmodelled_119[0x128 - 0x119];
	unsigned int m_status;
	unsigned char m_unmodelled_12c[0x344 - 0x12c];
	unsigned char m_destroyedFlags;
};

class GameLogic
{
public:
	Object *findCastleObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class CastleBehavior
{
public:
	Bool isPendingObjectUnavailable() const;

private:
	unsigned char m_unmodelled_00[0x14];
	ObjectID m_pendingObjectID;
};

Bool CastleBehavior::isPendingObjectUnavailable() const
{
	Object *object = TheGameLogic->findCastleObjectByID(m_pendingObjectID);
	if (object)
	{
		if (!(object->m_destroyedFlags & 1))
		{
			CastleObjectStatus status;
			status.value = object->m_status;
			if (!(status.value & 0x00010000))
			{
				if (status.byte1 >= 0)
				{
					if (!(object->m_modelConditionByte8 & 0x10))
					{
						Bool unavailable = object->m_modelConditions.test(61);
						return unavailable;
					}
				}
			}
		}
	}

	return true;
}
