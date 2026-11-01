// ?triggerAbilityEffect@ToggleMountedSpecialAbilityUpdate@@MAEXXZ
// Retail: 406 bytes at 0x0026C9E0, through RET at +0x195.
// cl: /DNDEBUG /MD /EHsc

// FILE: ToggleMountedSpecialAbilityUpdateTriggerAbilityEffect.cpp ////////////
//
// ToggleMountedSpecialAbilityUpdate::triggerAbilityEffect. Identity:
// ilt_oracle CONFIRMS the decorated name at this body (exact), and its first
// call goes to 0x002A9850, which ilt_oracle CONFIRMS as
// SpecialAbilityUpdate::triggerAbilityEffect (that body's ledger row and pins
// still carry address-derived names; the call below spells one of the pins).
//
// Shape from the Open BFME 2 donor ToggleMountedSpecialAbilityUpdate.cpp
// (donor revision 45afcff3): base call, idle-AI and state-1 gates, then
// dismount (contained riders out, mounted flag off, AI mode 0, weapon/armor
// set flags cleared, optional disguise cancel) or mount (flag on, AI mode 7,
// flags set), then a selected drawable dirties the control bar. BFME 1 has no
// mounted-template branch and tests object flag words where the donor tests
// kinds; offsets come from this body: owner +0x08, module data +0x04 (cancel
// disguise byte +0x259), state +0x24; object flags +0x128/+0x130 (bit 0x800),
// contain +0x1FC, AI +0x204; drawable selected byte +0x3AC; control bar +0x24.
//
///////////////////////////////////////////////////////////////////////////////

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Module;

#define BFME_SLOT( n ) virtual void unusedSlot##n();

class MountedAI
{
public:
	BFME_SLOT( 0 ) BFME_SLOT( 1 ) BFME_SLOT( 2 ) BFME_SLOT( 3 ) BFME_SLOT( 4 ) BFME_SLOT( 5 )
	BFME_SLOT( 6 ) BFME_SLOT( 7 ) BFME_SLOT( 8 ) BFME_SLOT( 9 ) BFME_SLOT( 10 ) BFME_SLOT( 11 )
	BFME_SLOT( 12 ) BFME_SLOT( 13 ) BFME_SLOT( 14 ) BFME_SLOT( 15 ) BFME_SLOT( 16 ) BFME_SLOT( 17 )
	BFME_SLOT( 18 ) BFME_SLOT( 19 ) BFME_SLOT( 20 ) BFME_SLOT( 21 ) BFME_SLOT( 22 ) BFME_SLOT( 23 )
	BFME_SLOT( 24 ) BFME_SLOT( 25 ) BFME_SLOT( 26 ) BFME_SLOT( 27 ) BFME_SLOT( 28 ) BFME_SLOT( 29 )
	BFME_SLOT( 30 ) BFME_SLOT( 31 ) BFME_SLOT( 32 ) BFME_SLOT( 33 ) BFME_SLOT( 34 ) BFME_SLOT( 35 )
	BFME_SLOT( 36 ) BFME_SLOT( 37 ) BFME_SLOT( 38 ) BFME_SLOT( 39 ) BFME_SLOT( 40 ) BFME_SLOT( 41 )
	BFME_SLOT( 42 ) BFME_SLOT( 43 ) BFME_SLOT( 44 ) BFME_SLOT( 45 ) BFME_SLOT( 46 ) BFME_SLOT( 47 )
	BFME_SLOT( 48 ) BFME_SLOT( 49 ) BFME_SLOT( 50 ) BFME_SLOT( 51 ) BFME_SLOT( 52 ) BFME_SLOT( 53 )
	BFME_SLOT( 54 ) BFME_SLOT( 55 ) BFME_SLOT( 56 ) BFME_SLOT( 57 ) BFME_SLOT( 58 ) BFME_SLOT( 59 )
	BFME_SLOT( 60 ) BFME_SLOT( 61 ) BFME_SLOT( 62 ) BFME_SLOT( 63 ) BFME_SLOT( 64 ) BFME_SLOT( 65 )
	BFME_SLOT( 66 ) BFME_SLOT( 67 ) BFME_SLOT( 68 ) BFME_SLOT( 69 ) BFME_SLOT( 70 ) BFME_SLOT( 71 )
	BFME_SLOT( 72 ) BFME_SLOT( 73 ) BFME_SLOT( 74 ) BFME_SLOT( 75 ) BFME_SLOT( 76 ) BFME_SLOT( 77 )
	BFME_SLOT( 78 ) BFME_SLOT( 79 ) BFME_SLOT( 80 ) BFME_SLOT( 81 ) BFME_SLOT( 82 ) BFME_SLOT( 83 )
	BFME_SLOT( 84 ) BFME_SLOT( 85 ) BFME_SLOT( 86 ) BFME_SLOT( 87 ) BFME_SLOT( 88 ) BFME_SLOT( 89 )
	BFME_SLOT( 90 ) BFME_SLOT( 91 ) BFME_SLOT( 92 ) BFME_SLOT( 93 ) BFME_SLOT( 94 ) BFME_SLOT( 95 )
	virtual Bool isIdle() const;																// slot 96
	BFME_SLOT( 97 ) BFME_SLOT( 98 ) BFME_SLOT( 99 ) BFME_SLOT( 100 ) BFME_SLOT( 101 )
	BFME_SLOT( 102 ) BFME_SLOT( 103 ) BFME_SLOT( 104 ) BFME_SLOT( 105 ) BFME_SLOT( 106 )
	BFME_SLOT( 107 ) BFME_SLOT( 108 ) BFME_SLOT( 109 ) BFME_SLOT( 110 ) BFME_SLOT( 111 )
	BFME_SLOT( 112 ) BFME_SLOT( 113 ) BFME_SLOT( 114 ) BFME_SLOT( 115 ) BFME_SLOT( 116 )
	BFME_SLOT( 117 ) BFME_SLOT( 118 ) BFME_SLOT( 119 ) BFME_SLOT( 120 ) BFME_SLOT( 121 )
	BFME_SLOT( 122 ) BFME_SLOT( 123 ) BFME_SLOT( 124 ) BFME_SLOT( 125 ) BFME_SLOT( 126 )
	virtual void slot127( Int mode );															// slot 127
};

class MountedContain
{
public:
	BFME_SLOT( 0 ) BFME_SLOT( 1 ) BFME_SLOT( 2 ) BFME_SLOT( 3 ) BFME_SLOT( 4 ) BFME_SLOT( 5 )
	BFME_SLOT( 6 ) BFME_SLOT( 7 ) BFME_SLOT( 8 ) BFME_SLOT( 9 ) BFME_SLOT( 10 ) BFME_SLOT( 11 )
	BFME_SLOT( 12 ) BFME_SLOT( 13 ) BFME_SLOT( 14 ) BFME_SLOT( 15 ) BFME_SLOT( 16 ) BFME_SLOT( 17 )
	BFME_SLOT( 18 ) BFME_SLOT( 19 ) BFME_SLOT( 20 ) BFME_SLOT( 21 ) BFME_SLOT( 22 ) BFME_SLOT( 23 )
	BFME_SLOT( 24 ) BFME_SLOT( 25 ) BFME_SLOT( 26 ) BFME_SLOT( 27 ) BFME_SLOT( 28 ) BFME_SLOT( 29 )
	BFME_SLOT( 30 ) BFME_SLOT( 31 ) BFME_SLOT( 32 ) BFME_SLOT( 33 ) BFME_SLOT( 34 ) BFME_SLOT( 35 )
	BFME_SLOT( 36 )
	virtual void slot37( Int flags );															// slot 37
	BFME_SLOT( 38 ) BFME_SLOT( 39 ) BFME_SLOT( 40 ) BFME_SLOT( 41 ) BFME_SLOT( 42 ) BFME_SLOT( 43 )
	BFME_SLOT( 44 ) BFME_SLOT( 45 ) BFME_SLOT( 46 ) BFME_SLOT( 47 ) BFME_SLOT( 48 ) BFME_SLOT( 49 )
	BFME_SLOT( 50 ) BFME_SLOT( 51 ) BFME_SLOT( 52 ) BFME_SLOT( 53 ) BFME_SLOT( 54 ) BFME_SLOT( 55 )
	BFME_SLOT( 56 ) BFME_SLOT( 57 ) BFME_SLOT( 58 ) BFME_SLOT( 59 ) BFME_SLOT( 60 ) BFME_SLOT( 61 )
	BFME_SLOT( 62 ) BFME_SLOT( 63 )
	virtual UnsignedInt slot64( Int flags );													// slot 64
};

class Drawable
{
public:
	unsigned char m_unmodelled_000[ 0x3AC ];
	Bool m_selected;
};

// The four set-flag helpers 0x001C9AC0 / 0x001BEF00 / 0x001C9A10 / 0x001BEEE0
// keep the receiver-typed names the ledger already carries.
class Gen001C9AC0 { public: void handle( Int flag ); };
class Rva001BEF00GuardedVCall { public: void forward( Int flag ); };
class Gen001C9A10 { public: void handle( Int flag ); };
class Rva001BEEE0GuardedVCall { public: void forward( Int flag ); };

class Rva00267D00
{
public:
	void m00267D00( char enable );
};

class ToggleMountedSpecialAbilityUpdate;

class Object
{
	friend class ToggleMountedSpecialAbilityUpdate;

public:
	BFME_SLOT( 0 ) BFME_SLOT( 1 ) BFME_SLOT( 2 ) BFME_SLOT( 3 ) BFME_SLOT( 4 )
	BFME_SLOT( 5 ) BFME_SLOT( 6 ) BFME_SLOT( 7 ) BFME_SLOT( 8 ) BFME_SLOT( 9 )
	virtual Drawable *getDrawable() const;														// slot 10

	MountedAI *getAI() const { return m_ai; }
	MountedContain *getContain() const { return m_contain; }
	void notifyModelConditionChanged();

	// Volatile read: retail re-reads the word in the mount branch instead of
	// reusing the tested value (docs/shape_levers.md volatile-first read).
	Bool isFlag128_800() const { return ( *(const volatile UnsignedInt *)&m_flags128 & 0x800 ) != 0; }
	void clearFlag128_800()
	{
		if( m_flags128 & 0x800 )
		{
			m_flags128 &= ~0x800;
			notifyModelConditionChanged();
		}
	}
	void setFlag128_800()
	{
		m_flags128 |= 0x800;
		notifyModelConditionChanged();
	}

protected:
	Module *findModule( NameKeyType key ) const;

private:
	unsigned char m_unmodelled_004[ 0x128 - 0x004 ];
	UnsignedInt m_flags128;
	unsigned char m_unmodelled_12C[ 0x130 - 0x12C ];
	UnsignedInt m_flags130;
	unsigned char m_unmodelled_134[ 0x1FC - 0x134 ];
	MountedContain *m_contain;
	unsigned char m_unmodelled_200[ 0x204 - 0x200 ];
	MountedAI *m_ai;
};

class ControlBar
{
public:
	unsigned char m_unmodelled_00[ 0x24 ];
	Bool m_UIDirty;
};

extern ControlBar *TheControlBar;

class ToggleMountedSpecialAbilityUpdateModuleData
{
public:
	unsigned char m_unmodelled_000[ 0x259 ];
	Bool m_cancelDisguise;
};

// 0x002A9850 is SpecialAbilityUpdate::triggerAbilityEffect (ilt_oracle);
// this pinned address-derived view names it for the direct base call.
class Rva0025EF90Owner
{
public:
	void callAt002A9850();
};

class ToggleMountedSpecialAbilityUpdate
{
protected:
	virtual void triggerAbilityEffect();

private:
	Object *getObject() const { return m_object; }
	const ToggleMountedSpecialAbilityUpdateModuleData *getModuleData() const { return m_moduleData; }

	const ToggleMountedSpecialAbilityUpdateModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_unmodelled_0C[ 0x24 - 0x0C ];
	Int m_state;
};

void ToggleMountedSpecialAbilityUpdate::triggerAbilityEffect()
{
	((Rva0025EF90Owner *)this)->callAt002A9850();

	Object *obj = getObject();
	if( !obj->getAI()->isIdle() )
		return;
	if( m_state != 1 )
		return;

	if( obj->isFlag128_800() )
	{
		MountedContain *contain = obj->getContain();
		if( contain && contain->slot64( 0 ) > 0 )
			obj->getContain()->slot37( 0 );
		obj->clearFlag128_800();
		obj->getAI()->slot127( 0 );
		((Gen001C9AC0 *)obj)->handle( 0x15 );
		((Rva001BEF00GuardedVCall *)obj)->forward( 6 );
		if( getModuleData()->m_cancelDisguise && ( obj->m_flags130 & 0x800 ) )
		{
			static const NameKeyType key = TheNameKeyGenerator->nameToKey( "SpecialDisguiseUpdate" );
			Rva00267D00 *disguise = (Rva00267D00 *)obj->findModule( key );
			if( disguise )
				disguise->m00267D00( true );
		}
	}
	else
	{
		obj->setFlag128_800();
		obj->getAI()->slot127( 7 );
		((Gen001C9A10 *)obj)->handle( 0x15 );
		((Rva001BEEE0GuardedVCall *)obj)->forward( 6 );
	}

	Drawable *drawable = obj->getDrawable();
	if( drawable && drawable->m_selected )
		TheControlBar->m_UIDirty = true;
}
