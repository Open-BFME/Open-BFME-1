// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// Rva000CFF80Owner::eraseInputKey, retail 0x000CFF80 (36 bytes).
//
// Address-qualified thiscall wrapper: the argument's unsigned short at +0x478
// is copied into a local and its address handed to the BfmeListXC at
// this+0x64C (ILT 0x00008BE8 -> matched bfmeEraseXC at 0x000CEAD0).  The
// owning class is not proven, so the names keep the address.
//
// The local being an unsigned short (not a widened int) is what gives
// retail's xor edx,edx / mov dx,[eax+0x478] zero-extension; VC7.1 then parks
// it in the dead parameter slot.

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

// ?eraseInputKey@Rva000CFF80Owner@@QAEXPAURva000CFF80Input@@@Z
void Rva000CFF80Owner::eraseInputKey(Rva000CFF80Input *input)
{
	unsigned short key = input->key;
	list.bfmeEraseXC(&key);
}
