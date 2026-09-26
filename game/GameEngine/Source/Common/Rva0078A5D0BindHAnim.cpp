// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x0078A5D0: bind an HAnim onto an empty Rva007896C0 holder.
// Path is name + "." + name; optional asset-list glob "a*" + path when the
// FirstUpdateSubsystem pointer at 0x0134FAA0 is set. Identity is not recovered
// beyond the landed neighbour publish helper and the Get_HAnim / AssetList
// callees.

#include <set>

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;

public:
	void concat(const StringBase<T> &other);

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	void concat(const char *text);
	void concat(const AsciiString &other)
	{
		StringBase<char>::concat(*(const StringBase<char> *)&other);
	}
	AsciiString &operator+=(const AsciiString &other);

	const char *str(void) const
	{
		return m_data ? m_data->m_text : "";
	}
};

class HAnimClass;

HAnimClass *Get_HAnim(const char *name);

class Rva0078A5D0Owner
{
public:
	virtual void release(void);
	int m_refCount;
};

class AssetList
{
public:
	AssetList &operator<<(const AsciiString &name);
};

struct Gen_t_00140950_k4
{
	int m_value;
};

typedef _STL::_Rb_tree<Gen_t_00140950_k4, Gen_t_00140950_k4,
	_STL::_Identity<Gen_t_00140950_k4>, _STL::less<Gen_t_00140950_k4>,
	_STL::allocator<Gen_t_00140950_k4> > ImageAssetTree;

class BfmeList950B
{
public:
	BfmeList950B(void);

	~BfmeList950B(void)
	{
		((ImageAssetTree *)this)->~ImageAssetTree();
	}

	char m_storage[0x14];
};

extern void Rva009EBAC0(int value);

#define FirstUpdateSubsystem (*(void **)0x0134FAA0)

class Rva007896C0
{
public:
	bool bindHAnim(const AsciiString &name, Rva0078A5D0Owner *owner, int mode);
	void publish(int first, int second);

	Rva0078A5D0Owner *m_owner;
	HAnimClass *m_animation;
	int m_second;
	int m_first;
};

// @?bindHAnim@Rva007896C0@@QAE_NABVAsciiString@@PAVRva0078A5D0Owner@@H@Z 0x0078A5D0
bool Rva007896C0::bindHAnim(const AsciiString &name, Rva0078A5D0Owner *owner, int mode)
{
	if (owner == 0)
		return false;
	if (m_owner != 0)
		return false;
	if (m_animation != 0)
		return false;

	AsciiString path(name);
	path.concat(".");
	path.concat(name);

	if (FirstUpdateSubsystem)
	{
		AsciiString glob("a*");
		glob += path;
		BfmeList950B assets;
		(*(AssetList *)&assets) << glob;
		Rva009EBAC0((int)&assets);
	}

	HAnimClass *anim = Get_HAnim(path.str());
	m_animation = anim;
	if (anim == 0)
		return false;

	++owner->m_refCount;
	Rva0078A5D0Owner *oldOwner = m_owner;
	if (oldOwner != 0)
	{
		if (--oldOwner->m_refCount == 0)
			oldOwner->release();
	}

	m_owner = owner;
	m_first = 0;
	publish(1, mode);
	return true;
}
