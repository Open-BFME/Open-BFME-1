// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::locale::~locale(), retail 0x00832170, 7 bytes. The body
// carried only a machine byte-dump row; targets/game/reverse/reloc_names.csv holds the name
// with identity=real.
//
// The mirror of the default constructor at 0x00832120, which takes a reference
// on the impl through virtual slot 1: this drops it again through slot 2. The
// member is not cleared, and the release is in tail position, so the whole
// destructor is the impl load, the vtable fetch and a jump.

namespace _STL
{

class _Locale_impl
{
public:
	virtual void _bfme_slot0(void) = 0;
	virtual void _bfme_incr(void) = 0;			// vtable slot 1
	virtual void _bfme_decr(void) = 0;			// vtable slot 2

};

class locale
{
public:
	~locale();

private:
	_Locale_impl *_M_impl;
};

// ??1locale@_STL@@QAE@XZ
locale::~locale()
{
	_M_impl->_bfme_decr();
}

}
