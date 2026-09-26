class Rva6EEE0SecondArgumentStore {
public:
    Rva6EEE0SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_0006eee0@@YAXXZ
Rva6EEE0SecondArgumentStore *Rva6EEE0SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}
