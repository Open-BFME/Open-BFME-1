// cl: /DNDEBUG /MD /EHsc
// MoneyCrateCollide's primary vtable slot 10 reaches this body through the
// retail ILT at 0x000227B9. The adjacent validation slot reaches the canonical
// CrateCollide::isValidToExecute body.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class GameLogicShim
{
public:
	Bool unidentified_0001e0ab();
};

class Rva00367E30Logic;
extern Rva00367E30Logic *TheBfmeGameLogic;

class Rva002EE330PlayerListThunk
{
public:
	Int unidentified_000389f6(Bool includeFields);
};

class Rva002EE330PlayerList;
extern Rva002EE330PlayerList *Rva002EE330ThePlayers;

class Rva00083240Thunk
{
public:
	float unidentified_00009e12(Int index) const;
};

class Rva006C9270GlobalData;
extern Rva006C9270GlobalData *TheWritableGlobalData;

class Rva000C97C0PlayerThunk
{
public:
	Int unidentified_00024938(Int bounty);
};

class Rva00027D6DMoney
{
public:
	void unidentified_00027d6d(UnsignedInt amount, Bool playSound);
};

class Rva0003A45EScoreKeeper
{
public:
	void unidentified_0003a45e(Int amount);
};

class Player
{
public:
	Rva00027D6DMoney *getMoney()
	{
		return reinterpret_cast<Rva00027D6DMoney *>(
			reinterpret_cast<char *>(this) + 0x48);
	}

	Rva0003A45EScoreKeeper *getScoreKeeper()
	{
		return reinterpret_cast<Rva0003A45EScoreKeeper *>(
			reinterpret_cast<char *>(this) + 0x348);
	}
};

class Object
{
public:
	Player *getControllingPlayer() const;
	ObjectID getID() const { return m_id; }

private:
	char m_bfmeHead[0x74];
	ObjectID m_id;
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AudioEventRTS &that);
	~AudioEventRTS();
	void setObjectID(ObjectID objectID);

private:
	char m_bfmeBody[0x70];
};

struct MiscAudio
{
	char m_bfmeHead[0xa10];
	AudioEventRTS m_crateMoney;
};

class Rva005A00B0AudioClient
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual UnsignedInt addAudioEvent(const AudioEventRTS *event) = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;
	virtual void slot63() = 0;
	virtual void slot64() = 0;
	virtual void slot65() = 0;
	virtual void slot66() = 0;
	virtual void slot67() = 0;
	virtual void slot68() = 0;
	virtual void slot69() = 0;
	virtual void slot70() = 0;
	virtual void slot71() = 0;
	virtual void slot72() = 0;
	virtual const MiscAudio *getMiscAudio() const = 0;
};

extern Rva005A00B0AudioClient *TheAudioClientUpdate;

struct MoneyCrateCollideModuleDataSlice
{
	char m_prefix[0x54];
	UnsignedInt m_moneyProvided;
};

class MoneyCrateCollide
{
protected:
	virtual Bool executeCrateBehavior(Object *other);

	const MoneyCrateCollideModuleDataSlice *getMoneyCrateCollideModuleData() const
	{
		return m_moduleData;
	}

private:
	const MoneyCrateCollideModuleDataSlice *m_moduleData;
	Object *m_object;
};

Bool MoneyCrateCollide::executeCrateBehavior(Object *other)
{
	UnsignedInt money = getMoneyCrateCollideModuleData()->m_moneyProvided;
	if (reinterpret_cast<GameLogicShim *>(TheBfmeGameLogic)->unidentified_0001e0ab())
	{
		const Int playerIndex = reinterpret_cast<Rva002EE330PlayerListThunk *>(
			Rva002EE330ThePlayers)->unidentified_000389f6(false);
		const float factor = reinterpret_cast<Rva00083240Thunk *>(
			reinterpret_cast<char *>(TheWritableGlobalData) + 0xee0)->unidentified_00009e12(playerIndex);
		money = static_cast<UnsignedInt>(money * factor);
	}

	Player *player = other->getControllingPlayer();
	if (player != 0)
	{
		money = reinterpret_cast<Rva000C97C0PlayerThunk *>(player)->unidentified_00024938(money);
		player->getMoney()->unidentified_00027d6d(money, true);
		player->getScoreKeeper()->unidentified_0003a45e(money);
	}

	AudioEventRTS soundToPlay = TheAudioClientUpdate->getMiscAudio()->m_crateMoney;
	soundToPlay.setObjectID(other->getID());
	TheAudioClientUpdate->addAudioEvent(&soundToPlay);

	return true;
}
