// cl: /DNDEBUG /MD /EHsc
// RVA 0x0081C490: index 28-byte elements from the pointer at offset zero.
// The old dump extent crosses two int3 bytes into a separate return-this body.
struct Rva0081C490Element
{
    char m_bytes[0x1C];
};

class Rva0081C490Owner
{
public:
    Rva0081C490Element *at(int index);

private:
    Rva0081C490Element *m_begin;
};

Rva0081C490Element *Rva0081C490Owner::at(int index)
{
    return m_begin + index;
}
