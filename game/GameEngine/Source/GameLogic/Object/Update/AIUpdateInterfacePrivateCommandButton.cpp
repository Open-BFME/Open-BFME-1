// BFME 1.03 AIUpdateInterface::privateCommandButton (RVA 0x0027DF90, 140 bytes).
// cl: /DNDEBUG /MD /EHsc
//
// Identity comes from the five calls the body makes. tools/callees.py resolves
// them, through their ILT thunks, to Overridable::getFinalOverride,
// Object::getCommandSetString, ControlBar::findCommandSet,
// CommandSet::getCommandButton and AICommandInterface::aiIdle, in that order,
// and the global the body loads at VA 0x012F33F8 is TheControlBar. Zero Hour's
// AIUpdateInterface::privateCommandButton makes exactly those calls in exactly
// that order, and nothing else in the image does.
//
// The TU-local views keep the retail object offsets: the owning Object sits at
// AIUpdateInterface + 8, the AI module at Object + 0x204, the kind-of word at
// ThingTemplate + 0xC8, and the command type at CommandButton + 0x10. The
// AICommandInterface base sits at AIUpdateInterface + 0x20, which is why the
// idle order loads its receiver with a lea.
//
// Read the owning Object once into a local. Retail keeps it in esi across the
// override-chain call, and a second getObject() read reloads it instead.
//
// upstream: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT,
	CMD_FROM_AI,
	CMD_FROM_DOZER,
	CMD_DEFAULT_SWITCH_WEAPON
};

enum KindOfType { KINDOF_PROJECTILE = 25 };

enum { MAX_COMMANDS_PER_SET = 20 };

enum GUICommandType
{
	GUI_COMMAND_NONE = 0,
	GUI_COMMAND_STOP = 13
};

class AsciiString;

// This view emits the same 26-byte chain walk already owned by
// Overridable::getFinalOverride in INIWater.cpp (RVA 0x00087A80). Its existing
// symbol pin reaches that body through ILT 0x000022BB.
class BfmeOverridable
{
public:
	virtual void slot00();
	const BfmeOverridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

	BfmeOverridable *m_nextOverride;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public BfmeOverridable
{
public:
	unsigned char m_unmodelled_08[0xC8 - 8];
	UnsignedInt m_kindof[1]; // partial view: only the observed first word is modelled
};

// Override.h accessor shape; Thing.h stores this one-pointer wrapper.
template<class T> class OVERRIDE
{
public:
	__forceinline const T *operator*() const
	{
		if (!m_overridable)
			return 0;
		return static_cast<const T *>(m_overridable->getFinalOverride());
	}
	__forceinline operator const T *() const { return operator*(); }

	const T *m_overridable;
};

class Thing
{
public:
	virtual void slot00();
	OVERRIDE<ThingTemplate> m_template;
	__forceinline const ThingTemplate *getTemplate() const { return m_template; }
};

class AIUpdateInterface;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	void aiIdle( CommandSourceType cmdSource );
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandButton
{
public:
	GUICommandType getCommandType() const { return m_command; }

	unsigned char m_unmodelled_00[0x10];
	GUICommandType m_command;
};

class CommandSet
{
public:
	const CommandButton *getCommandButton( Int i ) const;
};

class ControlBar
{
public:
	const CommandSet *findCommandSet( const AsciiString &name );
};

extern ControlBar *TheControlBar;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	const AsciiString &getCommandSetString() const;
	AIUpdateInterface *getAI() const { return m_ai; }

	unsigned char m_unmodelled_008[0x204 - 8];
	AIUpdateInterface *m_ai;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	virtual Int aiSlot00() = 0;
protected:
	virtual void privateCommandButton( const CommandButton *commandButton, CommandSourceType cmdSource );
public:
	Object *getObject() const { return m_object; }

	unsigned char m_unmodelled_04[4];
	Object *m_object;
};

void AIUpdateInterface::privateCommandButton( const CommandButton *commandButton, CommandSourceType cmdSource )
{
	if( !commandButton )
	{
		return;
	}

	Object *owner = getObject();

	if (owner->getTemplate()->m_kindof[0] & (1U << KINDOF_PROJECTILE))
		return;

	// Scripts order whole teams at once, so an object that cannot run the
	// command simply falls through here.
	if( owner )
	{
		AIUpdateInterface *ai = owner->getAI();
		if( ai )
		{
			// Make sure the owner has the same command button.
			const CommandSet *commandSet = TheControlBar->findCommandSet( owner->getCommandSetString() );
			if( commandSet )
			{
				for( Int i = 0; i < MAX_COMMANDS_PER_SET; i++ )
				{
					const CommandButton *aCommandButton = commandSet->getCommandButton(i);
					if( commandButton == aCommandButton )
					{
						switch( commandButton->getCommandType() )
						{
							// Only the no-target AI buttons are implemented here.
							case GUI_COMMAND_STOP:
								reinterpret_cast<AICommandInterface *>(
									reinterpret_cast<char *>(ai) + 0x20)->aiIdle( cmdSource );
								break;
							default:
								break;
						}
					}
				}
			}
		}
	}
}
