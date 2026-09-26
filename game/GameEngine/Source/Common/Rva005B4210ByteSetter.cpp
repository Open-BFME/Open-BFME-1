// Retail at 0x005B4210 stores its byte argument at this+0x0B and returns.
// The owning type and field semantics were not recovered.
struct Rva005B4210ByteSetter
{
    unsigned char m_pad[0x0B];
    unsigned char m_value;

    void set(unsigned char value);
};

void Rva005B4210ByteSetter::set(unsigned char value)
{
    m_value = value;
}
