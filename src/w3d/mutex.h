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

#endif // MUTEX_H
