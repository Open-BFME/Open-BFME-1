// cl: /DNDEBUG /MD /EHsc

class Rva00673A40WordGetter
{
    char padding[0x1c];
    unsigned short value;

public:
    unsigned int get() const;
};

unsigned int Rva00673A40WordGetter::get() const
{
    return value;
}
