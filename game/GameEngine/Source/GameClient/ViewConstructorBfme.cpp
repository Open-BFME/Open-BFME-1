// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME View base constructor, retail RVA 0x0045B8C0.
//
// W3DView's constructor at 0x00745B10 calls this body through ILT
// 0x0002284F before installing the derived W3DView vftable.  The BFME View
// layout is the one recovered by the matched reset body at 0x0045C1D0; the
// retail base vftable is the complete 64-slot table at 0x010F6940.

typedef unsigned int UnsignedInt;
typedef float Real;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class View
{
public:
	View();

private:
	void *m_vftable;
	void *m_next;
	UnsignedInt m_id;
	Real m_pos[3];
	int m_width;
	int m_height;
	int m_originX;
	int m_originY;
	Real m_angle;
	Real m_pitchAngle;
	Real m_maxZoom;
	Real m_minZoom;
	Real m_maxHeightAboveGround;
	Real m_minHeightAboveGround;
	Real m_zoom;
	bool m_zoomLimited;
	unsigned char m_zoomLimitedPadding[3];
	Real m_defaultAngle;
	Real m_defaultPitchAngle;
	Real m_heightAboveGround;
	Real m_currentHeightAboveGround;
	Real m_terrainHeightUnderCamera;
	UnsignedInt m_cameraLock;
	void *m_cameraLockDrawable;
	int m_lockType;
	Real m_lockDist;
	Real m_FOV;
	UnsignedInt m_mouseLocked;
	bool m_guardBandBiasX;
	bool m_okToAdjustHeight;
	bool m_snapImmediate;
	unsigned char m_flagsPadding;
	int m_guardBandBias[2];
	UnsignedInt m_bfme80;
	bool m_bfme84;
	unsigned char m_bfme84Padding[3];
	UnsignedInt m_bfme88;
	UnsignedInt m_bfme8c;
	UnsignedInt m_bfme90;
	UnsignedInt m_bfme94;
	UnsignedInt m_bfme98;
	Real m_bfme9c;
	Real m_bfmea0;
	Real m_bfmea4;
	Real m_bfmea8;
	UnsignedInt m_bfmeac;
	UnsignedInt m_bfmeb0;
	static UnsignedInt m_idNext;
};

View::View()
{
	m_vftable = (void *)0x010F6940;
	m_next = 0;
	m_id = m_idNext++;
	_ReadWriteBarrier();
	m_pos[0] = 0.0f;
	m_pos[1] = 0.0f;
	m_pos[2] = 0.0f;
	m_width = 0;
	m_height = 0;
	m_originX = 0;
	m_originY = 0;
	m_angle = 0.0f;
	m_pitchAngle = 0.0f;
	m_maxZoom = 0.0f;
	m_minZoom = 0.0f;
	m_maxHeightAboveGround = 0.0f;
	m_minHeightAboveGround = 0.0f;
	m_zoom = 0.0f;
	_ReadWriteBarrier();

	m_defaultAngle = 0.0f;
	m_defaultPitchAngle = 0.0f;
	m_heightAboveGround = 0.0f;
	m_currentHeightAboveGround = 0.0f;
	m_terrainHeightUnderCamera = 0.0f;
	m_cameraLock = 0;
	m_cameraLockDrawable = 0;
	m_lockType = 0;
	m_lockDist = 0.0f;
	m_FOV = 0.87266463f;
	_ReadWriteBarrier();
	m_mouseLocked = 0;
	m_guardBandBiasX = 0;
	m_snapImmediate = 0;
	_ReadWriteBarrier();
	m_zoomLimited = 1;
	m_okToAdjustHeight = 1;
	_ReadWriteBarrier();
	m_guardBandBias[0] = 0;
	m_guardBandBias[1] = 0;
	m_bfme80 = 0;
	_ReadWriteBarrier();
	Real one = 1.0f;
	_ReadWriteBarrier();
	m_bfme84 = 0;
	m_bfme88 = 0;
	m_bfme8c = 0;
	m_bfme90 = 0;
	m_bfme94 = 0;
	m_bfme98 = 0;
	m_bfme9c = one;
	m_bfmea0 = one;
	m_bfmea4 = one;
	m_bfmea8 = one;
	m_bfmeac = 0;
	m_bfmeb0 = 0;
}
