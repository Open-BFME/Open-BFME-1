// cl: /DNDEBUG /MD /EHs-
// Open-BFME5: lift Debug::WriteBuildInfo __emit thunk to clean C++. Retail
// starts two bytes before the old ledger anchor (push esi/push edi at
// 0x0088A490): writes "Version:", then " "+m_str1 and " internal "+m_str2
// when those buffers are non-empty, then " release", then " build "+m_str3
// when non-empty -- all through the chained virtual writer at vtable slot
// 0x38. /EHs- because retail has no unwind frame.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/debug_debug.h
class Debug
{
public:
    virtual void vslot00();
    virtual void vslot01();
    virtual void vslot02();
    virtual void vslot03();
    virtual void vslot04();
    virtual void vslot05();
    virtual void vslot06();
    virtual void vslot07();
    virtual void vslot08();
    virtual void vslot09();
    virtual void vslot10();
    virtual void vslot11();
    virtual void vslot12();
    virtual void vslot13();
    virtual Debug *writeStr(const char *);

    void WriteBuildInfo();

private:
    unsigned char m_pad[0x9E80];
    char m_str1[0x40];
    char m_str2[0x40];
    char m_str3[0x40];
};

// ?WriteBuildInfo@Debug@@QAEXXZ
void Debug::WriteBuildInfo()
{
    writeStr("Version:");
    if (m_str1[0]) {
        writeStr(" ")->writeStr(m_str1);
    }
    if (m_str2[0]) {
        writeStr(" internal ")->writeStr(m_str2);
    }
    writeStr(" release");
    if (m_str3[0]) {
        writeStr(" build ")->writeStr(m_str3);
    }
}
