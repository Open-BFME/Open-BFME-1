class Rva007F0C20PairStore
{
public:
    void setPair(unsigned int first, unsigned int second);
private:
    char m_padding[0x28];
    struct Pair { unsigned int first, second; } m_pair;
};

void Rva007F0C20PairStore::setPair(unsigned int first, unsigned int second)
{
    Pair pair = { first, second };
    m_pair = pair;
}
