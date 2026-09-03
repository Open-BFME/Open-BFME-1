// ?zoomCameraOneFrame@W3DView@@AAEXXZ -- retail 0x0073C7C0.
// stlport
// readable body of ?zoomCameraOneFrame@W3DView@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DView.cpp
//
// Ported verbatim from the Zero Hour twin (GeneralsMD/.../W3DView.cpp
// W3DView::zoomCameraOneFrame). BFME's W3DView carries extra fields ahead of
// m_zcInfo/m_doingZoomCamera that this project has not yet shimmed in the
// shared W3DView.cpp translation unit, so this TU-scoped file declares a
// minimal, address-derived W3DView layout instead of editing the shared
// header -- only the fields this one body touches, at their real BFME
// offsets (proven by probe.py against retail).

typedef float Real;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ParabolicEase.h
class ParabolicEase
{
public:
	Real operator()(Real param) const;

private:
	Real m_in, m_out;
};

namespace WWMath
{
	inline Real Lerp(Real a, Real b, Real t) { return a + (b - a) * t; }
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	char m_unreconstructed_00[0xA74];
	Bool m_disableCameraMovement;			// retail this+0xA74
};

extern GlobalData *TheWritableGlobalData;	// ?TheWritableGlobalData@@3PAVGlobalData@@A @ 0x012ED5C8

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DView.h
class W3DView
{
private:
	void zoomCameraOneFrame(void);

	char m_unreconstructed_000[0x3C];
	Real m_zoom;							// retail this+0x3C
	char m_unreconstructed_040[0x208 - 0x40];
	int m_zcNumFrames;						// retail this+0x208
	int m_zcCurFrame;						// retail this+0x20C
	Real m_zcStartZoom;					// retail this+0x210
	Real m_zcEndZoom;						// retail this+0x214
	char m_unreconstructed_218[0x220 - 0x218];
	ParabolicEase m_zcEase;				// retail this+0x220
	Bool m_doingZoomCamera;				// retail this+0x228
};

void W3DView::zoomCameraOneFrame(void)
{
	m_zcCurFrame++;
	if (TheWritableGlobalData->m_disableCameraMovement) {
		if (m_zcCurFrame >= m_zcNumFrames) {
			m_doingZoomCamera = false;
		}
		return;
	}
	if (m_zcCurFrame <= m_zcNumFrames)
	{
		// not just holding; do the camera adjustment
		Real factor = m_zcEase(((Real)m_zcCurFrame) / m_zcNumFrames);
		m_zoom = WWMath::Lerp(m_zcStartZoom, m_zcEndZoom, factor);
	}

	if (m_zcCurFrame >= m_zcNumFrames) {
		m_doingZoomCamera = false;
		m_zoom = m_zcEndZoom;
	}
}
