struct Rva006E1C80Pair {
    unsigned int first;
    unsigned int second;
};

class Rva006E1C80Owner {
public:
    void copyTo(Rva006E1C80Pair *destination) const;

private:
    unsigned char m_prefix[0x40];
    Rva006E1C80Pair m_value;
};

void Rva006E1C80Owner::copyTo(Rva006E1C80Pair *destination) const
{
    unsigned int first = m_value.first;
    destination->first = first;
    unsigned int second = m_value.second;
    destination->second = second;
}
