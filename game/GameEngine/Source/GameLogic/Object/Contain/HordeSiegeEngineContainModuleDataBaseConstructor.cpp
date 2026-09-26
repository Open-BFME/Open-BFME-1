// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// BFME siege horde module data: native STLport list and six KindOfMask fields.
#include <list>
#include <bitset>
#include "ascii_string.h"

class KindOfMask { public: std::bitset<181> m_bits; KindOfMask() {} };
extern const KindOfMask KINDOFMASK_NONE;
class EmotionTrackerUpdateName { public: void setPolicies(KindOfMask, KindOfMask); };
struct BfmeAttributePlainBlock { unsigned int m_values[6]; };
class BfmeSecondPlainMember { public: void setSecondPlain(BfmeAttributePlainBlock); };
class Gen003A0410 { public: Gen003A0410(); ~Gen003A0410(); int m_value; };
class OpenContainModuleData { public: OpenContainModuleData(); virtual ~OpenContainModuleData(); char m_before168[0x168 - 4]; };
struct SiegeLink { void *m_first, *m_second; };
class HordeSiegeEngineContainModuleDataBase : public OpenContainModuleData {
public:
 HordeSiegeEngineContainModuleDataBase();
 virtual ~HordeSiegeEngineContainModuleDataBase();
private:
 int m_zero168, m_zero16c;
 AsciiString m_name;
 _STL::list<SiegeLink> m_entries;
 int m_zero178, m_zero17c;
 KindOfMask m_accept0, m_accept1, m_accept2, m_accept3, m_accept4;
 unsigned char m_flag1f8, m_flag1f9, m_flag1fa, m_flag1fb;
 unsigned char m_flag1fc, m_flag1fd, m_flag1fe, m_flag1ff;
 int m_word200;
 unsigned char m_flag204;
 unsigned char m_pad205[3];
 int m_word208;
 Gen003A0410 m_attribute;
 unsigned char m_flag210, m_flag211;
 unsigned char m_pad212[2];
 int m_word214,m_word218;
 unsigned char m_flag21c;
 unsigned char m_pad21d[3];
 float m_value220;
};
HordeSiegeEngineContainModuleDataBase::HordeSiegeEngineContainModuleDataBase() {
 m_zero168=0;
 m_flag1fa=1; m_flag1fb=0; m_flag1fc=0; m_flag1fd=1; m_flag1fe=0;
 m_zero16c=0; m_zero178=0; m_zero17c=0;
 m_flag1f8=1; m_flag1f9=0;
 m_accept0 = KINDOFMASK_NONE;
 m_accept1 = KINDOFMASK_NONE;
 m_accept2 = KINDOFMASK_NONE;
 m_accept3 = KINDOFMASK_NONE;
 m_accept4 = KINDOFMASK_NONE;
 m_word208=-1;
 ((EmotionTrackerUpdateName*)((char*)this + 0x114))->setPolicies(KINDOFMASK_NONE,KINDOFMASK_NONE);
 ((BfmeSecondPlainMember*)((char*)this + 0x118))->setSecondPlain(*(const BfmeAttributePlainBlock*)&KINDOFMASK_NONE);
 m_flag210=0; m_flag211=0; m_word214=0; m_word218=0;
 ((EmotionTrackerUpdateName*)&m_attribute)->setPolicies(KINDOFMASK_NONE,KINDOFMASK_NONE);
 m_flag21c=0;
 m_word200=0;
 m_value220=0.7f;
 m_flag204=1;
}
