// BFME W3DSmudgeManager layout, aligned to retail by the landed ctor at
// 0x00722120 (Code/GameEngine/Source/Common/Rva00722120Ctor.cpp): base
// SmudgeManager occupies 0x24 bytes (vptr + 0x20), then eight dwords at
// +0x24..+0x40, the last initialized to the render-to-texture probe color
// 0x00FFEEDD that ZH's testHardwareSupport draws and reads back.
//
// ZH upstream: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/
//   GameEngineDevice/Include/W3DDevice/GameClient/W3DSmudge.h (+ .cpp).
// Bodies this hierarchy owns (identity per re_attempts evidence):
//   0x0071DAF0 838B  testHardwareSupport (SEH, D3D8 calls)
//   0x0071EEC0 4112B render (x87-heavy)
//   0x007202F0 805B / 0x00720D10 1312B  ReAcquireResources / copyRect family
//   0x007206E0 195B  ReleaseResources/dtor-adjacent
//   0x00722200 297B  ReAcquireResources (banked 0.55)
//   0x00722380 326B  copyRect candidate (banked 0.3)
//   0x00722640 1098B render candidate (banked 0.25)
//
// The member names follow ZH; which dword is which pointer must be proven per
// body (the ctor zeroes them indistinguishably). m_probeColor at +0x40 is the
// one anchored member.

class RenderInfoClass;
class SmudgeGroupClass;
class DX8IndexBufferClass;
template <class T> class ShareBufferClass;
class Vector3;

class SmudgeManager
{
public:
	SmudgeManager();
	virtual void smudgeManagerSlot0( void );

private:
	char m_smudgeManagerPad[0x20];	// +0x04..+0x24
};

class W3DSmudgeManager : public SmudgeManager
{
public:
	W3DSmudgeManager();

	void render( RenderInfoClass &rinfo );
	void ReleaseResources( void );
	void ReAcquireResources( void );
	bool testHardwareSupport( void );

	SmudgeGroupClass *m_smudgeGroup;					// +0x24
	ShareBufferClass<Vector3> *m_posBuffer;				// +0x28
	ShareBufferClass<unsigned int> *m_RGBABuffer;		// +0x2C
	ShareBufferClass<float> *m_sizeBuffer;				// +0x30
	DX8IndexBufferClass *m_indexBuffer;					// +0x34
	int m_backBufferWidth;								// +0x38
	int m_backBufferHeight;								// +0x3C
	unsigned int m_probeColor;							// +0x40 = 0x00FFEEDD (anchored)
};
