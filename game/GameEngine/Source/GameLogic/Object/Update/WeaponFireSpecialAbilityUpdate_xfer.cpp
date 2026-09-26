// cl: /DNDEBUG /MD /EHsc
// WeaponFireSpecialAbilityUpdate::xfer, retail RVA 0x0026D550.
// The WeaponFireSpecialWeapon block string and the weapon field at +0xE8
// identify this body as the WeaponFireSpecialAbilityUpdate serializer.

struct XferVersion
{
	unsigned char m_version;
	unsigned char m_currentVersion;
};

class Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual bool isSaving();
	virtual bool skipTransfer0C();
	virtual void slot04();
	virtual int beginBlock(const char *name);
	virtual void endBlock();
	virtual void skipBlock(const char *name);
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(XferVersion *version);
	virtual void slot11();
	virtual void xferSnapshot(void *value);
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(bool *value);
};

class SpecialAbilityUpdate
{
public:
	void xfer(Xfer *xfer);

private:
	unsigned char m_base[4];
};

class WeaponFireSpecialAbilityUpdate : public SpecialAbilityUpdate
{
public:
	void xfer(Xfer *xfer);

private:
	unsigned char m_padding[0xE4];
	void *m_weapon;
};

#pragma comment(linker, "/alternatename:?xfer@SpecialAbilityUpdate@@QAEXPAVXfer@@@Z=?j_000289f7@@YAXXZ")

// ?xfer@WeaponFireSpecialAbilityUpdate@@QAEXPAVXfer@@@Z
void WeaponFireSpecialAbilityUpdate::xfer(Xfer *xfer)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 2;
	xfer->xferVersion(&version);
	SpecialAbilityUpdate::xfer(xfer);
	if (xfer->skipTransfer0C())
		return;
	if (version.m_currentVersion < 2)
		return;

	bool weaponPresent = m_weapon != 0;
	xfer->xferBool(&weaponPresent);
	if (!weaponPresent)
		return;
	if (xfer->isSaving() || m_weapon != 0)
	{
		xfer->beginBlock("WeaponFireSpecialWeapon");
		xfer->xferSnapshot(m_weapon);
		xfer->endBlock();
	}
	else
	{
		xfer->skipBlock("WeaponFireSpecialWeapon");
	}
}
