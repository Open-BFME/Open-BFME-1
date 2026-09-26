// stlport

extern "C" __declspec(dllimport) void * __cdecl bfme006EE640Memmove(void *destination,
	const void *source, unsigned int bytes);

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
			bfme006EE640Memmove(position, next, (char *)finish - (char *)next);
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
