// cl: /O2 /MD
struct RvaEmptyAlloc { RvaEmptyAlloc() {} };
class RvaList
{
public:
    unsigned char m_storage[0xC];
};
namespace _STL { template<class T> class allocator; template<class T, class A> class list; }
class QueuedDownload;
extern _STL::list<QueuedDownload, _STL::allocator<QueuedDownload> > queuedDownloads;
extern void j_00049c4c();
void bfmeForward_00C708D0();
struct Rva00C6C3F0Caller
{
    Rva00C6C3F0Caller()
    {
        typedef void (RvaList::*Member)(const RvaEmptyAlloc &);
        union { void (*function)(); Member method; } call;
        call.function = j_00049c4c;
        ((*reinterpret_cast<RvaList *>(&queuedDownloads)).*call.method)(RvaEmptyAlloc());
        atexit(bfmeForward_00C708D0);
    }
};
struct Rva00C6C3F0Global
{
    Rva00C6C3F0Caller m_caller;
    unsigned char m_pad[0xB];
};
Rva00C6C3F0Global g_rva012F7180Global;
