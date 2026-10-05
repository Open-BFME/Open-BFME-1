// ?bfmeRefreshFormation@BfmeHordeContainOwner@@QAEXXZ
// partial score=0.502 date=2026-10-05
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_NO_EXCEPTIONS /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /FAsc /Fa/Users/segrob/git/OpenBFME/wt-luna-7/build/0023cec0-sret.cod
// stlport
#include <bitset>

class AsciiString
{
	void *m_data;
};

template <class T>
class StringBase
{
protected:
	void releaseBuffer();
private:
	void *m_data;
};

template <class T>
class BFMERetailStringBase : private StringBase<T>
{
public:
	~BFMERetailStringBase() { this->releaseBuffer(); }
};

template <int N>
class BitFlags
{
public:
	_STL::bitset<N> m_bits;
};

class Team;
class Drawable;
class Matrix3D;
class ThingTemplate;
class Object;
struct BfmeOwnZE;

enum ObjectShroudStatus { OBJECT_SHROUD_0 };
enum PathfindLayerEnum { PATHFIND_LAYER_0 };

class Rva00235D20Host
{
public:
	BFMERetailStringBase<char> copyStringAt240();
};

class TeamFactory
{
public:
	Team *findTeam(const AsciiString &name);
};
extern TeamFactory *TheTeamFactory;

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *thing, Team *team,
		const BitFlags<86> &flags, unsigned int extra);
};
struct Rva0020AA00Registry;
extern Rva0020AA00Registry *Rva0020AA00TheRegistry;

class Drawable
{
public:
	void setDrawableHidden(bool hidden);
};

class Thing
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
	void setMatrix(const Matrix3D *matrix);
};

class Object : public Thing
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
	virtual Drawable *getDrawable() = 0;
	bool testStatus(int status) const;
	ObjectShroudStatus getShroudedStatus(int player) const;
	void bfmeTransferReplacementState(Object *replacement);
	int getLayer() const;
	void setLayer(PathfindLayerEnum layer);
	Object *findObjectByID(int id);
	struct ExitInterface *getObjectExitInterface() const;
};

class ObjectWithDrawableBool
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
	virtual Drawable *getDrawable() = 0;
};

struct ExitInterface
{
	virtual void slot00() = 0;
	virtual int canUseOwner(BfmeOwnZE *owner) = 0;
	virtual void updateOwner(Object *object, int value) = 0;
};

class BfmeObjZE
{
public:
	BfmeOwnZE *bfmeOwnerZE();
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};
extern GameLogic *TheBfmeGameLogic;

class BfmeGlobFEA
{
public:
	void bfmeCallFEA(void *object, int value);
};

struct Rva002EE330PlayerList
{
	char m_head[0x0c];
	char *m_player;
};
extern Rva002EE330PlayerList *Rva002EE330ThePlayers;

struct BfmeHordeRefreshInterface
{
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
	virtual void slot17() = 0;
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
	virtual void refresh(Object *replacement, Object *source, bool force) = 0;
};

class BfmeHordeContainOwner
{
public:
	void bfmeRefreshFormation();
	unsigned int m_rva0023cec0_000;
	void *m_rva0023cec0_004;
	Object *m_rva0023cec0_008;
	char m_rva0023cec0_00c[0xd8];
	unsigned int m_rva0023cec0_0e4;
	char m_rva0023cec0_0e8[0xd4];
	void *m_pendingRefresh;
	char m_rva0023cec0_1c0[0x0c];
	unsigned int m_rva0023cec0_1cc;
};

extern void j_00017355();
extern void j_0003f5da();

void BfmeHordeContainOwner::bfmeRefreshFormation()
{
	if (m_pendingRefresh)
		return;

	char *container = reinterpret_cast<char *>(m_rva0023cec0_004);
	unsigned int nameAddress = *reinterpret_cast<unsigned int *>(container + 0x2b0);
	if (nameAddress == *reinterpret_cast<unsigned int *>(container + 0x2b4))
		return;

	const AsciiString &name = *reinterpret_cast<const AsciiString *>(nameAddress);
	const ThingTemplate *thing = reinterpret_cast<ThingFactory *>(Rva0020AA00TheRegistry)->findTemplate(name);
	if (!thing)
		return;

	Object *source = m_rva0023cec0_008;
	BitFlags<86> flags;
	Team *team;
	unsigned int oldStatus = *reinterpret_cast<unsigned int *>(
		reinterpret_cast<char *>(source) + 0x94);
	if (!(oldStatus & 0x20000000))
	{
		team = *reinterpret_cast<Team **>(reinterpret_cast<char *>(source) + 0x23c);
	}
	else
	{
		team = TheTeamFactory->findTeam(
			(const AsciiString &)
			reinterpret_cast<Rva00235D20Host *>(source)->copyStringAt240());
		if (!team)
			return;
	}

	Object *replacement = reinterpret_cast<ThingFactory *>(Rva0020AA00TheRegistry)->newObject(thing, team, flags, 0);
	if (!replacement)
		return;

	Drawable *drawable = replacement->getDrawable();
	if (drawable)
	{
	char *player = *reinterpret_cast<char **>(
		reinterpret_cast<char *>(Rva002EE330ThePlayers) + 0x0c);
		int playerIndex = *reinterpret_cast<int *>(player + 0x24);
		if (source->getShroudedStatus(playerIndex) >= 3)
		{
			reinterpret_cast<ObjectWithDrawableBool *>(replacement)->getDrawable()->setDrawableHidden(true);
		}
	}

	if (*reinterpret_cast<unsigned int *>(reinterpret_cast<char *>(source) + 0x94)
		& 0x20000000)
		source->bfmeTransferReplacementState(replacement);

	reinterpret_cast<BfmeGlobFEA *>(TheBfmeGameLogic)->bfmeCallFEA(
		replacement, *reinterpret_cast<int *>(reinterpret_cast<char *>(source) + 0x370));

	Object *owner = TheBfmeGameLogic->findObjectByID(
		*reinterpret_cast<int *>(reinterpret_cast<char *>(source) + 0x78));
	bool copyMatrixAndLayer = true;
	if (owner && source->testStatus(2))
	{
		ExitInterface *exit = owner->getObjectExitInterface();
		if (exit)
		{
			int state = exit->canUseOwner(
				reinterpret_cast<BfmeObjZE *>(replacement)->bfmeOwnerZE());
			if (state != -1)
			{
				exit->updateOwner(replacement, state);
				copyMatrixAndLayer = false;
			}
		}
	}
	if (copyMatrixAndLayer)
	{
		replacement->setMatrix(reinterpret_cast<const Matrix3D *>(
			reinterpret_cast<char *>(source) + 8));
		replacement->setLayer(static_cast<PathfindLayerEnum>(source->getLayer()));
	}

	reinterpret_cast<BfmeHordeRefreshInterface *>(&m_rva0023cec0_0e4)->refresh(
		replacement, source, true);

	union
	{
		void (*raw)();
		void (BfmeHordeContainOwner::*member)(Object *);
	} update;
	update.raw = j_00017355;
	(this->*update.member)(replacement);

	union
	{
		void (*raw)();
		void *(BfmeHordeContainOwner::*member)(Object *);
	} find;
	find.raw = j_0003f5da;
	void *result = (this->*find.member)(replacement);
	if (result)
	{
		unsigned int nested = *reinterpret_cast<unsigned int *>(
			reinterpret_cast<char *>(result) + 4);
		m_rva0023cec0_1cc = *reinterpret_cast<unsigned int *>(
			reinterpret_cast<char *>(nested) + 0x14);
	}
}
