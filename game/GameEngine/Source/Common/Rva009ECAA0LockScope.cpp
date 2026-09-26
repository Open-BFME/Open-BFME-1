// cl: /O2
struct CRITICAL_SECTION;
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(CRITICAL_SECTION *);
class Rva009ECAA0LockScope {
public:
 explicit Rva009ECAA0LockScope(CRITICAL_SECTION *lock);
private:
 CRITICAL_SECTION *m_lock;
};
Rva009ECAA0LockScope::Rva009ECAA0LockScope(CRITICAL_SECTION *lock)
 : m_lock(lock)
{
 EnterCriticalSection(lock);
}
