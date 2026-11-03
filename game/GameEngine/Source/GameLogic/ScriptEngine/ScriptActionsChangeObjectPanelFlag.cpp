// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail RVA 0x002F8A50, 413 bytes (ret 0xC):
// ScriptActions::changeObjectPanelFlagForSingleObject. Identity: the body calls
// itself through ILT 0x0002DD85, which is pinned to this decorated name and
// which tools/ilt_oracle.py CONFIRMS for this address; its two callers are the
// matched doAffectObjectPanelFlagsUnit/Team; the seven tested names are
// Scripts.cpp's TheObjectFlagsNames (retail VA 0x012B3E78: "Enabled" ..
// "Player Targetable"). Zero Hour's ScriptActions.cpp body, with BFME's
// changes: the first five names are tested with StringBase<char>::compare, the
// last two with the out-of-line operator==, and "Indestructible" also walks
// the object's contain list and applies the flag to every contained object.
// Control shape (one else-if chain, then a propagate flag guarding the contain
// walk) follows the BFME 2 donor Code/GameEngine/Source/GameLogic/ScriptEngine/
// ScriptActions_doAffectObjectPanelFlagsTeam.cpp (open-bfme-2 45afcff3); the
// return-per-branch Zero Hour shape swaps the two contain vcall registers.
// Object offsets: contain +0x1FC, body +0x200, AI +0x204 (matched sibling
// ScriptActionsTeamMemberWalk.cpp reads AI +0x204 and its +0x32C flag).

typedef bool Bool;

#include "ascii_string.h"

// out-of-line StringBase<char> == const char * (retail callee; the header declares only the template forms)
bool operator==(const StringBase<char> &s1, const char *s2);

extern const char *TheObjectFlagsNames[];

enum ObjectScriptStatusBit
{
	OBJECT_STATUS_SCRIPT_DISABLED = 1,
	OBJECT_STATUS_SCRIPT_UNPOWERED = 2,
	OBJECT_STATUS_SCRIPT_UNSELLABLE = 4,
	OBJECT_STATUS_SCRIPT_TARGETABLE = 0x10
};

class Object;

class BodyModuleInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32();
	virtual void setIndestructible(Bool indestructible);		// +0x84
};

struct ContainedObjectNode
{
	ContainedObjectNode *m_next;
	ContainedObjectNode *m_prev;
	Object *m_object;
};

struct ContainedObjectList
{
	ContainedObjectNode *m_head;
};

class ContainModuleInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	virtual int slot26();											// +0x68
	virtual void slot27(); virtual void slot28(); virtual void slot29(); virtual void slot30();
	virtual void slot31(); virtual void slot32(); virtual void slot33(); virtual void slot34();
	virtual void slot35(); virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual void slot39(); virtual void slot40(); virtual void slot41(); virtual void slot42();
	virtual void slot43(); virtual void slot44(); virtual void slot45(); virtual void slot46();
	virtual void slot47(); virtual void slot48(); virtual void slot49(); virtual void slot50();
	virtual void slot51(); virtual void slot52(); virtual void slot53(); virtual void slot54();
	virtual void slot55(); virtual void slot56(); virtual void slot57(); virtual void slot58();
	virtual void slot59(); virtual void slot60(); virtual void slot61(); virtual void slot62();
	virtual void slot63(); virtual void slot64();
	virtual const ContainedObjectList *slot65();					// +0x104
};

class AIUpdateInterface
{
	unsigned char m_pad[0x32C];
	unsigned char m_isRecruitable;
public:
	void setIsRecruitable(Bool recruitable) { m_isRecruitable = recruitable; }
};

class Object
{
public:
	void setScriptStatus(ObjectScriptStatusBit bit, Bool set);
	Bool isMassSelectable() const;
	void setSelectable(Bool selectable);

	ContainModuleInterface *getContain() const { return m_contain; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }

private:
	unsigned char m_pad[0x1FC];
	ContainModuleInterface *m_contain;		// +0x1FC
	BodyModuleInterface *m_body;			// +0x200
	AIUpdateInterface *m_ai;				// +0x204
};

class ScriptActions
{
protected:
	void changeObjectPanelFlagForSingleObject(Object *obj, const AsciiString &flagToChange, Bool newVal);
};

// ?changeObjectPanelFlagForSingleObject@ScriptActions@@IAEXPAVObject@@ABVAsciiString@@_N@Z
void ScriptActions::changeObjectPanelFlagForSingleObject(Object *obj, const AsciiString &flagToChange, Bool newVal)
{
	Bool propagate = false;
	if (flagToChange.compare(TheObjectFlagsNames[0]) == 0) {
		obj->setScriptStatus(OBJECT_STATUS_SCRIPT_DISABLED, !newVal);
	} else if (flagToChange.compare(TheObjectFlagsNames[1]) == 0) {
		obj->setScriptStatus(OBJECT_STATUS_SCRIPT_UNPOWERED, !newVal);
	} else if (flagToChange.compare(TheObjectFlagsNames[2]) == 0) {
		BodyModuleInterface *body = obj->getBodyModule();
		if (body)
			body->setIndestructible(newVal);
		propagate = true;
	} else if (flagToChange.compare(TheObjectFlagsNames[3]) == 0) {
		obj->setScriptStatus(OBJECT_STATUS_SCRIPT_UNSELLABLE, newVal);
	} else if (flagToChange.compare(TheObjectFlagsNames[4]) == 0) {
		if (obj->isMassSelectable() != newVal)
			obj->setSelectable(newVal);
	} else if ((const StringBase<char> &)flagToChange == TheObjectFlagsNames[5]) {
		if (obj->getAIUpdateInterface())
			obj->getAIUpdateInterface()->setIsRecruitable(newVal);
	} else if ((const StringBase<char> &)flagToChange == TheObjectFlagsNames[6]) {
		obj->setScriptStatus(OBJECT_STATUS_SCRIPT_TARGETABLE, newVal);
	} else {
		return;
	}
	if (propagate) {
		ContainModuleInterface *contain = obj->getContain();
		if (contain && contain->slot26()) {
			const ContainedObjectList *list = obj->getContain()->slot65();
			for (ContainedObjectNode *node = list->m_head->m_next; node != list->m_head; node = node->m_next)
			{
				if (node->m_object)
					changeObjectPanelFlagForSingleObject(node->m_object, flagToChange, newVal);
			}
		}
	}
}
