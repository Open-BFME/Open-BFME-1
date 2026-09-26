// cl: /O2 /Ob0

// Retail RVA 0x0036AD60 reads the dword at this+0x14 and returns it.
// No caller or identity table proves a semantic owner.

class Rva0036AD60Field
{
    char m_padding[0x14];
    int m_value;

public:
    int value() const;
};

int Rva0036AD60Field::value() const
{
    return m_value;
}
