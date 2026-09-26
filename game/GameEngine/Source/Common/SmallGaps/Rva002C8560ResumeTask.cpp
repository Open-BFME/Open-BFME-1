// ?resumeTask@Rva002C8560Owner@@QAEXPAVObject@@W4CommandSourceType@@@Z
// Identity evidence: calls TheActionManager->canResumeConstructionOf(this->m_object, obj, cmdSource)
// then, if allowed, dispatches through a vtable at this+0x340 slot 0x30 (index 12) with args
// (0, obj) -- byte-identical shape to the already-landed twin at 0x002B6BF0
// (?privateResumeConstruction@DozerAIUpdate@@MAEXPAVObject@@W4CommandSourceType@@@Z in
// game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdate_privateResumeConstructionTwin.cpp,
// which itself models DozerAIUpdate::privateResumeConstruction / WorkerAIUpdate::privateResumeConstruction
// from inputs/reference/CnC_Generals_Zero_Hour). This RVA is a distinct unclaimed twin of that body
// (different address, no ledger row), so it is landed address-derived per the GAP naming policy.
class Object;
enum CommandSourceType { CMD_FROM_PLAYER = 0 };

class BFMEActionManager;
extern BFMEActionManager* TheActionManager;

class ActionManager
{
public:
	bool canResumeConstructionOf(const Object*, const Object*, CommandSourceType);
};

struct Rva002C8560Iface
{
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
	virtual void newTask(int task, Object* obj);
};

struct Rva002C8560Owner
{
	unsigned char m_pad0[8];
	Object* m_object;
	unsigned char m_pad2[0x340 - 0xC];
	Rva002C8560Iface m_iface;

	void resumeTask(Object* obj, CommandSourceType cmdSource);
};

void Rva002C8560Owner::resumeTask(Object* obj, CommandSourceType cmdSource)
{
	if (obj == 0)
		return;

	CommandSourceType src = cmdSource;
	Object* self = m_object;
	if (((ActionManager*)TheActionManager)->canResumeConstructionOf(self, obj, src) == false)
		return;

	m_iface.newTask(0, obj);
}
