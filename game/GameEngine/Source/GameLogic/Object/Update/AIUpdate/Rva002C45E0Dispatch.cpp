// BFME anonymous AI command override at retail 0x002C45E0.
// The secondary command interface is adjusted by -0x20 in the retail body;
// the root and Object views preserve the proven BFME offsets and vtable slots.
// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
struct AICommandParms
{
	int m_cmd;
	int m_cmdSource;
	char m_pos[12];
	void *m_obj;
};
class Object;
class Contain
{
public:
	virtual void containPad0() = 0;
	virtual void containPadBeforeGarrisonable() = 0;
	virtual Bool isGarrisonable() = 0;
	virtual void containPad1() = 0;
	virtual void containPad2() = 0;
	virtual void containPad3() = 0;
	virtual void containPad4() = 0;
	virtual void containPad5() = 0;
	virtual void containPad6() = 0;
	virtual void containPad7() = 0;
	virtual void containPad8() = 0;
	virtual void containPad9() = 0;
	virtual void containPad10() = 0;
	virtual void containPad11() = 0;
	virtual void containPad12() = 0;
	virtual void containPad13() = 0;
	virtual void containPad14() = 0;
	virtual void containPad15() = 0;
	virtual void containPad16() = 0;
	virtual void containPad17() = 0;
	virtual void containPad18() = 0;
	virtual void containPad19() = 0;
	virtual void containPad20() = 0;
	virtual void containPad21() = 0;
	virtual void containPad22() = 0;
	virtual void containPad23() = 0;
	virtual Object *getObject() = 0;
};
class Object
{
public:
	char m_beforeContain[0x1fc];
	Contain *m_contain;
	char m_toContainedBy[0x214 - 0x200];
	Object *m_containedBy;
};
class ActionObject
{
public:
	virtual void actionPad0() = 0;
	virtual void actionPad1() = 0;
	virtual void actionPad2() = 0;
	virtual void actionPad3() = 0;
	virtual void actionPad4() = 0;
	virtual void action(Object *object) = 0;
};
class Root
{
public:
	virtual void rootPad0() = 0;
	virtual void rootPad1() = 0;
	virtual void rootPad2() = 0;
	virtual void rootPad3() = 0;
	virtual void rootPad4() = 0;
	virtual void rootPad5() = 0;
	virtual void rootPad6() = 0;
	virtual void rootPad7() = 0;
	virtual void rootPad8() = 0;
	virtual void rootPad9() = 0;
	virtual void rootPad10() = 0;
	virtual void rootPad11() = 0;
	virtual void rootPad12() = 0;
	virtual void rootPad13() = 0;
	virtual void rootPad14() = 0;
	virtual void rootPad15() = 0;
	virtual void rootPad16() = 0;
	virtual void rootPad17() = 0;
	virtual void rootPad18() = 0;
	virtual void rootPad19() = 0;
	virtual void rootPad20() = 0;
	virtual void rootPad21() = 0;
	virtual void rootPad22() = 0;
	virtual void rootPad23() = 0;
	virtual void rootPad24() = 0;
	virtual void rootPad25() = 0;
	virtual void rootPad26() = 0;
	virtual void rootPad27() = 0;
	virtual void rootPad28() = 0;
	virtual void rootPad29() = 0;
	virtual void rootPad30() = 0;
	virtual void rootPad31() = 0;
	virtual void rootPad32() = 0;
	virtual void rootPad33() = 0;
	virtual void rootPad34() = 0;
	virtual void rootPad35() = 0;
	virtual void rootPad36() = 0;
	virtual void rootPad37() = 0;
	virtual void rootPad38() = 0;
	virtual void rootPad39() = 0;
	virtual void rootPad40() = 0;
	virtual void rootPad41() = 0;
	virtual void rootPad42() = 0;
	virtual void rootPad43() = 0;
	virtual void rootPad44() = 0;
	virtual void rootPad45() = 0;
	virtual void rootPad46() = 0;
	virtual void rootPad47() = 0;
	virtual void rootPad48() = 0;
	virtual void rootPad49() = 0;
	virtual void rootPad50() = 0;
	virtual void rootPad51() = 0;
	virtual void rootPad52() = 0;
	virtual void rootPad53() = 0;
	virtual void rootPad54() = 0;
	virtual void rootPad55() = 0;
	virtual void rootPad56() = 0;
	virtual void rootPad57() = 0;
	virtual void rootPad58() = 0;
	virtual void rootPad59() = 0;
	virtual void rootPad60() = 0;
	virtual void rootPad61() = 0;
	virtual void rootPad62() = 0;
	virtual void rootPad63() = 0;
	virtual void rootPad64() = 0;
	virtual void rootPad65() = 0;
	virtual void rootPad66() = 0;
	virtual void rootPad67() = 0;
	virtual void rootPad68() = 0;
	virtual void rootPad69() = 0;
	virtual void rootPad70() = 0;
	virtual void rootPad71() = 0;
	virtual void rootPad72() = 0;
	virtual void rootPad73() = 0;
	virtual void rootPad74() = 0;
	virtual void rootPad75() = 0;
	virtual void rootPad76() = 0;
	virtual void rootPad77() = 0;
	virtual void rootPad78() = 0;
	virtual void rootPad79() = 0;
	virtual void rootPad80() = 0;
	virtual void rootPad81() = 0;
	virtual void rootPad82() = 0;
	virtual void rootPad83() = 0;
	virtual void rootPad84() = 0;
	virtual void rootPad85() = 0;
	virtual void rootPad86() = 0;
	virtual void rootPad87() = 0;
	virtual void rootPad88() = 0;
	virtual void rootPad89() = 0;
	virtual void rootPad90() = 0;
	virtual void rootPad91() = 0;
	virtual void rootPad92() = 0;
	virtual void rootPad93() = 0;
	virtual void rootPad94() = 0;
	virtual void rootPad95() = 0;
	virtual void rootPad96() = 0;
	virtual void rootPad97() = 0;
	virtual void rootPad98() = 0;
	virtual void rootPad99() = 0;
	virtual void rootPad100() = 0;
	virtual void rootPad101() = 0;
	virtual void rootPad102() = 0;
	virtual void rootPad103() = 0;
	virtual void rootPad104() = 0;
	virtual void rootPad105() = 0;
	virtual void rootPad106() = 0;
	virtual void rootPad107() = 0;
	virtual void rootPad108() = 0;
	virtual void rootPad109() = 0;
	virtual void rootPad110() = 0;
	virtual void rootPad111() = 0;
	virtual void rootPad112() = 0;
	virtual void rootPad113() = 0;
	virtual void rootPad114() = 0;
	virtual void rootPad115() = 0;
	virtual void rootPad116() = 0;
	virtual void rootPad117() = 0;
	virtual void rootPad118() = 0;
	virtual void rootPad119() = 0;
	virtual void rootPad120() = 0;
	virtual void rootPad121() = 0;
	virtual void rootPad122() = 0;
	virtual void rootPad123() = 0;
	virtual void rootPad124() = 0;
	virtual void rootPad125() = 0;
	virtual void rootPad126() = 0;
	virtual void rootPad127() = 0;
	virtual void rootPad128() = 0;
	virtual void rootPad129() = 0;
	virtual void rootPad130() = 0;
	virtual void rootPad131() = 0;
	virtual Bool gate(const AICommandParms *parms) = 0;
	char m_beforeObject[4];
	Object *m_object;
	char m_afterObject[0x20 - 0x0c];
};
class AIUpdateInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms);
};
class Rva002C45E0
{
public:
	virtual void dispatch(const AICommandParms *parms);
};

void Rva002C45E0::dispatch(const AICommandParms *parms)
{
	const AICommandParms *command = parms;
	Root *root = reinterpret_cast<Root *>(reinterpret_cast<char *>(this) - 0x20);
	if (!root->gate(command))
		return;

	Object *object = *reinterpret_cast<Object **>(reinterpret_cast<char *>(this) - 0x18);
	Object *containedBy = object->m_containedBy;
	Bool garrisonable = false;
	if (containedBy) {
		Contain *contain = containedBy->m_contain;
		if (contain)
			garrisonable = contain->isGarrisonable();
	}

	Object *target = 0;
	switch (command->m_cmd) {
	case 11:
	case 12:
		target = reinterpret_cast<Object *>(command->m_obj);
		// fall through to the commands that perform the contain action
	case 0:
	case 1:
	case 3:
	case 4:
	case 6:
	case 7:
	case 8:
	case 9:
	case 23:
	case 24:
	case 36:
	case 50:
	case 51:
	case 52:
	case 54:
	case 65:
	case 66:
		if (!garrisonable) {
			Contain *contain = object->m_contain;
			if (contain) {
				Object *actionObject = contain->getObject();
				if (actionObject)
					reinterpret_cast<ActionObject *>(actionObject)->action(target);
			}
		}
		break;
	default:
		goto finish;
	}

	finish:
	reinterpret_cast<AIUpdateInterface *>(this)->AIUpdateInterface::aiDoCommand(command);
}

