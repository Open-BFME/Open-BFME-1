// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: this-adjustor thunks of W3DView's SubsystemInterface vtable.
// Retail 0x00746170 and 0x00746180 are 11-byte `sub ecx,0xFC / jmp` entries
// reached only from ILT 0x00036D63 / 0x0003F995. They jump through ILT
// 0x00041191 to the scalar deleting destructor 0x007463F0 and through ILT
// 0x00014A38 to W3DView::reset (0x0073AC90). ilt_oracle CONFIRMS
// ??_EW3DView@@WPM@AEPAXI@Z and ?reset@W3DView@@WPM@AEXXZ at those addresses,
// so the SubsystemInterface base sits at +0xFC. Only that offset and the two
// overrides are modelled; the base constructors stay external and the bases are
// novtable, so this unit emits no base vtable or base constructor copy.

class __declspec(novtable) View
{
public:
	View();
	virtual ~View();
	virtual void reset();
private:
	char m_viewFill[0xFC - 4];
};

class __declspec(novtable) SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void reset();
};

class W3DView : public View, public SubsystemInterface
{
public:
	virtual ~W3DView();
	virtual void reset();
private:
	friend void forceW3DViewAdjustorThunks();
};

void forceW3DViewAdjustorThunks()
{
	W3DView value;
}
