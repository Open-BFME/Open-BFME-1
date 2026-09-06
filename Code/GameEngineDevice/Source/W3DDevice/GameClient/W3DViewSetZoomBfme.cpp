// ?setZoom@W3DView@@UAEXM@Z
// Retail 0x00742E60. BFME blocks camera changes while the game client or a
// camera movement owns the view, then clamps zoom through the view's limits.
// cl: /DNDEBUG /MD /EHsc

typedef float Real;

class GameClient
{
private:
	unsigned char m_padding0000[0xBC];

public:
	unsigned char m_cameraChangeBlocked;
};

class BfmeZoomLimits
{
public:
	virtual Real getMinimum();
	virtual Real getMaximum();
};

extern GameClient *TheGameClient;

class W3DView
{
public:
	virtual void setZoom(Real zoom);

private:
	unsigned char m_padding0004[0x3C];
	Real m_zoom;
	unsigned char m_zoomLimited;
	unsigned char m_padding0045[0x1DC - 0x45];
	unsigned char m_rotatingCamera;
	unsigned char m_padding01DD[0x204 - 0x1DD];
	unsigned char m_zoomingCamera;
	unsigned char m_padding0205[0x228 - 0x205];
	unsigned char m_pitchingCamera;
	unsigned char m_padding0229[0x27C - 0x229];
	unsigned char m_cameraMovementAlternate;
	unsigned char m_cameraMovementFinished;
	unsigned char m_padding027E[0x2354 - 0x27E];
	int m_cameraMovementMode;
	unsigned char m_padding2358[0x240C - 0x2358];
	unsigned char m_cameraHasMovedSinceRequest;
	unsigned char m_padding240D[0x24B8 - 0x240D];
	BfmeZoomLimits m_zoomLimits;

	void setCameraTransform();
};

void W3DView::setZoom(Real zoom)
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

	m_zoom = zoom;
	if (m_zoomLimited)
	{
		if (m_zoom < m_zoomLimits.getMinimum())
			m_zoom = m_zoomLimits.getMinimum();
		if (m_zoom > m_zoomLimits.getMaximum())
			m_zoom = m_zoomLimits.getMaximum();
	}

	m_rotatingCamera = 0;
	m_zoomingCamera = 0;
	m_pitchingCamera = 0;
	m_cameraMovementAlternate = 0;
	m_cameraMovementFinished = 0;
	m_cameraHasMovedSinceRequest = 0;
	setCameraTransform();
}
