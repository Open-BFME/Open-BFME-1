// cl: /DNDEBUG /MD /EHsc
// The handle-from-plain constructor at 0x00785140 installs VA 0x01126AB8
// and increments its target's WORD count at +4. That vtable's slot 0 reaches
// 0x007851A0 through ILT 0x00017DAA; it calls the destructor at 0x007851D0.
// This is a counted resource handle, not NetCommandRef: it releases through
// 0x009EB7A0 and restores base vtable VA 0x01126A80. Real BFME network refs
// have no vptr and use the 12-byte destructor at 0x00676280.
// The owning class remains address-named, consistent with its proven ctor.
class CountedAsset { public: void Release_Ref(); };
class Rva00782CB0
{
public:
    virtual ~Rva00782CB0() {}
};
class Rva00785140Handle : public Rva00782CB0
{
public:
    virtual ~Rva00785140Handle();
private:
    CountedAsset *m_target;
};
Rva00785140Handle::~Rva00785140Handle()
{
    if (m_target)
        m_target->Release_Ref();
}
