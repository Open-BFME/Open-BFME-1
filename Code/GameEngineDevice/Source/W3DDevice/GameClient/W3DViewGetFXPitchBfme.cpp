// ?getFXPitch@W3DView@@UBEMXZ
// Retail RVA 0x00746120, full body 4 bytes: fld [ecx+0x70]; ret.
//
// The BFME W3DView primary vtable at 0x011217A0 dispatches slot 125 through
// ILT 0x0003FA12 to this const W3DView accessor.  The shipped W3DView API
// names that slot getFXPitch, and W3DDisplay reads it while constructing the
// camera transform.  The retail constructor at 0x00745B10 initializes the
// corresponding +0x70 Real.  Keep the BFME layout local to this TU.

typedef float Real;

class W3DView
{
public:
	virtual Real getFXPitch() const;

private:
	char m_padding[0x6c];
	Real m_FXPitch;
};

Real W3DView::getFXPitch() const
{
	return m_FXPitch;
}
