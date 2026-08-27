// Open-BFME: signed arithmetic predicate reconstructed from retail RVA 0x0037A810.

class Rva0037A810Object
{
public:
    bool isNonNegative(int value);

private:
    char m_pad0[0x1C];
    int m_factor;
    int m_offset;
};

bool Rva0037A810Object::isNonNegative(int value)
{
    return m_factor * value + m_offset >= 0;
}
