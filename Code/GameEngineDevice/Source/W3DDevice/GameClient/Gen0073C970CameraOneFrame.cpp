// Address-derived reconstruction of a per-frame ParabolicEase blend update at
// 0x0073C970. Same shape as W3DView::zoomCameraOneFrame/pitchCameraOneFrame
// (see W3DViewZoomCameraOneFrame.cpp) -- increment a frame counter, honor
// TheWritableGlobalData's m_disableCameraMovement flag, ease-blend two float
// fields into an output field once curFrame<=numFrames, and snap+flag-clear
// once curFrame>=numFrames. No ZH twin identified for this specific instance
// (zoom/pitch are; rotate/waypoint-path in ZH's W3DView carry extra fields
// this body does not touch), so this is a private, address-derived class
// rather than a claimed W3DView member.

typedef float Real;
typedef bool Bool;

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

class GlobalData
{
public:
	char m_unreconstructed_00[0xA74];
	Bool m_disableCameraMovement;			// retail this+0xA74
};

extern GlobalData *TheWritableGlobalData;	// ?TheWritableGlobalData@@3PAVGlobalData@@A @ 0x012ED5C8

class Gen0073C970Owner
{
private:
	void updateOneFrame(void);

	char m_unreconstructed_000[0x70];
	Real m_output;							// retail this+0x70
	char m_unreconstructed_074[0x1E0 - 0x74];
	int m_numFrames;						// retail this+0x1E0
	int m_curFrame;							// retail this+0x1E4
	char m_unreconstructed_1E8[0x1EC - 0x1E8];
	Real m_start;							// retail this+0x1EC
	Real m_end;								// retail this+0x1F0
	char m_unreconstructed_1F4[0x1FC - 0x1F4];
	ParabolicEase m_ease;					// retail this+0x1FC
	Bool m_active;							// retail this+0x204
};

void Gen0073C970Owner::updateOneFrame(void)
{
	m_curFrame++;
	if (TheWritableGlobalData->m_disableCameraMovement) {
		if (m_curFrame >= m_numFrames) {
			m_active = false;
		}
		return;
	}
	if (m_curFrame <= m_numFrames)
	{
		Real factor = m_ease(((Real)m_curFrame) / m_numFrames);
		m_output = WWMath::Lerp(m_start, m_end, factor);
	}

	if (m_curFrame >= m_numFrames) {
		m_active = false;
		m_output = m_end;
	}
}
