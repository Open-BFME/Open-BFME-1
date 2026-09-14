// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: FloatingTextData scalar-deleting destructor at retail RVA
// 0x00442290 (30 bytes).  The matched constructor at 0x0043F4D0 and complete
// virtual destructor at 0x0043F550 establish the same InGameUI floating-text
// class; direct newInstance(FloatingTextData) callers in InGameUI provide an
// independent ownership/vtable witness.  This replaces the generated wrapper
// without changing the already matched complete destructor.

class FloatingTextData
{
public:
	virtual ~FloatingTextData();
};

// Retail calls ILT 0x0001661C, which reaches FloatingTextData::~FloatingTextData
// at 0x0043F550, then invokes the scalar operator delete.
#pragma comment(linker, "/alternatename:??1FloatingTextData@@UAE@XZ=?j_0001661c@@YAXXZ")

void forceFloatingTextDataDeletingDestructor()
{
	FloatingTextData value;
}
