#pragma once

struct BfmeElemVLH
{
	char m_bfmePad[0x60];
};

class BfmeVecVLH
{
public:
	BfmeElemVLH *bfmeAtVLH(int i);
	int m_bfme00;
	BfmeElemVLH *volatile m_bfme04;
	BfmeElemVLH *volatile m_bfme08;
};
