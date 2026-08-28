// cl: /DNDEBUG /MD /EHsc

// FILE: ICoord2DVectorResizeThunk.cpp ////////////////////////////////////////
//
// STLport vector<ICoord2D>::resize, retail 0x004535F0.
//
// MapUtil.cpp compiles it at 60 of 66 bytes.  Two of the six are the erase
// call, which resolves to that file's own copy rather than the one retail
// calls; the other four are the same fact twice.  Retail returns with ret 0xc
// and forms the fill value's address with `lea edi,[esp+0x10]', so the value
// is passed BY VALUE -- eight bytes of ICoord2D on the stack -- where the port
// passes const ICoord2D&, four bytes, and reads the pointer with a mov.  The
// mangled name follows: QAEXIUICoord2D@@@Z, not the QAEXIABUICoord2D@@@Z the
// work packet guessed.
//
// This is the same by-value fill the resize family at 0x001DC360 and
// 0x009407B0 already landed on; the only thing new here is that erase stays
// out of line, because ICoord2D's element move is not the trivial copy those
// two inline.
//
///////////////////////////////////////////////////////////////////////////////

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	int x;
	int y;
};

namespace _STL
{

template <class Type>
class allocator {};

template <class Type, class Allocator>
class vector
{
public:

	Type *begin() { return _M_start; }
	Type *end() { return _M_finish; }
	unsigned int size() const { return (unsigned int)(_M_finish - _M_start); }

	// Declared, never defined: only the .obj is produced and both calls resolve
	// by mangled name against the ledger.
	Type *erase(Type *first, Type *last);
	void _M_fill_insert(Type *pos, unsigned int n, const Type &value);

	void resize(unsigned int newSize, Type value);

private:

	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;

};

template <class Type, class Allocator>
void vector<Type, Allocator>::resize(unsigned int newSize, Type value)
{
	if (newSize < size())
		erase(begin() + newSize, end());
	else
		_M_fill_insert(end(), newSize - size(), value);
}

template void vector<ICoord2D, allocator<ICoord2D> >::resize(unsigned int, ICoord2D);

}
