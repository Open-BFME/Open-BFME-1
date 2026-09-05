// cl: /DNDEBUG /MD /EHsc
//
// 111B twin of _STL::hashtable<pair<const Int,Int> >::_M_insert
// (stlport_hashtable_int_int_insert.cpp, retail 0x000D3430): identical
// shape (resize, inline bucket-index divide, node allocate, out-of-line
// construct, link into bucket, ++count), but the node size pushed before
// the allocate call is 0x68 here (not 0xc), so the value type is 0x64
// bytes, not the 8-byte pair<const int,int>. The construct callee is
// already pinned as ?bfmeInitSubEFA@@YAXPAX0@Z (0x0000129E) rather than a
// template _Construct instantiation, so it is declared and called
// directly instead of through a generic _Construct<> template.
// Address-derived: the real key/value types are unknown, only their total
// size (0x64) is recovered from the node-size immediate.

namespace _STL
{

// The node allocator's own _M_allocate is private in STLport, so the call is
// spelled through the free-function name the ledger already pins on the same
// body at 0x0082E540.
void *__cdecl vectorSmallAllocate(unsigned int bytes);

}

// retail 0x0000129E: out-of-line copy-construct of the 0x64-byte value type.
void __cdecl bfmeInitSubEFA(void *dest, void *src);

struct Rva001B0780Value
{
	char m_bytes[0x64];
};

// _BucketVector: a vector of void*, not of node pointers; size and indexing
// go through separate inline accessors, matching why retail reloads the
// start pointer after the divide instead of keeping it live.
class Rva001B0780Buckets
{
public:
	unsigned int size(void) const { return (unsigned int)(_M_finish - _M_start); }

	void *&operator[](unsigned int n) { return *(_M_start + n); }

	void **_M_start;					// +0x00
	void **_M_finish;					// +0x04
	void **_M_end_of_storage;				// +0x08
};

struct Rva001B0780Node
{
	Rva001B0780Node *_M_next;
	Rva001B0780Value _M_val;
};

class Rva001B0780Hashtable
{
public:
	typedef unsigned int size_type;

	Rva001B0780Value &_M_insert(const Rva001B0780Value &obj);

private:
	void resize(size_type numElementsHint);			// retail 0x000D10F0 family; here 0x00047FBE

	size_type bucketOf(const Rva001B0780Value &obj) const
	{
		unsigned int key = *(const unsigned int *)&obj;
		return key % _M_buckets.size();
	}

	Rva001B0780Node *_M_new_node(const Rva001B0780Value &obj)
	{
		Rva001B0780Node *n = (Rva001B0780Node *)_STL::vectorSmallAllocate(sizeof(Rva001B0780Node));
		n->_M_next = 0;
		bfmeInitSubEFA(&n->_M_val, (void *)&obj);
		return n;
	}

	char m_pad0[4];						// three empty functors, padded to +0x00
	Rva001B0780Buckets _M_buckets;				// +0x04
	size_type _M_num_elements;				// +0x10
};

Rva001B0780Value &Rva001B0780Hashtable::_M_insert(const Rva001B0780Value &obj)
{
	resize(_M_num_elements + 1);

	size_type n = bucketOf(obj);
	Rva001B0780Node *first = (Rva001B0780Node *)_M_buckets[n];
	Rva001B0780Node *tmp = _M_new_node(obj);
	tmp->_M_next = first;
	_M_buckets[n] = tmp;
	++_M_num_elements;
	return tmp->_M_val;
}
