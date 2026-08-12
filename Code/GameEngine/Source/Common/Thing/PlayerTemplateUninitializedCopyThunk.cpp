// cl: /DNDEBUG /MD /EHsc

class PlayerTemplate
{
private:
    unsigned char m_storage[0x124];
};

namespace _STL
{
struct __false_type
{
};

struct PlayerTemplateConstructShim
{
    static void construct(PlayerTemplate *destination, const PlayerTemplate &source);
};

template <class In, class Out>
Out __uninitialized_copy(In first, In last, Out destination, const __false_type &)
{
    Out current = destination;
    while (first != last) {
        PlayerTemplateConstructShim::construct(current, *first);
        ++first;
        ++current;
    }
    return current;
}

template PlayerTemplate *__uninitialized_copy<PlayerTemplate *, PlayerTemplate *>(
    PlayerTemplate *, PlayerTemplate *, PlayerTemplate *, const __false_type &);
}
