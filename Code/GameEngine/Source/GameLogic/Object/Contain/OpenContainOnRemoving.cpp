// ?onRemoving@OpenContain@@UAEXPAVObject@@@Z
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <map>
// Open-BFME: OpenContain::onRemoving, retail 0x00227DC0, 525 bytes.
//
// The callback is the ContainModuleInterface secondary-base method.  Retail
// enters with that subobject in ECX; the owning OpenContain object is at
// `this - 0x20`, and its Object member is therefore at `this - 0x18`.
// OpenContain_onContaining.cpp proves the same receiver and Object ABI.
// BFME extends the two scoped audio events with rider-ID map cleanup, clearing
// model-condition bits 184..188, and a timed list of per-rider applications.
// The timestamp tree uses SIGNED comparisons (jl/jge in 0x002231C0), even
// though the Object ID field is an unsigned bit pattern. Its authentic
// STLport find/erase wrappers also preserve the returned-iterator lifetime.
// CaveContain::onRemoving at 0x00219FA0 calls this qualified base method, and
// OpenContain's secondary vtable 0x010AC038 slot +0x48 reaches this body.

#define _STLP_USE_STATIC_LIB 1

typedef int Int;
typedef unsigned int ObjectID;
typedef bool Bool;

enum
{
	BFME_SOUND_EXIT = 0x66,
	BFME_SOUND_FALLING = 0x6A
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AudioEventRTS &src); // ILT 0x00047B27
	~AudioEventRTS(); // ILT 0x00026F35
	void setObjectID(ObjectID id); // ILT 0x00019A6A

private:
	unsigned int m_unmodelled[0x70 / 4];
};

class ThingTemplate
{
public:
	const AudioEventRTS *getSound(Int index) const; // ILT 0x0001BFD1
};

template<int NUMBITS> class BitFlags
{
public:
 enum BogusInitType { kInit = 0 };
 BitFlags(BogusInitType tag,int a,int b,int c,int d,int e);
 unsigned int m_words[(NUMBITS+31)/32];
};
class Rva00367E30Sink { public: void apply(int*,int); };
class Object
{
public:
	virtual void unusedSlot00();
	virtual void unusedSlot01();
	virtual void unusedSlot02();
	virtual void unusedSlot03();
	virtual void unusedSlot04();
	virtual void unusedSlot05();
	virtual void unusedSlot06();
	virtual void unusedSlot07();
	virtual void unusedSlot08();
	virtual void unusedSlot09();
	virtual const ThingTemplate *getTemplate() const; // vtable +0x28

	ObjectID getID() const { return m_id; }
 void clearModelConditionFlags(const BitFlags<304>&);
 void applyBonus(int *bonus) { ((Rva00367E30Sink*)this)->apply(bonus,-1); }

private:
	unsigned char m_unmodelled[0x74 - 4];
	ObjectID m_id;
};

class AudioManager
{
public:
	virtual void unusedSlot00();
	virtual void unusedSlot01();
	virtual void unusedSlot02();
	virtual void unusedSlot03();
	virtual void unusedSlot04();
	virtual void unusedSlot05();
	virtual void unusedSlot06();
	virtual void unusedSlot07();
	virtual void unusedSlot08();
	virtual void unusedSlot09();
	virtual void unusedSlot10();
	virtual void unusedSlot11();
	virtual void unusedSlot12();
	virtual void unusedSlot13();
	virtual void unusedSlot14();
	virtual void unusedSlot15();
	virtual void unusedSlot16();
	virtual void addAudioEvent(const AudioEventRTS *event); // vtable +0x44
};

extern AudioManager *TheAudio;

class ContainModuleInterface
{
public:
	virtual void onRemoving(Object *obj) = 0;
};

class Rva00225BE0RiderMap { public: unsigned int erase(const Int &); unsigned char m_data[12]; };
class Rva00224870RiderMap { public: unsigned int erase(const Int &); unsigned char m_data[12]; };
struct RiderTimeNode { unsigned int m_color; RiderTimeNode *m_parent,*m_left,*m_right; ObjectID m_id; unsigned int m_frame; };
typedef _STL::map<Int,unsigned int> RiderTimeMap;
typedef RiderTimeMap::iterator RiderTimeIterator;
class Rva002231C0RiderTimeMap : public RiderTimeMap
{
public:

};
class OpenContainModuleData
{
public:
 unsigned char m_pad[0x158];
 int *m_bonusBegin;
 int *m_bonusEnd;
 int *m_bonusCapacity;
 unsigned int m_minimumFrames;
};
struct Rva012F0898GameLogic { unsigned char m_pad[0x3c]; unsigned int m_frame; };
extern Rva012F0898GameLogic *Rva012F0898TheGameLogic;
class __declspec(novtable) OpenContain : public ContainModuleInterface
{
public:
 virtual void onRemoving(Object *obj);
 unsigned char m_pad04[0x1c];
 Rva00225BE0RiderMap m_riderState;
 Rva00224870RiderMap m_riderNames;
 unsigned char m_pad38[0x70];
 Rva002231C0RiderTimeMap m_riderTimes;
private:
 Object *getObject() const { return *(Object **)((const char *)this - 0x18); }
 OpenContainModuleData *getModuleData() const { return *(OpenContainModuleData **)((const char *)this - 0x1c); }
};
void OpenContain::onRemoving(Object *rider)
{
 if (getObject()->getTemplate())
 {
  const ThingTemplate *exitTemplate = getObject()->getTemplate();
  AudioEventRTS exitSound = *exitTemplate->getSound(BFME_SOUND_EXIT);
  exitSound.setObjectID(getObject()->getID());
  TheAudio->addAudioEvent(&exitSound);
 }
 if (rider && rider->getTemplate())
 {
  const ThingTemplate *fallingTemplate = rider->getTemplate();
  AudioEventRTS fallingSound = *fallingTemplate->getSound(BFME_SOUND_FALLING);
  fallingSound.setObjectID(rider->getID());
  TheAudio->addAudioEvent(&fallingSound);
  m_riderState.erase(rider->getID());
  m_riderNames.erase(rider->getID());
  rider->clearModelConditionFlags(BitFlags<304>(BitFlags<304>::kInit,184,185,186,187,188));
  OpenContainModuleData *data = getModuleData();
  if (data->m_bonusBegin != data->m_bonusEnd && !m_riderTimes.empty())
  {
   RiderTimeIterator it; it = m_riderTimes.find((Int)rider->getID());
   if (it != m_riderTimes.end())
   {
    unsigned int entryFrame = ((RiderTimeNode *)it._M_node)->m_frame;
    m_riderTimes.erase(it);
    if (Rva012F0898TheGameLogic->m_frame-entryFrame > data->m_minimumFrames)
    {
     for (int *bonus = data->m_bonusBegin; bonus != data->m_bonusEnd; ++bonus)
      rider->applyBonus(bonus);
    }
   }
  }
 }
}
