// cl: /DNDEBUG /MD /EHsc

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

template <int NUMBITS>
class BitFlags
{
public:
	UnsignedInt m_words[ 6 ];
	Bool testSetAndClear( const BitFlags &mustBeSet, const BitFlags &mustBeClear ) const;
};

typedef BitFlags<116> KindOfMaskType;

class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const;

	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	Bool isKindOfMulti( const KindOfMaskType &mustBeSet,
		const KindOfMaskType &mustBeClear ) const
	{
		return m_kindOf.testSetAndClear( mustBeSet, mustBeClear );
	}

private:
	unsigned char m_unmodelled_008[ 0xc0 ];
	KindOfMaskType m_kindOf;
};

class Object;

class BfmeObjectVirtualTail
{
public:
	unsigned char m_vt[ 4 ];
};

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[ 4 ];
};

class BfmeObjectVtbl
{
public:
	virtual void bfmeObjectSlot0();
};

template <class T>
class BfmeOverride
{
public:
	const T *operator->() const
	{
		const T *value = m_overridable;
		if (value && value->m_nextOverride)
			value = (const T *)value->m_nextOverride->getFinalOverride();
		return value;
	}

	const T *volatile m_overridable;
};

// BFME puts Object's template override pointer in the dlink base at +0x04.
// The volatile field preserves retail's null check before each dlink advance.
class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList() const;
	BfmeOverride<ThingTemplate> m_template;
};

#define callMemberFunction(object, ptrToMember) ((object).*(ptrToMember))

class BfmeObjectDlinkPad
{
public:
	unsigned char m_pad[ 0x60 ];
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	const ThingTemplate *getTemplate() const
	{
		return m_template.operator->();
	}

	unsigned char m_tail[ 0x40 ];
};

template <class ObjectType>
class BfmeDlinkIterator
{
public:
	typedef ObjectType *(ObjectType::*GetNextFunc)() const;

	BfmeDlinkIterator( ObjectType *cur, GetNextFunc getNext )
		: m_cur( cur ), m_getNext( getNext ) { }

	Bool done() const
	{
		return m_cur == 0;
	}
	ObjectType *cur() const { return m_cur; }

	void advance()
	{
		if (m_cur)
			m_cur = callMemberFunction( *m_cur, m_getNext )();
	}

	private:
	ObjectType *m_cur;
	GetNextFunc m_getNext;
};

class Team
{
public:
	Int countObjects( KindOfMaskType setMask, KindOfMaskType clearMask );

private:
	Object *m_unmodelled_000;
	Object *m_unmodelled_004;
	Object *m_unmodelled_008;
	Object *m_head;

public:
	BfmeDlinkIterator<Object> iterate_TeamMemberList() const
	{
		return BfmeDlinkIterator<Object>( m_head,
			BfmeObjectDlinkBase::dlink_next_TeamMemberList );
	}
};

Int Team::countObjects( KindOfMaskType setMask, KindOfMaskType clearMask )
{
	Int retVal = 0;
	for (BfmeDlinkIterator<Object> iter = iterate_TeamMemberList();
		 !iter.done(); iter.advance())
	{
		const ThingTemplate *objtmpl = iter.cur()->getTemplate();
		if (!objtmpl)
			continue;
		if (objtmpl->isKindOfMulti( setMask, clearMask ))
			++retVal;
	}
	return retVal;
}

#pragma comment(linker, "/alternatename:?dlink_next_TeamMemberList@BfmeObjectDlinkBase@@QBEPAVObject@@@Z=?j_00001140@@YAXXZ")

extern void j_000022bb();
extern void j_00019bcd();
#pragma comment(linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")
#pragma comment(linker, "/alternatename:?testSetAndClear@?$BitFlags@$0HE@@@QBE_NABV1@0@Z=?j_00019bcd@@YAXXZ")
