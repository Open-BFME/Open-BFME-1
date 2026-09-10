// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Retail 0x003AA270 copies the sixteen-byte audio-event record used by the
// append body at 0x003B1A80. Both bodies store vtable 0x010EC768 and retain
// the handle at offset 0x08.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

extern int R2Data010EC768;

struct P6Elem003B1A80
{
	void *m_at00;
	int m_at04;
	void *m_at08;
	char m_at0C;

	P6Elem003B1A80();
	P6Elem003B1A80(const P6Elem003B1A80 &source)
	{
		m_at00 = &R2Data010EC768;
		m_at04 = source.m_at04;
		m_at08 = source.m_at08;
		if (m_at08 != 0)
			InterlockedIncrement((long volatile *)((char *)m_at08 + 4));
		m_at0C = source.m_at0C;
	}
	~P6Elem003B1A80();
};

template _STL::vector<P6Elem003B1A80, _STL::allocator<P6Elem003B1A80> >::vector(
	const _STL::vector<P6Elem003B1A80, _STL::allocator<P6Elem003B1A80> > &);
