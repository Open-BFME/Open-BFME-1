// Retail [0x0076CB10,0x0076CD3A): 554 bytes, thiscall, no arguments (plain
// RET at +0x209 and +0x229). Reached only through ILT 0x00036A70 from two
// still-unowned draw bodies (0x00755F70, 0x00778590); the owner's identity is
// unresolved, so the owner, drawable, template and render-object views keep
// address-derived names.
// Witnessed from the retail bytes: owner +0x08 drawable, +0x34 render object
// (virtual slots 119/120 read and set flag words), +0x1B8 mode word; drawable
// +0x04 override-walked template pointer (Overridable::getFinalOverride via
// ILT 0x000022BB), +0xFC object, +0x250 condition bits (bit test 0x000D2F40);
// template +0xC8..+0xDF flag words; object +0x23C team, +0x343/+0x344 bytes.
// Callees: Player::getRelationship 0x000D19C0, Object::isLocallyControlled
// 0x001BE570, Thing::isKindOf 0x000A2CF0, Rva000C4A70::field 0x000C4A70.
// The ZH-style inline OVERRIDE/getFinalOverride walk reproduces retail's
// first-level expansion at the call site.
// cl: /DNDEBUG /MD /EHsc
enum KindOfType { KINDOF_0x07 = 7, KINDOF_0x16 = 0x16, KINDOF_0x18 = 0x18, KINDOF_0x3B = 0x3b };
enum Relationship { REL_0 = 0 };
class Team;
class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}
	Overridable *m_nextOverride;
};
template <class T> class OVERRIDE
{
public:
	const T *operator->() const
	{
		if (!m_overridable)
			return 0;
		return (const T *)m_overridable->getFinalOverride();
	}
	const Overridable *m_overridable;
};
class Rva0076CB10Template
{
public:
	unsigned int bits(int word) const { return m_kindOf[word]; }
	unsigned char m_pad000[0xc8];
	unsigned int m_kindOf[6];
};
class Thing
{
public:
	bool isKindOf(KindOfType t) const;
};
class Player
{
public:
	Relationship getRelationship(const Team *team) const;
};
class PlayerList
{
public:
	Player *getLocalPlayer() { return m_local; }
	unsigned char m_pad00[0xc];
	Player *m_local;
};
extern PlayerList *ThePlayerList;
class Object : public Thing
{
public:
	bool isLocallyControlled() const;
	const Team *getTeam() const { return *(const Team *const *)((const char *)this + 0x23c); }
	unsigned char byte343() const { return *((const unsigned char *)this + 0x343); }
	unsigned char byte344() const { return *((const unsigned char *)this + 0x344); }
};
class Rva000C4A70
{
public:
	bool field(void) const;
};
struct WordBitTest000D2F40
{
	bool test(unsigned index) const;
	unsigned m_words[1];
};
class Rva0076CB10Drawable
{
public:
	unsigned char m_pad000[4];
	OVERRIDE<Rva0076CB10Template> m_template;
	unsigned char m_pad008[0xfc - 8];
	Object *m_object;
	unsigned char m_pad100[0x250 - 0x100];
	WordBitTest000D2F40 m_conditions;
	const Rva0076CB10Template *getTemplate() const { return m_template.operator->(); }
	Object *getObject() const { return m_object; }
};
class Rva0076CB10Render
{
public:
#define S(n) virtual void slot##n();
	S(00) S(01) S(02) S(03) S(04) S(05) S(06) S(07) S(08) S(09) S(0A) S(0B) S(0C) S(0D) S(0E) S(0F)
	S(10) S(11) S(12) S(13) S(14) S(15) S(16) S(17) S(18) S(19) S(1A) S(1B) S(1C) S(1D) S(1E) S(1F)
	S(20) S(21) S(22) S(23) S(24) S(25) S(26) S(27) S(28) S(29) S(2A) S(2B) S(2C) S(2D) S(2E) S(2F)
	S(30) S(31) S(32) S(33) S(34) S(35) S(36) S(37) S(38) S(39) S(3A) S(3B) S(3C) S(3D) S(3E) S(3F)
	S(40) S(41) S(42) S(43) S(44) S(45) S(46) S(47) S(48) S(49) S(4A) S(4B) S(4C) S(4D) S(4E) S(4F)
	S(50) S(51) S(52) S(53) S(54) S(55) S(56) S(57) S(58) S(59) S(5A) S(5B) S(5C) S(5D) S(5E) S(5F)
	S(60) S(61) S(62) S(63) S(64) S(65) S(66) S(67) S(68) S(69) S(6A) S(6B) S(6C) S(6D) S(6E) S(6F)
	S(70) S(71) S(72) S(73) S(74) S(75) S(76)
#undef S
	virtual unsigned int getFlags();
	virtual void setFlags(unsigned int flags, int on);
};
class Rva0076CB10Owner
{
public:
	void run();
	unsigned char m_pad000[8];
	Rva0076CB10Drawable *m_drawable;
	unsigned char m_pad00c[0x34 - 0xc];
	Rva0076CB10Render *m_render;
	unsigned char m_pad038[0x1b8 - 0x38];
	int m_mode;
};

void Rva0076CB10Owner::run()
{
	Rva0076CB10Drawable *draw = m_drawable;
	const Rva0076CB10Template *tmpl = draw->getTemplate();
	if (!tmpl)
		return;

	if (m_mode == -1)
	{
		if ((tmpl->bits(0) & 0x2) || (tmpl->bits(1) & 0x8000000))
			m_render->setFlags(4, 1);
	}
	else if (m_mode == 1)
		m_render->setFlags(4, m_mode);

	if (tmpl->bits(0) & 0x40)
		m_render->setFlags(8, 1);
	else if ((tmpl->bits(3) & 0x1) || (tmpl->bits(4) & 0x80))
		m_render->setFlags(0x200, 1);

	Object *obj = draw->getObject();
	if (m_render->getFlags() & 4)
	{
		unsigned int flags = 4;
		if ((tmpl->bits(2) & 0x2000000) || (tmpl->bits(0) & 0x400) || (tmpl->bits(5) & 0x400))
			flags = 0x84;
		if (obj)
		{
			Relationship rel = ThePlayerList->getLocalPlayer()->getRelationship(obj->getTeam());
			if (obj->isLocallyControlled())
				flags |= 0x100;
			else if (rel == REL_0 && !obj->isKindOf(KINDOF_0x3B))
				flags |= 0x10;
		}
		m_render->setFlags(flags, 1);
	}

	if (tmpl->bits(2) & 0x8)
		m_render->setFlags(0x20, 1);
	if (tmpl->bits(2) & 0x800)
		m_render->setFlags(0, 1);

	if (!obj)
		return;
	if (obj->byte343() & 0x10)
		m_render->setFlags(0x40, 1);
	if (obj->isKindOf(KINDOF_0x16))
		return;
	if (obj->isKindOf(KINDOF_0x18))
		return;
	if (((const Rva000C4A70 *)obj)->field())
		return;
	if (obj->isKindOf(KINDOF_0x07) && draw->m_conditions.test(5))
	{
		m_render->setFlags(0, 1);
		return;
	}
	if (obj->byte344() & 1)
		m_render->setFlags(0, 1);
}

// Retail 0x000D2F40 (37 B, thiscall RET4), reached through ILT 0x0000666D
// from the condition-bit test above: word index>>5, mask 1<<(index&31),
// normalized bool. Its STLport bitset spelling is shared by many byte-equal
// copies, so the address-derived caller name stays.
// ?test@WordBitTest000D2F40@@QBE_NI@Z
__declspec(noinline) bool WordBitTest000D2F40::test(unsigned index) const
{
	return (m_words[index >> 5] & (1U << (index & 31))) != 0;
}
