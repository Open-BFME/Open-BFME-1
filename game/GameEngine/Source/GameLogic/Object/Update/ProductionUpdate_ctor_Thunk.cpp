// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: ProductionUpdate constructor.  The module factory, matched
// destructor, and original ProductionUpdate.cpp body establish its identity.

#include <list>
#include <string.h>

class Thing;
class ModuleData;

class ObjectModule
{
public:
	ObjectModule(Thing *, const ModuleData *);
	virtual ~ObjectModule();
private:
	const ModuleData *m_moduleData;
	void *m_object;
};

class BehaviorModuleInterface
{
public: virtual void behaviorSlot();
};

class UpdateModuleInterface
{
public: virtual void updateSlot();
};

class UpdateModule : public ObjectModule,
	public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *data)
		: ObjectModule(thing, data), m_nextCallFrameAndPhase(0),
		  m_indexInLogic(-1), m_updateState(-1) {}
	virtual ~UpdateModule();
private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class ProductionUpdateInterface
{
public: virtual void productionSlot();
};

class DieModuleInterface
{
public: virtual void dieSlot();
};

struct DoorInfo
{
	DoorInfo()
		: m_doorOpenedFrame(0), m_doorWaitOpenFrame(0),
		  m_doorClosedFrame(0), m_holdOpen(false) {}
	unsigned int m_doorOpenedFrame;
	unsigned int m_doorWaitOpenFrame;
	unsigned int m_doorClosedFrame;
	bool m_holdOpen;
	unsigned char m_pad[3];
};

struct ModelConditionFlags
{
	ModelConditionFlags() { clear(); }
	void clear()
	{
		memset(m_bits, 0, sizeof(m_bits));
	}
	unsigned int m_bits[10];
};

class ProductionUpdate : public UpdateModule,
	public ProductionUpdateInterface, public DieModuleInterface
{
public:
	ProductionUpdate(Thing *, const ModuleData *);
	virtual ~ProductionUpdate();
	virtual void productionSlot();
	virtual void dieSlot();
private:
	void *m_productionQueue;
	void *m_productionQueueTail;
	unsigned int m_uniqueID;
	unsigned int m_productionCount;
	unsigned int m_constructionCompleteFrame;
	DoorInfo m_doors[4];
	ModelConditionFlags m_clearFlags;
	ModelConditionFlags m_setFlags;
	bool m_flagsDirty;
	unsigned char m_padcd[3];
	void *m_specialPowerConstructionCommandButton;
	bool m_flagd4;
	bool m_flagd5;
	unsigned char m_padd6[2];
	void *m_valueD8;
	_STL::list<int> m_list;
	unsigned int m_listCount;
	unsigned int m_valueE4;
};

// ??0ProductionUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
ProductionUpdate::ProductionUpdate(Thing *thing, const ModuleData *data)
	: UpdateModule(thing, data),
	  m_productionQueue(0), m_productionQueueTail(0), m_uniqueID(1),
	  m_productionCount(0), m_constructionCompleteFrame(0),
	  m_flagsDirty(false), m_specialPowerConstructionCommandButton(0),
	  m_flagd4(false), m_flagd5(false), m_valueD8(0), m_listCount(0),
	  m_valueE4(1)
{
	for (int i = 0; i != 4; ++i)
	{
		m_doors[i].m_doorOpenedFrame = 0;
		m_doors[i].m_doorWaitOpenFrame = 0;
		m_doors[i].m_doorClosedFrame = 0;
		m_doors[i].m_holdOpen = false;
	}
}
