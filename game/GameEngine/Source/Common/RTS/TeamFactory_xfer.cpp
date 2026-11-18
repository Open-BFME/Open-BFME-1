// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/stringinline
// stlport
//
// TeamFactory::DoXfer (ZH TeamFactory::xfer), retail RVA 0x000EF0D0, 351
// bytes, ending with the noreturn _CxxThrowException call at +0x15A (INT3
// padding follows).
// Identity: the TeamFactory constructor 0x000F2250 installs the Snapshot
// vftable 0x01085F08 at this+8. Its slot 2 reaches the literal "TeamFactory"
// name getter 0x000F2300 and its slot 3 (the BFME Snapshot DoXfer slot, as in
// GarrisonContain and TeamRelationMap) reaches this body through ILT
// 0x00012AF8. The ILT table confirms ?DoXfer@TeamFactory@@MAEXAAVXfer@@@Z,
// the BFME Snapshot spelling of System/snapshot.h. The body is GeneralsMD
// Team.cpp TeamFactory::xfer: version, unique team ID at TeamFactory+0x1C,
// prototype count of the pair-keyed map at +0x0C, then a save loop over the
// map and a load loop through the id-matching prototype walk at 0x000EF010.
// BFME throws XferException(5, 0) (ThrowInfo VA 0x011DFE5C) where ZH throws
// SC_INVALID_DATA. Retail frame: the scoped version record shares its slot
// with the first throw temporary, as in GarrisonContain_xfer.cpp.

#define BFME_STLP_NODE_ALLOC
#include <map>

#include "StringInline.h"

#include "../../../Include/Common/ScalarTypes.h"




typedef UnsignedInt TeamID;
typedef UnsignedInt TeamPrototypeID;

#include "../System/snapshot.h"

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void init(void);
	virtual void reset(void);
	virtual void update(void);

private:
	void *m_name;
};

struct XferVersion
{
	XferVersion(UnsignedByte version) :
		m_version(version), m_currentVersion(version)
	{
	}

	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

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
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void xferTeamID(UnsignedInt *);
	virtual void slot30();
	virtual void xferUnsignedShort(UnsignedShort *);
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

class TeamPrototype : public Snapshot
{
	friend class TeamFactory;

private:
	void *m_factory;
	void *m_owningPlayer;
	TeamPrototypeID m_id;
};

struct BfmeQ1107;

class BfmeW1107
{
public:
	BfmeQ1107 *bfmeGo1107A(int);
};

typedef _STL::pair<Int, Int> TeamPrototypeKey;
typedef _STL::map<TeamPrototypeKey, TeamPrototype *> TeamPrototypeMap;

class TeamFactory : public SubsystemInterface, public Snapshot
{
protected:
	virtual void DoXfer(Xfer &xfer);

private:
	TeamPrototypeMap m_prototypes;
	TeamPrototypeID m_uniqueTeamPrototypeID;
	TeamID m_uniqueTeamID;
};

// ?DoXfer@TeamFactory@@MAEXAAVXfer@@@Z
void TeamFactory::DoXfer(Xfer &xferRef)
{
	Xfer *xfer = &xferRef;

	if (xfer->isDoingCRC())
		return;

	{
		XferVersion version(1);
		xfer->xferVersion(&version);
	}

	xfer->xferTeamID(&m_uniqueTeamID);

	UnsignedShort prototypeCount = m_prototypes.size();
	xfer->xferUnsignedShort(&prototypeCount);
	if (prototypeCount != m_prototypes.size())
		throw XferException(5, 0);

	TeamPrototypeMap::iterator it;
	TeamPrototypeID teamPrototypeID;
	TeamPrototype *teamPrototype;
	AsciiString prototypeName;
	if (xfer->isSaving())
	{
		for (it = m_prototypes.begin(); it != m_prototypes.end(); ++it)
		{
			teamPrototype = (*it).second;
			teamPrototypeID = teamPrototype->m_id;
			xfer->xferTeamID(&teamPrototypeID);
			xfer->xferSnapshot(teamPrototype);
		}
	}
	else
	{
		for (UnsignedShort i = 0; i < prototypeCount; ++i)
		{
			xfer->xferTeamID(&teamPrototypeID);
			// 0x000EF010 is ZH findTeamPrototypeByID (ledger name kept).
			teamPrototype = (TeamPrototype *)((BfmeW1107 *)this)->bfmeGo1107A(teamPrototypeID);
			if (teamPrototype == 0)
				throw XferException(5, 0);
			xfer->xferSnapshot(teamPrototype);
		}
	}
}
