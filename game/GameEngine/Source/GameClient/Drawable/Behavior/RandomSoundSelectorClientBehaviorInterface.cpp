// cl: /DNDEBUG /MD /EHsc

typedef float Real;

struct RandomSoundSelectorSound
{
	char m_value[4];
};

struct RandomSoundSelectorEntry
{
	unsigned int m_key;
	RandomSoundSelectorSound m_sound;
};

struct BfmeKeySD;
struct BfmeSlotSD
{
	char m_value[4];
};

// Retail calls the STLport _Rb_tree<AsciiString, ...>::_M_find<AsciiString>
// body at 0x00142FD0 (ILT 0x00020E7D), matched in
// WWLib/RvaTreeFindAsciiString.cpp.  Only the declaration that body's name
// needs is spelled here; the key is the AsciiString the caller passes.
class AsciiString;
struct Rva00142FD0Value;
struct Rva00142FD0KeyOfValue;

namespace _STL
{
template <class T> struct less;
template <class T> class allocator;
template <class V> struct _Rb_tree_node;

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
public:
	template <class KT> _Rb_tree_node<Value> *find(const KT &key) const
	{
		return _M_find(key);
	}

private:
	template <class KT> _Rb_tree_node<Value> *_M_find(const KT &key) const;
};
}

typedef _STL::_Rb_tree<AsciiString, Rva00142FD0Value, Rva00142FD0KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva00142FD0Value> > Rva00142FD0Tree;

class BfmeMapSD
{
public:
	BfmeSlotSD *bfmeFindSD(BfmeKeySD *key) const
	{
		return reinterpret_cast<BfmeSlotSD *>(
			reinterpret_cast<const Rva00142FD0Tree *>(this)->find(
				*reinterpret_cast<const AsciiString *>(key)));
	}
	BfmeSlotSD *m_header;
	char m_pad04[8];
};

struct RandomSoundSelectorClientBehaviorModuleDataView
{
	char m_pad000[8];
	RandomSoundSelectorEntry *m_indexedSounds[109];
	BfmeMapSD m_soundMap;
	Real m_chance;
	unsigned int m_selectedValue;
	bool m_selectedFlag;

	RandomSoundSelectorSound *getIndexedSound(unsigned int index) const
	{
		RandomSoundSelectorEntry *entry = m_indexedSounds[index];
		if (entry != 0)
			return &entry->m_sound;
		return 0;
	}
};

class RandomSoundSelectorPrimary
{
public:
	virtual void anchor();
	RandomSoundSelectorClientBehaviorModuleDataView *m_moduleData;
	void *m_drawable;
};

class SoundSelectorInterface
{
public:
	virtual RandomSoundSelectorSound *getIndexedSound(unsigned int index) = 0;
	virtual BfmeSlotSD *findMappedSound(BfmeKeySD *key) = 0;
	virtual bool getSelectedValue(unsigned int *value) = 0;
};

class RandomSoundSelectorClientBehavior : public RandomSoundSelectorPrimary, public SoundSelectorInterface
{
public:
	virtual RandomSoundSelectorSound *getIndexedSound(unsigned int index);
	virtual BfmeSlotSD *findMappedSound(BfmeKeySD *key);
	virtual bool getSelectedValue(unsigned int *value);

private:
	void reroll();
	Real m_randomSelection;
	unsigned int m_lastFrame;
};

RandomSoundSelectorSound *RandomSoundSelectorClientBehavior::getIndexedSound(unsigned int index)
{
	RandomSoundSelectorClientBehaviorModuleDataView *data = m_moduleData;
	reroll();
	if (m_randomSelection >= data->m_chance)
		return 0;
	return data->getIndexedSound(index);
}

bool RandomSoundSelectorClientBehavior::getSelectedValue(unsigned int *value)
{
	RandomSoundSelectorClientBehaviorModuleDataView *data = m_moduleData;
	reroll();
	if (m_randomSelection >= data->m_chance)
		return false;
	*value = data->m_selectedValue;
	return data->m_selectedFlag;
}

BfmeSlotSD *RandomSoundSelectorClientBehavior::findMappedSound(BfmeKeySD *key)
{
	RandomSoundSelectorClientBehaviorModuleDataView *data = m_moduleData;
	reroll();
	if (m_randomSelection >= data->m_chance)
		return 0;
	BfmeMapSD *map = &data->m_soundMap;
	BfmeSlotSD *node = map->bfmeFindSD(key);
	if (node != map->m_header)
		return reinterpret_cast<BfmeSlotSD *>(reinterpret_cast<char *>(node) + 0x14);
	return 0;
}
