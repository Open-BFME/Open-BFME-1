// cl: /DNDEBUG /MD /EHsc

class Rva004104C0ByteClear
{
    char padding[0x38];
    unsigned char value;

public:
    void clear();
};

void Rva004104C0ByteClear::clear()
{
    value = 0;
}
