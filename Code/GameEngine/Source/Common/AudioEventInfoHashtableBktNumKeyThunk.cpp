// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventInfo.h
struct AudioEventInfo
{
};

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

template <class Value, class Key, class Hash, class Extract, class Equal, class Alloc>
class hashtable
{
	unsigned int _M_bkt_num_key(const Key &, unsigned int) const;
};

class AudioEventInfoBktNumKeyShim
{
public:
	unsigned int bkt_num_key(const AsciiString &key, unsigned int n) const;
};

template <class Value, class Key, class Hash, class Extract, class Equal, class Alloc>
unsigned int hashtable<Value, Key, Hash, Extract, Equal, Alloc>::_M_bkt_num_key(const Key &key, unsigned int n) const
{
	return ((AudioEventInfoBktNumKeyShim const *)this)->bkt_num_key((const AsciiString &)key, n);
}
}

typedef _STL::pair<const AsciiString, AudioEventInfo *> AudioEventInfoPair;
typedef _STL::hashtable<AudioEventInfoPair, AsciiString, rts::hash<AsciiString>, _STL::_Select1st<AudioEventInfoPair>, rts::equal_to<AsciiString>, _STL::allocator<AudioEventInfoPair> > AudioEventInfoHashtable;
template unsigned int AudioEventInfoHashtable::_M_bkt_num_key(const AsciiString &, unsigned int) const;
