// cl: /O2 /DNDEBUG /MD

// The carved body at 0x0013A300 reads a dword at this plus 0x10.
// Its thunk supplies no semantic owner, so the type keeps the retail address.
class Rva0013A300DwordOwner
{
public:
    int getValue() const;

private:
    char m_prefix[0x10];
    int m_value;
};

// ?getValue@Rva0013A300DwordOwner@@QBEHXZ
int Rva0013A300DwordOwner::getValue() const
{
    return m_value;
}
