// cl: /DNDEBUG /MD /EHsc /Iinputs/vendor/stlport /D_STLP_USE_STATIC_LIB
// stlport
// Secondary-interface selectors at00608530/84B and00608630/99B.
// Constructor006086E0 and copy006089C0 establish the210-byte records.
// Matched findMappedSound witnesses the same module/Drawable relationship;
// both selectors call matchesObject006083A0 through ILT000420B9.
// Names retain addresses because the original method spellings are unknown.
// A selected item exposes its payload after its vptr; payload size is unknown.

#include <stl/_config.h>
#include <vector>

struct Rva00608530Sound;

struct Rva00608FE0Item
{
	virtual void release(bool now);
};

struct Rva00608FE0Element
{
	Rva00608FE0Element();
	Rva00608FE0Element(const Rva00608FE0Element &);
	~Rva00608FE0Element();
	char m_prefix[0x48];
	Rva00608FE0Item *m_items[0x6D];
	char m_map[0x0C];
	int m_field208;
	unsigned char m_field20C;
	char m_padding20D[3];
};

typedef char Rva00608FE0Extent[sizeof(Rva00608FE0Element) == 0x210 ? 1 : -1];

typedef _STL::vector<Rva00608FE0Element,
	_STL::allocator<Rva00608FE0Element> > Rva00608FE0Vector;

struct Rva00608530ModuleData
{
	virtual void anchor();
	unsigned int m_moduleTagNameKey;
	Rva00608FE0Vector m_soundUpgrades;
};

struct Rva00608530Drawable
{
	char m_prefix[0xFC];
	void *m_upgrade;
};

struct Rva00608530Primary
{
	virtual void anchor();
	Rva00608530ModuleData *m_moduleData;
	Rva00608530Drawable *m_drawable;
};

struct Rva006083A0SoundUpgrade
{
	bool matchesObject(void *object);
};

#pragma comment(linker, "/alternatename:?matchesObject@Rva006083A0SoundUpgrade@@QAE_NPAX@Z=?j_000420b9@@YAXXZ")

struct Rva00608530SoundSelectorInterface
{
	virtual Rva00608530Sound *getIndexedSound(unsigned int index) = 0;
	virtual void *findMappedSound(void *key) = 0;
	virtual bool getSelectedValue(unsigned int *value) = 0;
};

class Rva00608530SoundSelector : public Rva00608530Primary,
	public Rva00608530SoundSelectorInterface
{
public:
	virtual Rva00608530Sound *getIndexedSound(unsigned int index);
	virtual void *findMappedSound(void *key);
	virtual bool getSelectedValue(unsigned int *value);
};

Rva00608530Sound *Rva00608530SoundSelector::getIndexedSound(unsigned int index)
{
	Rva00608530ModuleData *data = m_moduleData;
	Rva00608530Drawable *drawable = m_drawable;
	void *upgrade = drawable->m_upgrade;
	if (upgrade == 0)
		return 0;

	Rva00608FE0Vector::iterator it = data->m_soundUpgrades.begin();
	Rva00608FE0Vector::iterator finish = data->m_soundUpgrades.end();
	for (; it != finish; ++it)
	{
		if (((Rva006083A0SoundUpgrade *)&*it)->matchesObject(upgrade))
		{
			Rva00608FE0Item *item = it->m_items[index];
			if (item == 0)
				continue;
			Rva00608530Sound *sound =
				(Rva00608530Sound *)((char *)item + 4);
			if (sound != 0)
				return sound;
		}
	}
	return 0;
}

bool Rva00608530SoundSelector::getSelectedValue(unsigned int *value)
{
	Rva00608530ModuleData *data = m_moduleData;
	Rva00608530Drawable *drawable = m_drawable;
	void *upgrade = drawable->m_upgrade;
	if (upgrade == 0)
		return false;

	Rva00608FE0Vector::iterator it = data->m_soundUpgrades.begin();
	Rva00608FE0Vector::iterator finish = data->m_soundUpgrades.end();
	for (; it != finish; ++it)
	{
		if (((Rva006083A0SoundUpgrade *)&*it)->matchesObject(upgrade))
		{
			*value = it->m_field208;
			if (it->m_field20C != 0)
				return true;
		}
	}
	return false;
}
