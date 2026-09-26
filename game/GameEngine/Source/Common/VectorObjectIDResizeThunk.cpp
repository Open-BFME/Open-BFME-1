// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift vector<ObjectID>::resize __emit thunk to clean C++.
// STLport shape: shrink goes through erase(begin()+n, end()), whose
// copy(__last, end(), __first) range is empty by construction (__last==end()),
// yielding the dead zero-count move loop; grow calls _M_fill_insert (matched).

enum ObjectID {};

namespace _STL
{

template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class vector
{
    Type *_M_start;
    Type *_M_finish;
    Type *_M_end_of_storage;

    static Type *copy(Type *first, Type *last, Type *result)
    {
        int n = (int)(last - first);
        for (; n > 0; --n) {
            *result = *first;
            ++first;
            ++result;
        }
        return result;
    }

public:
    unsigned int size() const { return (unsigned int)(_M_finish - _M_start); }
    Type *begin() { return _M_start; }
    Type *end() { return _M_finish; }

    Type *erase(Type *first, Type *last)
    {
        Type *i = copy(last, end(), first);
        _M_finish = i;
        return first;
    }

    void _M_fill_insert(Type *pos, unsigned int n, const Type &x);

    void resize(unsigned int new_size, const Type x)
    {
        if (new_size < size())
            erase(begin() + new_size, end());
        else
            _M_fill_insert(end(), new_size - size(), x);
    }
};

// ?resize@?$vector@W4ObjectID@@V?$allocator@W4ObjectID@@@_STL@@@_STL@@QAEXIABW4ObjectID@@@Z
// ?resize@?$vector@W4ObjectID@@V?$allocator@W4ObjectID@@@_STL@@@_STL@@QAEXIW4ObjectID@@@Z
template void vector<ObjectID, allocator<ObjectID> >::resize(unsigned int, const ObjectID);

}
