// cl: /DNDEBUG /DWIN32 /MD /EHsc /O2 /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stlp_nodealloc
// stlport
// Team::DoXfer (ZH Team::xfer), retail RVA 0x000F3550, 843 bytes (ret 4 at
// +0x348).
// Identity: Team's vftable 0x01085F88 (stored at RVAs 0x000F4271 and
// 0x000F77BC) holds ??_GTeam 0x000F7280 in slot 0, loadPostProcess
// 0x000F1800 in slot 1, and in slot 3, the BFME Snapshot DoXfer slot, ILT
// 0x00013007, which jumps to this body. tools/ilt_oracle.py check confirms
// ?DoXfer@Team@@MAEXAAVXfer@@@Z (exact). The body is GeneralsMD Team.cpp
// Team::xfer: team ID check, DLINK member walk (count, then save IDs or load
// the pending ID list), state, flags, destroy threshold, current units,
// waypoint ID relink through TheTerrainLogic, the 32 generic-script flags
// (BFME adds a dword per script), recruitability, common attack target, the
// two relation snapshots, then the BFME-only float, dword, ObjectID set
// (0x000EFB00) and flag. BFME throws XferException(5, 0) where ZH throws
// SC_INVALID_DATA.
// Shape: the member walk is the ZH DLINK_ITERATOR over the Object view of
// Rva000EDF80TeamMemberScan.cpp (vbptr at +0x68), so the pointer-to-member
// call reads the vbtable as retail does. The version record is
// function-scope: it keeps its own slot instead of sharing the throw
// temporary's, which gives retail's 0x34-byte frame.

#define BFME_STLP_NODE_ALLOC
#define _STLP_NO_EXCEPTIONS 1
#include <list>

// Use the original insert(end(), value) operation locally so this TU does
// not instantiate a competing out-of-line list<int>::push_back.
static inline void appendListWord(_STL::list<int> *list, const int &value)
{
	list->insert(list->end(), value);
}

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include "../System/xfer.h"
#include "../System/snapshot.h"

#include "../../../Include/Common/ScalarTypes.h"





typedef int ObjectID;

class Object;

class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl { public: virtual void bfmeObjectSlot0(void); };

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList(void) const;
};

class BfmeObjectDlinkPad { public: unsigned char m_pad[0x64]; };

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	ObjectID getID() const { return m_id; }

	unsigned char m_pad6C[4];
	ObjectID m_id;					// +0x74
};

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;

public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc) {}

	void advance(void)
	{
		if (m_cur)
			m_cur = (m_cur->*m_getNextFunc)();
	}

	Bool done(void) const { return m_cur == 0; }
	OBJCLASS *cur(void) const { return m_cur; }
};

struct XferVersion : public Xfer::Version
{
	XferVersion(unsigned char v)
	{
		data[0] = v;
		data[1] = v;
	}
};

class XferException
{
public:
	XferException(Int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();

	char *text;
	Int tag;
};

class Waypoint
{
public:
	UnsignedInt getID() const { return m_id; }

private:
	void *m_next;
	UnsignedInt m_id;
};

class TerrainLogic
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
	virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C();
	virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4C();
	virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5C();
	virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6C();
	virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7C();
	virtual Waypoint *getWaypointByID(UnsignedInt id);
};

extern TerrainLogic *TheTerrainLogic;

class MidVirtualSlot90Receiver;
// 0x0010C3C0 (through ILT 0x0000C9B4): the cdecl ObjectID hand-over helper.
Xfer &Rva0010C3C0(MidVirtualSlot90Receiver *receiver, void *context);

class BfmeObjectIDTree { public: unsigned char m_tree[0x10]; };
// 0x000EFB00 (through ILT 0x00012576): the cdecl ObjectID set transfer.
Xfer *xferObjectIDSet(Xfer *xfer, BfmeObjectIDTree *set);

class TeamRelationMap : public Snapshot {};
class PlayerRelationMap : public Snapshot {};

enum { MAX_GENERIC_SCRIPTS = 32 };

class Team
{
protected:
	virtual void DoXfer(Xfer &xfer);

private:
	DLINK_ITERATOR<Object> iterate_TeamMemberList(void) const
	{
		return DLINK_ITERATOR<Object>(m_firstItemIn_TeamMemberList,
			Object::dlink_next_TeamMemberList);
	}

	void *m_prototype;				// +0x04
	UnsignedInt m_id;				// +0x08
	Object *m_firstItemIn_TeamMemberList;		// +0x0C
	unsigned char m_pad10[8];
	AsciiString m_state;				// +0x18
	unsigned char m_pad1C[0x14];
	Bool m_enteredOrExited;				// +0x30
	Bool m_active;
	Bool m_created;
	Bool m_checkEnemySighted;
	Bool m_seeEnemy;
	Bool m_prevSeeEnemy;
	Bool m_wasIdle;
	Bool m_flag37;
	Int m_destroyThreshold;				// +0x38
	Int m_curUnits;					// +0x3C
	Waypoint *m_currentWaypoint;			// +0x40
	Bool m_shouldAttemptGenericScript[MAX_GENERIC_SCRIPTS];	// +0x44
	UnsignedInt m_genericScriptValue[MAX_GENERIC_SCRIPTS];	// +0x64
	Bool m_isRecruitablitySet;			// +0xE4
	Bool m_isRecruitable;
	Bool m_flagE6;
	Bool m_flagE7;
	ObjectID m_commonAttackTarget;			// +0xE8
	TeamRelationMap *m_teamRelations;		// +0xEC
	PlayerRelationMap *m_playerRelations;		// +0xF0
	Real m_realF4;					// +0xF4
	UnsignedInt m_valueF8;				// +0xF8
	Bool m_flagFC;					// +0xFC
	_STL::list<ObjectID> m_xferMemberIDList;	// +0x100
	BfmeObjectIDTree m_set104;			// +0x104
};

// ?DoXfer@Team@@MAEXAAVXfer@@@Z
void Team::DoXfer(Xfer &xfer)
{
	if (xfer.IsLightCRC())
		return;

	XferVersion version(1);
	xfer == version;

	UnsignedInt teamID = m_id;
	xfer == teamID;
	if (teamID != m_id)
		throw XferException(5, 0);

	ObjectID memberID;
	UnsignedShort memberCount = 0;
	for (DLINK_ITERATOR<Object> objIt = iterate_TeamMemberList(); !objIt.done(); objIt.advance())
		memberCount++;
	xfer == memberCount;
	if (xfer.IsStoring())
	{
		for (DLINK_ITERATOR<Object> objIt = iterate_TeamMemberList(); !objIt.done(); objIt.advance())
		{
			memberID = objIt.cur()->getID();
			Rva0010C3C0((MidVirtualSlot90Receiver *)&xfer, &memberID);
		}
	}
	else
	{
		for (UnsignedShort i = 0; i < memberCount; ++i)
		{
			Rva0010C3C0((MidVirtualSlot90Receiver *)&xfer, &memberID);
			appendListWord(&m_xferMemberIDList, memberID);
		}
	}

	xfer == m_state;
	xfer == m_enteredOrExited;
	xfer == m_active;
	xfer == m_created;
	xfer == m_checkEnemySighted;
	xfer == m_seeEnemy;
	xfer == m_prevSeeEnemy;
	xfer == m_wasIdle;
	xfer == m_flag37;
	xfer == m_destroyThreshold;
	xfer == m_curUnits;

	UnsignedInt currentWaypointID = m_currentWaypoint ? m_currentWaypoint->getID() : 0;
	xfer == currentWaypointID;
	if (xfer.IsLoading())
		m_currentWaypoint = TheTerrainLogic->getWaypointByID(currentWaypointID);

	UnsignedShort shouldAttemptGenericScriptCount = MAX_GENERIC_SCRIPTS;
	xfer == shouldAttemptGenericScriptCount;
	if (shouldAttemptGenericScriptCount != MAX_GENERIC_SCRIPTS)
		throw XferException(5, 0);

	for (Int i = 0; i < shouldAttemptGenericScriptCount; ++i)
	{
		xfer == m_shouldAttemptGenericScript[i];
		xfer == m_genericScriptValue[i];
	}

	xfer == m_isRecruitablitySet;
	xfer == m_isRecruitable;
	xfer == m_flagE6;
	xfer == m_flagE7;
	Rva0010C3C0((MidVirtualSlot90Receiver *)&xfer, &m_commonAttackTarget);
	xfer == *m_teamRelations;
	xfer == *m_playerRelations;
	xfer == m_realF4;
	xfer == m_valueF8;
	xferObjectIDSet(&xfer, &m_set104);
	xfer == m_flagFC;
}
