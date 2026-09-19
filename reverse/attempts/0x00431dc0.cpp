// ?d_00431dc0@@YAXXZ
// partial score=0.98 date=2026-09-18
// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// BFME GameClient::xferDrawableTOC at retail 0x00431DC0.
// The BFME GameClient layout places its drawable TOC at this+0xF0.

#pragma comment(linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")
#pragma comment(linker, "/alternatename:?findTOCEntryByName@GameClient@@AAEPAUDrawableTOCEntry@1@VAsciiString@@@Z=?j_00029af0@@YAXXZ")
#pragma comment(linker, "/alternatename:?addTOCEntry@GameClient@@AAEXVAsciiString@@G@Z=?j_000266f2@@YAXXZ")
#pragma comment(linker, "/alternatename:?clear@?$list@UDrawableTOCEntry@GameClient@@H@_STL@@QAEXXZ=?j_0003c6af@@YAXXZ")

typedef unsigned char Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

enum XferMode
{
	XFER_INVALID,
	XFER_SAVE,
	XFER_LOAD
};

struct XferVersion
{
	unsigned char m_version;
	unsigned char m_currentVersion;
};

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase();

	void *m_data;

public:
	void set(const StringBase<T> &other);
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	AsciiString &operator=(const AsciiString &other)
	{
		((StringBase<char> *)this)->set((const StringBase<char> &)other);
		return *this;
	}
};

class Xfer
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual Bool getXferMode() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void xferVersion(XferVersion *version) = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void xferAsciiString(AsciiString *value) = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void xferUnsignedInt(UnsignedInt *value) = 0;
	virtual void slot30() = 0;
	virtual void xferUnsignedShort(UnsignedShort *value) = 0;
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
};

class ThingTemplate
{
public:
	char m_pad00[4];
	Overridable *m_override;

	const AsciiString &getName() const
	{
		const Overridable *owner = (const Overridable *)this;
		if (this != 0 && m_override != 0)
			owner = m_override->getFinalOverride();
		return *(const AsciiString *)((const char *)owner + 0x20);
	}
};

class Drawable
{
public:
	void *m_vtable;
	ThingTemplate *m_template;
	char m_pad08[0xF4];
	void *m_object;
	char m_pad100[4];
	Drawable *m_next;
	char m_pad108[8];
	unsigned char m_status[4];

	ThingTemplate *getTemplate() const { return m_template; }
	void *getObject() const { return m_object; }
	Bool testDrawableStatus(unsigned int status) const { return (m_status[0] & status) != 0; }
	Drawable *getNextDrawable() const { return m_next; }
};

namespace _STL
{
	template <typename T>
	struct _List_node_base
	{
		_List_node_base *next;
		_List_node_base *previous;
	};

	template <typename T>
	struct _List_node : _List_node_base<T>
	{
		T value;
	};

	template <typename T, typename Traits>
	struct _List_iterator
	{
		typedef _List_node<T> Node;
		_List_node_base<T> *node;

		_List_iterator() {}
		_List_iterator(Node *value) : node(value) {}
		T &operator*() const { return ((Node *)node)->value; }
		T *operator->() const { return &((Node *)node)->value; }
		_List_iterator &operator++()
		{
			node = node->next;
			return *this;
		}
		bool operator!=(const _List_iterator &other) const { return node != other.node; }
	};

	template <typename T, typename Allocator>
	class list
	{
	public:
		typedef _List_node<T> Node;
		typedef _List_iterator<T, T> iterator;
		Node *head;

		void clear();
		iterator begin() { return iterator((Node *)head->next); }
		iterator end() { return iterator(head); }
	};
}

class GameClient
{
public:
	struct DrawableTOCEntry
	{
		AsciiString name;
		UnsignedShort id;
	};
	typedef _STL::list<DrawableTOCEntry, int> DrawableTOCList;
	typedef DrawableTOCList::iterator DrawableTOCListIterator;

	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual Drawable *getDrawableList() = 0;

private:
	char m_pad04[0xEC];
	DrawableTOCList m_drawableTOC;

	void addTOCEntry(AsciiString name, UnsignedShort id);
	DrawableTOCEntry *findTOCEntryByName(AsciiString name);
	void xferDrawableTOC(Xfer *xfer);
};

static Bool shouldSaveDrawable(const Drawable *draw)
{
	if (draw->testDrawableStatus(0x10) && draw->getObject() == 0)
		return false;
	return 1;
}

void GameClient::xferDrawableTOC(Xfer *xfer)
{
	{
		XferVersion version = {1, 1};
		xfer->xferVersion(&version);
	}

	DrawableTOCList *tocList;
	tocList = &m_drawableTOC;
	tocList->clear();

	UnsignedInt tocCount = 0;
	if (xfer->getXferMode())
	{
		AsciiString templateName;

		for (Drawable *draw = getDrawableList(); draw; draw = draw->getNextDrawable())
		{
			if (!shouldSaveDrawable(draw))
				continue;

			templateName = draw->getTemplate()->getName();

			if (findTOCEntryByName(templateName) != 0)
				continue;

			addTOCEntry(draw->getTemplate()->getName(), ++tocCount);
		}

		xfer->xferUnsignedInt(&tocCount);

		for (DrawableTOCListIterator it = tocList->begin(); it != tocList->end(); ++it)
		{
			xfer->xferAsciiString(&(*it).name);
			xfer->xferUnsignedShort(&(*it).id);
		}
	}
	else
	{
		AsciiString templateName;
		UnsignedShort id;
		xfer->xferUnsignedInt(&tocCount);

		for (UnsignedInt i = 0; i < tocCount; ++i)
		{
			xfer->xferAsciiString(&templateName);
			xfer->xferUnsignedShort(&id);
			addTOCEntry(templateName, id);
		}
	}
}
