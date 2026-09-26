// cl: /DNDEBUG /MD /GX
// The global at VA 0x012F9808 is constructed at 0x00C6C4F0 and registered
// with the 0x00C709C0 exit callback, which reaches this destructor. Matched
// W3DMouse methods use the same polling thread and its Thread_Function slot.

class ThreadClass
{
public:
    virtual ~ThreadClass();
    virtual void Execute();
    void Stop();

protected:
    virtual void Thread_Function() = 0;

private:
    // The base constructor initializes storage through offset +0x4F.
    unsigned char m_threadStorage[0x4c];
};

class MouseThreadClass : public ThreadClass
{
public:
    virtual ~MouseThreadClass();
    virtual void Thread_Function();
};

MouseThreadClass::~MouseThreadClass()
{
    Stop();
}
