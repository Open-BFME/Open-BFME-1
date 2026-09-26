// cl: /DNDEBUG /MD /GX
#include <string.h>
#include <process.h>

extern "C" __declspec(dllimport) int __stdcall SetThreadPriority(void *, int);
extern "C" __declspec(dllimport) unsigned long __stdcall ResumeThread(void *);
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *, unsigned long);
extern "C" unsigned int __stdcall BFMENetworkBackendThreadStart(void *);

class ThreadClass
{
public:
    ThreadClass(const char *name);
    virtual ~ThreadClass();
    virtual void Execute();
    void Set_Priority(int priority);
    __declspec(noinline) bool Is_Running();
    __declspec(noinline) void Stop();

protected:
    virtual void Thread_Function() = 0;

private:
    char m_name[0x40];
    unsigned int m_threadId;
    void *m_handle;
    int m_priority;
};

ThreadClass::ThreadClass(const char *name)
{
    m_handle = 0;
    m_priority = 0;
    m_threadId = 0;
    if (name)
        strcpy(m_name, name);
    else
        memcpy(m_name, "No name", 8);
}

void ThreadClass::Set_Priority(int priority)
{
    m_priority = priority;
    if (m_handle)
        SetThreadPriority(m_handle, m_priority);
}

ThreadClass::~ThreadClass()
{
}

bool ThreadClass::Is_Running()
{
    return m_handle != 0;
}

void ThreadClass::Stop()
{
    if (m_handle) {
        WaitForSingleObject(m_handle, 0xffffffff);
        m_handle = 0;
        m_threadId = 0;
    }
}

void ThreadClass::Execute()
{
    m_handle = reinterpret_cast<void *>(_beginthreadex(0, 0,
        BFMENetworkBackendThreadStart, this, 4, &m_threadId));
    SetThreadPriority(m_handle, m_priority);
    ResumeThread(m_handle);
}
