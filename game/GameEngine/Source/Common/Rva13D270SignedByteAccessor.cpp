class Rva13D270SignedByteAccessor {
public:
    int value() const;

private:
    unsigned char m_prefix[0x493];
    signed char m_value;
};

// ?d_0013d270@@YAXXZ
int Rva13D270SignedByteAccessor::value() const
{
    return m_value;
}
