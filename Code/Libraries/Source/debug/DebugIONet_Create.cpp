// cl: /DNDEBUG /MD /EHa /Oy-

#include <new>

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
