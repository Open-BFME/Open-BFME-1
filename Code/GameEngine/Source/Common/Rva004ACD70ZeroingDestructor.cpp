// Open-BFME: zeroing destructor body reconstructed from retail RVA 0x004ACD70.

class BfmeDtorMemberC
{
public:
    ~BfmeDtorMemberC();

private:
    unsigned char m_padding[0x14];
};

class Rva004ACD70Object : public BfmeDtorMemberC
{
public:
    ~Rva004ACD70Object();
    int m_value;
};

Rva004ACD70Object::~Rva004ACD70Object()
{
    m_value = 0;
}
