// cl: /DNDEBUG /MD /EHsc
// NetCommandMsg::detach at RVA 0x00673610, full 27-byte retail body.
// The former 16-byte naked claim ended at the first ret, but JNE at 0x00673617
// reaches 0x00673620: negative reference counts also destroy the message.
// That second path ends at ret 0x0067362A, as does the Ghidra 27-byte boundary.
// The old prefix byte proof therefore omitted a live branch and falsely called
// the straightforward reference C++ a codegen blocker.
//
// The GeneralsMD body preserves both zero and negative-count deletion paths.
// BFME's de-pooled command has its count at +0x18 and uses the virtual deleting
// destructor directly. This local view avoids the reference header's pool base.
class NetCommandMsg {
public:
    virtual ~NetCommandMsg();
    void detach();
private:
    char m_unrecovered04[0x14];
    int m_referenceCount;
};
void NetCommandMsg::detach()
{
    --m_referenceCount;
    if (m_referenceCount == 0) {
        delete this;
        return;
    }
    if (m_referenceCount < 0)
        delete this;
}
