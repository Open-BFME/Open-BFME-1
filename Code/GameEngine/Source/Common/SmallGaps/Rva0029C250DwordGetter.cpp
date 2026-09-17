// ?get@Rva0029C250DwordField@@QBEHXZ
// cl: /O2 /DNDEBUG /MD /EHsc
// Address-derived identity: the only direct caller is anonymous ILT 0x0003FE59.

class Rva0029C250DwordField
{
public:
    int get() const;

private:
    int m_pad00;
    int m_value;
};

int Rva0029C250DwordField::get() const
{
    return m_value;
}
