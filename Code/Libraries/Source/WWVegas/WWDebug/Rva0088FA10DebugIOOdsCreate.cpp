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

class DebugIOOds : public DebugIOInterface
{
public:
    DebugIOOds(void) {}
    static DebugIOInterface *Create(void);
};

// ?Create@DebugIOOds@@SAPAVDebugIOInterface@@XZ
DebugIOInterface *DebugIOOds::Create(void)
{
    return new (DebugAllocMemory(sizeof(DebugIOOds))) DebugIOOds();
}
