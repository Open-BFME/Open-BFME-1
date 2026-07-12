// Lean stand-in for the WWLib mutex.h CriticalSectionClass (the reference also carries
// MutexClass/FastCriticalSectionClass; only CriticalSectionClass is needed here). The
// layout -- a void* handle and an unsigned locked -- is reproduced so objects that embed
// a CriticalSectionClass (e.g. SimpleFileFactoryClass::Mutex) match. Its ctor/dtor and
// the LockClass sentry ctor/dtor are ordinary out-of-line functions in the game, reached
// by masked REL32 call and resolved through reverse/symbols.csv.
#if defined(_MSC_VER)
#pragma once
#endif

#ifndef MUTEX_H
#define MUTEX_H

#include "always.h"
#include "thread.h"

class CriticalSectionClass
{
	void* handle;
	unsigned locked;

	// Lock and unlock are private so that you can't use them directly. Use LockClass as a sentry instead!
	void Lock();
	void Unlock();

public:
	CriticalSectionClass();
	~CriticalSectionClass();

	class LockClass
	{
		CriticalSectionClass& CriticalSection;
	public:
		// In order to lock a mutex create a local instance of LockClass with mutex as a parameter.
		LockClass(CriticalSectionClass& c);
		~LockClass();
	private:
		LockClass &operator=(const LockClass&) { return(*this); }
	};
	friend class LockClass;
};

// Verbatim reference MutexClass (incl. LockClass sentry): the stand-in above
// covers CriticalSectionClass only; zh TUs like mutex.cpp need the full class.

class MutexClass
{
	void* handle;
	unsigned locked;

	// Lock and unlock are private so that you can't use them directly. Use LockClass as a sentry instead!
	// Lock returns true if lock was succesful, false otherwise
	bool Lock(int time);
	void Unlock();

public:
	// Name can (and usually should) be NULL. Use name only if you wish to create a globally unique mutex
	MutexClass(const char* name = NULL);
	~MutexClass();

	enum {
		WAIT_INFINITE=-1
	};

	class LockClass
	{
		MutexClass& mutex;
		bool failed;
	public:

		// In order to lock a mutex create a local instance of LockClass with mutex as a parameter.
		// Time is in milliseconds, INFINITE means infinite wait.
		LockClass(MutexClass& m, int time=MutexClass::WAIT_INFINITE);
		~LockClass();

		// Returns true if the lock failed
		bool Failed() { return failed; }
	private:
		LockClass &operator=(const LockClass&) { return(*this); }
	};
	friend class LockClass;
};

// Verbatim reference FastCriticalSectionClass (inline-asm spinlock; needs thread.h).
// NOTE: wwstring.h carries a functionally-equivalent fastcall-spin model of the same
// class (its call sites byte-match retail only with that model); first include wins.
#ifndef BFME_FASTCRITICALSECTION_DEFINED
#define BFME_FASTCRITICALSECTION_DEFINED
class FastCriticalSectionClass
{
	unsigned Flag;

public:
	// Name can (and usually should) be NULL. Use name only if you wish to create a globally unique mutex
	FastCriticalSectionClass() : Flag(0) {}

	class LockClass
	{
		FastCriticalSectionClass& cs;
	public:
		__forceinline LockClass(FastCriticalSectionClass& critical_section) : cs(critical_section)
		{
		  unsigned& nFlag=cs.Flag;

		  #define ts_lock _emit 0xF0
		  assert(((unsigned)&nFlag % 4) == 0);

      // I'm terribly sorry for these emits in here but
      // VC won't inline any functions that have labels in them...

      // Had to remove the emits back to normal
      // ASM statements because sometimes the jump
      // would be 1 byte off....
      
		  __asm mov ebx, [nFlag]
		  __asm ts_lock
		  __asm bts dword ptr [ebx], 0
		  __asm jnc BitSet
      //__asm _emit 0x73
      //__asm _emit 0x0f

		  The_Bit_Was_Previously_Set_So_Try_Again:
		    ThreadClass::Switch_Thread();
		  __asm mov ebx, [nFlag]
		  __asm ts_lock
		  __asm bts dword ptr [ebx], 0
		  __asm jc  The_Bit_Was_Previously_Set_So_Try_Again
      //_asm _emit 0x72
      //_asm _emit 0xf1

      BitSet:
        ;
		}

		~LockClass()
		{
      cs.Flag=0;
		}
    
	private:
		LockClass &operator=(const LockClass&);
    LockClass(const LockClass&);
	};

  friend class LockClass;
};
#endif // BFME_FASTCRITICALSECTION_DEFINED

#endif // MUTEX_H
