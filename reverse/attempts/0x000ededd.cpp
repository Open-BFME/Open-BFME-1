// ?affectedByUpgrade@Team@@QBE_NPBVUpgradeTemplate@@@Z
// partial score=0.95 date=2026-09-04
// ?affectedByUpgrade@Team@@QBE_NPBVUpgradeTemplate@@@Z
// partial score=0.95 date=2026-09-04
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink
// Open-BFME5: Team::affectedByUpgrade, retail 0x000EDEDD, 119 bytes.
// Sibling of Team::giveUpgrade 0xED9D0. Same Object DLINK + contain/+0x1FC
// UpgradeSink/+0x68 path; sink predicate at +0xA4; Object::affectedByUpgrade
// ILT 0x77B6 fallback with cmp al,1. Best 124B: sole residue 5B eb03/lea
// loop-align pad at +0x1B (same wall as 0xED9D0).

#include "ObjectDlinkPmf.h"
typedef bool Bool;
typedef unsigned char BoolByte;
#define callMemberFunction(object,ptrToMember)  ((object).*(ptrToMember))
template<class OBJCLASS>
class DLINK_ITERATOR {
public:
	typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;
private:
	OBJCLASS* m_cur; GetNextFunc m_getNextFunc;
public:
	DLINK_ITERATOR(OBJCLASS* cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc) {}
	void advance() { m_cur = callMemberFunction(*m_cur, m_getNextFunc)(); }
	Bool done() const { return m_cur == 0; }
	OBJCLASS* cur() const { return m_cur; }
};
class UpgradeTemplate;
class BfmeUpgradeSink {
public:
	virtual void _s00()=0;virtual void _s01()=0;virtual void _s02()=0;virtual void _s03()=0;
	virtual void _s04()=0;virtual void _s05()=0;virtual void _s06()=0;virtual void _s07()=0;
	virtual void _s08()=0;virtual void _s09()=0;virtual void _s10()=0;virtual void _s11()=0;
	virtual void _s12()=0;virtual void _s13()=0;virtual void _s14()=0;virtual void _s15()=0;
	virtual void _s16()=0;virtual void _s17()=0;virtual void _s18()=0;virtual void _s19()=0;
	virtual void _s20()=0;virtual void _s21()=0;virtual void _s22()=0;virtual void _s23()=0;
	virtual void _s24()=0;virtual void _s25()=0;virtual void _s26()=0;virtual void _s27()=0;
	virtual void _s28()=0;virtual void _s29()=0;virtual void _s30()=0;virtual void _s31()=0;
	virtual void _s32()=0;virtual void _s33()=0;virtual void _s34()=0;virtual void _s35()=0;
	virtual void _s36()=0;virtual void _s37()=0;virtual void _s38()=0;virtual void _s39()=0;
	virtual void _s40()=0;
	virtual Bool affectedByUpgrade(const UpgradeTemplate *u)=0;
	virtual void _s42()=0; virtual void _s43()=0;
};
class ContainModuleInterface {
public:
	virtual void _c00()=0;virtual void _c01()=0;virtual void _c02()=0;virtual void _c03()=0;
	virtual void _c04()=0;virtual void _c05()=0;virtual void _c06()=0;virtual void _c07()=0;
	virtual void _c08()=0;virtual void _c09()=0;virtual void _c10()=0;virtual void _c11()=0;
	virtual void _c12()=0;virtual void _c13()=0;virtual void _c14()=0;virtual void _c15()=0;
	virtual void _c16()=0;virtual void _c17()=0;virtual void _c18()=0;virtual void _c19()=0;
	virtual void _c20()=0;virtual void _c21()=0;virtual void _c22()=0;virtual void _c23()=0;
	virtual void _c24()=0;virtual void _c25()=0;
	virtual BfmeUpgradeSink *getUpgradeSink()=0;
};
class BfmeObjectContainView {
public:
	unsigned char m_head[0x1FC];
	ContainModuleInterface *m_contain;
	BoolByte affectedByUpgrade(const UpgradeTemplate *u) const;
};
class Team {
public:
	Bool affectedByUpgrade(const UpgradeTemplate *u) const;
	void *m_vptr; void *m_proto; void *m_id; Object *m_head;
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const {
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};
Bool Team::affectedByUpgrade(const UpgradeTemplate *upgrade) const {
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		ContainModuleInterface *contain = ((BfmeObjectContainView *)iter.cur())->m_contain;
		if (contain != 0) {
			BfmeUpgradeSink *sink = contain->getUpgradeSink();
			if (sink != 0) {
				if (sink->affectedByUpgrade(upgrade))
					return true;
				continue;
			}
		}
		if (((BfmeObjectContainView *)iter.cur())->affectedByUpgrade(upgrade) == 1)
			return true;
	}
	return false;
}
