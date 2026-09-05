// cl: /DNDEBUG /MD /EHs-c-
// Twin of 0x00283330 (BannerCarrierUpdateRawCtor.cpp): same base chain
// (ObjectModule ctor via ILT 0x000170E4, shared with many ModuleFactory
// bodies) and the same +0x0C/+0x10 interface vtables (BehaviorModuleInterface
// / LargeGroupBonusIface2, 0x0109C9D0 / 0x0109CBA0), plus the same
// +0x18/+0x1C/+0x14 plain-base member layout. Only the own-class vtables at
// +0x00/+0x0C/+0x10 differ (0x010A6DD4 / 0x010A6D10 / 0x010A6D04).
// Address-derived — owning type is not recovered.

typedef int Int;

class Thing;
class ModuleData;

class ObjectModule
{
public:
	ObjectModule(Thing *thing, const ModuleData *moduleData);	// ILT 0x000170E4

	virtual void bfmeModuleSlot(void) = 0;

private:
	char m_bfmeTail[0x0C - 0x04];
};

class BfmeBannerInterface
{
public:
	virtual void bfmeInterfaceSlot(void) = 0;
};

class BfmeBannerCarrierInterface
{
public:
	virtual void bfmeCarrierSlot(void) = 0;
};

class BfmeBannerCarrierState
{
public:
	BfmeBannerCarrierState()
	{
		m_bfme0018 = -1;
		m_bfme001C = -1;
		m_bfme0014 = 0;
	}

	Int m_bfme0014;							// +0x14
	Int m_bfme0018;							// +0x18
	Int m_bfme001C;							// +0x1C
};

class Rva0020CC70Update : public ObjectModule,
			  public BfmeBannerInterface,
			  public BfmeBannerCarrierInterface,
			  public BfmeBannerCarrierState
{
public:
	Rva0020CC70Update(Thing *thing, const ModuleData *moduleData);

	virtual void bfmeModuleSlot(void) { }
	virtual void bfmeInterfaceSlot(void) { }
	virtual void bfmeCarrierSlot(void) { }
};

// ??0Rva0020CC70Update@@QAE@PAVThing@@PBVModuleData@@@Z
Rva0020CC70Update::Rva0020CC70Update(Thing *thing, const ModuleData *moduleData)
	: ObjectModule(thing, moduleData)
{
}
