// ?bfmeRefreshEY@BfmeHostEY@@QAEXXZ
// partial score=0.94 date=2026-09-28
// ?bfmeRefreshEY@BfmeHostEY@@QAEXXZ
// Retail 0x0094D450, 1111 bytes: rebuilds the host's texture atlas.  Sorts
// the textures of the +0x08 map<RefCountPtr<TextureClass>, rect> by area into
// a local multimap, packs them in descending area on a 32-pixel row-skyline
// (rows[64], doubling the atlas until size*64 exceeds the +0x00 limit), writes
// each rect back through map::operator[] (0x0094D370), creates the atlas via
// the +0x18 handle, blits every texture with D3DXLoadSurfaceFromSurface and
// filters the mip chain.  Owner/role proven by the matched bfmeLookupEY caller.
// The STL classes are a view in namespace _STL (as Rva0019A1D0TreeCtor.cpp)
// so the retail direct calls to __new_alloc::allocate, _Rb_global and the
// out-of-line ~_Rb_tree survive; the real STLport either imports them (DLL)
// or inlines them (static lib).
// cl: /DNDEBUG /MD /EHsc

class TextureClass
{
public:
	void Add_Ref()
	{
		++m_numRefs;
	}
	void Release_Ref();

	void *m_vftable;
	unsigned short m_numRefs;
};

template <class T>
class RefCountPtr
{
public:
	RefCountPtr() : m_referent(0) {}
	RefCountPtr(const RefCountPtr &other) : m_referent(other.m_referent)
	{
		if (m_referent != 0)
			m_referent->Add_Ref();
	}
	~RefCountPtr()
	{
		if (m_referent != 0)
			m_referent->Release_Ref();
	}
	bool operator<(const RefCountPtr &other) const
	{
		return m_referent < other.m_referent;
	}

	T *m_referent;
};

typedef RefCountPtr<TextureClass> TexturePtr;

// Ledger views of the texture handle's out-of-line accessors.
class BfmeThingEF
{
public:
	int bfmeAskEF();
};

class BfmeThingGN
{
public:
	int bfmeAskGN();
};

static __forceinline int textureWidth(TexturePtr &texture)
{
	return ((BfmeThingEF *)&texture)->bfmeAskEF();
}

static __forceinline int textureHeight(TexturePtr &texture)
{
	return ((BfmeThingGN *)&texture)->bfmeAskGN();
}

namespace _STL
{

template <class T> class allocator {};
template <class T> struct less {};
template <class P> struct _Select1st {};
template <class T> struct _Nonconst_traits {};

template <class T1, class T2>
struct pair
{
	pair(const T1 &a, const T2 &b) : first(a), second(b) {}
	template <class U1, class U2>
	pair(const pair<U1, U2> &p) : first(p.first), second(p.second) {}

	T1 first;
	T2 second;
};

struct _Rb_tree_node_base
{
	char _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};

template <class V>
struct _Rb_tree_node : public _Rb_tree_node_base
{
	V _M_value_field;
};

template <class Dummy>
struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *x);
	static _Rb_tree_node_base *_M_decrement(_Rb_tree_node_base *x);
};

template <class V, class Traits>
struct _Rb_tree_iterator
{
	typedef V value_type;

	_Rb_tree_iterator(_Rb_tree_node_base *x) : _M_node(x) {}
	V &operator*() const { return ((_Rb_tree_node<V> *)_M_node)->_M_value_field; }
	V *operator->() const { return &((_Rb_tree_node<V> *)_M_node)->_M_value_field; }
	_Rb_tree_iterator &operator++() { _M_node = _Rb_global<bool>::_M_increment(_M_node); return *this; }
	_Rb_tree_iterator &operator--() { _M_node = _Rb_global<bool>::_M_decrement(_M_node); return *this; }
	bool operator!=(const _Rb_tree_iterator &x) const { return _M_node != x._M_node; }

	_Rb_tree_node_base *_M_node;
};

template <class It>
struct reverse_iterator
{
	reverse_iterator(const It &x) : current(x) {}
	typename It::value_type &operator*() const { It tmp = current; return *--tmp; }
	typename It::value_type *operator->() const { return &(operator*()); }
	reverse_iterator &operator++() { --current; return *this; }
	bool operator!=(const reverse_iterator &x) const { return current != x.current; }

	It current;
};

class __new_alloc
{
public:
	static void *allocate(unsigned int n);
};

template <class K, class V, class KoV, class Cmp, class A>
class _Rb_tree
{
public:
	typedef _Rb_tree_iterator<V, _Nonconst_traits<V> > iterator;

	_Rb_tree()
	{
		_M_header = 0;
		_M_header = (_Rb_tree_node_base *)__new_alloc::allocate(sizeof(_Rb_tree_node<V>));
		_M_node_count = 0;
		_M_header->_M_color = 0;
		_M_header->_M_parent = 0;
		_M_header->_M_left = _M_header;
		_M_header->_M_right = _M_header;
	}
	~_Rb_tree();

	iterator begin() { return _M_header->_M_left; }
	iterator end() { return _M_header; }

	iterator insert_equal(const V &v)
	{
		_Rb_tree_node_base *y = _M_header;
		_Rb_tree_node_base *x = _M_header->_M_parent;
		while (x != 0)
		{
			y = x;
			x = v.first < ((_Rb_tree_node<V> *)x)->_M_value_field.first ? x->_M_left : x->_M_right;
		}
		return _M_insert(x, y, v, 0);
	}

private:
	iterator _M_insert(_Rb_tree_node_base *x, _Rb_tree_node_base *y, const V &v,
		_Rb_tree_node_base *w);

public:
	_Rb_tree_node_base *_M_header;
	unsigned int _M_node_count;
	Cmp _M_key_compare;
};

template <class K, class T, class Cmp = less<K>, class A = allocator<pair<const K, T> > >
class multimap
{
public:
	typedef pair<const K, T> value_type;
	typedef _Rb_tree<K, value_type, _Select1st<value_type>, Cmp, allocator<value_type> > _Rep_type;
	typedef typename _Rep_type::iterator iterator;
	typedef reverse_iterator<iterator> reverse_iterator;

	iterator insert(const value_type &v) { return _M_t.insert_equal(v); }
	reverse_iterator rbegin() { return reverse_iterator(_M_t.end()); }
	reverse_iterator rend() { return reverse_iterator(_M_t.begin()); }

	_Rep_type _M_t;
};

template <class K, class T, class Cmp = less<K>, class A = allocator<pair<const K, T> > >
class map
{
public:
	typedef pair<const K, T> value_type;
	typedef _Rb_tree<K, value_type, _Select1st<value_type>, Cmp, allocator<value_type> > _Rep_type;
	typedef typename _Rep_type::iterator iterator;

	iterator begin() { return _M_t.begin(); }
	iterator end() { return _M_t.end(); }
	T &operator[](const K &k);

	_Rep_type _M_t;
};

}

// The per-texture atlas rectangle (operator[] at 0x0094D370).
struct Rva0094D370Value
{
	int left;
	int top;
	int right;
	int bottom;
};

typedef _STL::map<TexturePtr, Rva0094D370Value> Rva0094D370Map;

// Area-sorted value (the multimap _M_insert at 0x0094CA90).
struct Rva0094CA90Value
{
	Rva0094CA90Value(const TexturePtr &t) : texture(t) {}

	TexturePtr texture;
};

typedef _STL::multimap<unsigned int, Rva0094CA90Value> Rva0094CA90Map;

class BfmeHandleCX;

class BfmePairDW : public _STL::pair<int, TexturePtr>
{
};

BfmePairDW __cdecl bfmeMakePair(const int *first, const BfmeHandleCX *second);

class W3DRadarResetSurface
{
public:
	~W3DRadarResetSurface();

	void *m_surface;
};

class W3DRadarResetTexture
{
public:
	W3DRadarResetSurface getSurfaceLevel();
};

class Rva008FC830Surface
{
public:
	void fill(unsigned int value);
};

#pragma comment(linker, "/alternatename:?fill@Rva008FC830Surface@@QAEXI@Z=?d_008fc830@@YAXXZ")

struct IDirect3DBaseTexture8;

class TextureBaseClass
{
public:
	IDirect3DBaseTexture8 *Peek_D3D_Base_Texture() const;
};

class BfmeThing930A
{
public:
	void bfmeGo930A();
};

class Rva006D6050
{
public:
	void init(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
};

class Rva0094D450Texture
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual bool slot28();
};

extern "C" long __stdcall D3DXLoadSurfaceFromSurface(void *dst, const void *dstPalette,
	const void *dstRect, void *src, const void *srcPalette, const void *srcRect,
	unsigned long filter, unsigned long colorKey);
extern "C" long __stdcall D3DXFilterTexture(IDirect3DBaseTexture8 *texture,
	const void *palette, unsigned long srcLevel, unsigned long filter);

class BfmeHostEY
{
public:
	void bfmeRefreshEY();

	unsigned int m_maxSize;			// +0x00
	unsigned int m_format;			// +0x04
	Rva0094D370Map m_rects;			// +0x08
	Rva0094D450Texture *m_texture;		// +0x18
	bool m_dirty;				// +0x1C
	unsigned char m_fill;			// +0x1D
	float m_scaleY;				// +0x20
	float m_scaleX;				// +0x24
};

void BfmeHostEY::bfmeRefreshEY()
{
	m_dirty = false;
	((BfmeThing930A *)&m_texture)->bfmeGo930A();
	m_scaleY = m_scaleX = 1.0f;

	Rva0094CA90Map sorted;
	for (Rva0094D370Map::iterator it = m_rects.begin(); it != m_rects.end(); ++it)
	{
		TexturePtr &texture = (TexturePtr &)it->first;
		int area = textureWidth(texture) * textureHeight(texture);
		sorted.insert(bfmeMakePair(&area, (const BfmeHandleCX *)&texture));
	}

	int size = 1;
	int rows[64];
	rows[0] = 0;
	for (Rva0094CA90Map::reverse_iterator rit = sorted.rbegin(); rit != sorted.rend(); ++rit)
	{
		TexturePtr texture = rit->second.texture;
		int width = (unsigned int)(textureWidth(texture) + 31) >> 5;
		int height = (unsigned int)(textureHeight(texture) + 31) >> 5;
		int row;
		for (;;)
		{
			row = 0;
			int last = size - height;
			for (; row <= last; row++)
			{
				int i;
				for (i = 0; i < height; i++)
				{
					if (rows[row + i] + width > size)
						break;
				}
				if (i == height)
					break;
			}
			if (row <= last)
				break;

			if ((unsigned int)(size * 64) > m_maxSize)
				return;
			int grown = size * 2;
			for (int i = size; i < grown; i++)
				rows[i] = 0;
			size = grown;
		}

		int column = 0;
		for (int i = 0; i < height; i++)
		{
			if (rows[row + i] > column)
				column = rows[row + i];
		}
		for (int i = 0; i < height; i++)
			rows[row + i] = width + column;

		Rva0094D370Value &rect = m_rects[texture];
		rect.left = column << 5;
		rect.top = row << 5;
		rect.right = textureWidth(texture) + rect.left;
		rect.bottom = textureHeight(texture) + rect.top;
	}

	int pixels = size << 5;
	((Rva006D6050 *)&m_texture)->init(pixels, pixels, m_format, 0, 1, 0);
	if (m_texture == 0 || !m_texture->slot28())
		return;

	m_scaleY = m_scaleX = 1.0f / (float)pixels;
	W3DRadarResetSurface destination = ((W3DRadarResetTexture *)&m_texture)->getSurfaceLevel();
	((Rva008FC830Surface *)&destination)->fill(m_fill);

	for (Rva0094D370Map::iterator it = m_rects.begin(); it != m_rects.end(); ++it)
	{
		TexturePtr texture = it->first;
		Rva0094D370Value rect = it->second;
		W3DRadarResetSurface source = ((W3DRadarResetTexture *)&texture)->getSurfaceLevel();
		D3DXLoadSurfaceFromSurface(destination.m_surface, 0, &rect, source.m_surface, 0, 0, 1, 0);
	}

	D3DXFilterTexture(((TextureBaseClass *)&m_texture)->Peek_D3D_Base_Texture(), 0,
		0xffffffff, 0xffffffff);
}
