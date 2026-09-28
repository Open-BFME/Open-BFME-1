// ?rva0027bf60@AIUpdateInterface@@QAEHXZ
// partial score=0.56 date=2026-09-28
// cl: /O2 /Ob1 /DNDEBUG /MD /EHs-c-
// Retry of retail 0x0027BF60. Corrected overlapping model flags at +0x110,
// unsigned template count, bit-not-set branch polarity, native override chain,
// and rva002774c0 ABI. Remaining frame and control-flow differences are banked.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

class Overridable {
public: virtual ~Overridable();
 const Overridable *getFinalOverride() const { if(next) return next->getFinalOverride(); return this; }
 Overridable *next;
};
template<class T> class OVERRIDE { public: const T* operator->() const { if(!value) return 0; return (const T*)value->getFinalOverride(); } operator const T*() const { return operator->(); } const T *value; };
class ThingTemplate : public Overridable
{
public:
	char m_bfmeUnreconstructed_008[0x3E8-8];
	Real getRange() const { return m_bfmeRangeSq; }
 Real m_bfmeRangeSq;						///< retail this+0x3E8
	char m_bfmeUnreconstructed_3EC[0x42C - 0x3EC];
	UnsignedInt getCount() const { return m_bfmeHalfCountBase; }
 UnsignedInt m_bfmeHalfCountBase;					///< retail this+0x42C
};

class Thing
{
public:
	const ThingTemplate *getTemplate(void) const;			// ILT 0x000084B8
};

class BFMESelectionStatusBits
{
public:
	Bool test(UnsignedInt index) const;				// ILT 0x0003AB20
};

class BfmeOwnerVNI
{
public:
	void bfmeApply1VNI(void);					// ILT 0x0002191D
};

class BfmeBlockVKQ
{
public:
	char bfmeAnyVKQ(const BfmeBlockVKQ &other);
 __forceinline unsigned test(unsigned i) const { return m_bfmeArr[i>>5] & (1u<<(i&31)); }
 __forceinline void set(unsigned i) { m_bfmeArr[i>>5] |= 1u<<(i&31); }
 __forceinline void reset(unsigned i) { m_bfmeArr[i>>5] &= ~(1u<<(i&31)); }		// ILT 0x00026F62
private:
	int m_bfmeArr[10];
};

template <int NUMBITS>
class BitFlags
{
public:
	enum BogusInitType { kInit = 0 };
	BitFlags(BogusInitType, Int, Int, Int);			// ILT 0x00048FDB
private:
	UnsignedInt m_bits[(NUMBITS + 31) / 32];
};

class BfmeObjAS
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
 BfmeObjAS *bfmeParentAS(Int flag);				// ILT 0x0000FAA6

	char m_bfmeUnreconstructed_000[0x04];
 OVERRIDE<ThingTemplate> m_template;
 char pad08[0x110-8];
 union {
  BfmeBlockVKQ m_bfmeConditionFlags;
  struct { char pad110[4]; unsigned char m_bfmeByte114; char pad115[0x120-0x115]; UnsignedInt m_bfmeFlags120; };
 };
 char pad138[0x204-0x138];
	void *m_bfmeAi;						///< retail this+0x204, opaque AIUpdateInterface*
};

class BfmeGameLogicLike
{
public:
	char m_bfmeUnreconstructed_000[0x3C];
	UnsignedInt getFrame() const { return m_bfmeFrame; }
 UnsignedInt m_bfmeFrame;					///< retail this+0x3C
};

extern BfmeGameLogicLike *TheBfmeGameLogic;				// 0x012F0898

class AIUpdateInterface
{
public:
	float rva002774c0(void);					// ABI-only pin, retail 0x002774C0
	Int rva0027bf60(void);						// this body, retail 0x0027BF60

	char m_bfmeUnreconstructed_000[0x08];
	BfmeObjAS *m_bfmeObject;					///< retail this+0x08
	char m_bfmeUnreconstructed_00C[0x214 - 0x0C];
	Int m_bfmeNextAllowedFrame;					///< retail this+0x214
};

// ?rva0027bf60@AIUpdateInterface@@QAEHXZ

__forceinline void updateCondition(BfmeObjAS *obj, bool enabled) {
 if(enabled) {
  if(!obj->m_bfmeConditionFlags.test(147)) { obj->m_bfmeConditionFlags.set(147); reinterpret_cast<BfmeOwnerVNI*>(obj)->bfmeApply1VNI(); }
 } else {
  if(obj->m_bfmeConditionFlags.test(147)) { obj->m_bfmeConditionFlags.reset(147); reinterpret_cast<BfmeOwnerVNI*>(obj)->bfmeApply1VNI(); }
 }
}
template<class T> inline const T& smaller(const T& a,const T& b) { return a<b ? a:b; }
Int AIUpdateInterface::rva0027bf60(void)
{
 BfmeObjAS *obj=m_bfmeObject;
 if(!obj) return 1;
 UnsignedInt result=0x3fffffff;
 static const BitFlags<304> s_bfmeAttackModeMask(BitFlags<304>::kInit,0x74,0x75,0x76);
 const BfmeBlockVKQ &attackModeMask=reinterpret_cast<const BfmeBlockVKQ&>(s_bfmeAttackModeMask);
 if(obj->m_bfmeConditionFlags.test(147)) {
  bool ready=false;
  AIUpdateInterface *owner=this;
  if(!obj->m_bfmeConditionFlags.bfmeAnyVKQ(attackModeMask)) {
   bool outside=false;
   if(obj->m_bfmeByte114&0x20) {
    Real range=obj->getTemplate()->getRange();
    if(rva002774c0()>range) outside=true;
   }
   if(!outside) {
    BfmeObjAS *parent=obj->bfmeParentAS(0);
    if(parent && reinterpret_cast<const BFMESelectionStatusBits*>(parent)->test(0x25)) {
     owner=(AIUpdateInterface*)parent->m_bfmeAi;
     if(owner) {
      Real range=reinterpret_cast<const Thing*>(parent)->getTemplate()->getRange();
      if(!(owner->rva002774c0()>range)) ready=true;
     } else ready=true;
     owner=this;
    } else ready=true;
   }
  }
  UnsignedInt count=(obj->getTemplate()->getCount()>>1)+1;
  if(ready) {
   UnsignedInt frame=TheBfmeGameLogic->getFrame();
   if((UnsignedInt)owner->m_bfmeNextAllowedFrame<=frame) {
    updateCondition(obj,false);
   } else { result=owner->m_bfmeNextAllowedFrame-frame; if(result>count) result=count; }
  } else { 
   UnsignedInt frame=TheBfmeGameLogic->getFrame();
   m_bfmeNextAllowedFrame=obj->getTemplate()->getCount()+frame;
   result=count;
  }
 } else if(obj->m_bfmeConditionFlags.bfmeAnyVKQ(attackModeMask)) {
  updateCondition(obj,true);
 }
 return result;
}
