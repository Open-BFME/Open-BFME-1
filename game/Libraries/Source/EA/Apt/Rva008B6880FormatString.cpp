// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008B6880: opaque receiver identity, hub 008985C0+437 and ret4+280.
// Fields and inline tables witnessed in docs/analysis/0x008985c0.md.
struct BfmeStringData3AF0 { unsigned short m_refCount, m_length, m_capacity, m_unknown06; };
struct BfmeStringPool3AF0 { void *m_unknown00; void (__cdecl *free)(void *); };
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;
extern "C" int __cdecl sprintf(char *, const char *, ...);
extern "C" int __cdecl abs(int);
#pragma intrinsic(abs)
class BfmeStrVKI {
public:
    BfmeStrVKI(const char *s) { bfmeSetVKI(s); }
    void __declspec(nothrow) bfmeSetVKI(const char *s);
    __forceinline ~BfmeStrVKI() {
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0) g_bfmeStringPool1284->free(old);
    }
    BfmeStringData3AF0 *m_data;
};
class Rva8CD130String {
public:
    __forceinline Rva8CD130String &operator=(const BfmeStrVKI &s) {
        ++s.m_data->m_refCount;
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0) g_bfmeStringPool1284->free(old);
        m_data = s.m_data;
        return *this;
    }
    Rva8CD130String &rva0089EA60Append(const char *text);
    BfmeStringData3AF0 *m_data;
};
class Rva008B6880 {
public:
    void invoke(Rva8CD130String *output);
    int rva008B66B0(int, int, int);
    unsigned char m_unknown00[0x20];
    int m_unknown20, m_unknown24, m_unknown28, m_unknown2C;
    int m_unknown30, m_unknown34, m_unknown38;
    unsigned char m_unknown3C[0x24];
    int m_unknown60;
};
void Rva008B6880::invoke(Rva8CD130String *output) {
    char weekdays[7][4] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
    char months[12][4] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jly", "Aug", "Sep", "Oct", "Nov", "Dec" };
    char buffer[4];
    *output = BfmeStrVKI(weekdays[rva008B66B0(m_unknown38, m_unknown34, m_unknown30)]);
    output->rva0089EA60Append(" ");
    output->rva0089EA60Append(months[m_unknown34]);
    output->rva0089EA60Append(" ");
    sprintf(buffer, "%d", m_unknown30);
    output->rva0089EA60Append(buffer);
    output->rva0089EA60Append(" ");
    sprintf(buffer, "%02d", m_unknown28);
    output->rva0089EA60Append(buffer);
    output->rva0089EA60Append(":");
    sprintf(buffer, "%02d", m_unknown24);
    output->rva0089EA60Append(buffer);
    output->rva0089EA60Append(":");
    sprintf(buffer, "%02d", m_unknown20);
    output->rva0089EA60Append(buffer);
    output->rva0089EA60Append(" GMT");
    output->rva0089EA60Append(m_unknown60 < 0 ? "-" : "+");
    sprintf(buffer, "%02d", abs(m_unknown60));
    output->rva0089EA60Append(buffer);
    output->rva0089EA60Append("00 ");
    sprintf(buffer, "%d", m_unknown38);
    output->rva0089EA60Append(buffer);
}
