// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// Retail 0x0034E1B0, 68 bytes.  Append an acquired science to the player's
// ScienceType vector; the vector's STLport growth helper is an existing body.

#include <vector>

enum ScienceType
{
	Rva0034E1B0ScienceType = 0
};

namespace _STL
{
template <class Type, class Allocator>
class public_vector : public vector<Type, Allocator>
{
public:
	using vector<Type, Allocator>::_M_start;
	using vector<Type, Allocator>::_M_finish;
	using vector<Type, Allocator>::_M_end_of_storage;
	using vector<Type, Allocator>::_M_insert_overflow;
};
}

class ScriptEngine
{
public:
	void notifyOfAcquiredScience(int playerIndex, ScienceType science);

private:
	char m_bfmePad[0x17474];
	_STL::public_vector<ScienceType, _STL::allocator<ScienceType> >
		m_acquiredSciences[8];
};

void ScriptEngine::notifyOfAcquiredScience(int playerIndex, ScienceType science)
{
	m_acquiredSciences[playerIndex].push_back(science);
}
