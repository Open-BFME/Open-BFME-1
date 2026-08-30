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

class BfmeAODHordeContainOwner
{
public:
	void refreshTrackedLargeUnit();

private:
	unsigned char m_pad00[0x230];
	ObjectID m_trackedLargeUnit;
	unsigned char m_pad234[4];
	Coord3D m_trackedPosition;
	float m_largeUnitHeightFactor;
	float m_largeUnitHeight;
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
