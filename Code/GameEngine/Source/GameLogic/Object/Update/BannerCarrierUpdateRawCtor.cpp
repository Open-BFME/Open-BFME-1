// cl: /DNDEBUG /MD /EHs-c-

// Retail 0x00283330, 76 bytes. reverse/reloc_names.csv names it
// ??0BannerCarrierUpdate@@QAE@PAVThing@@PBVModuleData@@@Z with identity=real,
// but that name is already on the 164-byte body at 0x00285F10, so this row
// goes in as dup_00283330 with the object symbol in its notes.
//
// The store order fixes the whole shape. A constructor runs its base
// constructors, then stores its own vftable pointers, then its member
// initialisers -- so everything before the three stores at the end belongs to
// a base:
//
//   call ILT 0x000170E4        first base, taking thing and moduleData
//   [+0x0C] = vftable          a bare interface base
//   [+0x10] = vftable          a second one
//   [+0x18] = -1               a fourth base, this one with no vftable of its
//   [+0x1C] = -1               own, assigning in body order rather than
//   [+0x14] = 0                declaration order
//   [+0x00] = vftable          this class overriding all three
//   [+0x0C] = vftable
//   [+0x10] = vftable
//
// The split matters: with the three words folded into a base that carries the
// interfaces, the compiler sinks one of the vftable stores below them and
// elides the other, because nothing separates it from the overwrite at the
// end. Giving the words their own plain base keeps both stores where retail
// has them.
//
// All the vftable addresses ride DIR32 relocations copied from retail.

typedef int Int;

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
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

class BannerCarrierUpdate : public ObjectModule,
			    public BfmeBannerInterface,
			    public BfmeBannerCarrierInterface,
			    public BfmeBannerCarrierState
{
public:
	BannerCarrierUpdate(Thing *thing, const ModuleData *moduleData);

	virtual void bfmeModuleSlot(void) { }
	virtual void bfmeInterfaceSlot(void) { }
	virtual void bfmeCarrierSlot(void) { }
};

// ??0BannerCarrierUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
BannerCarrierUpdate::BannerCarrierUpdate(Thing *thing, const ModuleData *moduleData)
	: ObjectModule(thing, moduleData)
{
}
