// ?updateAnimationSounds@AnimationSoundClientBehavior@@QAEXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib

// stlport

#include <set>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef float Real;
typedef bool Bool;

extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *buf1, const void *buf2, unsigned int count);

extern const char g_bfmeEmptyAscii[];

#include "ascii_string.h"
template<> inline int StringBase<char>::compareNoCase(const StringBase<char> &str) const
{
    const int len = str.m_data ? str.m_data->length : 0;
    const char *data = str.m_data ? &str.m_data->data[0] : g_bfmeEmptyAscii;
    const int myLen = m_data ? m_data->length : 0;
    const char *myData = m_data ? &m_data->data[0] : g_bfmeEmptyAscii;
    int result = _memicmp(myData, data, myLen < len ? myLen : len);
    if (result != 0) return result;
    return myLen - len;
}

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *);
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *);
class Rva006059F0Counted {
public:
    virtual ~Rva006059F0Counted();
    void Release_Ref() { if (InterlockedDecrement(&m_refCount) <= 0) delete this; }
    long m_refCount;
};
class EventNameRef006059F0 {
public:
    EventNameRef006059F0() : m_eventRef(0) {}
    // ??0EventNameRef006059F0@@QAE@ABV0@@Z absent-from-retail
    EventNameRef006059F0(const EventNameRef006059F0 &that) : m_eventRef(that.m_eventRef) {
        if (m_eventRef) InterlockedIncrement(&m_eventRef->m_refCount);
    }
    EventNameRef006059F0 &operator=(const EventNameRef006059F0 &that);
    ~EventNameRef006059F0() { if (m_eventRef) m_eventRef->Release_Ref(); }
    Rva006059F0Counted *m_eventRef;
};

#include "coord3d.h"
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
inline Coord3D::Coord3D(const Coord3D &that) { x = that.x; y = that.y; z = that.z; }


enum DrawableID
{
	INVALID_DRAWABLE_ID = 0
};

// The complete constructor and copy helper establish this 0x60-byte record.
// The +4 field owns a counted audio reference; comparison reads +0 and +8.
struct Rva00605800Value
{
	Rva00605800Value(const AsciiString &key, Real weight);
	~Rva00605800Value();

	AsciiString m_key;
	EventNameRef006059F0 m_eventName;
	Real m_weight;
	Int m_rangeA[10];
	Int m_rangeB[10];
	Bool m_gated;
};

struct Rva00605800Less
{
	bool operator()(const Rva00605800Value &left, const Rva00605800Value &right) const
	{
		int c = left.m_key.StringBase<char>::compareNoCase(right.m_key);
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

class DrawModule;

class Drawable
{
public:
	const Coord3D *getPosition(void) const;
	const DrawModule **getDrawModules(void) const;
	DrawableID getID(void) const;

	UnsignedByte m_unmodelled000[0x143];
	Bool m_143;
	UnsignedByte m_unmodelled144[0x250 - 0x144];
	Gen0003C2E5 m_250;
};

// Opaque storage for the decoded 0x70-byte audio record.
class AudioEvent006059F0
{
public:
	AudioEvent006059F0(const EventNameRef006059F0 &eventName, DrawableID drawableID);
	~AudioEvent006059F0();

private:
	unsigned int m_storage[28];
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
	virtual UnsignedInt addAudioEvent006059F0(const AudioEvent006059F0 *event);
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
	virtual const Coord3D *getListenerPosition006059F0() const;
};

// Retail 0x012ED668 is ?TheAudio@@3PAVAudioManager@@A (data_rows.csv,
// Common/Audio/GameAudio.cpp); TheAudioClientUpdate was only a pin.
class AudioManager;
extern AudioManager *TheAudio;
#define TheAudioClientUpdate ( *(Rva005A00B0AudioClient **)&TheAudio )

class U4Owner00604C00;
class U4Notify
{
public:
	void noteOwner(U4Owner00604C00 *owner);
};

class BfmeResetSubsystem;
extern BfmeResetSubsystem *g_animationSoundClientBehaviorGlobal;

class AnimationSoundClientBehavior
{
public:
	void updateAnimationSounds();
	// ?getModuleData006059F0@AnimationSoundClientBehavior@@QBEPAUModuleData006059F0@@XZ absent-from-retail
	__forceinline ModuleData006059F0 *getModuleData006059F0() const { return m_moduleData; }

	UnsignedByte m_unmodelled00[4];
	ModuleData006059F0 *m_moduleData;
	Drawable *m_drawable;
	UnsignedByte m_unmodelled0C[4];
	Real m_rangeSqr;
	AnimationSoundClientBehavior *m_next;
	AnimationSoundClientBehavior *m_prev;
};

struct Rva006059F0Delta {
    Real dx, dy, dz;
    // ??0Rva006059F0Delta@@QAE@MMM@Z absent-from-retail
    __forceinline Rva006059F0Delta(Real x, Real y, Real z) : dx(x), dy(y), dz(z) {}
    // ?lengthSqr@Rva006059F0Delta@@QBEMXZ absent-from-retail
    __forceinline Real lengthSqr() const { return dx * dx + dy * dy + dz * dz; }
};
// ?delta006059F0@@YAXPAURva006059F0Delta@@MMM@Z absent-from-retail
// The output parameter precedes the independent deltas to preserve their evaluation order.
static __forceinline void delta006059F0(Rva006059F0Delta *result, Real dz, Real dy, Real dx) { result->dx = dx; result->dy = dy; result->dz = dz; }

void AnimationSoundClientBehavior::updateAnimationSounds()
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
		Rva006059F0Delta delta(0.0f, 0.0f, 0.0f);
		delta006059F0(&delta, listener.z - pos->z, listener.y - pos->y, listener.x - pos->x);
		inRange = !(delta.lengthSqr() > m_rangeSqr);
	}
	if (!inRange)
	{
		if (g_animationSoundClientBehaviorGlobal)
			((U4Notify *)g_animationSoundClientBehaviorGlobal)->noteOwner((U4Owner00604C00 *)this);
		return;
	}
	Rva00605800Tree *sounds = &getModuleData006059F0()->m_sounds;

	const DrawModule **first = draw->getDrawModules();
	if (first)
	{
		const DrawModule **modules = first;
		if (*first)
		{
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
					Range006059F0 *range = &ranges[0];
					for (Int k = 0; k < 2; ++k, ++range)
					{
						if (range->m_start == range->m_end)
							continue;
						Real maxWeight = bfmeMax(range->m_start, range->m_end);
						Rva00605800Value key(name, bfmeMin(range->m_start, range->m_end));
						Rva00605800Tree::iterator it = sounds->lower_bound(key);
						Rva00605800Tree::iterator end = sounds->end();
						while (it != end)
						{
							const Rva00605800Value &value = *it;
							if (value.m_key.StringBase<char>::compareNoCase(name) != 0)
								break;
							if (!(it->m_weight <= maxWeight))
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
	}
}
