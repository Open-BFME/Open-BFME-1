// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ??0ThreadClass@@: Code/Libraries/Source/WWVegas/WWLib/thread.cpp

///////////////////////////////////////////////////////////////////////////////
//
// ThreadClass::ThreadClass, retail 0x008B2EF0 (41 bytes).
//
// The pin is correct: the already-matched LoaderThreadClass constructor at
// 0x008B38D0 (textureloader.cpp) encodes a REL32 to exactly 0x008B2EF0 and
// then overwrites the vptr with its own 0x01136A40, which is what a derived
// constructor does.
//
// What thread.h cannot express is that BFME's ThreadClass is DERIVED.  Retail
// is, byte for byte:
//
//   mov  eax,[esp+4]              ; name
//   push esi ; push 8 ; push eax
//   mov  esi,ecx
//   call 0x00899F00               ; base(name, 8)
//   mov  ecx,[esp+0xc]            ; exception_handler
//   mov  dword ptr [esi],0x011369F0
//   mov  [esi+0x20],ecx
//   mov  dword ptr [esi+0x24],0
//   mov  eax,esi ; pop esi ; ret 8
//
// so the base subobject owns this+0x00..0x1F and ExceptionHandler lands at
// this+0x20, not at the +0x4C thread.h computes.  0x00899F00 (183 bytes, still
// a gen_asm dump) writes the vptr 0x01135D68, a packed bitfield at +4 whose
// low six bits are its first argument, pushes `this` into the fixed registry
// array at 0x01337810 unless that id is 0x0A or 0x1C -- the natural backing
// store for Get_Thread_By_Index -- then re-writes the vptr as 0x01136058 and
// constructs a 16-byte embedded object at +8..+0x18 with its second argument,
// finishing with a flags dword at +0x18 and a masked byte at +0x1C.  Exactly
// 0x20 bytes.
//
// The base's real name is NOT known.  It is 44-times-called and every caller
// is still an unconverted dump, and the retail image carries no RTTI, so it is
// spelled here with an address-derived placeholder rather than a guess (the
// tree already does this, e.g. Rva89A110DeletingDestructorThunk.cpp).  Only
// the offsets and the call are claimed.
//
// This is a LOCAL ABI-slice replica for the same reason
// ThreadClassSetPriorityMethodThunk.cpp is one: five matched classes derive
// from thread.h's ThreadClass and must not be disturbed.  That sibling thunk
// independently pins handle/thread_priority at +0x48/+0x4C, so the class runs
// to 0x50 and this body's +0x20/+0x24 sit comfortably inside it.
//
///////////////////////////////////////////////////////////////////////////////

struct _EXCEPTION_POINTERS;

// Unknown identity; named for its address.  ctor(id, kind) at 0x00899F00,
// subobject size 0x20 (vptr + 0x1C).
class Rva899F00Base
{
public:
	Rva899F00Base(const char *name, int kind);
	virtual ~Rva899F00Base();

private:
	char	_bfme_base_slice[0x1c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/thread.h
class ThreadClass : public Rva899F00Base
{
public:
	typedef int (*ExceptionHandlerType)(int exception_code, struct _EXCEPTION_POINTERS *e_info);

	ThreadClass(const char *name = 0, ExceptionHandlerType exception_handler = 0);
	virtual ~ThreadClass();

protected:
	virtual void Thread_Function() = 0;

	ExceptionHandlerType	ExceptionHandler;	// retail this+0x20
	unsigned					ThreadID;			// retail this+0x24
	char						_bfme_tail[0x28];	// this+0x28..0x4f (handle at +0x48)
};

// ??0ThreadClass@@QAE@PBDP6AHHPAU_EXCEPTION_POINTERS@@@Z@Z
ThreadClass::ThreadClass(const char *name, ExceptionHandlerType exception_handler) :
	Rva899F00Base(name, 8),
	ExceptionHandler(exception_handler),
	ThreadID(0)
{
}
