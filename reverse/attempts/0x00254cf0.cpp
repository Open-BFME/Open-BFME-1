// ?d_00254cf0@@YAXXZ
// partial score=0.33 date=2026-09-25
// cl: /DNDEBUG /MD /EHsc

enum ObjectID
{
	INVALID_ID = 0
};

class ModuleData;
class Object;
class DamageInfo;

typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Thing
{
public:
	const Coord3D *getUnitDirectionVector2D() const;
};

class GeometryInfo
{
public:
	Real getMajorRadius() const
	{
		return m_majorRadius;
	}

private:
	char m_padding[0x10];
	Real m_majorRadius;
};

class AsciiString
{
public:
	AsciiString();
	AsciiString(const AsciiString &right);
	~AsciiString();
	AsciiString &operator=(const AsciiString &right);

	bool isEmpty() const
	{
		return m_text == 0 || *(const unsigned short *)(m_text + 4) == 0;
	}

private:
	char *m_text;
};

class CountedPtr
{
public:
	CountedPtr();
	~CountedPtr();

	void *m_ptr;
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AudioEventRTS &right);
	virtual ~AudioEventRTS();

	const AsciiString &getEventName() const
	{
		return *(const AsciiString *)((const char *)this + 0x14);
	}

	void setObjectID(ObjectID objectID);

private:
	AsciiString m_filenameToLoad;
	CountedPtr m_eventInfo;
	unsigned int m_playingHandle;
	unsigned int m_killThisHandle;
	AsciiString m_eventName;
	AsciiString m_attackName;
	AsciiString m_decayName;
	unsigned int m_pitchShift;
	unsigned int m_volume;
	unsigned int m_timeOfDay;
	unsigned int m_objectID;
	int m_ownerType;
	Coord3D m_position;
	unsigned char m_shouldFade;
	unsigned char m_isLogicalAudio;
	unsigned char m_uninterruptable;
	unsigned char m_flag43;
	unsigned char m_flag44;
	unsigned char m_flag45;
	unsigned char m_flag46;
	unsigned char m_flag47;
	unsigned char m_flag48;
	unsigned char m_flag49;
	unsigned char m_pad4a[2];
	unsigned int m_float4c;
	unsigned int m_volumeShift;
	unsigned int m_delay;
	unsigned int m_int58;
	unsigned int m_playerIndex;
	unsigned int m_portionToPlayNext;
	unsigned int m_loopCount;
	unsigned int m_int68;
	AsciiString m_tail;
};

class AudioManager;
struct AudioManagerVtable;
typedef void (__fastcall *AddAudioEventCall)(AudioManager *, AudioManagerVtable *,
	const AudioEventRTS *event);

struct AudioManagerVtable
{
	void *slots00_40[17];
	AddAudioEventCall addAudioEvent;
};

class AudioManager
{
};

extern AudioManager *TheAudio;

class DieMuxData
{
public:
	bool isDieApplicable(const Object *object, const DamageInfo *damageInfo) const;

private:
	unsigned char m_data[0x2c];
};

class DieModuleData
{
public:
	unsigned char m_data[8];
	DieMuxData m_dieMuxData;
};

class CrushDieModuleData : public DieModuleData
{
public:
	AudioEventRTS m_crushSounds[4];
	int m_crushSoundPercent[4];
};

class ObjectModule
{
public:
	virtual void objectModuleAnchor();

protected:
	Object *getObject() const
	{
		return m_object;
	}

	const ModuleData *getModuleData() const
	{
		return m_moduleData;
	}

private:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class DieModuleInterface
{
public:
	virtual void dieModuleInterfaceAnchor();
	virtual void onDie(const DamageInfo *damageInfo) = 0;
};

class DieModule : public ObjectModule,
	public BehaviorModuleInterface,
	public DieModuleInterface
{
public:
	const DieModuleData *getDieModuleData() const
	{
		return (const DieModuleData *)getModuleData();
	}

	bool isDieApplicable(const DamageInfo *damageInfo) const
	{
		return getDieModuleData()->m_dieMuxData.isDieApplicable(getObject(), damageInfo);
	}
};

enum CrushEnum
{
	TOTAL_CRUSH,
	BACK_END_CRUSH,
	FRONT_END_CRUSH,
	NO_CRUSH
};

struct DamageInfoInput
{
	unsigned char m_data[8];
	int m_sourceID;
	unsigned char m_gap[4];
	int m_damageType;
};

class DamageInfo
{
	public:
	DamageInfoInput in;
};

class BodyModuleInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18();
	virtual bool getFrontCrushed() const;
	virtual bool getBackCrushed() const;
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void setFrontCrushed(bool value);
	virtual void setBackCrushed(bool value);
};

class ModelConditionFlags;

class Object : public Thing
{
public:
	BodyModuleInterface *getBodyModule() const
	{
		return *(BodyModuleInterface **)((const char *)this + 0x200);
	}

	ObjectID getID() const
	{
		return *(const ObjectID *)((const char *)this + 0x74);
	}

	const Coord3D *getPosition() const
	{
		return (const Coord3D *)((const char *)this + 0x38);
	}

	const GeometryInfo &getGeometryInfo() const
	{
		return *(const GeometryInfo *)((const char *)this + 0xac);
	}

	void clearAndSetModelConditionFlags(const ModelConditionFlags &clear,
		const ModelConditionFlags &set);
};

class BfmeI1166
{
public:
	BfmeI1166(int tag, unsigned int first, unsigned int second);
	unsigned int m_words[10];
};

class Rva0015FC10BitSet
{
public:
	void setBit(unsigned int index, int value);
};

class ModelConditionFlags
{
public:
	ModelConditionFlags()
	{
		m_words[0] = 0;
		m_words[1] = 0;
		m_words[2] = 0;
		m_words[3] = 0;
		m_words[4] = 0;
		m_words[5] = 0;
		m_words[6] = 0;
		m_words[7] = 0;
		m_words[8] = 0;
		m_words[9] = 0;
	}

	void set(unsigned int index, int value)
	{
		((Rva0015FC10BitSet *)this)->setBit(index, value);
	}

	unsigned int m_words[10];
};

extern void j_00004048();
class GameLogic
{
public:
	Object *findObjectByID(int objectID);
};

extern GameLogic *TheGameLogic;
extern int GetGameLogicRandomValue(int low, int high, char *file, int line);

__declspec(noinline) static CrushEnum crushLocationCheck(Object *crusherObject,
	Object *victimObject)
{
	if ((crusherObject == 0) || (victimObject == 0))
		return NO_CRUSH;

	bool frontCrushed = victimObject->getBodyModule()->getFrontCrushed();
	bool backCrushed = victimObject->getBodyModule()->getBackCrushed();
	const Coord3D *otherDir = victimObject->getUnitDirectionVector2D();
	const Coord3D *pos = crusherObject->getPosition();
	const Coord3D *otherPos = victimObject->getPosition();

	Real crushPointOffsetDistance = victimObject->getGeometryInfo().getMajorRadius() * 0.5;

	Coord3D crushPointOffset;
	crushPointOffset.x = otherDir->x * crushPointOffsetDistance;
	crushPointOffset.y = otherDir->y * crushPointOffsetDistance;
	crushPointOffset.z = 0;

	Coord3D comparisonCoord;
	Real dx, dy;

	CrushEnum retval = NO_CRUSH;
	Real bestDist = 99999;

	if (!frontCrushed && !backCrushed)
	{
		comparisonCoord = *otherPos;

		dx = comparisonCoord.x - pos->x;
		dy = comparisonCoord.y - pos->y;
		Real dist = (Real)(dx * dx + dy * dy);

		retval = TOTAL_CRUSH;
		bestDist = dist;
	}

	if (!frontCrushed)
	{
		comparisonCoord = *otherPos;
		comparisonCoord.x += crushPointOffset.x;
		comparisonCoord.y += crushPointOffset.y;

		dx = comparisonCoord.x - pos->x;
		dy = comparisonCoord.y - pos->y;
		Real dist = (Real)(dx * dx + dy * dy);

		if (dist < bestDist)
		{
			if (backCrushed)
			{
				retval = TOTAL_CRUSH;
				bestDist = dist;
			}
			else
			{
				retval = FRONT_END_CRUSH;
				bestDist = dist;
			}
		}
	}

	if (!backCrushed)
	{
		comparisonCoord = *otherPos;
		comparisonCoord.x -= crushPointOffset.x;
		comparisonCoord.y -= crushPointOffset.y;

		dx = comparisonCoord.x - pos->x;
		dy = comparisonCoord.y - pos->y;
		Real dist = (Real)(dx * dx + dy * dy);

		if (dist < bestDist)
		{
			if (frontCrushed)
			{
				retval = TOTAL_CRUSH;
				bestDist = dist;
			}
			else
			{
				retval = BACK_END_CRUSH;
				bestDist = dist;
			}
		}
	}

	return retval;
}

class Rva00254CF0 : public DieModule
{
public:
	virtual void onDie(const DamageInfo *damageInfo);

	CrushDieModuleData *getCrushDieModuleData()
	{
		return (CrushDieModuleData *)getModuleData();
	}
};

// ?onDie@Rva00254CF0@@UAEXPBVDamageInfo@@@Z
void Rva00254CF0::onDie(const DamageInfo *damageInfo)
{
	if (!isDieApplicable(damageInfo))
		return;

	if (damageInfo->in.m_damageType != 1)
		return;

	Object *damageDealer = TheGameLogic->findObjectByID(damageInfo->in.m_sourceID);
	CrushEnum crushType = damageDealer ? crushLocationCheck(damageDealer, getObject()) : TOTAL_CRUSH;

	if (crushType != NO_CRUSH)
	{
		if (!getCrushDieModuleData()->m_crushSounds[crushType].getEventName().isEmpty())
		{
			if (GetGameLogicRandomValue(0, 99,
				(char *)"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Die\\CrushDie.cpp", 165)
				< getCrushDieModuleData()->m_crushSoundPercent[crushType])
			{
				AudioEventRTS crushSound(getCrushDieModuleData()->m_crushSounds[crushType]);
				crushSound.setObjectID(getObject()->getID());
				AudioManagerVtable &audioVtable = **(AudioManagerVtable **)TheAudio;
				audioVtable.addAudioEvent(TheAudio, &audioVtable, &crushSound);
			}
		}
		{
			Object *me = getObject();

			if (me)
		{
				me->getBodyModule()->setFrontCrushed(
					crushType == TOTAL_CRUSH || crushType == FRONT_END_CRUSH);
				me->getBodyModule()->setBackCrushed(
					crushType == TOTAL_CRUSH || crushType == BACK_END_CRUSH);

				ModelConditionFlags newCrushed;
				if (crushType == TOTAL_CRUSH || crushType == FRONT_END_CRUSH)
					newCrushed.set(1, 1);
				else
					newCrushed.set(1, 0);
				if (crushType == TOTAL_CRUSH || crushType == BACK_END_CRUSH)
					newCrushed.set(2, 1);
				else
					newCrushed.set(2, 0);

				BfmeI1166 clearMask(0, 2, 1);

				me->clearAndSetModelConditionFlags(
					(const ModelConditionFlags &)clearMask, newCrushed);
			}
		}
	}
}
