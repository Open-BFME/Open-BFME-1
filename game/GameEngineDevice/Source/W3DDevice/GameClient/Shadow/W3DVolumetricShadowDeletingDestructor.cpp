// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: W3DVolumetricShadow scalar-deleting destructor at retail RVA
// 0x007BDAD0 (30 bytes). The exact constructor at 0x007BA950 installs vtable
// 0x011284CC, whose slot zero routes through ILT 0x00025E0F to this wrapper.
// The named shadow-manager allocation corroborates identity; the wrapper calls
// the complete destructor through ILT 0x0001B6AD.

class W3DVolumetricShadow
{
public:
	virtual ~W3DVolumetricShadow();
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceW3DVolumetricShadowDeletingDestructor(const W3DVolumetricShadow &that)
{
	W3DVolumetricShadow value(that);
}
