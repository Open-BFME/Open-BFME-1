// cl: /DNDEBUG /MD
// readable body of ?updateCameraMovements@W3DView@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DView.cpp
// BFME W3DView::updateCameraMovements, retail 0x00744530.

typedef int Int;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	char m_padding[0xA90];
	Bool m_disableCameraMovement;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	char m_padding[0x3C];
	Int m_frame;
};

extern GlobalData *TheWritableGlobalData;
extern GameLogic *TheGameLogic;
extern Int TheW3DFrameLengthInMsec;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord2D
{
	float x;
	float y;
	Coord2D &operator=(const Coord2D &other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DView.h
class W3DView
{
public:
	Bool updateCameraMovements(void);

private:
	void zoomCameraOneFrame(void);
	void pitchCameraOneFrame(void);
	// Two more one-frame easers with no upstream twin; each is guarded by the
	// flag named after it and blends one Real field, +0x70 and +0x30.
	void cameraUpdateOneFrame(void);
	void cameraUpdateAlternateOneFrame(void);
	void rotateCameraOneFrame(void);
	void lerpCameraOneFrame(void);
	void moveAlongWaypointPath(Int milliseconds);
	void moveAlongWaypointPath(Int milliseconds, Bool alternate);

	char m_padding000[0x0C];
	Coord3D m_pos;
	char m_padding018[0x1DC - 0x18];
	Bool m_doingRotateCamera;
	char m_padding1DD[0x204 - 0x1DD];
	Bool m_doingCameraUpdate;
	char m_padding205[0x228 - 0x205];
	Bool m_doingZoomCamera;
	char m_padding229[0x254 - 0x229];
	Bool m_doingPitchCamera;
	char m_padding255[0x27C - 0x255];
	Bool m_doingCameraUpdateAlternate;
	Bool m_cameraMovementFinished;
	char m_padding27E[0x2354 - 0x27E];
	Int m_cameraMovementMode;
	char m_padding2358[0x23B8 - 0x2358];
	Bool m_doingMoveCameraOnWaypointPath;
	char m_padding23B9[0x23E4 - 0x23B9];
	Coord2D m_previousLookAtPosition;
	char m_padding23EC[0x24B4 - 0x23EC];
	Int m_cameraMovementLastFrame;
};

// ?updateCameraMovements@W3DView@@QAE_NXZ
Bool W3DView::updateCameraMovements(void)
{
	register Bool didUpdate = false;

	if (TheWritableGlobalData->m_disableCameraMovement) {
		Int frame = TheGameLogic->m_frame;
		if (m_cameraMovementLastFrame < frame) {
			m_cameraMovementLastFrame = frame;
		}
	}

	if (m_doingZoomCamera) {
		zoomCameraOneFrame();
		didUpdate = true;
	}
	if (m_doingPitchCamera) {
		pitchCameraOneFrame();
		didUpdate = true;
	}
	if (m_doingCameraUpdate) {
		cameraUpdateOneFrame();
		didUpdate = true;
	}
	if (m_doingCameraUpdateAlternate) {
		cameraUpdateAlternateOneFrame();
		didUpdate = true;
	}
	if (m_doingRotateCamera) {
		m_previousLookAtPosition = *(const Coord2D *)&m_pos;
		rotateCameraOneFrame();
		didUpdate = true;
	}
	if (m_doingMoveCameraOnWaypointPath) {
		moveAlongWaypointPath(TheW3DFrameLengthInMsec, true);
		didUpdate = true;
	}

	switch (m_cameraMovementMode) {
	case 1:
		m_previousLookAtPosition = *(const Coord2D *)&m_pos;
		moveAlongWaypointPath(TheW3DFrameLengthInMsec);
		goto camera_movement_updated;
	case 2:
		m_previousLookAtPosition = *(const Coord2D *)&m_pos;
		moveAlongWaypointPath(TheW3DFrameLengthInMsec, false);
		goto camera_movement_updated;
	case 3:
		lerpCameraOneFrame();
		goto camera_movement_updated;
	}
	goto camera_movement_finished;

camera_movement_updated:
	didUpdate = true;

camera_movement_finished:

	if (m_cameraMovementFinished) {
		didUpdate = true;
	}
	return didUpdate;
}
