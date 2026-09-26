// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// _STL::list<Z1Elem0013BF00>::operator= at retail 0x0076F7B0.
// Gen_t_00776240_p128pod::operator= calls this list assignment for its
// field at +0x50.  The element copy uses UnicodeString::set at +0x00 and
// copies the remaining 0x20 bytes as plain storage.

#include <list>

class UnicodeString
{
public:
	void set(const UnicodeString &other);

	UnicodeString &operator=(const UnicodeString &other)
	{
		set(other);
		return *this;
	}

private:
	void *m_text;
};

struct Z1Elem0013BF00
{
	UnicodeString m_text;
	unsigned char m_byte4;
	unsigned int m_dword8;
	unsigned int m_dwordC;
	unsigned int m_dword10;
	unsigned int m_dword14;
	unsigned int m_dword18;
	unsigned int m_dword1C;
	unsigned char m_byte20;

	~Z1Elem0013BF00();
};

template _STL::list<Z1Elem0013BF00> &
	_STL::list<Z1Elem0013BF00>::operator=(
		const _STL::list<Z1Elem0013BF00> &);
