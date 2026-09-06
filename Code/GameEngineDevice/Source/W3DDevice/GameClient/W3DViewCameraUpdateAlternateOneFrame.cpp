// Retail 0x0073CA40 -- W3DView::cameraUpdateAlternateOneFrame.
//
// The owner is not inferred: the matched caller
// ?updateCameraMovements@W3DView@@QAE_NXZ at 0x00744530
// (W3DViewUpdateCameraMovementsBfme.cpp) runs this body on its own `this`,
// under the flag at +0x27C.  The four per-frame easers of that run --
// 0x0073C7C0 zoomCameraOneFrame, 0x0073C890 pitchCameraOneFrame, 0x0073C970 and
// 0x0073CA40 -- are consecutive, and their info blocks are a contiguous run of
// one object: +0x1E0, +0x208 (zoom), +0x22C (pitch), +0x258.  Two of the four
// are already W3DView's, so all four are.
//
// The retail method name is not recovered -- ZH has three of these and names
// its third rotateCameraOneFrame, but that body is far larger and touches
// fields this one does not.  So the name here is the flag the caller tests,
// and what the body provably does: blend one Real field (+0x30) from start to
// end over m_numFrames with the ParabolicEase at +0x274.

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

class W3DView
{
private:
	void cameraUpdateAlternateOneFrame(void);

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

void W3DView::cameraUpdateAlternateOneFrame(void)
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
