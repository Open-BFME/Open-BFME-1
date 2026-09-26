// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::ctype<char>::ctype, retail 0x00840730, 76 bytes. The body
// carried only a machine byte-dump row. The vtable it installs is the same
// T2NarrowCtype table already claimed by T2CtypeTableFacets.cpp, and the
// destructor at 0x00840780 reseats that table then frees the mask table when
// the delete flag is set -- which is the layout of STLport 4.5.3 ctype<char>.
//
// locale::facet : private _Refcount_Base(1) stores 1 at +4 and
// (refs == 0) at +8. ctype then takes the caller's mask table or the classic
// table at +0xC, and sets _M_delete at +0x10 only when both the table pointer
// and the delete flag are true.

namespace _STL
{

struct _Refcount_Base
{
	int _M_ref_count;
	_Refcount_Base(int n) : _M_ref_count(n) {}
};

class locale
{
public:
	class facet : private _Refcount_Base
	{
	protected:
		explicit facet(unsigned int no_del = 0)
			: _Refcount_Base(1), _M_delete(no_del == 0) {}
		virtual ~facet();

	private:
		const bool _M_delete;
	};
};

class ctype_base
{
public:
	typedef unsigned int mask;
};

template <class CharT>
class ctype
{
};

template <>
class ctype<char> : public locale::facet, public ctype_base
{
public:
	explicit ctype(const mask *tab = 0, bool del = false, unsigned int refs = 0);

protected:
	virtual ~ctype();

	static const mask *classic_table();

private:
	static const mask _S_classic_table[257];
	const mask *_M_ctype_table;
	bool _M_delete;
};

inline const ctype<char>::mask *ctype<char>::classic_table()
{
	return &_S_classic_table[1];
}

// ??0?$ctype@D@_STL@@QAE@PBI_NI@Z
ctype<char>::ctype(const mask *tab, bool del, unsigned int refs)
	: locale::facet(refs),
	  _M_ctype_table(tab ? tab : classic_table()),
	  _M_delete(tab && del)
{
}

}
