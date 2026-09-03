// ?isPendingObjectUnavailable@CastleBehavior@@QBE_NXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX

typedef bool Bool;
typedef int ObjectID;

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

void j_0000666d();

class ModelConditionFlags
{
private:
	unsigned char m_words[8];

public:
	typedef unsigned char (ModelConditionFlags::*TestMethod)(unsigned int) const;

	unsigned char test(unsigned int condition) const
	{
		union { void *asVoid; TestMethod asMember; } testCast;
		testCast.asVoid = (void *)j_0000666d;
		return (this->*testCast.asMember)(condition);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
private:
	unsigned char m_pad000[0x110];
	ModelConditionFlags m_modelConditions;
	unsigned char m_modelConditionByte8;
	unsigned char m_pad119[0x128 - 0x119];
	unsigned int m_status;
	unsigned char m_pad12c[0x344 - 0x12c];
	unsigned char m_destroyedFlags;

public:
	ModelConditionFlags *modelConditions()
	{
		return &m_modelConditions;
	}

	unsigned char modelConditionByte8() const
	{
		return m_modelConditionByte8;
	}

	unsigned int status() const
	{
		return m_status;
	}

	unsigned char destroyedFlags() const
	{
		return m_destroyedFlags;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheBfmeGameLogic;

class CastleBehavior
{
public:
	Bool isPendingObjectUnavailable() const;

private:
	unsigned char m_pad00[0x14];
	ObjectID m_pendingObjectID;
};

Bool CastleBehavior::isPendingObjectUnavailable() const
{
	Object *object = TheBfmeGameLogic->findObjectByID(m_pendingObjectID);
	if (object)
	{
		if (!(object->destroyedFlags() & 1))
		{
			CastleObjectStatus status;
			status.value = object->status();
			if (!(status.value & 0x00010000))
			{
				if (status.byte1 & 0x80)
					return true;

				if (!(object->modelConditionByte8() & 0x10))
				{
					Bool unavailable = object->modelConditions()->test(61) != 0;
					return unavailable;
				}
			}
		}
	}

	return true;
}
