// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

class DamageInfoInput
{
public:
	DamageInfoInput &operator=(const DamageInfoInput &);

private:
	char m_unreconstructed[0x4c];
};

class DamageInfoOutputTail
{
public:
	DamageInfoOutputTail &operator=(const DamageInfoOutputTail &other)
	{
		m_actualDamageClipped = other.m_actualDamageClipped;
		m_noEffect = other.m_noEffect;
		return *this;
	}

	float m_actualDamageClipped;
	bool m_noEffect;
	char m_padding[3];
};

class DamageInfoOutput
{
public:
	float m_actualDamageDealt;
	DamageInfoOutputTail m_tail;
};

class Snapshot
{
protected:
	virtual void crc();
	virtual void xfer();
	virtual void loadPostProcess();
};

class DamageInfo : public Snapshot
{
private:
	DamageInfoInput in;
	DamageInfoOutput out;
};

namespace _STL
{
struct random_access_iterator_tag
{
};

template <class InputIterator, class OutputIterator, class Distance>
OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result,
	const random_access_iterator_tag &, Distance *)
{
	for (Distance count = last - first; count > 0; --count, ++first, ++result)
		*result = *first;
	return result;
}

template DamageInfo *__copy<DamageInfo *, DamageInfo *, int>(DamageInfo *, DamageInfo *,
	DamageInfo *, const random_access_iterator_tag &, int *);
}
