// ?resize@?$vector@URva00244A80Element@@V?$allocator@URva00244A80Element@@@_STL@@@_STL@@QAEXI@Z
// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// Open-BFME: STLport vector<Rva00244A80Element>::resize(size_type),
// retail 0x00247130, 47 bytes.  The identity is carried by the callee at
// 0x00246850: it is the same vector's two-argument resize and its 28-byte
// by-value element.  Its shrink and growth callees are the existing
// Rva00244A80Element copy/fill bodies at 0x00233A20 and 0x002403E0.
//
// This starts from targets/game/reverse/attempts/0x00247130.cpp.  The former free
// bfmeMakeAF wrapper had the right temporary layout but the wrong ABI model;
// as a free __stdcall function it left the zero value in ECX.  The retail
// body is the one-argument vector member, so ECX is this and MSVC selects EDX
// for the constructor's zero value.

struct Rva00244A80Element
{
	Rva00244A80Element()
	{
		m_at00 = 0;
		m_at10 = 1;
		m_at14 = 0;
		m_at18 = 0;
		m_at04 = 0;
		m_at08 = 0;
		m_at0c = 0;
	}

	Rva00244A80Element(const Rva00244A80Element &other) throw()
	{
		m_at00 = other.m_at00;
		m_at04 = other.m_at04;
		m_at08 = other.m_at08;
		m_at0c = other.m_at0c;
		m_at10 = other.m_at10;
		m_at14 = other.m_at14;
		m_at18 = other.m_at18;
	}

	~Rva00244A80Element();

	int m_at00;
	int m_at04;
	int m_at08;
	int m_at0c;
	char m_at10;
	int m_at14;
	int m_at18;
};

namespace _STL
{
	template <class Type>
	class allocator
	{
	};

	template <class Type, class Allocator>
	class vector
	{
	public:
		void resize(unsigned int newSize, Type value);

		void resize(unsigned int newSize)
		{
			resize(newSize, Type());
		}

	private:
		Type *_M_start;
		Type *_M_finish;
		Type *_M_end_of_storage;
	};

	template void vector<Rva00244A80Element,
		allocator<Rva00244A80Element> >::resize(unsigned int);
}
