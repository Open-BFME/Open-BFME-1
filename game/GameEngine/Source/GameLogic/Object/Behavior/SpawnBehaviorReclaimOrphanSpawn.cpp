// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// BFME's SpawnBehavior keeps its primary object/module pointers at +0x08 and
// +0x04.  This TU-local view leaves the shared behavior headers untouched.

#include <string.h>

#pragma intrinsic(memcmp)

typedef int Int;
typedef float Real;
typedef unsigned int ObjectID;

template <typename T> class StringBase
{
	friend class AsciiString;

public:
	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

private:
	StringBase(const T *text);
	void releaseBuffer();
	void set(const StringBase<T> &source);

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}

	~AsciiString() { releaseBuffer(); }

	int compare(const AsciiString &right) const
	{
		const StringBase<char> *self = (const StringBase<char> *)this;
		const StringBase<char> *that = (const StringBase<char> *)&right;
		int thatLength = that->m_data ? that->m_data->length : 0;
		const char *thatData = that->m_data ? &that->m_data->data[0] : "";
		int thisLength = self->m_data ? self->m_data->length : 0;
		const char *thisData = self->m_data ? &self->m_data->data[0] : "";
		int length = thisLength < thatLength ? thisLength : thatLength;
		int result = memcmp(thisData, thatData, length);
		if (result != 0)
			return result;
		return thisLength - thatLength;
	}

	AsciiString &operator=(const AsciiString &source)
	{
		((StringBase<char> *)this)->set(
			*(const StringBase<char> *)&source);
		return *this;
	}
};

class Object;
class Player;
class ThingTemplate;

class Player
{
public:
	void iterateObjects(void (__cdecl *callback)(Object *, void *), void *userData) const;
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

#define TheThingFactory (*(ThingFactory **)0x012EF1D8)

extern int __cdecl findClosestOrphan(Object *object, void *userData);

class Rva0020B860SpawnBehaviorModuleData
{
public:
    class NameVector
    {
    public:
        AsciiString *begin() const { return m_begin; }
        AsciiString *end() const { return m_end; }

    private:
        AsciiString *m_begin;
        AsciiString *m_end;
        AsciiString *m_capacity;
    };

private:
	unsigned char m_pad00[0x20];

public:
	NameVector m_spawnTemplateNameData;
};

class Rva0020B860ObjectModule
{
protected:
       void *m_vtable;
       const Rva0020B860SpawnBehaviorModuleData *m_moduleData;
       Object *m_object;
};

class Rva0020B860UpdateModule : public Rva0020B860ObjectModule
{
public:
	Object *getObject()
	{
		return m_object;
	}

	const Rva0020B860SpawnBehaviorModuleData *getSpawnBehaviorModuleData()
	{
		return m_moduleData;
	}
};

class Rva0020B860SpawnBehavior : public Rva0020B860UpdateModule
{
public:
	// ?reclaimOrphanSpawn@SpawnBehavior@@AAEPAVObject@@XZ
	Object *reclaimOrphanSpawn();
};

#define BIG_DISTANCE 99999999.9f

class OrphanData
{
public:
	OrphanData()
	{
		m_matchTemplate = 0;
		m_source = 0;
		m_closest = 0;
		m_closestDistSq = BIG_DISTANCE;
	}

	const ThingTemplate *m_matchTemplate;
	Object *m_source;
	Object *m_closest;
	Real m_closestDistSq;
};

// ?reclaimOrphanSpawn@SpawnBehavior@@AAEPAVObject@@XZ
Object *Rva0020B860SpawnBehavior::reclaimOrphanSpawn()
{
	Player *player = getObject()->getControllingPlayer();
	const Rva0020B860SpawnBehaviorModuleData *md = getSpawnBehaviorModuleData();
	OrphanData orphanData;
	AsciiString prevName((const char *)0x0107301C);
	for (AsciiString *tempName = md->m_spawnTemplateNameData.begin();
		tempName != md->m_spawnTemplateNameData.end(); ++tempName)
	{
		if (prevName.compare(*tempName))
			continue;
		orphanData.m_matchTemplate = TheThingFactory->findTemplate(*tempName);
		orphanData.m_source = getObject();
		orphanData.m_closest = 0;
		orphanData.m_closestDistSq = BIG_DISTANCE;
		player->iterateObjects(
			(void (__cdecl *)(Object *, void *))findClosestOrphan,
			&orphanData);
		prevName = *tempName;
	}
	return orphanData.m_closest;
}
