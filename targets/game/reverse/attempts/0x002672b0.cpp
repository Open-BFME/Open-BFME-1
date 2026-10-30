// ?rva002672B0@SiegeDeploySpecialPower@@UAEXPBXPBVObject@@PBVCoord3D@@I0@Z
// partial score=0.9908 date=2026-10-30
// cl: /DNDEBUG /MD /EHsc
// Retail 0x002672B0 (650 B, ret 0x14): slot 0 of SiegeDeploySpecialPower's +0x20 interface
// vtable 0x00CB7468 (ILT 0x000199C0).  Shape from the BFME 2 donor
// Code/GameEngine/Source/GameLogic/Object/SpecialPower/SiegeDeploySpecialPower.cpp
// (initiateIntentToDoSpecialPower, open-bfme-2 20a0cb6173); the real name is
// ILT-contradicted for 3456 signature variants, so the method keeps its address.
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

class Coord3D
{
public:
	Coord3D() {}
	Coord3D(const Coord3D &other) : x(other.x), y(other.y), z(other.z) {}
	Real x;
	Real y;
	Real z;
};

enum NameKeyType { NAMEKEY_INVALID };
enum CommandSourceType { CMD_FROM_AI = 2 };
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Module;
class SiegeDeploySpecialPower;

class Object
{
	friend class SiegeDeploySpecialPower;
protected:
	Module *findModule(NameKeyType key) const;
public:
	unsigned char m_unmodelled00[0x08];
	Real m_xAxisX;							// +0x08
	unsigned char m_unmodelled0C[0x0C];
	Real m_xAxisY;							// +0x18
	unsigned char m_unmodelled1C[0x0C];
	Real m_xAxisZ;							// +0x28
	unsigned char m_unmodelled2C[0x0C];
	Coord3D m_position;						// +0x38
	unsigned char m_unmodelled44[0x30];
	Int m_id;								// +0x74
};

class GameLogic
{
public:
	Object *findObjectByID(Int id);
};
extern GameLogic *TheGameLogic;

class Rva002672B0DockInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual Bool acceptsDockFor(Int id);
};

class Module
{
public:
	unsigned char m_unmodelled00[0x20];
	Rva002672B0DockInterface m_dock;		// +0x20
};

template <int NUMBITS> class BitFlags
{
public:
	enum BogusInitType { kInit = 0 };
	BitFlags(BogusInitType, Int index);
	UnsignedInt m_bits[6];
};

struct VptrZeroBlock24
{
	UnsignedInt m_dwords[6];
};

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *) = 0;
	virtual Int getPlayerMask();
	PartitionFilter *m_next;
};

class Rva00251980VptrZeroBlockObject : public PartitionFilter
{
public:
	Rva00251980VptrZeroBlockObject(const VptrZeroBlock24 &mask);
	virtual ~Rva00251980VptrZeroBlockObject() {}
	virtual Bool allow(Object *);
	VptrZeroBlock24 m_block;
};

struct Rva002672B0Entry
{
	Object *m_object;
	Int m_unknown04;
};

struct Rva002672B0Data
{
	Rva002672B0Entry *m_begin;
	Rva002672B0Entry *m_end;
	Rva002672B0Entry *m_capacity;
	Rva002672B0Entry *m_current;
};

struct BfmeWideResult
{
	Rva002672B0Data *m_value;
	~BfmeWideResult();
	Object *next()
	{
		Rva002672B0Entry *end = m_value->m_end;
		if (m_value->m_current == end)
			return 0;
		return (m_value->m_current++)->m_object;
	}
};

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(Int, Int, Int, Int, Int);
};
extern BfmeWideForwardC *ThePartitionManager;

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	void ignoreObstacle(const Object *obj);
	unsigned char m_unmodelled00[0x20];
	AICommandInterface m_command;			// +0x20
};

struct Rva002672B0Owner
{
	unsigned char m_unmodelled00[0x204];
	AIUpdateInterface *m_ai;				// +0x204
};

class SiegeDeploySpecialPowerModuleData
{
public:
	unsigned char m_unmodelled00[0x1DC];
	Real m_searchRadius;					// +0x1DC
	Real m_pushDistance;					// +0x1E0
	Int searchRadiusBits() const { return *(const Int *)&m_searchRadius; }
};

class UpdateModule
{
public:
	virtual ~UpdateModule();
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
public:
	const SiegeDeploySpecialPowerModuleData *m_data;	// +0x04
	Object *m_object;						// +0x08
	const SiegeDeploySpecialPowerModuleData *getData() const { return m_data; }
};

class Rva00266EB0SiegeDeployBase
{
public:
	void transition(Int phase);
	void clearStatusBit63();
};

class SiegeDeployIface0C { public: virtual void slot00(); };
class SiegeDeployIface10 { public: virtual void slot00(); unsigned char m_iface10Data[0x0C]; };
class SiegeDeploySpecialPowerInterface
{
public:
	virtual void rva002672B0(const void *specialPowerTemplate, const Object *targetObj,
		const Coord3D *targetPos, UnsignedInt commandOptions, const void *way) = 0;
	virtual void slot01() = 0;
	virtual Bool slot02() = 0;
};
class SiegeDeployIface24 { public: virtual void slot00(); };

struct Rva002666A0Point
{
	Real x;
	Real y;
	Real z;
};

class SiegeDeploySpecialPower : public UpdateModule, public SiegeDeployIface0C,
	public SiegeDeployIface10, public SiegeDeploySpecialPowerInterface, public SiegeDeployIface24
{
public:
	virtual void rva002672B0(const void *specialPowerTemplate, const Object *targetObj,
		const Coord3D *targetPos, UnsignedInt commandOptions, const void *way);
	virtual void slot01();
	virtual Bool slot02();

	Rva002666A0Point rva002666A0(Object *dock, Coord3D *dockPosition, Bool *docked);

	unsigned char m_unmodelled28[0x18];
	Int m_dockID;							// +0x40
	unsigned char m_unmodelled44[0x10];
	Rva002666A0Point m_approachPoint;		// +0x54
	Bool m_docked;							// +0x60
	Coord3D m_dockPosition;					// +0x64
};

void SiegeDeploySpecialPower::rva002672B0(const void *specialPowerTemplate, const Object *targetObj,
	const Coord3D *targetPos, UnsignedInt commandOptions, const void *way)
{
	if (slot02())
		return;
	if (!targetObj)
		return;
	Object *dockObject = 0;
	Object *self = m_object;
	AIUpdateInterface *ai = ((Rva002672B0Owner *)self)->m_ai;
	if (!ai)
		return;
	static NameKeyType key = TheNameKeyGenerator->nameToKey("SiegeDockingBehavior");
	Module *dock = targetObj->findModule(key);
	if (!dock)
		return;
	Int selfID = self->m_id;
	if (dock->m_dock.acceptsDockFor(selfID))
	{
		dockObject = TheGameLogic->findObjectByID(targetObj->m_id);
	}
	else
	{
		BfmeWideResult hits = ThePartitionManager->bfmeForwardWideC((Int)&targetObj->m_position,
			*(const Int *)&getData()->m_searchRadius, 0,
			(Int)&Rva00251980VptrZeroBlockObject(*(const VptrZeroBlock24 *)&BitFlags<192>(BitFlags<192>::kInit, 0x3B)), 1);
		Object *other;
		while ((other = hits.next()) != 0)
		{
			Module *otherDock = other->findModule(key);
			if (!otherDock)
				continue;
			Int id = self->m_id;
			if (otherDock->m_dock.acceptsDockFor(id))
			{
				dockObject = other;
				break;
			}
		}
	}
	if (dockObject)
	{
		Bool docked = false;
		m_approachPoint = rva002666A0(dockObject, &m_dockPosition, &docked);
		if (docked)
		{
			ai->ignoreObstacle(dockObject);
			ai->m_command.aiIdle(CMD_FROM_AI);
			ai->m_command.aiMoveToPosition((const Coord3D *)&m_approachPoint, CMD_FROM_AI);
			m_docked = true;
			((Rva00266EB0SiegeDeployBase *)(UpdateModule *)this)->transition(1);
			m_dockID = dockObject->m_id;
		}
		else
		{
			m_dockID = 0;
			((Rva00266EB0SiegeDeployBase *)(UpdateModule *)this)->clearStatusBit63();
		}
	}
	else
	{
		if (m_data->m_pushDistance > 0.0f)
		{
			Coord3D pos(targetObj->m_position);
			Coord3D p;
			p.z = pos.z;
			Coord3D forward;
			forward.x = targetObj->m_xAxisX;
			forward.y = targetObj->m_xAxisY;
			forward.z = targetObj->m_xAxisZ;
			Real scale = m_data->m_pushDistance;
			forward.x *= scale;
			forward.y *= scale;
			forward.z *= scale;
			p.x = pos.x + forward.x;
			p.y = pos.y + forward.y;
			ai->m_command.aiMoveToPosition(&p, CMD_FROM_AI);
		}
		else
		{
			ai->m_command.aiMoveToPosition(&targetObj->m_position, CMD_FROM_AI);
		}
	}
	setWakeFrame(m_object, UPDATE_SLEEP_NONE);
}
