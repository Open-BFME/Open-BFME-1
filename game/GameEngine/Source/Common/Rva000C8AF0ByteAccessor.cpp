class Rva000C8AF0ByteAccessor
{
    char padding[0xbc];
    unsigned char value;

public:
    unsigned char get() const;
};

unsigned char Rva000C8AF0ByteAccessor::get() const
{
    return value;
}
