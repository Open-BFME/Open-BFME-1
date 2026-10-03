// cl: /O2 /MD
// Retail009EB8A0..009EB8C4: table VA01145744 slot11 (+2C),
// installed by the matched base constructor009EB7D0. Derived prototype
// tables also share this slot. The original method identity is unknown.
// Global pointer VA0134FAAC is the existing Q1 registry receiver.
// The one stacked argument is this object: target009F0FA0 reads its+4
// state bits and+8 key, keeps incoming ECX as the registry, and RET4 at
// 009F144B. The call binding is address-derived and independently checked.
class Rva009EF0D0Element;
class Q1Receiver0134FAAC {
public:
    void m009F0FA0(Rva009EF0D0Element *);
};
extern Q1Receiver0134FAAC *g_q1Receiver0134FAAC;
class Rva009EB8A0 {
public:
    void method();
private:
    char prefix[4];
    unsigned int word0004;
};
void Rva009EB8A0::method()
{
    if ((word0004 & 0xff0000) != 0x30000 && g_q1Receiver0134FAAC)
        g_q1Receiver0134FAAC->m009F0FA0(reinterpret_cast<Rva009EF0D0Element *>(this));
}
