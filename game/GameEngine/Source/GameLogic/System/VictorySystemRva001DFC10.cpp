// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2 /G6

// VictorySystem::rva001DFC10 (0x001DFC10, 262 bytes, ret 8).
// Owner: the only caller, 0x001CEFC0 (via ILT 0x00026963 at 0x001CF02C),
// loads TheVictorySystem (0x012EF734) into ECX and passes its own this and its
// incoming DamageInfo pointer; the body reads the VictorySystem layout the landed constructor
// 0x001E0160 builds (+0x24 player parameter index, +0x64 root cell, +0xEC
// faction parameter vector, +0xF8 two cell grids). No caller, string or vtable
// slot names the method, so it keeps its address token.
//
// Retail re-reads the object player's index (+0x24) for the grid calls
// instead of keeping the value it indexed the parameter table with, so the
// grid loop calls getPlayerIndex() again; caching it left the object in EBP.
// The parameter-index guard tests the high bit as a flag (the landed
// bfmeParametersForPlayer 0x001DE880 masks it off with 0x7FFFFFFF); spelled as
// a signed `< 0` compare VC7.1 swaps the player registers.

typedef int Int;
typedef float Real;

enum KindOfType
{
};

class Player
{
public:
	Int getPlayerIndex() const { return m_playerIndex; }

private:
	unsigned char m_unmodelled_00[0x24];
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

	unsigned char m_unmodelled_04[0x344 - 0x04];
	unsigned char m_privateStatus;
};

class DamageInfo
{
public:
	unsigned char m_unmodelled_00[0x08];
	Int m_sourceID;
};

class GameLogic
{
public:
	Object *findObjectByID(Int id);
};

extern GameLogic *TheGameLogic;	// 0x012F0898

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
	void bfmeApplyAtObject(const Object *object, Real amount, Int firstIndex,
		Int secondIndex) const;
};

struct FactionVictoryParameters
{
	char m_data[0x14];
	Real m_majorUnitValue;	// FieldParse MajorUnitValue +0x14 (0x00C9FBC8)
};

class FactionVictoryParametersVector
{
public:
	FactionVictoryParameters &operator[](unsigned int index) { return m_begin[index]; }

private:
	FactionVictoryParameters *m_begin;
	FactionVictoryParameters *m_end;
	FactionVictoryParameters *m_storageEnd;
};

class VictorySystem
{
public:
	void rva001DFC10(Object *object, DamageInfo *damageInfo);

private:
	unsigned char m_unmodelled_00[0x24];
	Int m_playerParameterIndex[16];
	BfmeCell m_rootCell;
	FactionVictoryParametersVector m_factionVictoryParameters;
	BfmeCellGrid *m_cellGrids[2];
};

void VictorySystem::rva001DFC10(Object *object, DamageInfo *damageInfo)
{
	if (object == 0)
		return;
	if (damageInfo == 0)
		return;
	if ((object->m_privateStatus & 0x08) != 0)
		return;

	Object *source = TheGameLogic->findObjectByID(damageInfo->m_sourceID);
	if (source == 0)
		return;

	Player *objectPlayer = object->getControllingPlayer();
	Player *sourcePlayer = source->getControllingPlayer();
	if (objectPlayer == 0)
		return;
	if (sourcePlayer == 0)
		return;

	Int objectPlayerIndex = objectPlayer->getPlayerIndex();
	Int parameterIndex = m_playerParameterIndex[objectPlayerIndex];
	if ((parameterIndex & 0x80000000) != 0)
		return;

	FactionVictoryParameters *parameters =
		&m_factionVictoryParameters[(unsigned int)parameterIndex];
	Real amount;
	if (object->isKindOf((KindOfType)0x0a) ||
		object->isKindOf((KindOfType)0x59))
		amount = parameters->m_majorUnitValue;
	else
		amount = 1.0f;

	m_rootCell.bfmeAdd(amount, objectPlayerIndex, sourcePlayer->getPlayerIndex());

	for (Int i = 0; i < 2; ++i)
	{
		if (m_cellGrids[i] != 0)
			m_cellGrids[i]->bfmeApplyAtObject(object, amount,
				objectPlayer->getPlayerIndex(), sourcePlayer->getPlayerIndex());
	}
}
