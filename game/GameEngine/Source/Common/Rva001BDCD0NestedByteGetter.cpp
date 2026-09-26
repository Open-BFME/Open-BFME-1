// cl: /DNDEBUG /MD /EHsc

class Rva001BDCD0NestedByteGetter
{
    struct Nested
    {
        char padding[0x70];
        unsigned char value;
    };

    char padding[4];
    Nested *nested;

public:
    unsigned char get() const;
};

unsigned char Rva001BDCD0NestedByteGetter::get() const
{
    return nested->value;
}
