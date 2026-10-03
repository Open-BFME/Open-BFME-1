// cl: /O2 /Ob2 /DNDEBUG /MD
// The pre-existing opaque callee consumes one stack word (RET4). Keep its
// binding; reinterpret_cast<void *>(1) expresses the literal ABI word only,
// not an assertion that the original source parameter was a pointer.
class BfmeThing916D
{
public:
    void bfmeGo916D(void *);
};
struct Rva0016CA00At1C
{
    unsigned char m_offset00[0x10];
    BfmeThing916D *m_offset10;
};
class Rva0016CA00
{
public:
    virtual void method(unsigned int);
private:
    unsigned char m_offset04[0x18];
    Rva0016CA00At1C *m_offset1C;
};
void Rva0016CA00::method(unsigned int)
{
    m_offset1C->m_offset10->bfmeGo916D(reinterpret_cast<void *>(1));
}
