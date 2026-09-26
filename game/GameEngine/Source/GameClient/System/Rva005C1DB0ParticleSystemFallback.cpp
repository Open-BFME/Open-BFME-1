// cl: /DNDEBUG /MD /EHsc

class ParticleSystemZA
{
};

extern ParticleSystemZA *bfmeNullSystemZA(void);

class Rva005C1DB0
{
public:
	ParticleSystemZA *get(void) const;

private:
	unsigned char m_padding00[0x4c];
	ParticleSystemZA *m_system;
};

ParticleSystemZA *Rva005C1DB0::get(void) const
{
	ParticleSystemZA *system = m_system;
	if (system == 0)
		system = bfmeNullSystemZA();

	return *(ParticleSystemZA **)((unsigned char *)system + 0x7c);
}
