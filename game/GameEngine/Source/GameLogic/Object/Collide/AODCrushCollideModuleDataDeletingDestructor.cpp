// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: public scalar-deleting destructor for AODCrushCollideModuleData.
// The exact constructor at 0x00215B90 installs dedicated vtable 0x010A9740;
// slot zero routes through ILT 0x0003F8F0 to this 30-byte wrapper, whose
// complete destructor is reached through ILT 0x0000FC31.

// The scalar-deleting destructor (??_G, matched 30B row) must call the rowed
// complete destructor ??1Rva00215DF0 (0x00215DF0, defined in
// BigTwoMemberDtors.cpp) rather than an AODCrushCollideModuleData complete
// destructor nothing defines. An explicit empty derived destructor inlines
// into the generated ??_G wrapper, leaving the direct base call.
class Rva00215DF0
{
public:
	~Rva00215DF0();
};

class AODCrushCollideModuleData : public Rva00215DF0
{
public:
	virtual ~AODCrushCollideModuleData();
};

// ??1AODCrushCollideModuleData@@UAE@XZ present-unmatched
AODCrushCollideModuleData::~AODCrushCollideModuleData()
{
}

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceAODCrushCollideModuleDataDeletingDestructor(const AODCrushCollideModuleData &that)
{
	AODCrushCollideModuleData value(that);
}
