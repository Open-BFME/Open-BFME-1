// ?update006059F0@Node004092A0@@QAEXXZ
// partial score=0.953 date=2026-09-28
// ?update006059F0@Node004092A0@@QAEXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x006059F0, 903 bytes (ret at +0x386; the gen row says 896 but stops
// 7 bytes short of the epilogue). Only caller: SpatialList004092A0::update
// (retail 0x0040936B via ILT 0x0003765F) walks its owner list and calls this
// on each node. The node is the AnimationSoundClientBehavior owner: out of
// listener range (or drawable flag +0x143 clear) it hands itself to the
// registry's U4Notify::noteOwner; in range it walks the drawable's draw
// modules, and for every named sound range queries the module-data sound set
// (tree 0x00605550) and fires an audio event per matching entry.
//
// LINK TODO before landing: the key ctor/dtor (0x00605690 via ILT 0x00040C28,
// 0x00605080 via ILT 0x000014D8) and the audio event ctor (0x000B45E0 via ILT
// 0x0000AFBF) need pins under the TU-local names used here.

#include <set>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef float Real;
typedef bool Bool;

extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *buf1, const void *buf2, unsigned int count);

extern const char g_bfmeEmptyAscii[];

class BFMERetailAsciiString
{
public:
	void releaseBuffer(void);
};

class AsciiString
{
public:
	AsciiString(void) : m_data(0) {}
	~AsciiString(void)
	{
		((BFMERetailAsciiString *)this)->releaseBuffer();
	}
	int compareNoCase(const AsciiString &str) const
	{
		const int len = str.m_data ? str.m_data->length : 0;
		const char *data = str.m_data ? &str.m_data->data[0] : g_bfmeEmptyAscii;
		const int myLen = m_data ? m_data->length : 0;
		const char *myData = m_data ? &m_data->data[0] : g_bfmeEmptyAscii;
		int result = _memicmp(myData, data, myLen < len ? myLen : len);
		if (result != 0)
			return result;
		return myLen - len;
	}

private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};

	Header *m_data;
};

struct Coord3D
{
	Real x, y, z;
};

enum DrawableID
{
	INVALID_DRAWABLE_ID = 0
};

// Sound entry of the animation-sound set: the tree at 0x00605550 orders it
// by name (case-insensitive) then weight; 0x00605690 constructs it and
// 0x00605080 destroys it (the tree's node destructor 0x00605820 reaches the
// same body through ILT 0x000014D8).
struct Rva00605800Value
{
	Rva00605800Value(const AsciiString &key, Real weight);
	~Rva00605800Value();

	AsciiString m_key;
	AsciiString m_eventName;
	Real m_weight;
	Int m_rangeA[10];
	Int m_rangeB[10];
	Bool m_gated;
};

struct Rva00605800Less
{
	bool operator()(const Rva00605800Value &left, const Rva00605800Value &right) const
	{
		int c = left.m_key.compareNoCase(right.m_key);
		if (c < 0)
			return true;
		if (c > 0)
			return false;
		return left.m_weight < right.m_weight;
	}
};

typedef _STL::_Rb_tree<Rva00605800Value, Rva00605800Value, _STL::_Identity<Rva00605800Value>,
	Rva00605800Less, _STL::allocator<Rva00605800Value> > Rva00605800Tree;

struct ModuleData006059F0
{
	UnsignedByte m_unmodelled00[8];
	Rva00605800Tree m_sounds;
};

class Gen0003C2E5
{
public:
	Bool test(void *a, void *b);
};

class Drawable
{
public:
	const Coord3D *getPosition(void) const;
	void **getDrawModules(void) const;
	DrawableID getID(void) const;

	UnsignedByte m_unmodelled000[0x143];
	Bool m_143;
	UnsignedByte m_unmodelled144[0x250 - 0x144];
	Gen0003C2E5 m_250;
};

// Address-derived 0x70-byte view of the audio event built per sound entry.
class AudioEvent006059F0
{
public:
	AudioEvent006059F0(const AsciiString &eventName, DrawableID drawableID);
	~AudioEvent006059F0();

private:
	unsigned __int64 m_storage[14];
};

template <class T> inline const T &bfmeMax(const T &a, const T &b) { return a > b ? a : b; }
template <class T> inline const T &bfmeMin(const T &a, const T &b) { return a < b ? a : b; }

struct Range006059F0
{
	Real m_start;
	Real m_end;
};

class SoundSource006059F0
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08();
	virtual Int getCount006059F0();
	virtual AsciiString getName006059F0(Int index);
	virtual void slot0B(); virtual void slot0C();
	virtual void getRanges006059F0(Int index, Range006059F0 *first, Range006059F0 *second);
};

class DrawModule006059F0
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot0A(); virtual void slot0B();
	virtual void slot0C(); virtual void slot0D(); virtual void slot0E(); virtual void slot0F();
	virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot1A(); virtual void slot1B();
	virtual void slot1C(); virtual void slot1D(); virtual void slot1E(); virtual void slot1F();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	virtual SoundSource006059F0 *getSoundSource006059F0();
};

struct Rva005A00B0AudioClient
{
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot0A(); virtual void slot0B();
	virtual void slot0C(); virtual void slot0D(); virtual void slot0E(); virtual void slot0F();
	virtual void slot10();
	virtual void addAudioEvent006059F0(AudioEvent006059F0 *event);
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot1A(); virtual void slot1B(); virtual void slot1C(); virtual void slot1D();
	virtual void slot1E(); virtual void slot1F(); virtual void slot20(); virtual void slot21();
	virtual void slot22(); virtual void slot23(); virtual void slot24(); virtual void slot25();
	virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot2A(); virtual void slot2B(); virtual void slot2C(); virtual void slot2D();
	virtual void slot2E(); virtual void slot2F(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot3A(); virtual void slot3B(); virtual void slot3C(); virtual void slot3D();
	virtual void slot3E(); virtual void slot3F(); virtual void slot40(); virtual void slot41();
	virtual void slot42();
	virtual const Coord3D *getListenerPosition006059F0();
};

extern Rva005A00B0AudioClient *TheAudioClientUpdate;

class U4Owner00604C00;
class U4Notify
{
public:
	void noteOwner(U4Owner00604C00 *owner);
};

class BfmeResetSubsystem;
extern BfmeResetSubsystem *g_animationSoundClientBehaviorGlobal;

struct Node004092A0
{
	void update006059F0();

	UnsignedByte m_unmodelled00[4];
	ModuleData006059F0 *m_moduleData;
	Drawable *m_drawable;
	UnsignedByte m_unmodelled0C[4];
	Real m_rangeSqr;
	Node004092A0 *m_next;
	Node004092A0 *m_prev;
};

void Node004092A0::update006059F0()
{
	Drawable *draw = m_drawable;
	if (!draw)
		return;

	Bool inRange = false;
	if (draw->m_143)
	{
		if (!TheAudioClientUpdate)
			return;
		Coord3D listener = *TheAudioClientUpdate->getListenerPosition006059F0();
		const Coord3D *pos = draw->getPosition();
		Real dx = listener.x - pos->x;
		Real dy = listener.y - pos->y;
		Real dz = listener.z - pos->z;
		inRange = !(dx * dx + dy * dy + dz * dz > m_rangeSqr);
	}
	if (!inRange)
	{
		if (g_animationSoundClientBehaviorGlobal)
			((U4Notify *)g_animationSoundClientBehaviorGlobal)->noteOwner((U4Owner00604C00 *)this);
		return;
	}
	Rva00605800Tree *sounds = &m_moduleData->m_sounds;
	void **modules = draw->getDrawModules();
	if (!modules || !*modules)
		return;

	do
	{
		SoundSource006059F0 *source = ((DrawModule006059F0 *)*modules)->getSoundSource006059F0();
		if (!source)
			continue;
		Int count = source->getCount006059F0();
		for (Int i = 0; i < count; ++i)
		{
			AsciiString name = source->getName006059F0(i);
			Range006059F0 ranges[2];
			ranges[0].m_start = 0.0f;
			ranges[0].m_end = 0.0f;
			ranges[1].m_start = 0.0f;
			ranges[1].m_end = 0.0f;
			source->getRanges006059F0(i, &ranges[0], &ranges[1]);
			for (Int k = 0; k < 2; ++k)
			{
				Range006059F0 *range = &ranges[k];
				if (range->m_start == range->m_end)
					continue;
				Real maxWeight = bfmeMax(range->m_start, range->m_end);
				Rva00605800Value key(name, bfmeMin(range->m_start, range->m_end));
				Rva00605800Tree::iterator it = sounds->lower_bound(key);
				Rva00605800Tree::iterator end = sounds->end();
				while (it != end)
				{
					const Rva00605800Value &value = *it;
					if (value.m_key.compareNoCase(name) != 0)
						break;
					if (!(value.m_weight <= maxWeight))
						break;
					++it;
					if (value.m_weight == range->m_start)
						continue;
					if (value.m_gated && !draw->m_250.test((void *)value.m_rangeA, (void *)value.m_rangeB))
						continue;
					AudioEvent006059F0 event(value.m_eventName, draw->getID());
					TheAudioClientUpdate->addAudioEvent006059F0(&event);
				}
			}
		}
	} while (*++modules);
}
