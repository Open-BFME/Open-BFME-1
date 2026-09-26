// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#define _STLP_USE_NEWALLOC 1
#include <map>

class BfmeObjB0
{
public:
	char m_pad[0x74];
	int m_id;
};

class Gen_002281B0
{
public:
	bool bfmeUpdate(BfmeObjB0 *obj, int mode);

private:
	char m_pad[0x38];
	_STL::map<int, int> m_map;
};

// ?bfmeUpdate@Gen_002281B0@@QAE_NPAVBfmeObjB0@@H@Z
bool Gen_002281B0::bfmeUpdate(BfmeObjB0 *obj, int mode)
{
	if (obj == 0)
		return true;
	int id = obj->m_id;
	if (mode == 2)
	{
		_STL::map<int, int>::iterator it = m_map.find(id);
		if (it != m_map.end())
			m_map.erase(it);
	}
	else
		m_map[id] = mode;
	return true;
}
