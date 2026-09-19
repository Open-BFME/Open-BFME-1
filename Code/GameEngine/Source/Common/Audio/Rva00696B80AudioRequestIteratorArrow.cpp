// cl: /O2 /DNDEBUG /MD /EHsc
// STLport list iterator body at retail RVA 0x00696B80.
// The neighboring GameAudio.cpp rows identify the AudioRequest iterator family.

struct AudioRequest;

namespace _STL
{
template <class T>
struct _Nonconst_traits
{
};

template <class T, class Traits>
struct _List_iterator
{
	struct _List_node_base
	{
		_List_node_base *m_next;
		_List_node_base *m_prev;
	};

	_List_node_base *m_node;

	T *operator->() const
	{
		return (T *)((char *)m_node + 8);
	}
};
}

template AudioRequest **_STL::_List_iterator<AudioRequest *,
	_STL::_Nonconst_traits<AudioRequest *> >::operator->() const;
