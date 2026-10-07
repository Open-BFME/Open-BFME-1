// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// stlport
// Native unsigned-key lookup; address-derived name is pinned by the matched
// caller at 0x009EC0D0. See identity_evidence/009eedf0-key-lookup.md.
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include <windows.h>

class Rva009EEDF0LockGuard
{
public:
	explicit Rva009EEDF0LockGuard(int lock) : m_lock(lock)
	{
		EnterCriticalSection((CRITICAL_SECTION *)m_lock);
	}
	~Rva009EEDF0LockGuard()
	{
		LeaveCriticalSection((CRITICAL_SECTION *)m_lock);
	}

	int m_lock;
};

// Slot 0 is called with only ECX and returns the registry entry name.
class Rva009EEDF0Value { public: virtual const char* rvaSlot0(); };
class AssetManagerImpl {
public:
 const char* GetString(unsigned int key);
 char m_at00[0x2c]; CRITICAL_SECTION m_at2c;
 _STL::hash_map<unsigned int,Rva009EEDF0Value*> m_at44;
};
const char* AssetManagerImpl::GetString(unsigned int key) {
 Rva009EEDF0LockGuard lock((int)&m_at2c);
 _STL::hash_map<unsigned int,Rva009EEDF0Value*>::iterator i=m_at44.find(key);
 if(i==m_at44.end())return "<unknown>";
 return i->second->rvaSlot0();
}
