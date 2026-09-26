class Rva13E720SecondArgumentStore {
public:
    Rva13E720SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_0013e720@@YAXXZ
Rva13E720SecondArgumentStore *Rva13E720SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}
