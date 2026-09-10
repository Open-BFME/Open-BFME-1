// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

class LargeGroupAudioKeyMap
{
public:
	LargeGroupAudioKeyMap(void);
	LargeGroupAudioKeyMap(const LargeGroupAudioKeyMap &other);
	~LargeGroupAudioKeyMap(void);

	void bfmeMerge(const LargeGroupAudioKeyMap &other);

private:
	void *m_bfmeData[3];
};

class LargeGroupAudioUpdateModuleData
{
public:
	static LargeGroupAudioKeyMap bfmeCollectRegisteredKeyMap(void);

private:
	void *m_bfmeVtable;
	unsigned int m_bfmeBaseValue;
	LargeGroupAudioKeyMap m_keys;
};

typedef LargeGroupAudioUpdateModuleData *LargeGroupAudioUpdateModuleDataPtr;
typedef _STL::_Rb_tree<LargeGroupAudioUpdateModuleDataPtr,
	LargeGroupAudioUpdateModuleDataPtr,
	_STL::_Identity<LargeGroupAudioUpdateModuleDataPtr>,
	_STL::less<LargeGroupAudioUpdateModuleDataPtr>,
	_STL::allocator<LargeGroupAudioUpdateModuleDataPtr> >
	LargeGroupAudioUpdateModuleDataRegistry;

// The independently matched constructors insert `this` into the tree at
// 0x012EFFA0 and the matched destructor removes it.  Each node's object has the
// LargeGroupAudioKeyMap member at +0x08, proving both the owner and operation.
LargeGroupAudioKeyMap
LargeGroupAudioUpdateModuleData::bfmeCollectRegisteredKeyMap(void)
{
	LargeGroupAudioKeyMap result;
	typedef _STL::_Rb_tree_node<LargeGroupAudioUpdateModuleDataPtr> RegistryNode;
	_STL::_Rb_tree_node_base *end =
		*(_STL::_Rb_tree_node_base **)0x012EFFA0;
	RegistryNode *it = (RegistryNode *)end->_M_left;

	for (; it != end; it = (RegistryNode *)_STL::_Rb_global<bool>::_M_increment(it))
	{
		result.bfmeMerge(it->_M_value_field->m_keys);
	}

	return result;
}
