// ?pitchCameraOneFrame@W3DView@@AAEXXZ -- retail 0x0073C890.
// stlport
//
// Ported from the Zero Hour twin (GeneralsMD/.../W3DView.cpp
// W3DView::pitchCameraOneFrame) with one BFME-only addition: the blended
// pitch is scaled by an extra global float (g_01075954, already pinned in
// reverse/symbols.csv) before landing in a field the ZH source doesn't have
// at all -- probably a camera-effects-pitch-to-radians factor. TU-scoped,
// address-derived W3DView layout for the same reason as
// W3DViewZoomCameraOneFrame.cpp (BFME's W3DView has fields ahead of these
// not yet shimmed into the shared translation unit).

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
extern Real g_01075954;						// @ 0x01075954

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DView.h
class W3DView
{
private:
	void pitchCameraOneFrame(void);

	char m_unreconstructed_000[0x6C];
	Real m_cameraPitchFX;					// retail this+0x6C
	char m_unreconstructed_070[0x22C - 0x70];
	int m_pcNumFrames;						// retail this+0x22C
	int m_pcCurFrame;						// retail this+0x230
	char m_unreconstructed_234[0x23C - 0x234];
	Real m_pcStartPitch;					// retail this+0x23C
	Real m_pcEndPitch;						// retail this+0x240
	char m_unreconstructed_244[0x24C - 0x244];
	ParabolicEase m_pcEase;					// retail this+0x24C
	Bool m_doingPitchCamera;				// retail this+0x254
};

void W3DView::pitchCameraOneFrame(void)
{
	m_pcCurFrame++;
	if (TheWritableGlobalData->m_disableCameraMovement) {
		if (m_pcCurFrame >= m_pcNumFrames) {
			m_doingPitchCamera = false;
		}
		return;
	}
	if (m_pcCurFrame <= m_pcNumFrames)
	{
		// not just holding; do the camera adjustment
		Real factor = m_pcEase(((Real)m_pcCurFrame) / m_pcNumFrames);
		m_cameraPitchFX = WWMath::Lerp(m_pcStartPitch, m_pcEndPitch, factor) * g_01075954;
	}

	if (m_pcCurFrame >= m_pcNumFrames) {
		// MSVC 7.1 commutes this multiply in C++, so spell the retail x87
		// operand order around the intervening flag store.
		__asm { fld dword ptr [esi + 240h] }
		m_doingPitchCamera = false;
		__asm {
			fmul dword ptr [g_01075954]
			fstp dword ptr [esi + 6ch]
		}
	}
}
