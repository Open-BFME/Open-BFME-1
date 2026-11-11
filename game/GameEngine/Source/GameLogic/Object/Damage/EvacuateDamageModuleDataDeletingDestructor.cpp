// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: public scalar-deleting destructor for EvacuateDamageModuleData.
// The exact constructor at 0x00250C20 installs dedicated vtable 0x010B2018;
// slot zero routes through ILT 0x000076A8 to this 30-byte wrapper, whose
// complete destructor is reached through ILT 0x00004BD8.

// The scalar-deleting destructor (??_G, matched 30B row) must call the rowed
// complete destructor ??1Rva00250DF0 (0x00250DF0, defined in
// BigTwoMemberDtors.cpp) rather than an EvacuateDamageModuleData complete
// destructor nothing defines. An explicit empty derived destructor inlines
// into the generated ??_G wrapper, leaving the direct base call.
class Rva00250DF0
{
public:
	~Rva00250DF0();
};

class EvacuateDamageModuleData : public Rva00250DF0
{
public:
	virtual ~EvacuateDamageModuleData();
};

// ??1EvacuateDamageModuleData@@UAE@XZ present-unmatched
EvacuateDamageModuleData::~EvacuateDamageModuleData()
{
}

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceEvacuateDamageModuleDataDeletingDestructor(const EvacuateDamageModuleData &that)
{
	EvacuateDamageModuleData value(that);
}
