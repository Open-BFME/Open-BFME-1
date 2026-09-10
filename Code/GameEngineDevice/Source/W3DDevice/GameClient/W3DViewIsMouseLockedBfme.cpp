// ?isMouseLocked@View@@UAE_NXZ
// Retail RVA 0x007460A0, full body 7 bytes: mov al, [ecx+0x2480]; ret.
//
// The BFME W3DView primary vtable at 0x011217A0 dispatches slot 152 through
// ILT 0x00049BB6 to this inherited View accessor.  Slot 151 is the adjacent
// setMouseLock body at 0x00746090 (ILT 0x00010640), both operating on the
// +0x2480 byte named m_mouseLocked by the shipped View declaration.  The
// WindowXlat input path supplies the named isMouseLocked callers.  Keep the
// BFME member offset local to this TU.

typedef bool Bool;

class View
{
public:
	virtual Bool isMouseLocked();

private:
	char m_padding[0x247c];
	Bool m_mouseLocked;
};

Bool View::isMouseLocked()
{
	return m_mouseLocked;
}
