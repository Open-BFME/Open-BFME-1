// Retail's strncpy ILT thunk (0x009F70BA, IAT slot 0x013594C0) is defined as
// a no-argument jump stub; the caller supplies strncpy's three stack arguments.
// Same convention as Y4FeslFavGameAddress.cpp / Rva00809E40FeslAdmission.cpp.
void __cdecl ji_009f70ba();
typedef char *(__cdecl *Rva007EA3E0StrncpyThunk)(char *destination, const char *source, unsigned int count);

struct Rva007EA3E0Nested
{
    char m_padding[0x183];
    char m_prefix[0x5f];
};

class Rva007EA3E0Owner
{
public:
    void setPrefix(const char *value);
private:
    void *m_head;
    Rva007EA3E0Nested *m_nested;
};

void Rva007EA3E0Owner::setPrefix(const char *value)
{
    reinterpret_cast<Rva007EA3E0StrncpyThunk>(&ji_009f70ba)(
        m_nested->m_prefix, value, sizeof(m_nested->m_prefix));
}
