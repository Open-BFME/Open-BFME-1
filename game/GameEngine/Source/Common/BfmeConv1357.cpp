// Open-BFME5 conversions.

// The ledger pins bfmeSetVGR's second parameter as PAVBfmeTexVGR, so that
// element spelling stays.  The release it performs is the shared
// counted-texture base leaf ?Release_Ref@TextureBaseClass@@QAEXXZ
// (0x009EB7A0), which retail calls out of line.
class BfmeTexVGR
{
public:
	int m_bfme00;
	unsigned short m_bfmeRefs;
};

class TextureBaseClass
{
public:
	void Release_Ref();
};

// The texture-array lookup this body calls at retail 0x0092C220 lives at
// 0x0092BE50 as ?Get_Texture_Array@MeshMatDescClass@@QAEPAVTexBufferClass@@
// HH_N@Z (game/Libraries/Source/WWVegas/WW3D2/meshmatdesc.cpp), so the
// callee and its buffer return type are spelled with the real owners.
class TexBufferClass
{
public:
	char m_bfmePad[8];
	BfmeTexVGR **m_bfmeArray;
};

class MeshMatDescClass
{
public:
	TexBufferClass *Get_Texture_Array(int pass, int stage, bool create);
};

class BfmeMeshVGR
{
public:
	void bfmeSetVGR(int index, BfmeTexVGR **src, int pass, int stage);
};

void BfmeMeshVGR::bfmeSetVGR(int index, BfmeTexVGR **src, int pass, int stage)
{
	BfmeTexVGR **p = &((MeshMatDescClass *)this)->Get_Texture_Array(pass, stage, true)->m_bfmeArray[index];
	if (*src)
		(*src)->m_bfmeRefs++;
	if (*p)
		((TextureBaseClass *)*p)->Release_Ref();
	*p = *src;
}
