// cl: /DNDEBUG /MD /EHsc
// Drawable::setShadowsEnabled, retail 0x004140E0, 69 bytes.
//
// The matched SlowDeathBehavior caller establishes the identity.  BFME stores
// Drawable status at +0x110 and the null-terminated draw-module array at +0x150.

typedef bool Bool;
typedef unsigned int UnsignedInt;

class BfmeDrawModuleForShadows
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void setShadowsEnabled(Bool enable) = 0;
};

class BfmeDrawableForShadows
{
public:
	void setShadowsEnabled(Bool enable);
};

void BfmeDrawableForShadows::setShadowsEnabled(Bool enable)
{
	UnsignedInt &status = *reinterpret_cast<UnsignedInt *>((unsigned char *)this + 0x110);
	if (enable)
		status |= 2;
	else
		status &= ~2;

	BfmeDrawModuleForShadows **modules =
		*reinterpret_cast<BfmeDrawModuleForShadows ***>((unsigned char *)this + 0x150);
	for (BfmeDrawModuleForShadows **dm = modules; *dm; ++dm)
		(*dm)->setShadowsEnabled(enable);
}
