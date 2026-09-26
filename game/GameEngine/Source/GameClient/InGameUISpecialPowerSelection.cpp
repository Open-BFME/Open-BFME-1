// cl: /O2 /Ob2 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// InGameUI::canSelectedObjectsDoSpecialPower, retail RVA 0x00443270, 587 B.
// Ported from GeneralsMD/Code/GameEngine/Source/GameClient/InGameUI.cpp.
// Copyright 2025 Electronic Arts Inc.; GPL-3.0-or-later, as in that source.
// Identity: the six-argument source twin and all three ActionManager calls;
// callers at VA 0x009AE446/47C/49C route through ILT RVA 0x0003BC64.
// Capstone covers both ret 0x18 exits, with the final one at +0x248 and
// int3 padding beginning at +0x24B. No bytes beyond that boundary are claimed.
// BFME permits object and position checks independently, including when both
// option groups are set. The final boolean argument to each manager call is true.
// STLport keeps this function's EH frame but omits per-node try/catch wrappers.
#define _STLP_NO_EXCEPTIONS 1
#include <list>
class SpecialPowerTemplate;
struct Coord3D;
class Object;
// BFME layout witness: Drawable::m_object is +0xFC.
class Drawable {
 unsigned char m_unmodelled_00[0xfc];
 Object *m_object;
public: Object *getObject() const { return m_object; }
};
// Matched Object::getDrawable: vtable slot 10 -> ILT 0x2074D -> 0x1BE440.
class Object { public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual Drawable *getDrawable() const;
};
// name_oracle: m_options +0x18; m_specialPower +0x34 (BFME, not ZH +0x24).
class CommandButton {
 unsigned char m_unmodelled_00[0x18];
 unsigned m_options;
 unsigned char m_unmodelled_1c[0x34-0x1c];
 const SpecialPowerTemplate *m_specialPower;
public:
 unsigned getOptions() const { return m_options; }
 const SpecialPowerTemplate *getSpecialPowerTemplate() const { return m_specialPower; }
};
enum CommandSourceType { CMD_FROM_PLAYER = 0 };
class ActionManager { public:
 bool canDoSpecialPower(const Object *,const SpecialPowerTemplate *,CommandSourceType,unsigned,bool=true);
 bool canDoSpecialPowerAtObject(const Object *,const Object *,CommandSourceType,const SpecialPowerTemplate *,unsigned,bool=true);
 bool canDoSpecialPowerAtLocation(const Object *,const Coord3D *,CommandSourceType,const SpecialPowerTemplate *,const Object *,unsigned,bool=true);
};
extern ActionManager *TheActionManager;
typedef std::list<Drawable *> DrawableList;
typedef DrawableList::const_iterator DrawableListCIt;
// Slot +0xFC agrees with the landed CommandXlatVoice.cpp callers.
class InGameUI { public:
 enum SelectionRules { SELECTION_ANY=0, SELECTION_ALL=1 };
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
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
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot50();
 virtual void slot51();
 virtual void slot52();
 virtual void slot53();
 virtual void slot54();
 virtual void slot55();
 virtual void slot56();
 virtual void slot57();
 virtual void slot58();
 virtual void slot59();
 virtual void slot60();
 virtual void slot61();
 virtual void slot62();
 virtual const DrawableList *getAllSelectedDrawables() const;
 bool canSelectedObjectsDoSpecialPower(const CommandButton *,const Object *,const Coord3D *,SelectionRules,unsigned,Object *) const;
};
extern InGameUI *TheInGameUI;
bool InGameUI::canSelectedObjectsDoSpecialPower( const CommandButton *command, const Object *objectToInteractWith, const Coord3D *position, SelectionRules rule, unsigned commandOptions, Object* ignoreSelObj ) const
{
	//Get the special power template.
	const SpecialPowerTemplate *spTemplate = command->getSpecialPowerTemplate();

	// NEED_TARGET_POS is bit 5; COMMAND_OPTION_NEED_OBJECT_TARGET is bits 0..2.
	bool doAtPosition = (command->getOptions() & 0x20) != 0;
	bool doAtObject = (command->getOptions() & 7) != 0;

	//Sanity checks
	if( doAtObject && !objectToInteractWith && !doAtPosition )
	{
		return false;
	}
	if( doAtPosition && !position && !doAtObject )
	{
		return false;		
	}

	// get selected list of drawables
	Drawable* ignoreSelDraw = ignoreSelObj ? ignoreSelObj->getDrawable() : 0;

	DrawableList tmpList;
	if (ignoreSelDraw)
		tmpList.push_back(ignoreSelDraw);

	const DrawableList* selected = (tmpList.size() > 0) ? &tmpList : TheInGameUI->getAllSelectedDrawables();

	// set up counters for rule checking
	int count = 0;
	int qualify = 0;

	// loop through all the selected drawables
	for( DrawableListCIt it = selected->begin(); it != selected->end(); ++it )
	{
	
		// get this drawable
		Drawable* other = *it;
		count++;

		if( !doAtObject && !doAtPosition )
		{
			if( TheActionManager->canDoSpecialPower( other->getObject(), spTemplate, CMD_FROM_PLAYER, commandOptions ) )
			{
				//This is the no target version
				if( rule == SELECTION_ANY )
				{
					return true;
				}
				qualify++;
			}
		}
		if( doAtObject )
		{
			if( objectToInteractWith && TheActionManager->canDoSpecialPowerAtObject( other->getObject(), objectToInteractWith, CMD_FROM_PLAYER, spTemplate, commandOptions ) )
			{
				//This requires a object target
				if( rule == SELECTION_ANY )
				{
					return true;
				}
				qualify++;
			}
		}
		if( doAtPosition )
		{
			if( position && TheActionManager->canDoSpecialPowerAtLocation( other->getObject(), position, CMD_FROM_PLAYER, spTemplate, objectToInteractWith, commandOptions ) )
			{
				//This requires a valid location.
				if( rule == SELECTION_ANY )
				{
					return true;
				}
				qualify++;
			}
		}
	}
	if( rule == SELECTION_ALL && count > 0 && qualify == count )
	{
		return true;
	}
	return false;
}

