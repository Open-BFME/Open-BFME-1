// cl: /DNDEBUG /MD /EHsc
// RVA 0x008B4260: compare two payload pointers, then their text after the header.
// The _strcmpi import thunk at 0x009F6FA0 (IAT slot 0x0135933C) is landed as a
// no-argument jump stub; its caller supplies the two arguments on the stack.
// See Rva008D30D0EventFlags.cpp for the same convention.
extern void ji_009f6fa0();
typedef int (__cdecl *Rva009F6FA0Compare)(const char *left, const char *right);

struct Rva008B4260StringRef
{
    const char *m_payload;
    int compare008B4260(const Rva008B4260StringRef &other) const;
};

int Rva008B4260StringRef::compare008B4260(const Rva008B4260StringRef &other) const
{
    const char *left = m_payload;
    const char *right = other.m_payload;
    if (left == right)
        return 0;
    return ((Rva009F6FA0Compare)ji_009f6fa0)(left + 8, right + 8);
}
