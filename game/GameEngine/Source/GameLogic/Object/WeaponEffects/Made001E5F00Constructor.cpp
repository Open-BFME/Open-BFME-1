// cl: /DNDEBUG /MD /EHsc
// Open-BFME: Made001E5F00::Made001E5F00, retail 0x002DDBE0, 58 bytes.
//
// One of the Made001E5xxx constructors: run the shared base at 0x002DF2B0 --
// unidentified, so it is named for its own address -- put this class's vftable
// down and set the handful of fields below. The zero is materialised once and
// reused, which is what interleaves the stores the way retail has them.

typedef float Real;
typedef int Int;
typedef bool Bool;

class Made002DF2B0
{
public:
	Made002DF2B0();						// ILT 0x00010D07

	virtual ~Made002DF2B0();

private:
	unsigned char m_unmodelled_004[0x58 - 0x04];
};

class Made001E5F00 : public Made002DF2B0
{
public:
	Made001E5F00();

private:
	Int m_a;						// +0x58
	Int m_b;						// +0x5C
	Real m_angle;						// +0x60
	Int m_c;						// +0x64
	Int m_d;						// +0x68
	Real m_scale;						// +0x6C
	Int m_e;						// +0x70
	Bool m_f;						// +0x74
	Bool m_g;						// +0x75
	unsigned char m_unmodelled_076[2];
	Int m_h;						// +0x78
};

Made001E5F00::Made001E5F00()
{
	m_a = 0;
	m_b = 0;
	m_angle = 3.14159274f;
	m_c = 0;
	m_d = 0;
	m_scale = 1.0f;
	m_e = 0;
	m_f = false;
	m_g = false;
	m_h = 0;
}
