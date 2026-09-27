// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: ProneUpdate::ProneUpdate(Thing *, const ModuleData *), retail
// 0x0029FE70, 77 bytes.  Until now this file was a naked assembly lift of
// retail; the body below is the real C++ and the lifted function is gone.
//
// IDENTITY.  The byte-true factory
//   ?friend_newModuleInstance@ProneUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
// does `new ProneUpdate(thing, data)`, and vtable 0x010C13F4 slot zero routes
// through ILT 0x00012C2E to the already matched protected deleting destructor
// (ProneUpdateDeletingDestructor.cpp, 0x0029FF70), so the class and the
// (Thing *, const ModuleData *) signature are both proven.  The three-base
// module-constructor shape and the `ret 8` tail are shared with
// ??0AssistedTargetingUpdate (0x0027FB60), whose clean source is the donor for
// the class shape below.
//
// FIELDS.  The layout is the UpdateModule shape: ObjectModule at +0x00
// (vptr, m_moduleData +0x04, m_object +0x08 = 0x0C bytes), one-slot
// secondary bases BehaviorModuleInterface at +0x0C and UpdateModuleInterface
// at +0x10, UpdateModule's own m_nextCallFrameAndPhase +0x14,
// m_indexInLogic +0x18, m_pad +0x1C, and ProneUpdate's own m_proneFrames
// (Zero Hour's ProneUpdate.h) at +0x20, which retail zeroes.

class Thing;
class ModuleData;
class Object;

// upstream layout: GameLogic/Module/ObjectModule.h
class ObjectModule
{
public:
	ObjectModule(Thing *, const ModuleData *);
	virtual ~ObjectModule();

protected:
	void *m_moduleData;
	Object *m_object;
};

// upstream layout: GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void updateInterfaceAnchor();
};

// upstream layout: GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorInterfaceAnchor();
};

// upstream layout: GameLogic/Module/UpdateModule.h
class UpdateModule : public ObjectModule,
	public BehaviorModuleInterface,
	public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData)
		: ObjectModule(thing, moduleData),
		  m_nextCallFrameAndPhase(0), m_indexInLogic(-1), m_pad(-1)
	{
	}

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_pad;
};

// upstream layout: GameLogic/Module/ProneUpdate.h
class ProneUpdate : public UpdateModule
{
public:
	ProneUpdate(Thing *, const ModuleData *);

private:
	int m_proneFrames;
};

ProneUpdate::ProneUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	// Retail writes the trailing field AFTER its own most-derived vftable batch
	// and before the epilogue, which a plain store would sink past the batch;
	// the volatile lvalue is what keeps it in the middle.
	*(volatile int *)&m_proneFrames = 0;
}
