// cl: /DNDEBUG /MD /EHsc

typedef unsigned int ObjectID;
typedef unsigned int UnsignedInt;

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
	unsigned char m_pad08[0x6c];
	ObjectID m_id;
	unsigned char m_pad78[0x2cc];
	UnsignedInt m_status;
};

class GameLogic
{
public:
	unsigned char m_pad00[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

class BfmeAODHordeContainOwner
{
public:
	void refreshTrackedLargeUnit();
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
