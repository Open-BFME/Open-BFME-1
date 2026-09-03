// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: recover the retail vertex-buffer lock destructor as clean C++.

extern void DX8_Assert();
extern void BFME_DX8_Thread_Assert();
extern void _bfme_debugRecordCallsite(int kind);

class BFMEIndexBufferDebugStream
{
public:
    virtual BFMEIndexBufferDebugStream *Put_Unsigned(unsigned value);
    virtual void Slot04(); virtual void Slot08(); virtual void Slot0C();
    virtual void Slot10(); virtual void Slot14(); virtual void Slot18(); virtual void Slot1C();
    virtual void Slot20(); virtual void Slot24(); virtual void Slot28(); virtual void Slot2C();
    virtual void Slot30(); virtual void Slot34();
    virtual BFMEIndexBufferDebugStream *Put_String(const char *text);
    virtual void Slot3C(); virtual void Slot40(); virtual void Slot44(); virtual void Slot48();
    virtual BFMEIndexBufferDebugStream *Finish(int report);
};

class BFMEIndexBufferDebugClass
{
public:
    virtual void Slot00(); virtual void Slot04(); virtual void Slot08(); virtual void Slot0C();
    virtual void Slot10(); virtual void Slot14(); virtual void Slot18(); virtual void Slot1C();
    virtual void Slot20(); virtual void Slot24(); virtual void Slot28(); virtual void Slot2C();
    virtual void Slot30(); virtual void Slot34(); virtual void Slot38(); virtual void Slot3C();
    virtual void Slot40(); virtual void Slot44(); virtual void Slot48(); virtual void Slot4C();
    virtual void Slot50(); virtual void Slot54(); virtual void Slot58(); virtual void Slot5C();
    virtual void Begin_Report();
    virtual void Slot64(); virtual void Slot68();
    virtual BFMEIndexBufferDebugStream *Get_Stream(void *owner, void *context);
};

extern BFMEIndexBufferDebugClass *g_BFMEIndexBufferDebug;

static __forceinline void BFME_DX8_ErrorCode(unsigned result)
{
    if (result != 0) {
        _bfme_debugRecordCallsite(1);
        g_BFMEIndexBufferDebug->Begin_Report();
        BFMEIndexBufferDebugStream *stream =
            g_BFMEIndexBufferDebug->Get_Stream(0, 0);
        stream->Put_String("DX8 error ")->Put_Unsigned(result)->Finish(1);
    }
}

class BFMEVertexBufferDevice
{
public:
    void **vtable;
};

typedef int (__stdcall *BFMEVertexBufferUnlock)(BFMEVertexBufferDevice *device);

class __declspec(novtable) VertexBufferClass
{
public:
    virtual void Delete_This();

    int Type() const
    {
        return *(const int *)((const unsigned char *)this + 8);
    }

    void Release_Ref()
    {
        int refs = --*(int *)((unsigned char *)this + 4);
        if (refs == 0) {
            Delete_This();
        }
    }

    class __declspec(novtable) WriteLockClass
    {
    public:
        ~WriteLockClass();

        VertexBufferClass *VertexBuffer;
        void *Vertices;
    };
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8vertexbuffer.h
class DX8VertexBufferClass : public VertexBufferClass
{
public:
    BFMEVertexBufferDevice *Get_DX8_Vertex_Buffer() const
    {
        return *(BFMEVertexBufferDevice *const *)((const unsigned char *)this + 0x1c);
    }
};

// ??1WriteLockClass@VertexBufferClass@@QAE@XZ
VertexBufferClass::WriteLockClass::~WriteLockClass()
{
    if (VertexBuffer->Type() == 0) {
        DX8_Assert();
        BFMEVertexBufferDevice *device = static_cast<DX8VertexBufferClass *>(VertexBuffer)
            ->Get_DX8_Vertex_Buffer();
        unsigned result = reinterpret_cast<BFMEVertexBufferUnlock>(device->vtable[12])(device);
        BFME_DX8_ErrorCode(result);
    }
    VertexBuffer->Release_Ref();
    BFME_DX8_Thread_Assert();
}
