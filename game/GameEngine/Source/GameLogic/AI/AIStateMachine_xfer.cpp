// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System
// stlport
// ?xfer@AIStateMachine@@MAEXPAVXfer@@@Z
#include "ascii_string.h"
#include "xfer.h"
#include <vector>

struct Coord3DBase { float x, y, z; };
struct Coord3D : Coord3DBase {};
enum ObjectID { INVALID_OBJECT_ID = 0 };

struct XferVersion : Xfer::Version
{
	XferVersion(unsigned char value, unsigned char current)
	{
		data[0] = value;
		data[1] = current;
	}
};

// The waypoint ILT pin uses this return spelling for the AsciiString layout.
class BfmeWaypointNameString : public AsciiString {};

class Waypoint
{
public:
	BfmeWaypointNameString getName() const;
};

class Squad
{
public:
	virtual ~Squad();
	virtual void crc(Xfer *);
	virtual void xfer(Xfer *);
	virtual void loadPostProcess();

	_STL::vector<ObjectID> m_objectIDs;
	_STL::vector<void *> m_objectsCached;
};

class State
{
public:
	virtual ~State();
	unsigned int m_id;
	unsigned int getID() const { return m_id; }
};

class TerrainLogic
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30();
	virtual Waypoint *getWaypointByName(AsciiString name);
};

extern TerrainLogic *TheTerrainLogic;
extern void __cdecl friend_xferObjectID(Xfer *, ObjectID *);

class BfmeThingXZ;
class BfmeHostXZ
{
public:
	BfmeThingXZ *bfmeAcquireXZ(void *);
};

class AIStateMachine;
class BfmeSeedTarget;
// Existing ILT pins retain address-derived aliases for the base xfer and state lookup.
class Gen_0014F150
{
	friend class AIStateMachine;
	void bfmeAccept(BfmeSeedTarget *);
};

class StateMachine
{
public:
	virtual ~StateMachine();

protected:
	virtual void crc(Xfer *);
	virtual void xfer(Xfer *);
	char m_beforeGoalPath[0x40];
	State *internalGetState(unsigned int id);
};

class AIStateMachine : public StateMachine
{
protected:
	virtual void xfer(Xfer *);

public:
	_STL::vector<Coord3D> m_goalPath;
	const Waypoint *m_goalWaypoint;
	Squad *m_goalSquad;
	State *m_temporaryState;
	unsigned int m_temporaryStateFrameEnd;
	ObjectID m_objectID60;
	Coord3D m_coord64;
};

void AIStateMachine::xfer(Xfer *xfer)
{
	XferVersion version(1, 2);
	*xfer == version;
	reinterpret_cast<Gen_0014F150 *>(this)->bfmeAccept(reinterpret_cast<BfmeSeedTarget *>(xfer));

	int count = m_goalPath.size();
	*xfer == count;
	for (int i = 0; i < count; ++i)
	{
		Coord3D pos;
		if (xfer->IsStoring())
			pos = m_goalPath[i];
		*xfer == static_cast<Coord3DBase &>(pos);
		if (xfer->IsLoading())
			m_goalPath.push_back(pos);
	}

	AsciiString waypointName;
	if (m_goalWaypoint)
		waypointName = m_goalWaypoint->getName();
	*xfer == waypointName;
	if (xfer->IsLoading())
	{
		const unsigned char *data = *reinterpret_cast<const unsigned char *const *>(&waypointName);
		if (data && *reinterpret_cast<const unsigned short *>(data + 4) != 0)
			m_goalWaypoint = TheTerrainLogic->getWaypointByName(waypointName);
	}

	bool hasSquad = m_goalSquad != 0;
	*xfer == hasSquad;
	if (xfer->IsLoading() && hasSquad && m_goalSquad == 0)
		m_goalSquad = new Squad;
	if (hasSquad)
		*xfer == *reinterpret_cast<Snapshot *>(m_goalSquad);

	unsigned int id = 0xF423F;
	if (m_temporaryState)
		id = m_temporaryState->getID();
	*xfer == id;
	if (xfer->IsLoading() && id != 0xF423F)
		m_temporaryState = reinterpret_cast<State *>(
			reinterpret_cast<BfmeHostXZ *>(this)->bfmeAcquireXZ(reinterpret_cast<void *>(id)));
	if (m_temporaryState)
		*xfer == *reinterpret_cast<Snapshot *>(m_temporaryState);
	*xfer == m_temporaryStateFrameEnd;
	friend_xferObjectID(xfer, &m_objectID60);
	if (version.data[1] >= 2)
		*xfer == static_cast<Coord3DBase &>(m_coord64);
}
