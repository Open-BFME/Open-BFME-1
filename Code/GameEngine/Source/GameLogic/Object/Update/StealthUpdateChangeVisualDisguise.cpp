// BFME StealthUpdate::changeVisualDisguise, retail 0x002AC620..0x002ACA5D.
// StealthUpdate::update calls through ILT0x000378DF. Actual destructor is
// 0x002AC070, reached from deleting destructor0x002ACD50 viaILT0x0003EFC7.
// TU-local layout views preserve the existing canonical callee ABIs.

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef int Int;

struct Coord3D
{
	float x, y, z;
};

class Matrix3D;

template <int NUMBITS>
class BitFlags
{
public:
	UnsignedInt m_bfmeBitsYG[NUMBITS / 32];
};

typedef BitFlags<320> ModelConditionFlags;

class Drawable;
class Player;
class Team;
class ThingTemplate;
class AudioEventRTS;
class BFMERetailAsciiString;

template <class T> class StringBase
{
	protected:
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	T *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
};

class FXList;
class AIUpdateInterface;

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
};

class ThingTemplate
{
public:
	char m_pad00[4];
	// The BFME view exposes the retail +0x04 link named m_nextOverride in
	// AIGroupForwardedOrders.cpp; preserve that source-backed spelling here.
	Overridable *m_nextOverride;
};

class Object
{
public:
	virtual void _pad00();
	virtual void _pad04();
	virtual void _pad08();
	virtual void _pad0C();
	virtual void _pad10();
	virtual void _pad14();
	virtual void _pad18();
	virtual void _pad1C();
	virtual void _pad20();
	virtual void _pad24();
	virtual Drawable *getDrawable();

	const ThingTemplate *getTemplate() const
	{
		const ThingTemplate *t = *(const ThingTemplate * const *)((const char *)this + 4);
		if (t && t->m_nextOverride)
			t = (const ThingTemplate *)t->m_nextOverride->getFinalOverride();
		return t;
	}

	const Coord3D *getPosition() const
	{
		return (const Coord3D *)((const char *)this + 0x38);
	}

	float getOrientation() const
	{
		return *(const float *)((const char *)this + 0x44);
	}

	UnsignedInt getID() const
	{
		return *(const UnsignedInt *)((const char *)this + 0x74);
	}

	ModelConditionFlags readModelConditionFlags() const
	{
		return *(const ModelConditionFlags *)((const char *)this + 0x110);
	}

	Player *getControllingPlayer() const;
	void bfmeClearYG(const BitFlags<320> &flags);
	Int getNightIndicatorColor() const;
	UnsignedInt getIndicatorColor() const;
	void forceRefreshSubObjectUpgradeStatus();
	AIUpdateInterface *getAI() const
	{
		return *(AIUpdateInterface * const *)((const char *)this + 0x204);
	}
};

class Thing
{
public:
	void setOrientation(float orientation);
};

class Drawable : public Thing
{
public:
	Bool isSelected() const
	{
		return *(const unsigned char *)((const char *)this + 0x3AC);
	}

	void setPosition(const Coord3D *position);
	void setIndicatorColor(UnsignedInt color);
	const AudioEventRTS *getPerUnitSound(const AsciiString &name) const;
};

// The existing body at 0x0041BE60 is the present-unmatched
// Drawable::updateDrawable implementation in GameClient/Drawable.cpp, while
// its current generated ledger name is ?d_0041be60@@YAXXZ.  Route through that
// existing address-derived symbol; the fastcall view supplies Drawable in
// ECX and preserves the retail no-stack-argument call shape.
void d_0041be60();
typedef void (__fastcall *DrawableUpdateCall)(Drawable *draw);

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

class Player
{
public:
	Team *getDefaultTeam() const
	{
		return *(Team * const *)((const char *)this + 0x230);
	}

	UnsignedInt getPlayerColor() const
	{
		return *(const UnsignedInt *)((const char *)this + 0x1C4);
	}

	UnsignedInt getPlayerNightColor() const
	{
		return *(const UnsignedInt *)((const char *)this + 0x1C8);
	}

	Int getPlayerIndex() const;
	Relationship getRelationship(const Team *team) const;
	Bool isPlayerActive() const;
};

class PlayerList
{
public:
	Player *m_pad00[3];
	Player *m_localPlayer;
	Player *getNthPlayer(Int index);
};

extern PlayerList *ThePlayerList;

class GameClient
{
public:
	virtual void _pad00(); virtual void _pad01(); virtual void _pad02();
	virtual void _pad03(); virtual void _pad04(); virtual void _pad05();
	virtual void _pad06(); virtual void _pad07(); virtual void _pad08();
	virtual void _pad09(); virtual void _pad10(); virtual void _pad11();
	virtual void _pad12(); virtual void _pad13(); virtual void _pad14();
	virtual void _pad15(); virtual void _pad16(); virtual void _pad17();
	virtual void _pad18(); virtual void _pad19(); virtual void _pad20();
	virtual void _pad21(); virtual void _pad22(); virtual void _pad23();
	virtual void destroyDrawable(Drawable *draw);
};

extern GameClient *TheGameClient;

enum DrawableStatus
{
	DRAWABLE_STATUS_NONE = 0
};

class BFMEThingFactory
{
public:
	Drawable *newDrawable(const ThingTemplate *t,
		DrawableStatus status = DRAWABLE_STATUS_NONE, Int id = -1);
};

extern BFMEThingFactory *TheThingFactory;

class GameLogic
{
public:
	void bindObjectAndDrawable(Object *object, Drawable *draw);
};

extern GameLogic *TheGameLogic;

class InGameUI
{
public:
	virtual void _pad00(); virtual void _pad01(); virtual void _pad02();
	virtual void _pad03(); virtual void _pad04(); virtual void _pad05();
	virtual void _pad06(); virtual void _pad07(); virtual void _pad08();
	virtual void _pad09(); virtual void _pad10(); virtual void _pad11();
	virtual void _pad12(); virtual void _pad13(); virtual void _pad14();
	virtual void _pad15(); virtual void _pad16(); virtual void _pad17();
	virtual void _pad18(); virtual void _pad19(); virtual void _pad20();
	virtual void _pad21(); virtual void _pad22(); virtual void _pad23();
	virtual void _pad24(); virtual void _pad25(); virtual void _pad26();
	virtual void _pad27(); virtual void _pad28(); virtual void _pad29();
	virtual void _pad30(); virtual void _pad31(); virtual void _pad32();
	virtual void _pad33(); virtual void _pad34(); virtual void _pad35();
	virtual void _pad36(); virtual void _pad37(); virtual void _pad38();
	virtual void _pad39(); virtual void _pad40(); virtual void _pad41();
	virtual void _pad42(); virtual void _pad43(); virtual void _pad44();
	virtual void _pad45(); virtual void _pad46(); virtual void _pad47();
	virtual void _pad48(); virtual void _pad49(); virtual void _pad50();
	virtual void _pad51(); virtual void _pad52(); virtual void _pad53();
	virtual void _pad54(); virtual void _pad55();
	virtual void selectDrawable(Drawable *draw);
};

extern InGameUI *TheInGameUI;

struct GlobalData
{
	char m_pad00[0x218];
	UnsignedInt m_timeOfDay;
};

extern GlobalData *TheWritableGlobalData;

class AudioClient
{
public:
	virtual void _pad00(); virtual void _pad01(); virtual void _pad02();
	virtual void _pad03(); virtual void _pad04(); virtual void _pad05();
	virtual void _pad06(); virtual void _pad07(); virtual void _pad08();
	virtual void _pad09(); virtual void _pad10(); virtual void _pad11();
	virtual void _pad12(); virtual void _pad13(); virtual void _pad14();
	virtual void _pad15(); virtual void _pad16();
	virtual void addAudioEvent(AudioEventRTS *event);
};

extern AudioClient *TheAudioClientUpdate;

class BFMERetailAsciiString : public AsciiString
{
public:
	BFMERetailAsciiString(const char *text) : AsciiString(text) {}
	BFMERetailAsciiString(const BFMERetailAsciiString &other)
		: AsciiString(other) {}
	~BFMERetailAsciiString() { releaseBuffer(); }
	void releaseBuffer();
};

class AudioEventRTS
{
public:
	AudioEventRTS(void *allocator, Int extra);
	AudioEventRTS(const AudioEventRTS &other);
	AudioEventRTS &operator=(const AudioEventRTS &other);
	~AudioEventRTS();
	void setObjectID(UnsignedInt id);

private:
	char m_pad00[0x70];
};

extern AsciiString g_disguiseRevealedSuccess;
extern AsciiString g_disguiseRevealedFailure;

class FXList
{
public:
	Bool isEmpty() const;
	void doFXPos(const Coord3D *position, const Matrix3D *matrix, float speed,
		const Coord3D *secondary) const;
};

class AIUpdateInterface
{
public:
	Object *getCurrentVictim() const;
};

class Radar
{
public:
	void removeObject(Object *object);
	void addObject(Object *object);
};

extern Radar *TheRadar;

class UpdateModule
{
protected:
	virtual void _pad00();
	void *m_moduleData;
	Object *m_object;
	char m_pad0C[0x14];
};

class StealthUpdateModuleData
{
public:
	char m_pad00[0x38];
	FXList *m_disguiseRevealFX;
	FXList *m_disguiseFX;
};

class StealthUpdate : public UpdateModule
{

protected:
	void changeVisualDisguise();

private:
	char m_pad20[0x14];
	Int m_disguiseAsPlayerIndex;
	const ThingTemplate *m_disguiseAsTemplate;
	UnsignedInt m_disguiseTransitionFrames;
	Bool m_disguiseHalfpointReached;
	Bool m_transitioningToDisguise;
	Bool m_disguised;
	Bool m_xferRestoreDisguise;
};

// ?changeVisualDisguise@StealthUpdate@@IAEXXZ
void StealthUpdate::changeVisualDisguise()
{
	Object *self = m_object;
	const StealthUpdateModuleData *data =
		(const StealthUpdateModuleData *)m_moduleData;
	Drawable *draw = self->getDrawable();
	Bool selected = draw->isSelected();

	if (m_disguiseAsTemplate)
	{
		Player *player = ThePlayerList->getNthPlayer(m_disguiseAsPlayerIndex);
		ModelConditionFlags flags = self->readModelConditionFlags();
		TheGameClient->destroyDrawable(draw);
		draw = TheThingFactory->newDrawable(m_disguiseAsTemplate);
		if (draw)
		{
			TheGameLogic->bindObjectAndDrawable(self, draw);
			draw->setPosition(self->getPosition());
			draw->setOrientation(self->getOrientation());
			self->bfmeClearYG(flags);
			((DrawableUpdateCall)d_0041be60)(draw);
			if (selected)
				TheInGameUI->selectDrawable(draw);

			Player *clientPlayer = ThePlayerList->m_localPlayer;
			if (self->getControllingPlayer()->getRelationship(
					clientPlayer->getDefaultTeam()) != 2 &&
				clientPlayer->isPlayerActive())
			{
				if (TheWritableGlobalData->m_timeOfDay == 4)
					draw->setIndicatorColor(player->getPlayerNightColor());
				else
					draw->setIndicatorColor(player->getPlayerColor());
			}
			else
			{
				if (TheWritableGlobalData->m_timeOfDay == 4)
					draw->setIndicatorColor(self->getNightIndicatorColor());
				else
					draw->setIndicatorColor(self->getIndicatorColor());
			}

			AudioEventRTS sound = *draw->getPerUnitSound(
				BFMERetailAsciiString("DisguiseStarted"));
			sound.setObjectID(self->getID());
			TheAudioClientUpdate->addAudioEvent(&sound);
		}

		FXList *fx = data->m_disguiseFX;
		if (fx && !fx->isEmpty())
			fx->doFXPos(self->getPosition(), 0, 0.0f, 0);
		m_disguised = 1;
	}
	else if (m_disguiseAsPlayerIndex != -1)
	{
		m_disguiseAsPlayerIndex = -1;
		ModelConditionFlags flags = self->readModelConditionFlags();
		TheGameClient->destroyDrawable(draw);
		const ThingTemplate *tTemplate = self->getTemplate();
		TheThingFactory->newDrawable(tTemplate);
		if (draw)
		{
			TheGameLogic->bindObjectAndDrawable(self, draw);
			draw->setPosition(self->getPosition());
			draw->setOrientation(self->getOrientation());
			self->bfmeClearYG(flags);
			((DrawableUpdateCall)d_0041be60)(draw);
			if (TheWritableGlobalData->m_timeOfDay == 4)
				draw->setIndicatorColor(self->getNightIndicatorColor());
			else
				draw->setIndicatorColor(self->getIndicatorColor());
			if (selected)
				TheInGameUI->selectDrawable(draw);
			self->forceRefreshSubObjectUpgradeStatus();
		}

		Bool successfulReveal = 0;
		AIUpdateInterface *ai = self->getAI();
		if (ai && ai->getCurrentVictim())
			successfulReveal = 1;

		{
			AudioEventRTS sound((void *)0x01336e50, 0);
			if (successfulReveal)
			{
				BFMERetailAsciiString eventName("DisguiseRevealedSuccess");
				sound = *draw->getPerUnitSound(eventName);
			}
			else
			{
				BFMERetailAsciiString eventName("DisguiseRevealedFailure");
				sound = *draw->getPerUnitSound(eventName);
			}
			sound.setObjectID(self->getID());
			TheAudioClientUpdate->addAudioEvent(&sound);
		}
		FXList *fx = data->m_disguiseRevealFX;
		if (fx && !fx->isEmpty())
			fx->doFXPos(self->getPosition(), 0, 0.0f, 0);
		m_disguised = 0;
	}

	TheRadar->removeObject(self);
	TheRadar->addObject(self);
	m_xferRestoreDisguise = 0;
}
