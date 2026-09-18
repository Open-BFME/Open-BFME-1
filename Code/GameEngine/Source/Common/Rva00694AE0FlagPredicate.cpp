// cl: /DNDEBUG /MD /EHsc
// The retail predicate reads three byte flags and returns a full-width integer.
class Rva00694AE0
{
public:
    int anyFlagSet();

private:
    unsigned char m_prefix[0x12];
    unsigned char m_flag12;
    unsigned char m_flag13;
    unsigned char m_flag14;
};

int Rva00694AE0::anyFlagSet()
{
    if (m_flag12 || m_flag13 || m_flag14)
        return 1;
    return 0;
}
