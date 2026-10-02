// cl: /Od
// stlport

#include <string>

template <> char *_STL::basic_string<char, _STL::char_traits<char>,
	_STL::allocator<char> >::erase(char *first, char *last);

class BfmeStrVLT
{
public:
	BfmeStrVLT *bfmeAppendVLT( unsigned n, char c );
};

class BfmeStrVME
{
public:
	void bfmeResizeVME(unsigned n, char c);
	void bfmeEraseVME(char *a, char *b);
	void bfmeAppendVME(unsigned n, char c);
	char *m_bfme00;
	char *m_bfme04;
};

void BfmeStrVME::bfmeResizeVME(unsigned n, char c)
{
	if (n <= (unsigned)(m_bfme04 - m_bfme00))
	{
		char *n1 = m_bfme04;
		char *n2;
		char *n3;
		char *n4 = m_bfme00;
		((_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > *)this)
			->erase(n4 + n, n1);
	}
	else
		((BfmeStrVLT *)this)->bfmeAppendVLT(
			n - (unsigned)(m_bfme04 - m_bfme00), c);
}
