// ?add@ContainInsert2265F0@@QAEXPAVObject@@@Z
// partial score=0.94 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>
#include <vector>
struct Rva002253A0Value { char m_body[4]; };
typedef _STL::pair<const int,Rva002253A0Value> Rva002253A0Pair;
typedef _STL::_Rb_tree<int,Rva002253A0Pair,_STL::_Select1st<Rva002253A0Pair>,_STL::less<int>,_STL::allocator<Rva002253A0Pair> > Rva002253A0Tree;
namespace _STL { template<> pair<Rva002253A0Tree::iterator,bool> Rva002253A0Tree::insert_unique(const Rva002253A0Pair &); }
class Object;
struct Drawable2265F0 { char pad[0x3ac]; bool byte_3ac; };
struct Player { char pad[0x24]; int m_playerIndex; };
class ContainDispatch2265F0 { public:
 virtual void slot00() = 0;
 virtual void slot04() = 0;
 virtual void slot08() = 0;
 virtual void slot0C() = 0;
 virtual void slot10() = 0;
 virtual void slot14() = 0;
 virtual void slot18() = 0;
 virtual void slot1C() = 0;
 virtual void slot20() = 0;
 virtual void slot24() = 0;
 virtual void slot28() = 0;
 virtual void slot2C() = 0;
 virtual void slot30() = 0;
 virtual void slot34() = 0;
 virtual void slot38() = 0;
 virtual void slot3C() = 0;
 virtual void slot40() = 0;
 virtual void onContaining(Object *,bool) = 0;
};
class Object { public:
 virtual void slot00() = 0;
 virtual void slot04() = 0;
 virtual void slot08() = 0;
 virtual void slot0C() = 0;
 virtual void slot10() = 0;
 virtual void slot14() = 0;
 virtual void slot18() = 0;
 virtual void slot1C() = 0;
 virtual void slot20() = 0;
 virtual void slot24() = 0;
 virtual Drawable2265F0 *getDrawable() const = 0;
 Player *getControllingPlayer() const;
 void onContainedBy(Object *);
 char pad04[0x70]; unsigned m_id;
 char pad78[0x1c]; unsigned field_94;
 char pad98[0x164]; ContainDispatch2265F0 *m_contain;
 char pad200[0x14]; Object *field_214;
};
class PrimaryContain2265F0 { public:
 virtual void slot00() = 0;
 virtual void slot04() = 0;
 virtual void slot08() = 0;
 virtual void slot0C() = 0;
 virtual void slot10() = 0;
 virtual void slot14() = 0;
 virtual void slot18() = 0;
 virtual void slot1C() = 0;
 virtual void slot20() = 0;
 virtual void slot24() = 0;
 virtual void slot28() = 0;
 virtual void slot2C() = 0;
 virtual void slot30() = 0;
 virtual void slot34() = 0;
 virtual void slot38() = 0;
 virtual void slot3C() = 0;
 virtual void slot40() = 0;
 virtual void slot44() = 0;
 virtual void slot48() = 0;
 virtual void slot4C() = 0;
 virtual void slot50() = 0;
 virtual void slot54() = 0;
 virtual void slot58() = 0;
 virtual void slot5C(Object *,bool,bool) = 0;
};
struct Template2265F0 { char pad[0x158]; _STL::vector<int> field_158; };
struct Logic2265F0 { char pad[0x3c]; unsigned frame; };
extern Logic2265F0 *logic2265F0;
class ContainInsert2265F0 { public:
 virtual void slot00() = 0;
 virtual void slot04() = 0;
 virtual void slot08() = 0;
 virtual void slot0C() = 0;
 virtual void slot10() = 0;
 virtual void slot14() = 0;
 virtual void slot18() = 0;
 virtual void slot1C() = 0;
 virtual void slot20() = 0;
 virtual void slot24() = 0;
 virtual void slot28() = 0;
 virtual void slot2C() = 0;
 virtual void slot30() = 0;
 virtual void slot34() = 0;
 virtual void slot38() = 0;
 virtual void slot3C() = 0;
 virtual void slot40() = 0;
 virtual void slot44() = 0;
 virtual void slot48() = 0;
 virtual void slot4C() = 0;
 virtual void slot50() = 0;
 virtual void slot54() = 0;
 virtual void slot58() = 0;
 virtual void slot5C() = 0;
 virtual void slot60() = 0;
 virtual void slot64() = 0;
 virtual void slot68() = 0;
 virtual void slot6C() = 0;
 virtual void slot70() = 0;
 virtual void slot74() = 0;
 virtual void slot78() = 0;
 virtual void slot7C() = 0;
 virtual void slot80() = 0;
 virtual void slot84() = 0;
 virtual void slot88() = 0;
 virtual void addToList(Object *) = 0;

 char pad04[0x50]; unsigned short field_54;
 void add(Object *rider);
};
void ContainInsert2265F0::add(Object *rider)
{
 if (!rider) return;
 Drawable2265F0 *draw = rider->getDrawable();
 bool wasSelected = false;
 if (draw && draw->byte_3ac) wasSelected = true;
 if (rider->field_214) return;
 addToList(rider);
 field_54 = (unsigned short)(1 << rider->getControllingPlayer()->m_playerIndex);
 if ((*(Object **)((char *)this - 0x18))->m_contain)
  (*(Object **)((char *)this - 0x18))->m_contain->onContaining(rider,wasSelected);
 PrimaryContain2265F0 *primary = (PrimaryContain2265F0 *)((char *)this - 0x20);
 primary->slot44();
 rider->onContainedBy(*(Object **)((char *)this - 0x18));
 primary->slot50();
 Template2265F0 *data = *(Template2265F0 **)((char *)this - 0x1c);
 if (!data->field_158.empty()) {
  _STL::pair<int,unsigned> pair(rider->m_id, logic2265F0->frame);
  ((Rva002253A0Tree *)((char *)this + 0xa8))->insert_unique(*(const Rva002253A0Pair *)&pair);
 }
 if (rider->field_94 & 0x10000000) primary->slot5C(rider,false,false);
}
