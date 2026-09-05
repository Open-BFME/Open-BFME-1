// cl: /O2 /Ob1
//
// Retail 0x0037FE30. this+0x1C circular 0x14-byte list (push_back). arg2 is
// Object with ExperienceTracker at +0x210. RVA-derived host name.

typedef bool Bool;

inline void *operator new(unsigned int, void *place) { return place; }

namespace _STL
{

class __new_alloc
{
public:
	static void *allocate(unsigned int n);
};

template <class T1, class T2>
inline void __cdecl _Construct(T1 *destination, const T2 &value)
{
	new (destination) T1(value);
}

struct _List_node_base
{
	_List_node_base *_M_next;
	_List_node_base *_M_prev;
};

template <class T>
struct _List_node : public _List_node_base
{
	T _M_data;
};

template <class T>
struct _List_iterator
{
	explicit _List_iterator(_List_node_base *node) : _M_node(node) {}
	_List_node_base *_M_node;
};

template <class T>
class list
{
public:
	typedef _List_node<T> _Node;
	typedef _List_iterator<T> iterator;

	iterator insert(iterator position, const T &value)
	{
		_Node *node = (_Node *)__new_alloc::allocate(sizeof(_Node));
		_Construct(&node->_M_data, value);
		_List_node_base *at = position._M_node;
		_List_node_base *before = at->_M_prev;
		node->_M_prev = before;
		node->_M_next = at;
		before->_M_next = node;
		at->_M_prev = node;
		return iterator(node);
	}

	_Node *_M_node;
};

}

class AsciiString
{
public:
	void set(const AsciiString &other);

private:
	void *m_data;
};

class ExperienceTracker
{
public:
	void bfmeSetScalarIndex(int index);
	char m_pad[8];
	AsciiString m_name;
	char m_pad10[0x24 - 8 - 4];
	unsigned char m_flag24;
};

class Gen_000E8870
{
public:
	void bfmeAddA(int amount);
	void bfmeAddB(int amount);
};

class BfmeR1094
{
public:
	char m_pad[0x348];
	Gen_000E8870 m_add;
};

class SlotB
{
public:
	virtual void t00() = 0; virtual void t01() = 0; virtual void t02() = 0;
	virtual void t03() = 0; virtual void t04() = 0; virtual void t05() = 0;
	virtual void t06() = 0; virtual void t07() = 0; virtual void t08() = 0;
	virtual void t09() = 0; virtual void t10() = 0; virtual void t11() = 0;
	virtual void t12() = 0; virtual void t13() = 0; virtual void t14() = 0;
	virtual void t15() = 0; virtual void t16() = 0; virtual void t17() = 0;
	virtual void t18() = 0; virtual void t19() = 0; virtual void t20() = 0;
	virtual void t21() = 0; virtual void t22() = 0; virtual void t23() = 0;
	virtual void t24() = 0; virtual void t25() = 0; virtual void t26() = 0;
	virtual void t27() = 0; virtual void t28() = 0; virtual void t29() = 0;
	virtual void t30() = 0; virtual void t31() = 0; virtual void t32() = 0;
	virtual void t33() = 0; virtual void t34() = 0; virtual void t35() = 0;
	virtual void t36() = 0; virtual void t37() = 0; virtual void t38() = 0;
	virtual void t39() = 0; virtual void t40() = 0; virtual void t41() = 0;
	virtual void t42() = 0; virtual void t43() = 0; virtual void t44() = 0;
	virtual void vB4() = 0;
};

class Slot1FC
{
public:
	virtual void s00() = 0; virtual void s01() = 0; virtual void s02() = 0;
	virtual void s03() = 0; virtual void s04() = 0; virtual void s05() = 0;
	virtual void s06() = 0; virtual void s07() = 0; virtual void s08() = 0;
	virtual void s09() = 0; virtual void s10() = 0; virtual void s11() = 0;
	virtual void s12() = 0; virtual void s13() = 0; virtual void s14() = 0;
	virtual void s15() = 0; virtual void s16() = 0; virtual void s17() = 0;
	virtual void s18() = 0; virtual void s19() = 0; virtual void s20() = 0;
	virtual void s21() = 0; virtual void s22() = 0; virtual void s23() = 0;
	virtual void s24() = 0; virtual void s25() = 0;
	virtual SlotB *v68() = 0;
};

class BfmeThingAIA
{
public:
	Bool bfmeAskAIA(int kind);
};

class BfmeK1094
{
public:
	BfmeR1094 *bfmeCur1094();
};

class Arg1
{
public:
	char m_pad[0xC];
	AsciiString m_name;
	char m_pad10[0xCC - 0xC - 4];
	int m_index;
};

struct Payload
{
	unsigned int objectID;
	Arg1 *arg1;
	Bool flag;
};

class ObjectView
{
public:
	char m_pad[0x74];
	unsigned int m_objectID;
	char m_pad78[0x94 - 0x78];
	unsigned char m_flags94;
	char m_pad95[0x1FC - 0x95];
	Slot1FC *m_slot1FC;
	char m_pad200[0x210 - 0x200];
	ExperienceTracker *m_tracker;
};

class Rva0037FE30
{
public:
	void record(Arg1 *arg1, ObjectView *obj, Bool flag);

	char m_pad[0x1C];
	_STL::list<Payload> m_list;
};

void Rva0037FE30::record(Arg1 *arg1, ObjectView *obj, Bool flag)
{
	Bool f = flag;
	Arg1 *a = arg1;
	ObjectView *o = obj;
	unsigned int objectID = o->m_objectID;
	_STL::list<Payload>::_Node *sent = m_list._M_node;
	Payload pay;
	pay.objectID = objectID;
	pay.arg1 = a;
	pay.flag = f;
	m_list.insert(_STL::list<Payload>::iterator(sent), pay);

	o->m_tracker->m_name.set(a->m_name);
	o->m_tracker->bfmeSetScalarIndex(a->m_index);

	Slot1FC *slot = o->m_slot1FC;
	if (slot)
	{
		SlotB *inner = slot->v68();
		if (inner)
			inner->vB4();
	}

	ExperienceTracker *tracker = o->m_tracker;
	if (a->m_index > 1 && !tracker->m_flag24 && !((BfmeThingAIA *)o)->bfmeAskAIA(7))
	{
		tracker->m_flag24 = 1;
		if (((BfmeThingAIA *)o)->bfmeAskAIA(0x59))
		{
			BfmeR1094 *cur = ((BfmeK1094 *)o)->bfmeCur1094();
			cur->m_add.bfmeAddA(1);
			return;
		}
		if (!(o->m_flags94 & 0x20))
		{
			BfmeR1094 *cur = ((BfmeK1094 *)o)->bfmeCur1094();
			cur->m_add.bfmeAddB(1);
		}
	}
}
