// Forward the caller-owned result storage to the matched texture-handle getters.
// Retail passes ECX=table, then output/row/column on the stack. Returning a
// different C++ handle type normally introduces a copy-back temporary; this
// inline constructor preserves the native hidden-result ABI without that copy.
// See attempt_support/20261111-counted-handle-result-forwarding.md.

class BfmeHandleCX;
class Gen_009292E0 { public: BfmeHandleCX bfmeGet(int, int) const; };
class Gen_0092C9D0 { public: BfmeHandleCX bfmeGet(int, int) const; };

struct BfmeHandleUZA
{
    template<class T> __forceinline BfmeHandleUZA(const T *source, int a, int b)
    {
        union {
            BfmeHandleCX (T::*original)(int, int) const;
            void (T::*fill)(BfmeHandleUZA *, int, int) const;
        } call;
        call.original = &T::bfmeGet;
        (source->*call.fill)(this, a, b);
    }
	int m_bfmeValue;
};

class BfmeThingAUZA
{
public:
	BfmeHandleUZA bfmeGoAUZA(int a, int b) const;
	char m_bfmePad[0x9c];
	Gen_009292E0 *m_bfmeSub;
};

BfmeHandleUZA BfmeThingAUZA::bfmeGoAUZA(int a, int b) const
{
	volatile int m_bfmeDead = 0;
	return BfmeHandleUZA(m_bfmeSub, a, b);
}

class BfmeThingBUZA
{
public:
	BfmeHandleUZA bfmeGoBUZA(int a, int b) const;
	char m_bfmePad[0x9c];
	Gen_0092C9D0 *m_bfmeSub;
};

BfmeHandleUZA BfmeThingBUZA::bfmeGoBUZA(int a, int b) const
{
	volatile int m_bfmeDead = 0;
	return BfmeHandleUZA(m_bfmeSub, a, b);
}
