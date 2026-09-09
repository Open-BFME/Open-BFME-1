// cl: -GX-
// stlport

#include <vector>

// Retail stores this string at BfmeElem60 +0x1c and releases it directly while
// erase destroys the removed tail.
class BFMERetailAsciiString
{
public:
	void releaseBuffer();
};

struct BfmeElem60
{
	char m_body[0x24];

	BfmeElem60();
	BfmeElem60( const BfmeElem60 &other );
	~BfmeElem60()
	{
		reinterpret_cast<BFMERetailAsciiString *>(reinterpret_cast<char *>(this) + 0x1c)->releaseBuffer();
	}
	BfmeElem60 &operator=( const BfmeElem60 &other );
};

class BfmeVec60
{
public:
	BfmeElem60 *erase( BfmeElem60 *first, BfmeElem60 *last );

	BfmeElem60 *_M_start;
	BfmeElem60 *_M_finish;
	BfmeElem60 *_M_end_of_storage;
};

BfmeElem60 *BfmeVec60::erase( BfmeElem60 *first, BfmeElem60 *last )
{
	BfmeElem60 *i = _STL::copy( last, _M_finish, first );
	_STL::_Destroy( i, _M_finish );
	_M_finish = i;
	return first;
}
