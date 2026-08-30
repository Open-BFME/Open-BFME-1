// cl: /DNDEBUG /MD /EHsc

typedef unsigned int ObjectID;
typedef unsigned int UnsignedInt;

struct Coord3D
{
	float x, y, z;
};

class GeometryInfo
{
public:
	float getMaxHeightAbovePosition() const;
};

class BfmeLocomotorTemplate
{
public:
	BfmeLocomotorTemplate *getFinalOverride();

	void *m_vtable;
	BfmeLocomotorTemplate *m_override;
	unsigned char m_pad08[0x48d];
	unsigned char m_appearance;
};

class Object
{
public:
	unsigned char m_pad00[4];
	BfmeLocomotorTemplate *m_locomotorTemplate;
	unsigned char m_pad08[0x30];
	Coord3D m_position;
	unsigned char m_pad44[0x30];
	ObjectID m_id;
	unsigned char m_pad78[0x34];
	GeometryInfo m_geometry;
	unsigned char m_padAD[0x297];
	UnsignedInt m_status;
};

class GameLogic
{
public:
	Object *findObjectByID(int id);

	unsigned char m_pad00[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

struct BfmeMemberIndexNode
{
	unsigned char m_pad00[0x14];
	int m_index;
};

struct BfmeMemberIndexIterator
{
	BfmeMemberIndexNode *m_node;
};

class BfmeMemberIndexMap
{
public:
	BfmeMemberIndexIterator find(const int &id);

	BfmeMemberIndexNode *m_header;
	unsigned char m_pad04[8];
};

struct BfmeXferVersion
{
	unsigned char m_version;
	unsigned char m_minimumVersion;
};

class BfmeXfer
{
public:
	virtual void v00() = 0; virtual void v01() = 0;
	virtual void v02() = 0; virtual void v03() = 0;
	virtual void v04() = 0; virtual void v05() = 0;
	virtual void v06() = 0; virtual void v07() = 0;
	virtual void v08() = 0; virtual void v09() = 0;
	virtual void xferVersion(BfmeXferVersion *version) = 0;
	virtual void v11() = 0; virtual void v12() = 0;
	virtual void v13() = 0; virtual void v14() = 0;
	virtual void v15() = 0; virtual void v16() = 0;
	virtual void v17() = 0; virtual void v18() = 0;
	virtual void v19() = 0; virtual void v20() = 0;
	virtual void v21() = 0; virtual void v22() = 0;
	virtual void v23() = 0;
	virtual void xferTrackedPosition(Coord3D *position) = 0;
	virtual void v25() = 0; virtual void v26() = 0;
	virtual void xferLargeUnitValue(float *value) = 0;
	virtual void v28() = 0;
	virtual void xferTrackedFrame(UnsignedInt *frame) = 0;
};

void bfmeXferObjectID(BfmeXfer *xfer, ObjectID *id);

class BfmeAODHordeContainOwner
{
public:
	void refreshTrackedLargeUnit();
	int bfmeGetMemberIndex(int memberID);
	void xfer(BfmeXfer *xfer);
	void bfmeBaseXfer(BfmeXfer *xfer);

private:
	unsigned char m_pad00[0x120];
	BfmeMemberIndexMap m_memberIndices;
	unsigned char m_pad12C[0x104];
	ObjectID m_trackedLargeUnit;
	UnsignedInt m_lastLargeUnitFrame;
	Coord3D m_trackedPosition;
	float m_largeUnitHeightFactor;
	float m_largeUnitHeight;
	float m_largeUnitTailOff;
};

class AODHordeContainInterfaceView
{
public:
	void bfmeTrackLargeUnit(Object *source, Object *unit);

private:
	unsigned char m_pad04[0x14c];
	ObjectID m_trackedLargeUnit;
	UnsignedInt m_lastLargeUnitFrame;
};

// AOD's flow simulation only follows live treaded objects; the base horde hook
// at the same virtual slot is empty, and the derived hook refreshes its cached
// position only when the tracked object changes.
void AODHordeContainInterfaceView::bfmeTrackLargeUnit(Object *, Object *unit)
{
	if (unit == 0 || (unit->m_status & 1) != 0)
		return;

	BfmeLocomotorTemplate *locomotor = unit->m_locomotorTemplate;
	if (locomotor != 0 && locomotor->m_override != 0)
		locomotor = locomotor->m_override->getFinalOverride();

	if (locomotor->m_appearance == 2 && unit->m_id != m_trackedLargeUnit)
	{
		m_trackedLargeUnit = unit->m_id;
		reinterpret_cast<BfmeAODHordeContainOwner *>(
			reinterpret_cast<unsigned char *>(this) - 0xe4)->refreshTrackedLargeUnit();
		m_lastLargeUnitFrame = TheGameLogic->m_frame;
	}
}

void BfmeAODHordeContainOwner::refreshTrackedLargeUnit()
{
	Object *unit = TheGameLogic->findObjectByID((int)m_trackedLargeUnit);
	if (unit == 0)
	{
		m_trackedLargeUnit = 0;
		return;
	}

	m_trackedPosition = unit->m_position;
	m_largeUnitHeightFactor = 17.0f;
	m_largeUnitHeight = unit->m_geometry.getMaxHeightAbovePosition();
}

int BfmeAODHordeContainOwner::bfmeGetMemberIndex(int memberID)
{
	BfmeMemberIndexIterator i = m_memberIndices.find(memberID);
	if (i.m_node != m_memberIndices.m_header)
		return i.m_node->m_index;
	return 0;
}

void BfmeAODHordeContainOwner::xfer(BfmeXfer *xfer)
{
	BfmeXferVersion version = { 1, 1 };
	xfer->xferVersion(&version);
	bfmeBaseXfer(xfer);
	bfmeXferObjectID(xfer, &m_trackedLargeUnit);
	xfer->xferLargeUnitValue(&m_largeUnitTailOff);
	xfer->xferTrackedFrame(&m_lastLargeUnitFrame);
	if (m_trackedLargeUnit != 0)
		refreshTrackedLargeUnit();
	xfer->xferTrackedPosition(&m_trackedPosition);
}
