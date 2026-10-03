// stlport

// <algorithm> pulls in the CRT <string.h>, and this project compiles without
// /D_DLL, so _CRTIMP expands to nothing there and a local
// `__declspec(dllimport)` declaration of the same memmove is dropped in favour
// of the header's plain one: the call would become a direct call to the CRT's
// static `_memmove` instead of `call [__imp__memmove]`, which is what retail
// emits. Declaring _CRTIMP the way /MD does makes <string.h> itself declare
// memmove as the import it is.
#ifndef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#endif

#include <algorithm>
#include <vector>

class Gen006EE640Vector : public _STL::vector<int>
{
public:
	void eraseOne(iterator position)
	{
		int *finish = _M_finish;
		int *next = position + 1;
		if (finish != next)
			memmove(position, next, (char *)finish - (char *)next);
		--_M_finish;
	}
};

class Gen006EE640
{
public:
	void remove(int value);

private:
	char m_head[0x29C];
	Gen006EE640Vector m_values;
};

void Gen006EE640::remove(int value)
{
	_STL::vector<int>::iterator found =
		_STL::find(m_values.begin(), m_values.end(), value);
	if (found != m_values.end())
		m_values.eraseOne(found);
}
