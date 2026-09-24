// ?eraseInputKey@Rva000CFF80Owner@@QAEXPAURva000CFF80Input@@@Z
// partial score=0.94 date=2026-09-24
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
struct BfmeNodeXC;
class BfmeListXC
{
public:
    void bfmeEraseXC(unsigned short *key);
    BfmeNodeXC *m_bfmeEnd;
};
struct Rva000CFF80Input
{
    unsigned char unused[0x478];
    unsigned short key;
};
class Rva000CFF80Owner
{
    unsigned char unused[0x64c];
    BfmeListXC list;
public:
    void eraseInputKey(Rva000CFF80Input *input);
};
void Rva000CFF80Owner::eraseInputKey(Rva000CFF80Input *input)
{
    input = reinterpret_cast<Rva000CFF80Input *>(static_cast<unsigned int>(input->key));
    list.bfmeEraseXC(reinterpret_cast<unsigned short *>(&input));
}
