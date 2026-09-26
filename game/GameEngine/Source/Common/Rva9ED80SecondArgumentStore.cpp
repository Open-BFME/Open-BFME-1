class Rva9ED80SecondArgumentStore
{
public:
    Rva9ED80SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_0009ed80@@YAXXZ
Rva9ED80SecondArgumentStore *Rva9ED80SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}
