// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define private public
#include <map>
#undef private
#include <bitset>
#include <list>

typedef bool Bool;

template <int Number>
class BitFlags
{
public:
	enum _dummy_kInit { kInit };

	BitFlags() { }

	BitFlags(_dummy_kInit, int bit)
	{
		m_bits.set(bit);
	}

	void set(int bit) { m_bits._Unchecked_set(bit); }

private:
	_STL::bitset<Number> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

class Object
{
public:
	void setStatus(const ObjectStatusMaskType &status, Bool set);
	void *unidentified_001BFE20() const;
};

class BfmeObjE10
{
public:
	void actionB(int action);
};

struct Gen_t_0021c9d0_p12cd
{
	int a[3];
	Gen_t_0021c9d0_p12cd();
	Gen_t_0021c9d0_p12cd(const Gen_t_0021c9d0_p12cd &);
	~Gen_t_0021c9d0_p12cd();
	Gen_t_0021c9d0_p12cd &operator=(const Gen_t_0021c9d0_p12cd &);
};

bool operator==(const Gen_t_0021c9d0_p12cd &, const Gen_t_0021c9d0_p12cd &);
bool operator<(const Gen_t_0021c9d0_p12cd &, const Gen_t_0021c9d0_p12cd &);

typedef _STL::map<int, Gen_t_0021c9d0_p12cd> Rva0021D070Tree;

struct Rva0021D070TreeLayout
{
	_STL::_Rb_tree_node_base *header;
	unsigned int nodeCount;
};

class BfmeSubBDB
{
public:
	void bfmeDoBDB(void *what, int flag);

private:
	char m_unmodelled000[0x9c4];
	Rva0021D070Tree m_rva_09c4;
};

typedef void (__cdecl *Rva0021D070Callback)(void *, BfmeSubBDB *);

class Rva0021D070Interface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void *slot63(Rva0021D070Callback callback, BfmeSubBDB *owner, int flags);
};

// Callback thunk 0x0001FEA6 jumps to bfmeGoBDB, the matched wrapper below.
void j_0001fea6();

void bfmeGoBDB(void *one, BfmeSubBDB *two)
{
	two->bfmeDoBDB(one, 0);
}

void BfmeSubBDB::bfmeDoBDB(void *what, int flag)
{
	Object *object = (Object *)what;
	ObjectStatusMaskType mask(ObjectStatusMaskType::kInit, 36);
	object->setStatus(mask, false);
	((BfmeObjE10 *)object)->actionB(9);

	void *module = *(void **)((char *)object + 0x1fc);
	if (module)
	{
		if (object->unidentified_001BFE20())
		{
			Rva0021D070Interface *interface = (Rva0021D070Interface *)module;
			Rva0021D070Callback callback = (Rva0021D070Callback)j_0001fea6;
			interface->slot63(callback, this, 1);
			interface->slot63(callback, this, 0x10);
		}
	}
	else if ((*(unsigned char *)((char *)object + 0x94) & 0x20) != 0)
	{
		return;
	}

	if (!flag)
	{
		m_rva_09c4.erase(*(const int *)&what);
		return;
	}

	Rva0021D070Tree::iterator *entry = (Rva0021D070Tree::iterator *)flag;
	_STL::_Rb_tree_node_base *node = entry->_M_node;
	Rva0021D070TreeLayout *tree = (Rva0021D070TreeLayout *)&m_rva_09c4;
	_STL::_Rb_tree_node_base *header = tree->header;
	_STL::_Rb_tree_node_base *erased =
		_STL::_Rb_global<bool>::_Rebalance_for_erase(node,
			header->_M_parent, header->_M_left, header->_M_right);
	if (erased)
		_STL::__node_alloc<true, 0>::_M_deallocate(erased, 0x1c);
	--tree->nodeCount;
}

class Rva226730CountFlaggedOverrides
{
public:
	void updateCount();
};

class Rva0021D180Interface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
};

void j_0003be1c();

// ContestableContain primary view; bfmeDoBDB above is inlined into body().
class Rva0021D180
{
public:
	void body();

	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29(Object *object);

	char pad04[0x4];
	Object *m_object;
	char pad0c[0x14];
	Rva0021D180Interface m_interface;
	char pad24[0x14];
	_STL::list<Object *> m_containList;
	unsigned int m_containListSize;
	char pad40[0x97c];
	_STL::list<Object *> m_rva_09bc;
	Rva0021D070Tree m_rva_09c4;
	char pad9d0[0xc];
	Bool m_rva_09d8;
};

void Rva0021D180::body()
{
	m_object->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit, 35), false);

	if (m_containList.empty())
	{
		m_rva_09d8 = true;
		for (_STL::list<Object *>::iterator it = m_rva_09bc.begin(); it != m_rva_09bc.end(); )
		{
			Object *object = *it;
			++it;
			*(int *)((char *)object + 0x214) = 0;
			slot29(object);
			Rva0021D070Interface *module = *(Rva0021D070Interface **)((char *)object + 0x1fc);
			if (module)
			{
				Rva0021D070Callback callback = (Rva0021D070Callback)j_0003be1c;
				module->slot63(callback, (BfmeSubBDB *)this, 1);
				module->slot63(callback, (BfmeSubBDB *)this, 0x10);
			}
		}
		m_rva_09bc.clear();
		m_rva_09d8 = false;
		m_containListSize = m_containList.size();
		((Rva226730CountFlaggedOverrides *)this)->updateCount();
		m_interface.slot16();
	}

	for (_STL::list<Object *>::iterator it = m_containList.begin(); it != m_containList.end(); ++it)
		((BfmeSubBDB *)this)->bfmeDoBDB(*it, 0);
}
