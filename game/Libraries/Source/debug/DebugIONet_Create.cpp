// cl: /DNDEBUG /MD /EHa /Oy-

// The inline placement operator new/delete in <new> are emitted as COMDATs; they
// must be frameless like every other TU's copy (retail has no address for them),
// so /Oy- is lifted only while the header is compiled.
#pragma optimize("y", on)
#include <new>
#pragma optimize("y", off)

extern void *DebugAllocMemory(unsigned size);

class DebugIOInterface
{
protected:
    virtual ~DebugIOInterface(void) {}

public:
    DebugIOInterface(void) {}
};

class DebugIONet : public DebugIOInterface
{
public:
    DebugIONet(void) {}
    static DebugIOInterface *Create(void);

private:
    void *m_pipe;
};

// ?Create@DebugIONet@@SAPAVDebugIOInterface@@XZ
DebugIOInterface *DebugIONet::Create(void)
{
    return new (DebugAllocMemory(sizeof(DebugIONet))) DebugIONet();
}
