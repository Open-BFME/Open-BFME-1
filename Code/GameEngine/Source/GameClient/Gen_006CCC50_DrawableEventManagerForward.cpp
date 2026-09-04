// cl: /DNDEBUG /MD /EHsc
// Candidate for the drawable-event manager forwarder at retail 0x006CCC50.

template <class T>
class StringBase
{
friend class AsciiString;

private:
	StringBase(const StringBase<T> &that);
	~StringBase();
	T *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &that) : StringBase<char>(that) {}
	~AsciiString() {}
};

enum DrawableID
{
	INVALID_DRAWABLE_ID = 0
};

extern void j_0000c3d3(void);

class Gen006CCC50EventTarget
{
public:
	void dispatch(DrawableID id, AsciiString text,
		unsigned char secondSelector, unsigned char firstSelector);
};

class BfmeDrawableEventManager
{
public:
	void forwardDrawableEvent(DrawableID id, const void *text,
		unsigned char secondSelector, unsigned char firstSelector);

private:
	char m_beforeTarget[0x30a4];
	Gen006CCC50EventTarget *m_target;
};

void BfmeDrawableEventManager::forwardDrawableEvent(DrawableID id,
	const void *text, unsigned char secondSelector,
	unsigned char firstSelector)
{
	BfmeDrawableEventManager *self = this;
	if (self->m_target != 0)
	{
		typedef void (Gen006CCC50EventTarget::*MemberThunk)(DrawableID,
			AsciiString, unsigned char, unsigned char);
		union
		{
			void (*function)(void);
			MemberThunk member;
		} thunk;
		thunk.function = j_0000c3d3;
		(self->m_target->*thunk.member)(id,
			*(const AsciiString *)text, secondSelector, firstSelector);
	}
}
