// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: AutoPickUpUpdateModuleData dtor. dual members, SEH.
//
// Retail 0x00282A80 destroys +0x30 first and +0x2c second, then re-seats the
// base vptr, so the module data is 0x2c bytes of base, a four-byte member at
// +0x2c and a twelve-byte STLport container at +0x30 (reverse declaration
// order).  Both leaf calls go through incremental-link thunks:
//
//   0x0001A401 -> jmp 0x0039D550 = ??1AttributeHandleStandIn@@QAE@XZ
//     (AttributeHandleStandInDestructor.cpp, the ledger owner of that body)
//   0x00045016 -> jmp 0x00282690 =
//     ??1?$vector@UGen_t_00282690_p12cd@@V?$allocator@UGen_t_00282690_p12cd@@@_STL@@
//     @_STL@@QAE@XZ
//
// The +0x2c member is therefore spelled with its defining name, which is what
// makes that reference resolve.
//
// STILL BLOCKING THE LINK: the +0x30 member.  The only definition of its
// destructor is the gen-tgrid placeholder instantiation in
// game/gen_small/tgrid_109.cpp, and naming the type here to reach it would
// make this TU emit a second copy of the whole STLport vector teardown
// (??1?$_Vector_base, ??$__destroy, ??$__destroy_aux, ??$_Destroy), whose bytes
// the link census rejects as non-retail COMDAT copies.  That body has to be
// recovered in clean C++ under a real name first.

class AttributeHandleStandIn
{
public:
	~AttributeHandleStandIn();
private:
	unsigned char m_pad[4];
};

// The twelve-byte container retail destroys at +0x30.  Its destructor identity
// is not recovered yet; see the note above.
class AutoPickUpUpdateModuleDataMemberB
{
public:
	~AutoPickUpUpdateModuleDataMemberB();
private:
	unsigned char m_pad[12];
};

class AutoPickUpUpdateModuleDataBase
{
public:
	virtual ~AutoPickUpUpdateModuleDataBase() {}
private:
	unsigned char m_pad[0x28];
};

class __declspec(novtable) AutoPickUpUpdateModuleData : public AutoPickUpUpdateModuleDataBase
{
public:
	virtual ~AutoPickUpUpdateModuleData();
private:
	AttributeHandleStandIn m_a;
	AutoPickUpUpdateModuleDataMemberB m_b;
};

// ??1AutoPickUpUpdateModuleData@@UAE@XZ
AutoPickUpUpdateModuleData::~AutoPickUpUpdateModuleData()
{
}