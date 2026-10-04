// Candidate for retail RVA 0x00766A70 (34 bytes).
// The containing BFME W3DScriptedModelDraw object has a model-state pointer at
// +0x14 and a one-byte transition state at +0x230.  The five-argument sibling
// is the incremental-link thunk at 0x00001CA8, which enters retail
// W3DScriptedModelDraw's 0x00765FB0 body.
// cl: /O2 /Ob2 /GR- /EHsc-

class Rva00766A70W3DScriptedModelDraw
{
public:
	void update(int value);

private:
	char m_pad00[0x14];
	void *m_model;
	char m_pad18[0x218];
	unsigned char m_state;
};

extern void j_00001ca8();

// ?update@Rva00766A70W3DScriptedModelDraw@@QAEXH@Z
void Rva00766A70W3DScriptedModelDraw::update(int value)
{
	if (m_model)
	{
		typedef void (Rva00766A70W3DScriptedModelDraw::*Apply)(void *, int, int, int, int);
		union { void (*fn)(); Apply call; } u = { j_00001ca8 };
		m_state = 0;
		(this->*u.call)(m_model, value, 0, 1, 1);
	}
}
