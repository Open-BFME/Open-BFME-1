// cl: /DNDEBUG /MD /EHsc
// RVA 0x009CBA90: return this while consuming one stack argument.
class Rva009CBA90Owner
{
public:
    void *Rva009CBA90ReturnThis(void *unused);
};

void *Rva009CBA90Owner::Rva009CBA90ReturnThis(void *unused)
{
    return this;
}
