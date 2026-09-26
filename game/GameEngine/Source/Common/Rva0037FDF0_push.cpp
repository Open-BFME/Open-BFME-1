// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// Rva0037FDF0::push, retail 0x0037FDF0, 48 bytes on d_0036dcc0.
// Inlined vector<float>::push_back; overflow ILT 0x000264D1.

#include <vector>

class Rva0037FDF0
{
public:
	void push( float value );

private:
	_STL::vector<float> m_items;
};

// ?push@Rva0037FDF0@@QAEXM@Z
void Rva0037FDF0::push( float value )
{
	m_items.push_back( value );
}
