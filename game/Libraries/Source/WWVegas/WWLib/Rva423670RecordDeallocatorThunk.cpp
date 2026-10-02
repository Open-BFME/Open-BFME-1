void __cdecl operator delete(void *);
struct Rva423670RecordStorage;

namespace _STL
{
template <bool __threads, int __inst>
class __node_alloc
{
	friend struct ::Rva423670RecordStorage;
	static void _M_deallocate(void *block, unsigned int bytes);
};
}

struct Rva423670Record
{
	unsigned char data[24];
};

struct Rva423670RecordStorage
{
	void deallocate();

	Rva423670Record *begin;
	Rva423670Record *current;
	Rva423670Record *end;
};

// ?d_00423670@@YAXXZ
void Rva423670RecordStorage::deallocate()
{
	if (begin != 0) {
		const unsigned int bytes = (end - begin) * sizeof(Rva423670Record);
		if (bytes > 128) {
			operator delete(begin);
		} else {
			_STL::__node_alloc<true, 0>::_M_deallocate(begin, bytes);
		}
	}
}
