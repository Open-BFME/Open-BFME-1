// cl: /DNDEBUG /MD /EHsc

class Rva000C8D70ByteAccessor
{
    char padding[0x12be];
    unsigned char value;

public:
    unsigned char get() const;
};

unsigned char Rva000C8D70ByteAccessor::get() const
{
    return value;
}
