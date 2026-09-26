class Rva005790E0
{
public:
    static bool __stdcall set(Rva005790E0 *target, int value);

private:
    unsigned char m_padding[0x10];
    int m_value;
};

bool __stdcall Rva005790E0::set(Rva005790E0 *target, int value)
{
    target->m_value = value;
    return true;
}
