// ?moveAlongWaypointPath@W3DView@@AAEXH_N@Z
// partial score=0.3 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// BFME W3DView::moveAlongWaypointPath(Int, Bool), retail 0x00741360 (545 bytes).
//
// The two-argument overload is the BFME camera-movement-mode path helper.  Its
// exact boundary is FUN_00b41360; updateCameraMovements calls it for the
// alternate and non-alternate movement states, while the W3DView constructor
// and neighboring camera bodies establish the containing object and fields.

typedef float Real;
typedef int Int;
typedef bool Bool;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct WaypointRecord
{
	Coord3D position;
	unsigned char padding0c[0xb8 - 0x0c];
};

struct WaypointRange
{
	WaypointRecord *current;
	WaypointRecord *end;
};

struct CameraMovementState
{
	unsigned char padding00[0x04];
	Int totalTime;
	Int elapsedTime;
	Int finishTime;
	unsigned char ease[0x08];
	Real currentDistance;
	Real unmodelled1c;
	unsigned char padding20[0x04];
	Bool active;
	unsigned char padding25[0x07];
	WaypointRecord *currentWaypoint;
	WaypointRecord *endWaypoint;
	unsigned char padding34[0x04];
	Real distanceScale;
	unsigned char padding3c[0x09];
	Bool segmentChanged;
	Bool movementFinished;
	unsigned char padding47[0x01];
	Coord3D result;
	unsigned char padding54[0x0c];
};

// The generated ILT names are retained for calls which retail makes through
// those exact import-style entries.  The typed wrappers below only provide the
// recovered ABI at each call site.
extern void j_000023f6(void);
extern void j_00012931(void);
extern void j_000442bf(void);
extern void j_000481fd(void);

static __forceinline void updateMinMax(Real *minimum, Real value, Real *maximum)
{
	typedef void (*Function)(Real *, Real, Real *);
	union
	{
		void (*raw)(void);
		Function typed;
	} thunk;
	thunk.raw = j_00012931;
	thunk.typed(minimum, value, maximum);
}

struct SegmentIndexCall
{
	Int apply(void);
};

static __forceinline Int segmentIndex(WaypointRecord **range)
{
	typedef Int (SegmentIndexCall::*Function)(void);
	union
	{
		void (*raw)(void);
		Function member;
	} thunk;
	thunk.raw = j_000023f6;
	return (reinterpret_cast<SegmentIndexCall *>(range)->*thunk.member)();
}

struct ParabolicEaseCall
{
	Real apply(Real param);
};

static __forceinline Real easeValue(void *ease, Real param)
{
	typedef Real (ParabolicEaseCall::*Function)(Real);
	union
	{
		void (*raw)(void);
		Function member;
	} thunk;
	thunk.raw = j_000442bf;
	return (reinterpret_cast<ParabolicEaseCall *>(ease)->*thunk.member)(param);
}

struct CameraMovementNotifyCall
{
	void apply(CameraMovementState *state, Bool nonAlternate, Int flags);
};

static __forceinline void notifyCameraMovement(CameraMovementState *state,
	Bool nonAlternate)
{
	typedef void (CameraMovementNotifyCall::*Function)(CameraMovementState *, Bool, Int);
	union
	{
		void (*raw)(void);
		Function member;
	} thunk;
	thunk.raw = j_000481fd;
	CameraMovementNotifyCall *owner =
		reinterpret_cast<CameraMovementNotifyCall *>(
			*(void **)0x012F101C);
	(owner->*thunk.member)(state, nonAlternate, 0);
}

class GlobalData
{
public:
	unsigned char padding[0xa74];
	Bool m_disableCameraMovement;
};

extern GlobalData *TheWritableGlobalData;
extern Real g_bfmeDefaultBU;

#define BFME_W3D_SLOT(n) virtual void slot##n(void) = 0;

class W3DView
{
public:
	BFME_W3D_SLOT(0)  BFME_W3D_SLOT(1)  BFME_W3D_SLOT(2)
	BFME_W3D_SLOT(3)  BFME_W3D_SLOT(4)  BFME_W3D_SLOT(5)
	BFME_W3D_SLOT(6)  BFME_W3D_SLOT(7)  BFME_W3D_SLOT(8)
	BFME_W3D_SLOT(9)  BFME_W3D_SLOT(10) BFME_W3D_SLOT(11)
	BFME_W3D_SLOT(12) BFME_W3D_SLOT(13) BFME_W3D_SLOT(14)
	BFME_W3D_SLOT(15) BFME_W3D_SLOT(16) BFME_W3D_SLOT(17)
	BFME_W3D_SLOT(18) BFME_W3D_SLOT(19) BFME_W3D_SLOT(20)
	BFME_W3D_SLOT(21) BFME_W3D_SLOT(22) BFME_W3D_SLOT(23)
	BFME_W3D_SLOT(24) BFME_W3D_SLOT(25) BFME_W3D_SLOT(26)
	virtual void setPosition(const Coord3D *position) = 0;

private:
	unsigned char padding0004[0x22f4 - 0x04];
	CameraMovementState standardMovement;
	Int cameraMovementMode;
	CameraMovementState alternateMovement;
	unsigned char padding23b8[0x08];
	Bool cameraHasMoved;
	unsigned char padding23c1[0x243c - 0x23c1];
	Coord3D alternatePosition;

	void moveAlongWaypointPath(Int milliseconds, Bool alternate);
};

static __forceinline Coord3D *waypointAt(WaypointRecord *current, Int index,
	Int bias)
{
	return reinterpret_cast<Coord3D *>(
		reinterpret_cast<unsigned char *>(current) + index * 0xb8 - bias);
}

// ?moveAlongWaypointPath@W3DView@@AAEXH_N@Z
void W3DView::moveAlongWaypointPath(Int milliseconds, Bool alternate)
{
	CameraMovementState &movement = alternate ? alternateMovement : standardMovement;
	if (!movement.active)
		return;

	Int previousElapsed = movement.elapsedTime;
	movement.elapsedTime += milliseconds;
	if (TheWritableGlobalData->m_disableCameraMovement) {
		if (movement.elapsedTime <= movement.totalTime)
			return;
		cameraHasMoved = false;
		return;
	}
	if (movement.elapsedTime > movement.totalTime) {
		if (!alternate && !movement.segmentChanged)
			setPosition(waypointAt(movement.currentWaypoint,
				segmentIndex(&movement.currentWaypoint), 0xbc));
		cameraHasMoved = false;
	}

	Int segment = segmentIndex(&movement.currentWaypoint);
	Coord3D source = *waypointAt(movement.currentWaypoint, segment, 0xcc);
	if (alternate) {
		alternatePosition = source;
	} else {
		setPosition(&source);
		updateMinMax(&reinterpret_cast<Real *>(this)[0x23fc / 4], source.x,
			&reinterpret_cast<Real *>(this)[0x2404 / 4]);
		updateMinMax(&reinterpret_cast<Real *>(this)[0x2400 / 4], source.y,
			&reinterpret_cast<Real *>(this)[0x2408 / 4]);
	}

	if (!movement.segmentChanged)
		movement.segmentChanged = true;

	Int oldElapsed = movement.elapsedTime - milliseconds;
	movement.elapsedTime = oldElapsed;
	Real timeFraction = g_bfmeDefaultBU / (Real)movement.totalTime;
	Real easedCurrent = easeValue(&movement.ease,
		(Real)movement.elapsedTime * timeFraction);
	Real easedPrevious = easeValue(&movement.ease,
		(Real)previousElapsed * timeFraction);
	movement.currentDistance += (easedCurrent - easedPrevious) * movement.distanceScale;

	if (movement.movementFinished) {
		movement.currentDistance = 0.0f;
		if (movement.elapsedTime > movement.finishTime) {
			movement.movementFinished = false;
			movement.elapsedTime = 0;
		}
	}

	if (!movement.segmentChanged)
		notifyCameraMovement(&movement, !alternate);

	Coord3D *result = &movement.result;
	if (alternate)
		*reinterpret_cast<Coord3D *>(reinterpret_cast<unsigned char *>(this) + 0x243c) = *result;
	else
		*reinterpret_cast<Coord3D *>(reinterpret_cast<unsigned char *>(this) + 0x0c) = *result;
}

#undef BFME_W3D_SLOT
