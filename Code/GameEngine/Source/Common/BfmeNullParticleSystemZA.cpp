// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the null particle-system accessor at retail 0x005CFF50, 190
// bytes.  Two function-local statics sharing one guard word: a template named
// "--nullsystem" built from a string temporary, then the system itself.

class StringBaseZA
{
protected:
	StringBaseZA(const char *text);

	~StringBaseZA(void);

	char *m_bfmeDataZA;
};

class AsciiStringZA : public StringBaseZA
{
public:
	AsciiStringZA(const char *text) : StringBaseZA(text)
	{
	}

	~AsciiStringZA(void)
	{
	}
};

class ParticleSystemTemplateZA
{
public:
	ParticleSystemTemplateZA(const AsciiStringZA &name);

	~ParticleSystemTemplateZA(void);
};

class ParticleSystemZA
{
public:
	ParticleSystemZA(ParticleSystemTemplateZA *tmpl, int id, int attach);

	~ParticleSystemZA(void);
};

// ?bfmeNullSystemZA@@YAPAVParticleSystemZA@@XZ
ParticleSystemZA *bfmeNullSystemZA(void)
{
	static ParticleSystemTemplateZA s_bfmeNullTemplateZA(AsciiStringZA("--nullsystem"));

	static ParticleSystemZA s_bfmeNullSystemZA(&s_bfmeNullTemplateZA, -2, 0);

	return &s_bfmeNullSystemZA;
}
