// ?xfer@TeamRelationMap@@MAEXPAVXfer@@@Z
// partial score=0.9591 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// TeamRelationMap::xfer, retail 0x000F3C50, 269 bytes.
//
// BFME keeps one virtual base at TeamRelationMap+0 and the STLport relation
// map at +4.  The save/load body is the Team relation serializer from the
// upstream Team.h model.  BFME's three argument xferUser call is the existing
// 25-byte Relationship forwarder at 0x0010BE40; using that real helper keeps
// the retail literal and virtual slot rather than inventing a local wrapper.

#include <hash_map>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Snapshot;

// BFME Xfer layout: xferVersion +0x28, xferUnsignedShort +0x7c,
// isSaving +0x08, isDoingCRC +0x10.  The other declarations reserve the
// intervening slots so the calls use the retail vtable offsets.
class Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual Bool isSaving();
	virtual void slot03();
	virtual Bool isDoingCRC();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(XferVersion *);
	virtual void slot11();
	virtual void xferSnapshot(Snapshot *);
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void xferAsciiString(void *);
	virtual void slot27();
	virtual void slot28();
	virtual void xferTeamID(UnsignedInt *);
	virtual void slot30();
	virtual void xferUnsignedShort(UnsignedShort *);
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(Bool *);
};

// This is defined in MidVirtualSlot90Forwarders.cpp.  It is the retail
// helper used by this body, not a replacement implementation: it forwards
// ("Relationship", context, 4) to Xfer's slot +0x90.
class MidVirtualSlot90Receiver;
extern void Rva0010BE40(MidVirtualSlot90Receiver *, void *);

class TeamRelationPoolObject
{
public:
	virtual ~TeamRelationPoolObject() {}

protected:
	virtual void crc(Xfer *);
	virtual void xfer(Xfer *);
	virtual void loadPostProcess();
};

typedef unsigned int TeamID;
enum Relationship
{
	NEUTRAL = 0
};

typedef _STL::pair<const TeamID, Relationship> TeamRelationMapPair;
typedef _STL::hash_map<TeamID, Relationship, _STL::hash<TeamID>,
	_STL::equal_to<TeamID>, _STL::allocator<TeamRelationMapPair> >
	TeamRelationMapType;

class TeamRelationMap : public TeamRelationPoolObject
{
public:
	virtual ~TeamRelationMap();

protected:
	virtual void crc(Xfer *);
	virtual void xfer(Xfer *);
	virtual void loadPostProcess();

private:
	TeamRelationMapType m_map;
};

// ?xfer@TeamRelationMap@@MAEXPAVXfer@@@Z
void TeamRelationMap::xfer(Xfer *xfer)
{
    if (xfer->isDoingCRC())
        return;

    {
        XferVersion version = { 1, 1 };
        xfer->xferVersion(&version);
    }

    UnsignedShort teamRelationCount = m_map.size();
    xfer->xferUnsignedShort(&teamRelationCount);

    TeamID teamID;
    if (xfer->isSaving())
    {
        TeamRelationMapType::iterator teamRelationIt;
        for (teamRelationIt = m_map.begin(); teamRelationIt != m_map.end(); ++teamRelationIt)
        {
            teamID = (*teamRelationIt).first;
            xfer->xferTeamID(&teamID);
            Relationship relationship = (*teamRelationIt).second;
            Rva0010BE40((MidVirtualSlot90Receiver *)xfer, &relationship);
        }
    }
    else
    {
        Relationship relationship;
        for (UnsignedShort i = 0; i < teamRelationCount; ++i)
        {
            xfer->xferTeamID(&teamID);
            Rva0010BE40((MidVirtualSlot90Receiver *)xfer, &relationship);
            m_map[teamID] = relationship;
        }
    }
}
