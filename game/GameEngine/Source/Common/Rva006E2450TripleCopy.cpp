struct Rva006E2450Triple {
    unsigned int first;
    unsigned int second;
    unsigned int third;
};

class Rva006E2450Owner {
public:
    void copyTo(Rva006E2450Triple *destination) const;

private:
    unsigned char m_prefix[0xc4];
    Rva006E2450Triple m_value;
};

void Rva006E2450Owner::copyTo(Rva006E2450Triple *destination) const
{
    unsigned int first = m_value.first;
    destination->first = first;
    unsigned int second = m_value.second;
    destination->second = second;
    unsigned int third = m_value.third;
    destination->third = third;
}
