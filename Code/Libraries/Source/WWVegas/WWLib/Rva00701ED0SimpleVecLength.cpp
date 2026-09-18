// cl: /DNDEBUG /MD /O2 /EHsc

class Rva00701ED0SimpleVec
{
public:
    int length() const;

private:
    char m_beforeLength[8];
    int m_length;
};

int Rva00701ED0SimpleVec::length() const
{
    return m_length;
}
