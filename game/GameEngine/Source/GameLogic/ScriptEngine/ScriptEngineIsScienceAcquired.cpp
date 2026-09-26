// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// Retail 0x0034C830, 90 bytes.  Search the acquired-science vector for one
// player and optionally erase the matching science.

#include <vector>

enum ScienceType
{
	Rva0034C830ScienceType = 0
};

namespace _STL
{
template <class Type, class Allocator>
class public_vector : public vector<Type, Allocator>
{
public:
	using vector<Type, Allocator>::begin;
	using vector<Type, Allocator>::end;
	using vector<Type, Allocator>::size;
	using vector<Type, Allocator>::erase;
};
}

class ScriptEngine
{
public:
	virtual bool isScienceAcquired(int playerIndex, ScienceType science,
		bool removeFromList);

private:
	char m_bfmePad[0x17470];
	_STL::public_vector<ScienceType, _STL::allocator<ScienceType> >
		m_acquiredSciences[32];
};

bool ScriptEngine::isScienceAcquired(int playerIndex, ScienceType science,
	bool removeFromList)
{
	if (playerIndex < 0 || playerIndex >= 32)
		return false;

	unsigned int scaled = (unsigned int)playerIndex * 3;
	ScienceType *end = *(ScienceType **)((char *)this + scaled * 4 + 0x17478);
	_STL::public_vector<ScienceType, _STL::allocator<ScienceType> > *specialList =
		(_STL::public_vector<ScienceType, _STL::allocator<ScienceType> > *)
		((char *)this + scaled * 4 + 0x17474);
	ScienceType *begin = specialList->begin();
	for (_STL::public_vector<ScienceType, _STL::allocator<ScienceType> >::iterator it =
		begin; it != end; ++it)
	{
		if (*it == science)
		{
			if (removeFromList)
				specialList->erase(it);
			return true;
		}
	}
	return false;
}
