// cl: /DNDEBUG /MD /EHsc-
// Open-BFME: Made001E5940 constructor, retail 0x002DC520, 131 bytes.
//
// Identity is established by the matched parseDamageNugget caller: its
// operator-new size is 0xA4 and its ILT at 0x00009A0C jumps to this body.
// The callee is the shared GenBase002DF2B0 constructor, followed by this
// derived object's vptr and the scalar/array tail observed at +0x58..+0xA0.
// Field names stay offset-based because the matched parser proves ownership
// and size, but not semantic names for the individual tail words.

typedef int Int;
typedef float Real;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class GenBase002DF2B0
{
public:
	GenBase002DF2B0();
	virtual void slot();

private:
	char m_base[0x58 - 4];
};

extern "C" char Made001E5940_vtbl;

class __declspec(novtable) Made001E5940 : public GenBase002DF2B0
{
public:
	__declspec(noinline) Made001E5940();
	virtual void slot();

private:
	Int m_58;
	Int m_5c;
	Real m_60;
	Real m_64;
	unsigned char m_68;
	unsigned char m_pad69[3];
	Int m_6c;
	Int m_70;
	Int m_74;
	Int m_78;
	Int m_7c;
	Int m_80;
	Int m_84;
	Int m_88;
	Int m_8c[6];
};

// ??0Made001E5940@@QAE@XZ
Made001E5940::Made001E5940()
{
	*reinterpret_cast<char *volatile *>(this) = &Made001E5940_vtbl;
	_ReadWriteBarrier();
	Int zero = 0;
	m_7c = zero;
	m_80 = zero;
	m_84 = zero;
	for (int i = 0; i != 6; ++i)
		m_8c[i] = zero;
	m_58 = 0;
	m_68 = 1;
	m_5c = 0;
	m_60 = 3.14159274f;
	m_64 = -1.0f;
	m_6c = 0;
	m_70 = 0x16;
	m_74 = 0;
	m_78 = 0x0f;
	m_88 = 0;
	for (int i = 0; i != 6; ++i)
		m_8c[i] = zero;
}
