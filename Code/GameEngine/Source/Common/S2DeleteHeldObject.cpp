// Four bodies built out of one statement -- `delete <pointer>` -- in the two
// shapes MSVC 7.1 gives it when the deleted type has a NON-virtual destructor:
//
//   as a member (three rows)     push esi / mov esi,[ecx]
//   as a free function (one)   push esi / mov esi,[esp+8]
//
//   then, both:  test esi,esi / je end / mov ecx,esi / call <DTOR>
//                push esi / call ??3@YAXPAX@Z / add esp,4 / end: pop esi / ret
//
// WHAT THE BYTES SHOW.  The destructor is reached by a direct REL32 call, not
// through the object's vtable, so `delete` here is NOT deleting through a
// virtual destructor -- the static type's destructor is called outright.  The
// operator delete is 0x00881EB0, already pinned as ??3@YAXPAX@Z.  In the member
// form the pointer comes from +0 of `this`, and in the free form from the one
// __cdecl argument; nothing is stored back, so no slot is cleared afterwards.
//
// THE FIRST ROW DELETES ITS OWN TYPE.  0x003500C0's REL32 resolves through the
// thunk at 0x00002A7C to 0x003500C0 itself, so it is a destructor that deletes
// the next link of a list of its own kind.  That is why it is written here as a
// real destructor rather than a void member: the recursion has to name itself.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived.  The free-form row
// takes one pointer and is typed __cdecl because the caller pops nothing
// here and the argument sits at [esp+4] on entry.

class Rva003500C0
{
public:
	~Rva003500C0();
	Rva003500C0 *m_next;
};

// @??1Rva003500C0@@QAE@XZ 0x003500C0
Rva003500C0::~Rva003500C0()
{
	delete m_next;
}

#define BFME_DELETE_MEMBER( NAME, CALLEE )                                \
	class CALLEE                                                          \
	{                                                                     \
	public:                                                               \
		~CALLEE();                                                        \
	};                                                                    \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		~NAME();                                                          \
		CALLEE *m_held;                                                   \
	};                                                                    \
	NAME::~NAME()                                                         \
	{                                                                     \
		delete m_held;                                                    \
	}

#define BFME_DELETE_ARGUMENT( NAME, CALLEE )                              \
	class CALLEE                                                          \
	{                                                                     \
	public:                                                               \
		~CALLEE();                                                        \
	};                                                                    \
	void NAME( CALLEE *held )                                             \
	{                                                                     \
		delete held;                                                      \
	}

// @??1Rva00590790@@QAE@XZ 0x00590790
BFME_DELETE_MEMBER( Rva00590790, Gen0003FA7B )
// @??1Rva0063B130@@QAE@XZ 0x0063B130
BFME_DELETE_MEMBER( Rva0063B130, Gen009DB4D0 )

// @?Rva007889D0@@YAXPAVGen0002AB5D@@@Z 0x007889D0
BFME_DELETE_ARGUMENT( Rva007889D0, Gen0002AB5D )
