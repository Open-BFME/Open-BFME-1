// ?getPitch@View@@UAEMXZ
// Retail RVA 0x00746020, full body 4 bytes: fld [ecx+0x70]; ret.
//
// The BFME W3DView primary vtable at 0x011217A0 dispatches slot 107 through
// ILT 0x0003DEA1 to this inherited View accessor.  The W3DView constructor at
// 0x00745B10 initializes the corresponding +0x70 float; the shared View API
// identifies that camera value as the current pitch.  This TU-local
// declaration preserves the BFME layout without changing shared headers.

typedef float Real;

class View
{
public:
	virtual Real getPitch();

private:
	char m_padding[0x6c];
	Real m_pitch;
};

Real View::getPitch()
{
	return m_pitch;
}
