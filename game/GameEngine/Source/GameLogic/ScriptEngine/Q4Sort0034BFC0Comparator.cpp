// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// Q4Sort0034BFC0 compares particle-system template names without case.
// targets/game/reverse/symbols.csv resolves its ILT at 0x00024B81 to this body at
// 0x0033D5E0, and the adjacent median, partition, and sort bodies use the
// same comparator type.
//
// Retail evaluates the right-hand getName call first.  Keeping both calls in
// one expression reproduces the returned AsciiString temporaries and their
// cleanup at 0x00887940 without adding copy constructors.

template <typename T>
class StringBase
{
public:
	__declspec(nothrow) int compareNoCase(const StringBase<T> &other) const;

private:
	void *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	~AsciiString();

	__declspec(nothrow) int compareNoCase(const AsciiString &other) const
	{
		return ((const StringBase<char> *)this)->compareNoCase(
			*(const StringBase<char> *)&other);
	}
};

namespace FXParticleSystem
{

class ParticleSystemTemplate
{
public:
	AsciiString getName() const;
};

}

struct Q4Sort0034BFC0
{
	bool operator()(int a, int b) const;
};

bool Q4Sort0034BFC0::operator()(int a, int b) const
{
	return ((const FXParticleSystem::ParticleSystemTemplate *)a)->getName().compareNoCase(
		((const FXParticleSystem::ParticleSystemTemplate *)b)->getName()) < 0;
}
