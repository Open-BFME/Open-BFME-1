// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: erase one owned pointer payload from the map at +0x5c.

#include <map>

void __cdecl operator delete(void *memory);

class Gen_00654130
{
public:
	void bfmeErase(void *key);

private:
	unsigned char m_prefix[0x5c];
	_STL::map<void *, void *> m_values;
};

void Gen_00654130::bfmeErase(void *key)
{
	if (key == 0)
		return;

	_STL::map<void *, void *> *values = &m_values;
	_STL::map<void *, void *>::iterator found = values->find(key);
	if (found != values->end())
	{
		void *payload = found->second;
		if (payload != 0)
			::operator delete(payload);
		values->erase(found);
	}
}
