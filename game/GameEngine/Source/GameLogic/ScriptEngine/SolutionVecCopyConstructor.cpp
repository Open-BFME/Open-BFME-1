// cl: /DNDEBUG /MD /EHsc
// SolutionVec (vector<pair<ObjectID, ObjectID> >) copy constructor, retail
// 0x002F8980, 82 bytes, emitted beside the ScriptActions code that uses it.
//
// Identity: ScriptActions::doLoadAllTransports (0x003014C0) calls it through
// ILT 0x00027B2E with ECX = its local and the matched
// PartitionSolver::getSolution() result (0x00094BF0, &m_bestSolution) as the
// argument -- Zero Hour's `SolutionVec solution = partition.getSolution();` --
// and later tears the local down as an 8-byte-element vector.
//
// The body is STLport's copy constructor: _Vector_base(count, allocator) then
// an uninitialized copy. The count is the raw finish-start pointer difference;
// with the size() accessor MSVC hoists the count above the get_allocator call.
// The allocator comes back by value into the dead parameter slot (ILT
// 0x0002EBC2, a returns-its-argument body at 0x002F19E0), is passed with the
// element count to the _Vector_base constructor (ILT 0x00015ABE, the tgrid
// _Vector_base(size_t, const allocator &) at 0x002F19F0), and the null test in
// front of each element is placement-new codegen.

inline void *operator new(unsigned int, void *place)
{
	return place;
}

enum ObjectID
{
};

namespace _STL
{
template <class First, class Second>
struct pair
{
	First first;
	Second second;
};

template <class Type>
class allocator
{
public:
	allocator();
	allocator(const allocator &);
};

template <class Type, class Allocator>
class _Vector_base
{
public:
	_Vector_base(unsigned int count, const Allocator &alloc);

	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;
};

template <class Type, class Allocator>
class vector : public _Vector_base<Type, Allocator>
{
public:
	Allocator get_allocator() const;

	vector(const vector &other)
		: _Vector_base<Type, Allocator>(other._M_finish - other._M_start, other.get_allocator())
	{
		const Type *last = other._M_finish;
		const Type *element = other._M_start;
		Type *cursor = this->_M_start;
		while (element != last)
		{
			new (cursor) Type(*element);
			++element;
			++cursor;
		}
		this->_M_finish = cursor;
	}
};

template class vector<pair<ObjectID, ObjectID>, allocator<pair<ObjectID, ObjectID> > >;
}
