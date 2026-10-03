// cl: /O2 /MD
// Retail table VA 0x01135DB0 holds RVA 0x00892EB0 in slot 7.
// Constructor 0x00892DA0 installs this table at 0x00892DD9.
// The complete method reads bit 17 from receiver+0x60, ends at RET 0x00892EB9,
// and is followed by INT3 padding. Owner and semantic method name are unproven.
class Rva00892EB0
{
public:
    unsigned int method() const;
private:
    char prefix[0x60];
    unsigned int word0060;
};
unsigned int Rva00892EB0::method() const
{
    return (word0060 >> 17) & 1;
}
