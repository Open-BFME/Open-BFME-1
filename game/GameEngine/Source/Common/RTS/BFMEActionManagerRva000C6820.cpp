// cl: /DNDEBUG /MD /EHsc /Igame/GameEngine/Source/GameLogic
//
// Open-BFME: retail 0x000C6820 (209 bytes), reached through ILT 0x00002FEF.
// The matched InGameUI::canSelectedObjectsDoAction
// (InGameUICanSelectedObjectsDoAction.cpp) calls it as
// BFMEActionManager::rva000C6820 for its command case 17, beside
// rva000C4080 for case 16. It refuses when rva000C4080 already allows the
// pair, then walks the twenty buttons of the source object's command set and
// answers true for the first special-power button (command 0x17) whose
// template is power type 39 and whose module on the source object lets
// ActionManager::canDoSpecialPowerAtObject succeed (options with bit 0x8000
// cleared, source requirements checked). The method name is address-derived.
//
// Shape notes measured against retail: the special-power type test sits in
// its own nested if, the options are computed into a local before the module
// test, and the template goes through the const friend_getFinalOverride
// inline over the recursive non-const friend (two inlined levels, then the
// call).
#include "command_source_type.h"

enum SpecialPowerType
{
	SPECIAL_POWER_RVA000C6820_39 = 0x27
};

class AsciiString;


class Overridable
{
public:
	virtual ~Overridable();
	// Non-const, as Zero Hour declares it: the recursion's call binds to
	// ILT 0x00048C61, where ilt_oracle confirms the non-const decoration.
	Overridable *friend_getFinalOverride()
	{
		if( m_nextOverride )
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}
	const Overridable *getFinalOverride() const
	{
		if( m_nextOverride )
			return m_nextOverride->getFinalOverride();
		return this;
	}
	const Overridable *friend_getFinalOverride() const
	{
		if( m_nextOverride )
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}
	Overridable *m_nextOverride;
};

class SpecialPowerTemplate : public Overridable
{
public:
	SpecialPowerType getSpecialPowerType() const
	{
		return ( (const SpecialPowerTemplate *)friend_getFinalOverride() )->m_type;
	}
	char m_rva08[ 0x14 - 8 ];
	SpecialPowerType m_type;
};

class SpecialPowerModuleInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14();
	virtual const SpecialPowerTemplate *getSpecialPowerTemplate() const;
};

class CommandButton
{
public:
	char m_rva00[ 0x10 ];
	int m_command;
	char m_rva14[ 4 ];
	unsigned int m_options;
	char m_rva1C[ 0x34 - 0x1C ];
	const SpecialPowerTemplate *m_specialPower;
};

class CommandSet
{
public:
	const CommandButton *getCommandButton( int i ) const;
};

class ControlBar
{
public:
	const CommandSet *findCommandSet( const AsciiString &name );
};
extern ControlBar *TheControlBar;

class Object
{
public:
	const AsciiString &getCommandSetString() const;
	SpecialPowerModuleInterface *findSpecialPowerModuleInterface( SpecialPowerType type ) const;
};

class ActionManager
{
public:
	bool canDoSpecialPowerAtObject( const Object *obj, const Object *target, CommandSourceType commandSource,
		const SpecialPowerTemplate *spTemplate, unsigned int commandOptions, bool checkSourceRequirements );
};

class BFMEActionManager
{
public:
	bool rva000C4080( const Object *obj, const Object *target, CommandSourceType commandSource );
	bool rva000C6820( const Object *obj, const Object *target, CommandSourceType commandSource );
};

bool BFMEActionManager::rva000C6820( const Object *obj, const Object *target, CommandSourceType commandSource )
{
	if( rva000C4080( obj, target, commandSource ) )
		return false;

	const CommandSet *commandSet = TheControlBar->findCommandSet( obj->getCommandSetString() );
	if( commandSet )
	{
		for( int i = 0; i < 20; ++i )
		{
			const CommandButton *button = commandSet->getCommandButton( i );
			if( button && button->m_command == 0x17 )
			{
				if( button->m_specialPower->getSpecialPowerType() == SPECIAL_POWER_RVA000C6820_39 )
				{
					SpecialPowerModuleInterface *module = obj->findSpecialPowerModuleInterface( SPECIAL_POWER_RVA000C6820_39 );
					unsigned int options = button->m_options & ~0x8000;
					if( module )
					{
						if( ( (ActionManager *)this )->canDoSpecialPowerAtObject( obj, target, commandSource,
							module->getSpecialPowerTemplate(), options, true ) )
							return true;
					}
				}
			}
		}
	}
	return false;
}
