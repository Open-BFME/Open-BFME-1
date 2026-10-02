// Open-BFME5 conversions.

// 0x0082E5F0 is matched in functions.csv as
// _STL::__node_alloc<true,0>::_M_deallocate
// (game/Libraries/Source/WWVegas/WWLib/node_alloc_M_deallocateThunk.cpp), which
// is the private static member STLport declares there. The loop hands each
// 0x10-byte node straight to it -- the constant is below STLport's _MAX_BYTES,
// so its `deallocate` wrapper is folded away -- so the caller is named as a
// friend here, as the other TU-local __node_alloc shims in the tree do.

struct BfmeNodeVNY
{
	BfmeNodeVNY *m_bfme00;
	BfmeNodeVNY *m_bfme04;
};

class BfmeOwnerVNY
{
public:
	void bfmeResetVNY();
	char m_bfmePad0000[0x1304];
	BfmeNodeVNY *m_bfme1304;
	int m_bfme1308;
	int m_bfme130c;
	int m_bfme1310;
	int m_bfme1314;
};

namespace _STL
{

template <bool __threads, int __inst>
class __node_alloc
{
	friend void BfmeOwnerVNY::bfmeResetVNY();

private:
	static void _M_deallocate( void *p, unsigned int n );
};

}

void BfmeOwnerVNY::bfmeResetVNY()
{
	BfmeNodeVNY *p = m_bfme1304->m_bfme00;

	while (p != m_bfme1304)
	{
		BfmeNodeVNY *n = p;

		p = p->m_bfme00;
		_STL::__node_alloc<true, 0>::_M_deallocate(n, 0x10);
	}
	m_bfme1304->m_bfme00 = m_bfme1304;
	m_bfme1304->m_bfme04 = m_bfme1304;
	m_bfme1308 = -2;
	m_bfme130c = -2;
	m_bfme1310 = -2;
	m_bfme1314 = -2;
}
