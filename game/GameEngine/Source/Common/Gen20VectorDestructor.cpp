// cl: /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// The ILT at 0x00017EF4 is called from LuaScriptEngine::~LuaScriptEngine and
// names the Gen20 vector destructor at retail 0x002EB090.  Gen20 contains the
// BFMERetailAsciiString at offset 0 and the twelve-byte BfmeSortElem20Tail
// vector at offset 8.

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString()
	{
		releaseBuffer();
	}

	void releaseBuffer();
	void *m_data;
};

class BfmeSortElem20Tail
{
public:
	~BfmeSortElem20Tail();

	void *m_begin;
	void *m_finish;
	void *m_capacity;
};

struct Gen20
{
	BFMERetailAsciiString m_string;
	char m_padding[4];
	BfmeSortElem20Tail m_vector;
};

#include <vector>

template class _STL::vector<Gen20>;
