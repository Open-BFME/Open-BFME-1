// ?bfmeNotifyObject@VictorySystem@@QAEXPAVObject@@PAVDamageInfo@@@Z
// partial score=0.90 date=2026-09-08

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

enum KindOfType
{
};

class Player
{
public:
	Int getPlayerIndex() const { return m_playerIndex; }

private:
	char m_pad00[0x24];
	Int m_playerIndex;
};

class Thing
{
public:
	virtual void slot00() = 0;
	bool isKindOf(KindOfType kind) const;
};

class Object : public Thing
{
public:
	Player *getControllingPlayer() const;
	char m_pad04[0x340];
	unsigned char m_privateStatus;
};

class DamageInfo
{
public:
	char m_pad00[8];
	Int m_sourceID;
};

class GameLogic
{
public:
};

#define TheBfmeGameLogic (*(GameLogic **)0x012F0898)

class GameLogicFrameSlice
{
public:
	Object *bfmeFind(Int id);
};

class BfmeCell
{
public:
	void bfmeAdd(Real amount, Int firstIndex, Int secondIndex);

private:
	char m_data[0x88];
};

class BfmeCellGrid
{
public:
};

class BfmeObjectCall
{
public:
	Player *getControllingPlayer() const;
};

class BFMEActionThing
{
public:
	bool isKindOf(Int kind) const;
};

class BfmeGridApplyAtObject
{
public:
	void apply(const Object *object, Real amount, Int firstIndex,
		Int secondIndex) const;
};

struct FactionVictoryParameters
{
	char m_data[24];
};

class FactionVictoryParametersVector
{
public:
	FactionVictoryParameters &operator[](UnsignedInt index)
	{
		return m_begin[index];
	}

private:
	FactionVictoryParameters *m_begin;
	FactionVictoryParameters *m_end;
	FactionVictoryParameters *m_storageEnd;
};

class VictorySystem
{
public:
	void bfmeNotifyObject(Object *object, DamageInfo *damageInfo);

private:
	char m_pad00[0x24];
	Int m_playerParameterIndex[16];
	BfmeCell m_rootCell;
	FactionVictoryParametersVector m_parameters;
	BfmeCellGrid *m_grids[2];
};

void VictorySystem::bfmeNotifyObject(Object *object, DamageInfo *damageInfo)
{
	if (object == 0)
		return;
	if (damageInfo == 0)
		return;
	if ((object->m_privateStatus & 8) != 0)
		return;

	Object *source = ((GameLogicFrameSlice *)TheBfmeGameLogic)->bfmeFind(
		damageInfo->m_sourceID);
	if (source == 0)
		return;

	Player *objectPlayer = ((BfmeObjectCall *)object)->getControllingPlayer();
	Player *sourcePlayer = ((BfmeObjectCall *)source)->getControllingPlayer();
	if (objectPlayer == 0)
		return;

	if (sourcePlayer == 0)
		return;

	Int objectPlayerIndex = objectPlayer->getPlayerIndex();
	Int parameterIndex = m_playerParameterIndex[objectPlayerIndex];
	if ((parameterIndex & 0x80000000) != 0)
		return;

	FactionVictoryParameters *parameters = &m_parameters[(UnsignedInt)parameterIndex];
	Real amount;
	if (((BFMEActionThing *)object)->isKindOf(0xa) ||
		((BFMEActionThing *)object)->isKindOf(0x59))
		amount = *(Real *)((char *)parameters + 0x14);
	else
		amount = 1.0f;

	m_rootCell.bfmeAdd(amount, objectPlayerIndex, sourcePlayer->getPlayerIndex());

	BfmeCellGrid **grid = m_grids;
	Int count = 2;
	do
	{
		if (*grid != 0)
			((BfmeGridApplyAtObject *)*grid)->apply(object, amount, objectPlayerIndex,
				sourcePlayer->getPlayerIndex());
		++grid;
	}
	while (--count != 0);
}
