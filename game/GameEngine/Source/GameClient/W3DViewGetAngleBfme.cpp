// ?getAngle@View@@UAEMXZ
// Retail RVA 0x007460F0, full body 4 bytes: fld [ecx+0x6c]; ret.
//
// The BFME W3DView primary vtable at 0x011217A0 dispatches slot 86 through
// ILT 0x0000598E to this inherited View accessor.  The real field is the
// View angle at +0x6c; the padding below accounts for the vptr at +0x00.
// This TU-local declaration avoids changing the shared View layout.

typedef float Real;

class View
{
public:
	virtual Real getAngle();

private:
	char m_padding[0x68];
	Real m_angle;
};

Real View::getAngle()
{
	return m_angle;
}
