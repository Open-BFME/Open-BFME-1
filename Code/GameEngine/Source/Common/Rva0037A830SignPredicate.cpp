// Open-BFME: signed arithmetic predicate reconstructed from retail RVA 0x0037A830.

class Rva0037A830Object
{
public:
    bool isNonNegative(int value);

private:
    char m_pad0[0x24];
    int m_factor;
    int m_offset;
};

bool Rva0037A830Object::isNonNegative(int value)
{
    return m_factor * value + m_offset >= 0;
}
