class Rva00433740IndexedFloat {
public:
    float get(unsigned int index) const;

private:
    unsigned char m_prefix[0x24];
    float m_values[16];
};

float Rva00433740IndexedFloat::get(unsigned int index) const
{
    return m_values[index];
}
