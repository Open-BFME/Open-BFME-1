// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
};
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventInfo.h
struct AudioEventInfo
{
};

namespace _STL
{
template <class First, class Second>
struct pair
{
};
template <class T>
struct _Select1st
{
};
template <class T>
class allocator
{
};
template <class Value, class Key, class Hash, class Select, class Equal, class Alloc>
class hashtable
{
	unsigned int _M_bkt_num_key(Key const &, unsigned int) const;
};

class AudioEventHashtableBktNumKeyShim
{
public:
	unsigned int bkt_num_key(AsciiString const &key, unsigned int n) const;
};

template <class Value, class Key, class Hash, class Select, class Equal, class Alloc>
unsigned int hashtable<Value, Key, Hash, Select, Equal, Alloc>::_M_bkt_num_key(Key const &key, unsigned int n) const
{
	return ((AudioEventHashtableBktNumKeyShim const *)this)->bkt_num_key((AsciiString const &)key, n);
}
}

namespace rts
{
template <class T>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/STLTypedefs.h
struct hash
{
};
template <class T>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/STLTypedefs.h
struct equal_to
{
};
}

typedef _STL::pair<const AsciiString, AudioEventInfo *> AudioEventPair;
typedef _STL::hashtable<AudioEventPair, AsciiString, rts::hash<AsciiString>, _STL::_Select1st<AudioEventPair>, rts::equal_to<AsciiString>, _STL::allocator<AudioEventPair> > AudioEventHashtable;
template unsigned int AudioEventHashtable::_M_bkt_num_key(AsciiString const &, unsigned int) const;
