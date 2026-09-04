// ?setWeaponLock@Object@@QAEXHH@Z
// BFME Object::setWeaponLock wrapper.  The retail wrapper notifies the
// contain interface, changes the object mode, then forwards the lock to the
// four-slot WeaponSet at +0x264.
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class BfmeModeCall
{
};

class BfmeDropCall
{
};

class BfmeWeaponSetCall
{
};

typedef void (BfmeModeCall::*BfmeModeFunction)( int, int );

extern void j_00032dee();
extern void j_00031f7a();
extern void j_0004705f();

class BfmeContainInterface
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0;
	virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0;
	virtual void slot26() = 0; virtual void slot27() = 0;
	virtual void slot28() = 0; virtual void slot29() = 0;
	virtual void slot30() = 0; virtual void slot31() = 0;
	virtual void slot32() = 0; virtual void slot33() = 0;
	virtual void slot34() = 0; virtual void slot35() = 0;
	virtual void slot36() = 0; virtual void slot37() = 0;
	virtual void slot38() = 0; virtual void slot39() = 0;
	virtual void slot40() = 0; virtual void slot41() = 0;
	virtual void slot42() = 0; virtual void slot43() = 0;
	virtual void slot44() = 0; virtual void slot45() = 0;
	virtual void slot46() = 0; virtual void slot47() = 0;
	virtual void slot48() = 0; virtual void slot49() = 0;
	virtual void slot50() = 0; virtual void slot51() = 0;
	virtual void slot52() = 0; virtual void slot53() = 0;
	virtual void slot54() = 0; virtual void slot55() = 0;
	virtual void slot56() = 0; virtual void slot57() = 0;
	virtual void slot58() = 0; virtual void slot59() = 0;
	virtual void slot60() = 0; virtual void slot61() = 0;
	virtual void slot62() = 0; virtual void slot63() = 0;
	virtual void slot64() = 0; virtual void slot65() = 0;
	virtual void slot66() = 0; virtual void slot67() = 0;
	virtual void slot68() = 0; virtual void slot69() = 0;
	virtual void slot70() = 0; virtual void slot71() = 0;
	virtual void slot72() = 0; virtual void slot73() = 0;
	virtual void slot74() = 0; virtual void slot75() = 0;
	virtual void slot76() = 0; virtual void slot77() = 0;
	virtual void slot78() = 0; virtual void slot79() = 0;
	virtual void slot80() = 0; virtual void slot81() = 0;
	virtual void slot82() = 0; virtual void slot83() = 0;
	virtual void slot84() = 0;
	virtual void notifyWeaponLock( int slot, int lockType ) = 0;
};

class Object
{
public:
	void setWeaponLock( int weaponSlot, int lockType );

private:
	char m_pad00[0x1fc];
	BfmeContainInterface *m_contain;
};

void Object::setWeaponLock( int weaponSlot, int lockType )
{
	BfmeContainInterface *contain = m_contain;
	if ( contain )
		contain->notifyWeaponLock( weaponSlot, lockType );

	if ( lockType == 2 && weaponSlot != 0 )
	{
		BfmeModeFunction mode;
		union { void (*raw)(); BfmeModeFunction member; } modeCast;
		modeCast.raw = j_00032dee;
		mode = modeCast.member;
		(reinterpret_cast<BfmeModeCall *>(this)->*mode)( 0x50, 1 );
	}
	else
	{
		typedef void (BfmeDropCall::*DropFunction)( int );
		union { void (*raw)(); DropFunction member; } dropCast;
		dropCast.raw = j_00031f7a;
		(reinterpret_cast<BfmeDropCall *>(this)->*dropCast.member)( 0x50 );
	}

	typedef void (BfmeWeaponSetCall::*WeaponSetFunction)( int, int );
	union { void (*raw)(); WeaponSetFunction member; } weaponSetCast;
	weaponSetCast.raw = j_0004705f;
	(reinterpret_cast<BfmeWeaponSetCall *>((char *)this + 0x264)->*weaponSetCast.member)(
		weaponSlot, lockType );
}
