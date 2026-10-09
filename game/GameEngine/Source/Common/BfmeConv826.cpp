class Rva002E7C50Element;
class BfmeVector28;
class BfmeHostXZ { public: int bfmeStartXZ(unsigned int, int); };
namespace _STL {
 template<class T> class allocator;
 struct __false_type;
 template<class T, class A> class vector {
 protected: void _M_insert_overflow(T *, const T &, const __false_type &, unsigned int, bool);
 friend class ::BfmeVector28;
 };
}

class ThingTemplate;
class AsciiString;

// Retail's global at 0x012EF1D8 is EA's `ThingFactory *TheThingFactory`, the
// singleton game/GameEngine/Source/Common/Thing/ThingFactory.cpp defines
// (?TheThingFactory@@3PAVThingFactory@@A). The address-derived
// `g_mgr12EF1D8` spelling referenced a global nothing defines, so the two
// bodies below take the defining name and keep this TU's own ABI view of the
// factory, casting at the use.
class ThingFactory;

extern ThingFactory *TheThingFactory;

// Both bodies below reach retail 0x00028560, the ILT thunk onto the matched
// BfmeThingFactory::findTemplate body at 0x00137E80 -- the same address every
// other caller in this build spells ?findTemplate@BfmeThingFactory. The old
// `registerObj(void*)` spelling was a guess that no object ever defined.
class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

class BfmeSub4_78F
{
public:
	void* reg25C()
	{
		return (void*)((BfmeThingFactory*)TheThingFactory)->findTemplate(
			*(const AsciiString *)((char*)this + 0x25c));
	}
	void* reg260()
	{
		return (void*)((BfmeThingFactory*)TheThingFactory)->findTemplate(
			*(const AsciiString *)((char*)this + 0x260));
	}
};

struct BfmeThing78F
{
	unsigned char pad[4];
	BfmeSub4_78F *m_sub4;
	void* reg25C();
	void* reg260();
};

void* BfmeThing78F::reg25C()
{
	return m_sub4->reg25C();
}

void* BfmeThing78F::reg260()
{
	return m_sub4->reg260();
}

struct BfmeField58_FCD
{
	unsigned char pad[4];
	void *m_field4;
};

class BfmeSub30_FCD
{
public:
	unsigned char pad[0x58];
	BfmeField58_FCD *m_field58;
	int m_field5C;
};

struct BfmeThingFCD
{
	unsigned char pad[0x30];
	BfmeSub30_FCD *m_sub30;
	void checkAndNotify();
};

void BfmeThingFCD::checkAndNotify()
{
	BfmeSub30_FCD *sub = m_sub30;
	if (sub->m_field58 && sub->m_field5C == -1) {
		reinterpret_cast<BfmeHostXZ *>(sub)->bfmeStartXZ((unsigned int)sub->m_field58->m_field4, -2);
	}
}

struct BfmeItem28
{
	int words[7];
};

struct BfmeVector28
{
	void *m_start0;
	BfmeItem28 *m_cur4;
	BfmeItem28 *m_end8;
	void push_back(const BfmeItem28 &item);
};

void BfmeVector28::push_back(const BfmeItem28 &item)
{
	if (m_cur4 != m_end8) {
		if (m_cur4) {
			*m_cur4 = item;
		}
		m_cur4++;
	} else {
		void *temp;
		reinterpret_cast<_STL::vector<Rva002E7C50Element, _STL::allocator<Rva002E7C50Element> > *>(this)->_M_insert_overflow(reinterpret_cast<Rva002E7C50Element *>(m_cur4), *reinterpret_cast<const Rva002E7C50Element *>(&item), *reinterpret_cast<const _STL::__false_type *>(&temp), 1, true);
	}
}