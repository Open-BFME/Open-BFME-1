// Retail at 0x0049C930 is lea eax, [ecx+0xb0]; ret.
// The owning type and member semantics were not recovered.
class Rva0049C930Holder
{
public:
    int &get();

private:
    char m_padding[0xb0];
    int m_value;
};

int &Rva0049C930Holder::get()
{
    return m_value;
}
