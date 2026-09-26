// cl: /DNDEBUG /MD /EHsc
// NetCommandList scalar deleting destructor, RVA 0x00673550 (36 bytes).
// The matched constructor at 0x00672EA0 installs vtable VA 0x0111A470.
// Its first entry is VA 0x00408495, an ILT jump to this body, which restores
// that same vtable and calls reset through ILT 0x0000B9CE -> 0x006731A0.
// BFME has no MemoryPoolObject base here: the reference header would emit
// a base destructor and a different allocation/deletion path.
//
// Former claims at 0x001DDFD0 and 0x001DE080 belong to a different list:
// its destructor installs VA 0x0109FB9C and calls clear at 0x001DDD60.
// The ordinary NetCommandList destructor is inlined into the deleting
// destructor; no distinct out-of-line address is claimed.
class NetCommandList
{
public:
    void reset();
protected:
    virtual ~NetCommandList();
private:
    void *m_first;
    void *m_last;
    void *m_lastMessageInserted;
};
// ??1NetCommandList@@MAE@XZ present-unmatched
NetCommandList::~NetCommandList()
{
    reset();
}
