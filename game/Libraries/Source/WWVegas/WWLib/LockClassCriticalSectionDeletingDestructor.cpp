// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
//
// Open-BFME5: CriticalSectionClass::LockClass scalar-deleting destructor at
// retail 0x0063AB00 (30 bytes).  The matched LockClass constructor at
// 0x009DB4B0 and complete destructor at 0x009DB4D0 in mutex.cpp establish the
// nested class identity; this TU emits the compiler-owned deleting wrapper.

class CriticalSectionClass
{
public:
	class LockClass
	{
	public:
		~LockClass();
	};
};

void Force_CriticalSection_LockClass_Deleting_Destructor(
	CriticalSectionClass::LockClass *value)
{
	delete value;
}
