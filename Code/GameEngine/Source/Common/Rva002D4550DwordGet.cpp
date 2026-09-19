class Rva002D4550Owner
{
public:
    int get() const;

private:
    char m_padding[ 4 ];
    int m_value;
};

int Rva002D4550Owner::get() const
{
    return m_value;
}
