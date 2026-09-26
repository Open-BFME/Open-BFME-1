// cl: /DNDEBUG /MD /EHsc

class Rva005A73A0MemberAddressGetter
{
public:
    int &get();

private:
    char padding[0x278];
    int value;
};

int &Rva005A73A0MemberAddressGetter::get()
{
    return value;
}
