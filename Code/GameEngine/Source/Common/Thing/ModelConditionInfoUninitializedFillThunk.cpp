// cl: /DNDEBUG /MD /EHsc

struct ModelConditionInfo
{
    unsigned char m_storage[0xbc];
};

namespace _STL
{
struct __false_type
{
};

struct ModelConditionInfoConstructShim
{
    static void construct(ModelConditionInfo *destination, const ModelConditionInfo &value);
};

template <class ForwardIterator, class Size, class T>
ForwardIterator __uninitialized_fill_n(
    ForwardIterator first, Size count, const T &value, const __false_type &)
{
    ForwardIterator current = first;
    while (count > 0) {
        ModelConditionInfoConstructShim::construct(current, value);
        ++current;
        --count;
    }
    return current;
}

template ModelConditionInfo *__uninitialized_fill_n<ModelConditionInfo *, unsigned int, ModelConditionInfo>(
    ModelConditionInfo *, unsigned int, const ModelConditionInfo &, const __false_type &);
}
