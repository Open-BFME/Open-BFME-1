// ?rva0022AC00@RiderChangeContain@@UAEXPAVObject@@@Z
// partial score=0.58 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc-
//
// The secondary RiderChangeContain interface at 0x0022AC00 is installed by
// the constructor's vtable 0x010AC870.  Its receiver is the +0x20 subobject:
// [this-0x18] is the containing Object and [this-0x1c] is module data.
// The neutral method name is intentional: the old onRemoving row at another
// address is an unrelated thunk, while this constructor-installed slot is the
// identity evidence for the body recovered here.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef bool Bool;

class AsciiString
{
public:
	void *m_data;
};

template <int NUMBITS>
class BitFlags
{
public:
	UnsignedInt m_bits[(NUMBITS + 31) / 32];
};

typedef BitFlags<320> ModelConditionFlags;
typedef BitFlags<86> ObjectStatusMaskType;

class Object;
class Drawable;
class Player;
class GameMessage;

enum Relationship
{
	RELATIONSHIP_RIDER = 2
};

class Rva0022BDE0Obj
{
public:
	void apply(Object *object);
};

class Rva001B2040
{
public:
	void copyFields(void *source);
};

class BfmeSub210_4B0
{
public:
	void apply(float experience, Int setLevel);
};

class BfmeRvaA760Object
{
public:
	void apply(Int weaponSetFlag);
};

class BfmeHordeMember
{
public:
	Bool bfmeBlocksFormationRefresh();
};

class GameLogic
{
public:
	void destroyObject(Object *object);

	unsigned char m_pad000[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheBfmeGameLogic;

class Rva226800Overridable
{
public:
	Rva226800Overridable *getFinalOverride();
};

class ThingTemplate
{
public:
	void *m_vtable;
	Rva226800Overridable *m_nextOverride;

	Bool isEquivalentTo(const ThingTemplate *other) const;
};

class ThingFactory
{
public:
	ThingTemplate *findTemplate(const AsciiString &name);
};

extern ThingFactory *TheThingFactory;

struct RiderInfo
{
	AsciiString m_templateName;
	Int m_weaponSetFlag;
	Int m_modelConditionFlagType;
	UnsignedInt m_objectStatusType;
	AsciiString m_commandSet;
	Int m_locomotorSetType;
};

class RiderChangeContainModuleData
{
public:
	unsigned char m_pad000[0xe8];
	mutable UnsignedInt m_fieldE8;
	UnsignedByte m_fieldEC;
	unsigned char m_padED[0x24c - 0xed];
	RiderInfo m_riders[8];
	UnsignedInt m_scuttleFrames;
	UnsignedInt m_scuttleState;
	UnsignedByte m_field314;
};

class Object
{
public:
	virtual void unused00() = 0;
	virtual void unused04() = 0;
	virtual void unused08() = 0;
	virtual void unused0c() = 0;
	virtual void unused10() = 0;
	virtual void unused14() = 0;
	virtual void unused18() = 0;
	virtual void unused1c() = 0;
	virtual void unused20() = 0;
	virtual void unused24() = 0;
	virtual Drawable *getDrawable() = 0;

	ThingTemplate *m_template;

	Relationship getRelationship(const Object *other) const;
	void clearAndSetModelConditionFlags(const ModelConditionFlags &clear,
		const ModelConditionFlags &set);
	void setStatus(const ObjectStatusMaskType &status, Bool set);
	Player *getControllingPlayer() const;
	void notifyModelConditionChanged();

	Rva001B2040 *experienceTracker() const
	{
		return *reinterpret_cast<Rva001B2040 *const *>(
			reinterpret_cast<const unsigned char *>(this) + 0x210);
	}

	UnsignedInt objectID() const
	{
		return *reinterpret_cast<const UnsignedInt *>(
			reinterpret_cast<const unsigned char *>(this) + 0x74);
	}

	UnsignedByte status344() const
	{
		return *reinterpret_cast<const UnsignedByte *>(
			reinterpret_cast<const unsigned char *>(this) + 0x344);
	}

	UnsignedInt *modelConditionWords() const
	{
		return reinterpret_cast<UnsignedInt *>(
			const_cast<unsigned char *>(reinterpret_cast<const unsigned char *>(this)) + 0x110);
	}

	void *aiUpdate() const
	{
		return *reinterpret_cast<void *const *>(
			reinterpret_cast<const unsigned char *>(this) + 0x204);
	}
};

class Rva002EE330PlayerList
{
public:
	unsigned char m_pad000[0xc];
	Player *m_localPlayer;
};

extern Rva002EE330PlayerList *Rva002EE330ThePlayers;

class GameMessage
{
public:
	void appendBooleanArgument(Bool value);
	void appendObjectIDArgument(UnsignedInt objectID);
};

class MessageStream
{
public:
	virtual void unused00() = 0;
	virtual void unused04() = 0;
	virtual void unused08() = 0;
	virtual void unused0c() = 0;
	virtual void unused10() = 0;
	virtual void unused14() = 0;
	virtual void unused18() = 0;
	virtual void unused1c() = 0;
	virtual void unused20() = 0;
	virtual void unused24() = 0;
	virtual void unused28() = 0;
	virtual void unused2c() = 0;
	virtual void unused30() = 0;
	virtual GameMessage *appendMessage(Int type);
};

extern MessageStream *TheMessageStream;

class InGameUI
{
public:
	virtual void ui00() = 0;
	virtual void ui04() = 0;
	virtual void ui08() = 0;
	virtual void ui0c() = 0;
	virtual void ui10() = 0;
	virtual void ui14() = 0;
	virtual void ui18() = 0;
	virtual void ui1c() = 0;
	virtual void ui20() = 0;
	virtual void ui24() = 0;
	virtual void ui28() = 0;
	virtual void ui2c() = 0;
	virtual void ui30() = 0;
	virtual void ui34() = 0;
	virtual void ui38() = 0;
	virtual void ui3c() = 0;
	virtual void ui40() = 0;
	virtual void ui44() = 0;
	virtual void ui48() = 0;
	virtual void ui4c() = 0;
	virtual void ui50() = 0;
	virtual void ui54() = 0;
	virtual void ui58() = 0;
	virtual void ui5c() = 0;
	virtual void ui60() = 0;
	virtual void ui64() = 0;
	virtual void ui68() = 0;
	virtual void ui6c() = 0;
	virtual void ui70() = 0;
	virtual void ui74() = 0;
	virtual void ui78() = 0;
	virtual void ui7c() = 0;
	virtual void ui80() = 0;
	virtual void ui84() = 0;
	virtual void ui88() = 0;
	virtual void ui8c() = 0;
	virtual void ui90() = 0;
	virtual void ui94() = 0;
	virtual void ui98() = 0;
	virtual void ui9c() = 0;
	virtual void uia0() = 0;
	virtual void uia4() = 0;
	virtual void uia8() = 0;
	virtual void uiac() = 0;
	virtual void uib0() = 0;
	virtual void uib4() = 0;
	virtual void uib8() = 0;
	virtual void uibc() = 0;
	virtual void uic0() = 0;
	virtual void uic4() = 0;
	virtual void uic8() = 0;
	virtual void uicc() = 0;
	virtual void uid0() = 0;
	virtual void uid4() = 0;
	virtual void uid8() = 0;
	virtual void uidc() = 0;
	virtual void uie0(Drawable *draw);
	virtual void uie4(Drawable *draw);
	virtual void uie8() = 0;
	virtual void uiec() = 0;
	virtual void uif0() = 0;
	virtual void uif4() = 0;
	virtual void uif8() = 0;
	virtual void uifc() = 0;
	virtual void ui100() = 0;
	virtual void ui104() = 0;
	virtual void ui108() = 0;
	virtual void ui10c() = 0;
	virtual void ui110() = 0;
	virtual void ui114() = 0;
	virtual void ui118() = 0;
	virtual void ui11c() = 0;
	virtual void ui120() = 0;
	virtual void ui124() = 0;
	virtual void ui128() = 0;
	virtual void ui12c() = 0;
	virtual void ui130() = 0;
	virtual void ui134() = 0;
	virtual void ui138() = 0;
	virtual void ui13c() = 0;
	virtual void ui140() = 0;
	virtual void ui144() = 0;
	virtual void ui148() = 0;
	virtual void ui14c() = 0;
	virtual void ui150() = 0;
	virtual void ui154() = 0;
	virtual void ui158() = 0;
	virtual void ui15c() = 0;
	virtual void ui160() = 0;
	virtual void ui164() = 0;
	virtual void ui168() = 0;
	virtual void ui16c() = 0;
	virtual void ui170() = 0;
	virtual void setDisplayedMaxWarning(Bool displayed);
};

extern InGameUI *TheInGameUI;

struct GameMessageType
{
	enum
	{
		MSG_CREATE_SELECTED_GROUP = 0x3e9,
		MSG_REMOVE_FROM_SELECTED_GROUP = 0x3ec
	};
};

class RiderChangeContain
{
public:
	virtual void rva0022AC00(Object *rider);

private:
	Object *object() const
	{
		return *reinterpret_cast<Object *const *>(
			reinterpret_cast<const unsigned char *>(this) - 0x18);
	}

	const RiderChangeContainModuleData *moduleData() const
	{
		return *reinterpret_cast<const RiderChangeContainModuleData *const *>(
			reinterpret_cast<const unsigned char *>(this) - 0x1c);
	}
};

void RiderChangeContain::rva0022AC00(Object *rider)
{
	RiderChangeContain *self = this;
	Object *riderObject = rider;
	Object *containingObject = object();
	const RiderChangeContainModuleData *data = moduleData();

	if (containingObject->getRelationship(riderObject) != RELATIONSHIP_RIDER)
	{
		((Rva0022BDE0Obj *)self)->apply(riderObject);
		return;
	}

	if (data->m_field314 && (containingObject->status344() & 1) != 0)
	{
		TheBfmeGameLogic->destroyObject(riderObject);
		return;
	}

	((Rva0022BDE0Obj *)self)->apply(riderObject);

	Int riderIndex = 0;
	const RiderInfo *riderInfo = data->m_riders;
	for (; riderIndex < 8; ++riderIndex, ++riderInfo)
	{
		ThingTemplate *entryTemplate = TheThingFactory->findTemplate(riderInfo->m_templateName);
		ThingTemplate *riderTemplate = riderObject->m_template;
		if (riderTemplate && riderTemplate->m_nextOverride)
		{
			riderTemplate = (ThingTemplate *)riderTemplate->m_nextOverride->getFinalOverride();
		}
		if (entryTemplate->isEquivalentTo(riderTemplate))
			goto riderFound;
	}

	goto riderDone;

riderFound:
	{
		ModelConditionFlags clearModelConditions = {};
		UnsignedInt modelCondition = riderInfo->m_modelConditionFlagType;
		clearModelConditions.m_bits[modelCondition >> 5] |=
			1u << (modelCondition & 31);
		clearModelConditions.m_bits[0] |= 0x400000;
		ModelConditionFlags setModelConditions = {};
		containingObject->clearAndSetModelConditionFlags(clearModelConditions, setModelConditions);

		((BfmeRvaA760Object *)containingObject)->apply(riderInfo->m_weaponSetFlag);

		ObjectStatusMaskType riderStatus = {};
		riderStatus.m_bits[riderInfo->m_objectStatusType >> 5] |=
			1u << (riderInfo->m_objectStatusType & 31);
		containingObject->setStatus(riderStatus, false);

		Player *riderPlayer = riderObject->getControllingPlayer();
		if (riderPlayer != 0)
		{
			Rva001B2040 *riderExperience = rider->experienceTracker();
			Rva001B2040 *containingExperience = containingObject->experienceTracker();
			riderExperience->copyFields(riderObject);
			((BfmeSub210_4B0 *)containingExperience)->apply(0.0f, 1);
		}
	}

riderDone:
	if (data->m_fieldEC)
		return;

	Drawable *containingDrawable = containingObject->getDrawable();
	Drawable *riderDrawable = riderObject->getDrawable();
	if (containingDrawable == 0 || riderDrawable == 0)
		return;

	if (containingObject->getControllingPlayer() != Rva002EE330ThePlayers->m_localPlayer)
		return;
	if ((*reinterpret_cast<const UnsignedByte *>(
			reinterpret_cast<const unsigned char *>(containingDrawable) + 0x3ac) & 1) == 0)
		return;

	GameMessage *message = TheMessageStream->appendMessage(
		GameMessageType::MSG_CREATE_SELECTED_GROUP);
	message->appendBooleanArgument(false);
	message->appendObjectIDArgument(riderObject->objectID());
	TheInGameUI->uie0(riderDrawable);
	TheInGameUI->setDisplayedMaxWarning(false);

	message = TheMessageStream->appendMessage(
		GameMessageType::MSG_REMOVE_FROM_SELECTED_GROUP);
	message->appendObjectIDArgument(containingObject->objectID());
	TheInGameUI->uie4(containingDrawable);

	data->m_fieldE8 = TheBfmeGameLogic->m_frame;

	ObjectStatusMaskType selectedStatus = {};
	selectedStatus.m_bits[0] |= 8;
	containingObject->setStatus(selectedStatus, true);

	UnsignedInt scuttleState = data->m_scuttleState;
	UnsignedInt scuttleWord = scuttleState >> 5;
	UnsignedInt scuttleBit = 1u << (scuttleState & 31);
	UnsignedInt *modelWords = containingObject->modelConditionWords();
	if ((modelWords[scuttleWord] & scuttleBit) == 0)
	{
		modelWords[scuttleWord] |= scuttleBit;
		containingObject->notifyModelConditionChanged();
	}

	if (((BfmeHordeMember *)containingObject->aiUpdate())->bfmeBlocksFormationRefresh())
		return;

	ObjectStatusMaskType formationStatus = {};
	formationStatus.m_bits[0] |= 0x10000;
	containingObject->setStatus(formationStatus, true);
}
