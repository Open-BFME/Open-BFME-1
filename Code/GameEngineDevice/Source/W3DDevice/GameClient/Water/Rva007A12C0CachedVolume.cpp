// cl: /DNDEBUG /MD /EHsc
//
// Clean reconstruction of the lazy 24-byte cache accessor at retail
// 0x007A12C0.  The owning class name remains address-derived because the
// target has no named caller or identifying vtable reference.

class Rva007A12C0CachedVolume
{
public:
	Rva007A12C0CachedVolume(void *first, void *second);

	unsigned int first;
	unsigned int second;
	unsigned int third;
	unsigned int fourth;
	unsigned int fifth;
	unsigned int sixth;
};

class Rva007A12C0CacheOwner
{
public:
	Rva007A12C0CachedVolume &getCachedVolume(void);

private:
	unsigned char m_beforeSources[0x54];
	void *m_firstSource;
	void *m_secondSource;
	unsigned char m_beforeValid[8];
	bool m_cacheValid;
	unsigned char m_beforeCache[3];
	Rva007A12C0CachedVolume m_cachedVolume;
};

Rva007A12C0CachedVolume &Rva007A12C0CacheOwner::getCachedVolume(void)
{
	if (!m_cacheValid)
	{
		Rva007A12C0CachedVolume value(m_firstSource, m_secondSource);
		m_cachedVolume.first = value.first;
		m_cachedVolume.second = value.second;
		m_cachedVolume.third = value.third;
		m_cachedVolume.fourth = value.fourth;
		m_cachedVolume.fifth = value.fifth;
		m_cachedVolume.sixth = value.sixth;
		m_cacheValid = true;
	}

	return m_cachedVolume;
}
