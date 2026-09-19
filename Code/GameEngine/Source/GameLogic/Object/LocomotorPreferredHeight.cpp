// cl: /DNDEBUG /MD /EHsc

// Retail RVA 0x001B46A0 reads Locomotor::m_preferredHeight at offset 0x3C.
// The ILT at 0x0002ECAD and eleven callers prove the method identity.

typedef float Real;

class Locomotor
{
public:
	Real getPreferredHeight() const;
};

// ?getPreferredHeight@Locomotor@@QBEMXZ
Real Locomotor::getPreferredHeight() const
{
	return *(const Real *)((const unsigned char *)this + 0x3C);
}
