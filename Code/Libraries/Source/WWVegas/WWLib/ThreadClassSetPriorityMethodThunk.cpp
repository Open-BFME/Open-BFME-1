// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?Set_Priority@ThreadClass@@: Code/Libraries/Source/WWVegas/WWLib/thread.cpp

///////////////////////////////////////////////////////////////////////////////
//
// ThreadClass::Set_Priority, retail 0x009DB540 (25 bytes).
//
// thread.h (Code/Libraries/Source/WWVegas/WWLib/thread.h) computes `handle`
// and `thread_priority` at +0x50/+0x54. Retail reads them at +0x48/+0x4C --
// eight bytes earlier -- confirmed independently by two matched siblings:
//
//   ?Set_Priority@ThreadClass@@QAEXH@Z  (0x009DB540): mov [ecx+0x4c],eax ;
//       mov ecx,[ecx+0x48] ; test ecx,ecx ; je ... ; call SetThreadPriority
//   ?Is_Running@ThreadClass@@QAE_NXZ    (0x009DB590, matched as an ICF alias
//       of ?hasLiveHandle@BFMENetworkBackend@@QAE_NXZ): mov edx,[ecx+0x48] ;
//       test edx,edx ; setne al
//
// Both agree: handle lives at +0x48, thread_priority at +0x4C. This is
// landed here with a LOCAL minimal replica of the class layout, padded to
// the true offsets, rather than by editing thread.h -- five already-matched
// classes (BuddyThreadClass, PeerThreadClass, GameResultsThreadClass,
// PSThreadClass, LoaderThreadClass) derive from ThreadClass through that
// shared header and must not be disturbed by an unproven blanket shift.
//
// The drift is NOT known to be uniform across the whole class (see
// PeerThreadClearPlayerStats.cpp for two differently-signed offsets further
// into a derived class), so no correction is applied anywhere else here.
//
///////////////////////////////////////////////////////////////////////////////

#include <windows.h>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/thread.h
class ThreadClass
{
public:
	void Set_Priority(int priority);

private:
	char _bfme_pad_to_0x48[0x48];
	unsigned long handle;
	int thread_priority;
};

// ?Set_Priority@ThreadClass@@QAEXH@Z
void ThreadClass::Set_Priority(int priority)
{
	thread_priority = priority;
	if (handle) SetThreadPriority((HANDLE)handle, THREAD_PRIORITY_NORMAL + thread_priority);
}
