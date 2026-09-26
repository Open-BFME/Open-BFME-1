// cl: /DNDEBUG /MD /EHsc
//
// SpecialAbilityUpdate::isPowerCurrentlyInUse, retail 0x002A6260, the sibling of
// SpecialAbilityUpdate::getSpecialPowerType (0x002A6320) in the same dump.  Both
// walk the SpecialPowerTemplate override chain through the ILT at 0x00048C61, and
// the two walks in this body are NOT written the same way -- retail says so:
//
//   the remote-charges walk at +0x0c merges the three arms in EAX and pays a jmp,
//   which is getSpecialPowerType's shape: `self` is assigned in BOTH arms of the
//   outer if/else, so nothing pins it to the incoming register;
//
//   the reload-time walk at +0x5f merges in ECX with no jmp at all, because there
//   `self` is SEEDED with `this` and only reassigned inside the if.  ECX already
//   holds the template, so the untouched arm costs nothing and the other two share
//   one `mov ecx,eax`.  Returning the final override from a helper instead forces
//   the phi into EAX (the return register) and costs the extra jmp plus a
//   `mov eax,ecx` -- 152 bytes, which is where this body sat for nine verdicts.
//
// Identity and `this`:
//
//   `tools/vtable_lookup.py 0x010c36b8` puts 0x002A6260 in SLOT 6 of that vtable,
//   reached through ILT ?j_000093bd, with NO adjustor thunk in front of it.  The
//   landed ctor ??0SpecialAbilityUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
//   (0x002A6360) stores 0x010c36b8 at +0x20 of the object -- so 0x010c36b8 is the
//   vtable of the base that begins at +0x20, and this body is one of ITS virtuals.
//   That base is BFME's SpecialPowerUpdateInterface (upstream:
//   inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/
//   Module/SpecialPowerUpdateModule.h -- SpecialPowerUpdateModule derives from
//   UpdateModule and SpecialPowerUpdateInterface, SpecialAbilityUpdate from
//   SpecialPowerUpdateModule).  BFME's interface has 9 slots where Zero Hour's has
//   12, so only slot 6 is named here; the other eight keep opaque slot names.
//
//   MSVC 7.1 compiles an override of a virtual introduced only by a NON-PRIMARY
//   base with `this` already pointing at that base subobject and adjusts inside
//   the body -- which is why the slot needs no adjustor thunk, and why the retail
//   accesses [ecx+0x10], [ecx+0xb0] and byte [ecx+0xc2] are FULL-OBJECT +0x30,
//   +0xd0 and +0xe2.  The declarations below therefore carry the full-object
//   offsets; the compiler subtracts the 0x20 itself.
//
//   The Zero Hour twin (inputs/reference/.../Source/GameLogic/Object/Update/
//   SpecialAbilityUpdate.cpp:570) names those three fields m_packingState,
//   m_specialObjectEntries and m_withinStartAbilityRange.  Note the landed ctor TU
//   labels +0xd8 `m_packingState` and leaves +0x30 as `m_30`: this body compares
//   +0x30 against 0, 1 and 3, which is exactly STATE_NONE / STATE_PACKING /
//   STATE_PACKED of the twin's PackingState enum against the twin's first test, so
//   +0x30 is the packing state and the ctor TU's +0xd8 label is the one in doubt.
//   That disagreement is recorded here rather than papered over.

typedef bool Bool;
typedef unsigned int UnsignedInt;

class Thing;
class ModuleData;
class Object;
class Coord3D;
class CommandButton;
class SpecialPowerTemplate;

enum SpecialPowerType
{
	SPECIAL_REMOTE_CHARGES = 0x16
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();

	Overridable *friend_getFinalOverride( void );		// ILT thunk at 0x00048C61

	Overridable *m_nextOverride;						// +0x04
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class SpecialPowerTemplate : public Overridable
{
public:
	SpecialPowerType getSpecialPowerType( void ) const
	{
		const SpecialPowerTemplate *self;
		Overridable *o = m_nextOverride;

		if( o )
		{
			if( o->m_nextOverride )
				o = o->m_nextOverride->friend_getFinalOverride();

			self = (const SpecialPowerTemplate *)o;
		}
		else
			self = this;

		return self->m_specialPowerType;
	}

	UnsignedInt getReloadTime( void ) const
	{
		const SpecialPowerTemplate *self = this;
		Overridable *o = m_nextOverride;

		if( o )
		{
			if( o->m_nextOverride )
				o = o->m_nextOverride->friend_getFinalOverride();

			self = (const SpecialPowerTemplate *)o;
		}

		return self->m_reloadTime;
	}

private:
	unsigned char m_unmodelled_08[ 0x14 - 8 ];
	SpecialPowerType m_specialPowerType;				// +0x14
	UnsignedInt m_reloadTime;							// +0x18
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/CommandButton.h
class CommandButton
{
public:
	const SpecialPowerTemplate *getSpecialPowerTemplate( void ) const
	{
		return m_specialPowerTemplate;
	}

	UnsignedInt getOptions( void ) const
	{
		return m_options;
	}

private:
	unsigned char m_unmodelled_00[ 0x18 ];
	UnsignedInt m_options;								// +0x18
	unsigned char m_unmodelled_1c[ 0x34 - 0x1c ];
	const SpecialPowerTemplate *m_specialPowerTemplate;	// +0x34
};

// ---------------------------------------------------------------------------
// The 0x20-byte primary prefix, spelled as the landed ctor TU
// (game/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdate_ctor_Thunk.cpp)
// spells it: vfptrs at +0x00, +0x0c and +0x10, which is what that ctor installs.
// Only the total size, 0x20, reaches this body's codegen.
// ---------------------------------------------------------------------------

class __declspec(novtable) ObjectModule
{
public:
	virtual void objectModuleAnchor();

private:
	unsigned int m_moduleData;							// +0x04
	Object *m_object;									// +0x08
};

class __declspec(novtable) UpdateModule : public ObjectModule
{
};

class SpecialAbilityUpdateBaseC
{
public:
	virtual void specialAbilityBaseCAnchor();			// vfptr +0x0c
};

class SpecialAbilityUpdateBase10
{
public:
	virtual void specialAbilityBase10Anchor();			// vfptr +0x10

	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1c;
};

// The ctor TU folds the +0x20 base into its own `SpecialAbilityUpdateBase` under
// the opaque name SpecialAbilityUpdateBase20.  The vtable evidence above gives it
// a real name, so the split is made here instead; the full-object layout is the
// same in both TUs.
class __declspec(novtable) SpecialAbilityUpdateBase : public UpdateModule,
	public SpecialAbilityUpdateBaseC,
	public SpecialAbilityUpdateBase10
{
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerUpdateModule.h
// vtable 0x010c36b8, installed at +0x20 by the ctor at 0x002A6360.  BFME's
// interface has 9 slots against Zero Hour's 12 and only slot 6 is pinned by
// evidence, so the rest keep address-free opaque names rather than a guessed
// mapping onto the Zero Hour order.
class __declspec(novtable) SpecialPowerUpdateInterface
{
public:
	virtual void slot0( void ) = 0;
	virtual void slot1( void ) = 0;
	virtual void slot2( void ) = 0;
	virtual void slot3( void ) = 0;
	virtual void slot4( void ) = 0;
	virtual void slot5( void ) = 0;
	virtual Bool isPowerCurrentlyInUse( const CommandButton *command = 0 ) const = 0;	// slot 6 -> 0x002A6260
	virtual void slot7( void ) = 0;
	virtual void slot8( void ) = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbilityUpdate.h
class SpecialAbilityUpdate : public SpecialAbilityUpdateBase,
	public SpecialPowerUpdateInterface
{
public:
	virtual Bool isPowerCurrentlyInUse( const CommandButton *command = 0 ) const;

	UnsignedInt getSpecialObjectCount( void ) const
	{
		return m_specialObjectEntries;
	}

private:
	// upstream enum: SpecialAbilityUpdate.h:262 (PackingState)
	enum PackingState
	{
		STATE_NONE = 0,
		STATE_PACKING = 1,
		STATE_UNPACKING = 2,
		STATE_PACKED = 3,
		STATE_UNPACKED = 4
	};

	unsigned char m_unmodelled_24[ 0x30 - 0x24 ];
	PackingState m_packingState;						// +0x30
	unsigned char m_unmodelled_34[ 0xd0 - 0x34 ];
	UnsignedInt m_specialObjectEntries;					// +0xd0
	unsigned char m_unmodelled_d4[ 0xe2 - 0xd4 ];
	Bool m_withinStartAbilityRange;						// +0xe2
};

// ?isPowerCurrentlyInUse@SpecialAbilityUpdate@@UBE_NPBVCommandButton@@@Z
Bool SpecialAbilityUpdate::isPowerCurrentlyInUse( const CommandButton *command ) const
{
	if( command )
	{
		const SpecialPowerTemplate *specialPowerTemplate = command->getSpecialPowerTemplate();
		if( specialPowerTemplate &&
			specialPowerTemplate->getSpecialPowerType() == SPECIAL_REMOTE_CHARGES )
		{
			if( !(command->getOptions() & 0x200) )
				return getSpecialObjectCount() == 0;
		}
	}

	if( m_packingState != STATE_NONE )
	{
		if( m_packingState == STATE_PACKING || m_packingState == STATE_PACKED )
		{
			if( command )
			{
				const UnsignedInt reloadTime = command->getSpecialPowerTemplate()->getReloadTime();
				if( reloadTime == 0 )
					return false;
			}
		}

		if( m_withinStartAbilityRange )
			return true;
	}

	return false;
}
