// cl: /DNDEBUG /MD /EHsc
// BFME W3DView::setDefaultView, retail 0x0073F9C0.
//
// The W3DView vftable installed by the constructor at 0x00745B10 reaches this
// body through its slot +0xE0.  That slot is setDefaultView in the shipped View
// declaration, and its three arguments are (pitch, angle, maxHeight).  BFME's
// camera-limit member at +0x24B8 is also constructed by 0x006DF550; its vtable
// proves the float getters at slots 0/1 and the slot-7 setter for its +8 field.

typedef float Real;
typedef bool Bool;

class Rva006DF550
{
public:
	virtual Real getMinimum();
	virtual Real getMaximum();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void setMaximum(Real value);
};

class W3DView
{
public:
	virtual void setDefaultView(Real pitch, Real angle, Real maxHeight);

private:
	unsigned char m_padding0004[0x4C - 0x04];
	Real m_defaultPitchAngle;                 // +0x4C
	unsigned char m_padding0050[0x58 - 0x50];
	int m_field0058;                          // +0x58
	int m_field005C;                          // +0x5C
	unsigned char m_padding0060[0x68 - 0x60];
	int m_field0068;                          // +0x68
	unsigned char m_padding006C[0x1DC - 0x6C];
	Bool m_doingRotateCamera;                 // +0x1DC
	unsigned char m_padding01DD[0x204 - 0x1DD];
	Bool m_cameraFlag0204;                    // +0x204
	unsigned char m_padding0205[0x228 - 0x205];
	Bool m_doingZoomCamera;                    // +0x228
	unsigned char m_padding0229[0x27C - 0x229];
	Bool m_cameraFlag027C;                    // +0x27C
	Bool m_doingScriptedCameraLock;                    // +0x27D
	unsigned char m_padding027E[0x2354 - 0x27E];
	int m_cameraMovementMode;                 // +0x2354
	unsigned char m_padding2358[0x23B8 - 0x2358];
	Bool m_cameraState23B8;                   // +0x23B8
	unsigned char m_padding23B9[0x243C - 0x23B9];
	int m_cameraState243C;                    // +0x243C
	int m_cameraState2440;                    // +0x2440
	int m_cameraState2444;                    // +0x2444
	unsigned char m_padding2448[0x24B8 - 0x2448];
	Rva006DF550 m_limits;                     // +0x24B8
};

void W3DView::setDefaultView(Real pitch, Real, Real maxHeight)
{
	m_cameraMovementMode = 0;
	m_doingRotateCamera = false;
	m_cameraFlag0204 = false;
	m_doingZoomCamera = false;
	m_doingScriptedCameraLock = false;
	m_cameraFlag027C = false;
	m_cameraState23B8 = false;
	m_cameraState243C = 0;
	m_cameraState2440 = 0;
	m_cameraState2444 = 0;
	m_field0058 = 0;
	m_field005C = 0;
	m_field0068 = 0;
	m_defaultPitchAngle = pitch;

	m_limits.setMaximum(m_limits.getMaximum() * maxHeight);
	if (m_limits.getMinimum() > m_limits.getMaximum())
		m_limits.setMaximum(m_limits.getMinimum());
}
