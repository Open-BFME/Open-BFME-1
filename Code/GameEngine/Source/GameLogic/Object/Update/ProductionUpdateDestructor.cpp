// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// The retail ProductionUpdate destructor uses the BFME-era multiple-inheritance
// layout.  Keep that recovered layout in the proper source area rather than
// changing the shared reference headers or retaining a generic destructor TU.

#include <list>

class Gen_dtor_00113d40
{
public:
	virtual ~Gen_dtor_00113d40();

private:
	const void *m_moduleData;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void getBehaviorModuleInterface() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void updateModuleInterface() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule : public Gen_dtor_00113d40
{
private:
	void *m_object;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule() {}

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	unsigned int m_updateState;
};

template <int Number>
class ProductionUpdateSecondaryBase
{
public:
	virtual void slot();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ProductionUpdate.h
class ProductionEntry
{
public:
	virtual void *scalarDeletingDestructor(unsigned int flags);
};

class ProductionUpdateOwner
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0c(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1c(); virtual void slot20();
	virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual void slot30(); virtual void slot34(); virtual void slot38();
	virtual void slot3c(); virtual void slot40(); virtual void slot44();
	virtual void slot48();
	virtual void slot4c(void *arg);
};

extern ProductionUpdateOwner *TheProductionUpdateOwner;

class ProductionUpdate
	: public UpdateModule,
	  public ProductionUpdateSecondaryBase<1>,
	  public ProductionUpdateSecondaryBase<2>
{
public:
	virtual ~ProductionUpdate();

private:
	void removeEntry(ProductionEntry *entry);

	ProductionEntry *m_productionQueue;
	unsigned char m_unreconstructed_2c[0xb0];
	_STL::list<int> m_list;
	unsigned char m_unreconstructed_e0[4];
	void *m_unreconstructed_e4;
};

// ??1ProductionUpdate@@UAE@XZ
ProductionUpdate::~ProductionUpdate()
{
	while (m_productionQueue)
	{
		ProductionEntry *entry = m_productionQueue;
		removeEntry(entry);
		if (entry)
		{
			entry->scalarDeletingDestructor(1);
		}
	}

	if (TheProductionUpdateOwner)
	{
		TheProductionUpdateOwner->slot4c(m_unreconstructed_e4);
	}
}
