// Partial reconstruction for retail 0x00742F70.
// partial score=0.9 date=2026-09-08
// The W3DView fields and movement guards identify this body as
// ?setHeightAboveGround@W3DView@@UAEXM@Z. MSVC 7.1 emits the camera-change
// byte in BL and the zero value in EDX here, while retail keeps the byte in DL,
// preserves EBX, and uses BL for every zero comparison and reset.

typedef bool Bool;
typedef float Real;

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
	virtual void setHeightAboveGround(Real height);

private:
	unsigned char m_padding0004[0x34 - 0x04];
	Real m_minHeightAboveGround;
	Real m_maxHeightAboveGround;
	Real m_heightAboveGround;
	unsigned char m_padding0040[0x44 - 0x40];
	Bool m_zoomLimited;
	unsigned char m_padding0045[0x1DC - 0x45];
	Bool m_rotatingCamera;
	unsigned char m_padding01DD[0x204 - 0x1DD];
	Bool m_zoomingCamera;
	unsigned char m_padding0205[0x228 - 0x205];
	Bool m_pitchingCamera;
	unsigned char m_padding0229[0x27C - 0x229];
	Bool m_cameraMovementAlternate;
	Bool m_cameraMovementFinished;
	unsigned char m_padding027E[0x2354 - 0x27E];
	int m_cameraMovementMode;
	unsigned char m_padding2358[0x240C - 0x2358];
	Bool m_cameraHasMovedSinceRequest;

	void setCameraTransform();
};

void W3DView::setHeightAboveGround(Real height)
{
	if (TheGameClient->m_cameraChangeBlocked && m_zoomLimited)
		return;
	if (m_cameraMovementMode != 0)
		return;
	if (m_rotatingCamera)
		return;
	if (m_zoomingCamera)
		return;
	if (m_pitchingCamera)
		return;
	if (m_cameraMovementFinished)
		return;
	if (m_cameraMovementAlternate)
		return;

	m_heightAboveGround = height;
	if (m_zoomLimited)
	{
		if (m_heightAboveGround < m_minHeightAboveGround)
			m_heightAboveGround = m_minHeightAboveGround;
		if (m_heightAboveGround > m_maxHeightAboveGround)
			m_heightAboveGround = m_maxHeightAboveGround;
	}

	m_rotatingCamera = false;
	m_zoomingCamera = false;
	m_pitchingCamera = false;
	m_cameraMovementAlternate = false;
	m_cameraMovementFinished = false;
	m_cameraHasMovedSinceRequest = false;
	setCameraTransform();
}
