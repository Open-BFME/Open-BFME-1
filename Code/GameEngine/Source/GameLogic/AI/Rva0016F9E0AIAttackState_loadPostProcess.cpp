// cl: /DNDEBUG /MD /EHsc
// readable body of ?loadPostProcess@AIAttackState@@MAEXXZ: Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
// BFME AIAttackState::loadPostProcess, retail 0x0016F9E0.

typedef bool Bool;

class Object;
class Team;
class Weapon;
enum WeaponSlotType { WEAPON_SLOT_TYPE_UNSPECIFIED = 0 };

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const StringBase<T> &other );
	~StringBase();
	void set( const StringBase<T> &other );

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}

	AsciiString &operator=( const AsciiString &other )
	{
		StringBase<char>::set( other );
		return *this;
	}
};

class Rva0016F9E0SourceLockShim
{
public:
	Bool isCurWeaponLocked() const;
};

class Rva0016F9E0WeaponNameShim
{
public:
	AsciiString getName() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	Object *getGoalObject();

	char m_unreconstructed_00[ 0x10 ];
	Object *m_owner;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Weapon *getCurrentWeapon( WeaponSlotType *slot );

	Team *getTeam() const { return m_team; }

private:
	char m_unreconstructed_000[ 0x23C ];
	Team *m_team;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class Weapon
{
public:
	AsciiString getName() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIAttackState
{
protected:
	// The virtual slot is inherited through State in retail.  Keeping it here
	// preserves the State subobject's machine pointer at +0x1C.
	virtual void loadPostProcess();

private:
	char m_statePrefix[ 0x18 ];
	StateMachine *m_machine;
      char m_attackFields[ 0x10 ];
	Team *m_victimTeam;
	char m_originalVictimPos[ 0x0C ];
	AsciiString m_lockedWeaponOnEnter;
};

// ?loadPostProcess@AIAttackState@@MAEXXZ
void AIAttackState::loadPostProcess()
{
	Object *victim = m_machine->getGoalObject();
	if (victim)
		m_victimTeam = victim->getTeam();

      Object *source = m_machine->m_owner;
      Rva0016F9E0SourceLockShim *lockSource =
          reinterpret_cast<Rva0016F9E0SourceLockShim *>( source );
      if (lockSource->isCurWeaponLocked())
      {
          if (source->getCurrentWeapon( 0 ))
          {
              m_lockedWeaponOnEnter =
                  reinterpret_cast<Rva0016F9E0WeaponNameShim *>(
                      source->getCurrentWeapon( 0 ))->getName();
          }
          else
          {
              m_lockedWeaponOnEnter.~AsciiString();
          }
      }
      else
      {
          m_lockedWeaponOnEnter.~AsciiString();
      }
}
