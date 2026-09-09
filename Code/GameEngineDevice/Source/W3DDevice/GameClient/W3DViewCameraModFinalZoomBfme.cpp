// BFME W3DView::cameraModFinalZoom, retail 0x0073BF80 (322 bytes).
// The W3DView vtable at 0x011217A0 maps slot 30 to this body. The body calls
// the zoom virtual at +0xE8, while the neighboring 0x0073C440 body calls the
// pitch virtual at +0xF0 and therefore belongs to cameraModFinalPitch.

typedef float Real;
typedef int Int;
typedef bool Bool;

#define TheAnimationMsPerStep (*(Int *)0x012BB1CC)

extern void d_0073a9b0(void);
typedef Real (*TerrainHeight)(Real, Real);

class CameraLimit
{
public:
	virtual Real getMinimum();
	virtual Real getMaximum();
};

#define BFME_W3D_SLOT(n) virtual void slot##n() = 0;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct WaypointXY
{
	Real x;
	Real y;
	char padding[4];
};

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
	BFME_W3D_SLOT(27) BFME_W3D_SLOT(28) BFME_W3D_SLOT(29)
	BFME_W3D_SLOT(30) BFME_W3D_SLOT(31) BFME_W3D_SLOT(32)
	BFME_W3D_SLOT(33) BFME_W3D_SLOT(34) BFME_W3D_SLOT(35)
	BFME_W3D_SLOT(36) BFME_W3D_SLOT(37) BFME_W3D_SLOT(38)
	BFME_W3D_SLOT(39) BFME_W3D_SLOT(40) BFME_W3D_SLOT(41)
	BFME_W3D_SLOT(42) BFME_W3D_SLOT(43) BFME_W3D_SLOT(44)
	BFME_W3D_SLOT(45) BFME_W3D_SLOT(46) BFME_W3D_SLOT(47)
	BFME_W3D_SLOT(48) BFME_W3D_SLOT(49) BFME_W3D_SLOT(50)
	BFME_W3D_SLOT(51) BFME_W3D_SLOT(52) BFME_W3D_SLOT(53)
	BFME_W3D_SLOT(54) BFME_W3D_SLOT(55) BFME_W3D_SLOT(56)
	BFME_W3D_SLOT(57)
	virtual void zoomCamera(Real finalZoom, Int milliseconds,
		Real easeIn, Real easeOut);
	virtual void cameraModFinalZoom(Real finalZoom, Real easeIn, Real easeOut);

private:
	char m_padding0004[0x0c - 4];
	Coord3D m_pos;
	char m_padding0018[0x1ac - 0x18];
	Int m_rcNumFrames;
	Int m_rcCurFrame;
	char m_padding01b4[0x1bc - 0x1b4];
	Int m_rcNumHoldFrames;
	char m_padding01c0[0x1dc - 0x1c0];
	Bool m_doingRotateCamera;
	char m_padding01dd[0x22f0 - 0x1dd];
	Int m_numWaypoints;
	char m_padding22f4[0x2354 - 0x22f4];
	Int m_cameraMovementMode;
	char m_padding2358[0x23e0 - 0x2358];
	Real m_cameraOffsetZ;
	char m_padding23e4[0x24b8 - 0x23e4];
	CameraLimit m_cameraLimits;
};

#undef BFME_W3D_SLOT

void W3DView::cameraModFinalZoom(Real finalZoom, Real easeIn, Real easeOut)
{
	Real terrainHeightMax;
	Real maxHeight;
	Real maxZoom;
	Real time;

	if (m_doingRotateCamera)
	{
		terrainHeightMax = ((TerrainHeight)d_0073a9b0)(m_pos.x, m_pos.y);
		maxHeight = terrainHeightMax + m_cameraLimits.getMaximum();
		maxZoom = maxHeight / m_cameraOffsetZ;

		time = (m_rcNumFrames + m_rcNumHoldFrames - m_rcCurFrame) * TheAnimationMsPerStep;
		zoomCamera(finalZoom * maxZoom, time, time * easeIn, time * easeOut);
	}
	if (m_cameraMovementMode == 1)
	{
		if (m_numWaypoints >= 4)
		{
			Coord3D *position = (Coord3D *)((char *)this + 0x284 + m_numWaypoints * 0x14);
			WaypointXY waypoint;
			waypoint.x = position->x;
			waypoint.y = position->y;
			terrainHeightMax = ((TerrainHeight)d_0073a9b0)(waypoint.x, waypoint.y);
			maxHeight = terrainHeightMax + m_cameraLimits.getMaximum();
			maxZoom = maxHeight / m_cameraOffsetZ;
			time = *(Int *)((char *)this + 0x284) - *(Int *)((char *)this + 0x288);
			zoomCamera(finalZoom * maxZoom, time, time * easeIn, time * easeOut);
		}
	}
}
