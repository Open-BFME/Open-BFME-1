// cl: /O2
// Address-derived recovery for the otherwise unidentified byte getter at
// retail 0x00149E10.  Its +0x33A field is outside the recovered BFME
// ParticleSystem layout, so it must not carry ParticleSystem::isSaveable.

class Rva00149E10ByteGetter
{
public:
	bool get() const;

private:
	unsigned char m_beforeValue[0x33A];
	bool m_value;
};

bool Rva00149E10ByteGetter::get() const
{
	return m_value;
}
