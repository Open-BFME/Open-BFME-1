class Rva66830SecondArgumentStore {
public:
    Rva66830SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_00066830@@YAXXZ
Rva66830SecondArgumentStore *Rva66830SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}
