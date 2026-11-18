// ?setZoom@W3DView@@UAEXM@Z
// Retail 0x00742F70 (retail's ILT confirms the name; see
// identity_evidence/w3dview-setzoom-setheight-swap.md). Like
// setHeightAboveGround (0x00742E60), BFME refuses the change while the game
// client blocks camera changes on a zoom-limited view or a camera movement
// owns the view; unlike Zero Hour it clamps only a zoom-limited view, the
// minimum test reading the argument and the maximum test the stored zoom.
// cl: /DNDEBUG /MD /EHsc

#include "../../../../GameEngine/Include/Common/ScalarTypes.h"


class GameClient
{
private:
	unsigned char m_padding0000[0xBC];

public:
	Bool m_cameraChangeBlocked;
};

extern GameClient *TheGameClient;

class W3DView
{
public:
	virtual void setZoom(Real zoom);

private:
	unsigned char m_padding0004[0x34 - 0x04];
	Real m_maxZoom;
	Real m_minZoom;
	Real m_zoom;
	unsigned char m_padding0040[0x44 - 0x40];
	Bool m_zoomLimited;
	unsigned char m_padding0045[0x1DC - 0x45];
	Bool m_doingMoveCameraOnWaypointPath;
	unsigned char m_padding01DD[0x204 - 0x1DD];
	Bool m_zoomingCamera;
	unsigned char m_padding0205[0x228 - 0x205];
	Bool m_doingZoomCamera;
	unsigned char m_padding0229[0x27C - 0x229];
	Bool m_cameraMovementAlternate;
	Bool m_cameraMovementFinished;
	unsigned char m_padding027E[0x2354 - 0x27E];
	int m_cameraMovementMode;
	unsigned char m_padding2358[0x240C - 0x2358];
	Bool m_cameraConstraintValid;

	void setCameraTransform();
};

void W3DView::setZoom(Real zoom)
{
	if (TheGameClient->m_cameraChangeBlocked && m_zoomLimited)
		return;
	if (m_cameraMovementMode != 0)
		return;
	if (m_doingMoveCameraOnWaypointPath)
		return;
	if (m_zoomingCamera)
		return;
	if (m_doingZoomCamera)
		return;
	if (m_cameraMovementFinished)
		return;
	if (m_cameraMovementAlternate)
		return;

	m_zoom = zoom;
	if (m_zoomLimited && m_zoom < m_minZoom)
		m_zoom = m_minZoom;
	if (m_zoomLimited && m_zoom > m_maxZoom)
		m_zoom = m_maxZoom;

	m_doingMoveCameraOnWaypointPath = false;
	m_zoomingCamera = false;
	m_doingZoomCamera = false;
	m_cameraMovementAlternate = false;
	m_cameraMovementFinished = false;
	m_cameraConstraintValid = false;
	setCameraTransform();
}
