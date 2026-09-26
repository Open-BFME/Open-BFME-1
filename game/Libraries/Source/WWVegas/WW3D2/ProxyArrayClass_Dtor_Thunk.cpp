// cl: /DNDEBUG /MD /EHsc

// Slot 0 of the vtable at 0x0113EBAC, which ??0ProxyArrayClass installs.
//
// Byte for byte the same destructor as HAnimComboClass -- same guarded release
// of an owned buffer at +4, same unconditional clearing of the flag at +0xD and
// the count at +8 -- with one instruction's difference: the buffer goes back
// through the array operator delete at 0x00881EF0 rather than the scalar one at
// 0x00881EB0. So this member is an array and HAnimComboClass's is not, and the
// distinction is visible nowhere else in either body.
//
// The deleting stub still uses the scalar form for `this`, which is what tells
// the two calls apart: one is `delete [] m_proxies`, the other is `delete this`.
// MSVC 7.1 folds `delete []` onto the scalar ??3@YAXPAX@Z unless the array
// form is declared where it can see it; retail calls ??_V@YAXPAX@Z here.
void operator delete[]( void *block );

class ProxyArrayClass
{
public:
	ProxyArrayClass(void);
	virtual ~ProxyArrayClass(void);

private:
	unsigned char *m_proxies;
	int m_count;
	bool m_pad;
	bool m_owned;
};

// ??_GProxyArrayClass@@UAEPAXI@Z
ProxyArrayClass::~ProxyArrayClass(void)
{
	if (m_proxies != 0 && m_owned) {
		delete [] m_proxies;
		m_proxies = 0;
	}
	m_owned = false;
	m_count = 0;
}
