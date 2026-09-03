// Address-derived reconstruction of a per-frame ParabolicEase blend update at
// 0x0073CA40. Same shape as W3DView::zoomCameraOneFrame/pitchCameraOneFrame
// (see W3DViewZoomCameraOneFrame.cpp) -- increment a frame counter, honor
// TheWritableGlobalData's m_disableCameraMovement flag, ease-blend two float
// fields into an output field once curFrame<=numFrames, and snap+flag-clear
// once curFrame>=numFrames. No ZH twin identified for this specific instance
// (zoom/pitch are; rotate/waypoint-path in ZH's W3DView carry extra fields
// this body does not touch), so this is a private, address-derived class
// rather than a claimed W3DView member.

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

class Gen0073CA40Owner
{
private:
	void updateOneFrame(void);

	char m_unreconstructed_000[0x30];
	Real m_output;							// retail this+0x30
	char m_unreconstructed_034[0x258 - 0x34];
	int m_numFrames;						// retail this+0x258
	int m_curFrame;							// retail this+0x25C
	char m_unreconstructed_260[0x264 - 0x260];
	Real m_start;							// retail this+0x264
	Real m_end;								// retail this+0x268
	char m_unreconstructed_26C[0x274 - 0x26C];
	ParabolicEase m_ease;					// retail this+0x274
	Bool m_active;							// retail this+0x27C
};

void Gen0073CA40Owner::updateOneFrame(void)
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
