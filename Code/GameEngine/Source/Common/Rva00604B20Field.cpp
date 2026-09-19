// cl: /O2 /Ob0

// Retail RVA 0x00604B20 reads the float at this+0x14 and returns it.
// No caller or identity table proves a semantic owner.

class Rva00604B20Field
{
    char m_padding[0x14];
    float m_value;

public:
    float value() const;
};

float Rva00604B20Field::value() const
{
    return m_value;
}
