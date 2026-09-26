// cl: /DNDEBUG /MD /EHsc

class Rva004893D0ByteClear
{
    char padding[0x55];
    unsigned char value;

public:
    void clear();
};

void Rva004893D0ByteClear::clear()
{
    value = 0;
}
