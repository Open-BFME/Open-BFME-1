// cl: /O2 /MD /EHs-c-

class Rva00881B90Class;

// Declared (not defined) here: bfmeRasterCircleFC's fourth parameter is passed
// by value, so this TU only needs the name for the mangling and the 12-byte
// { pointer, int, bool } shape that body already had as SomeStruct.
class BfmeRangeUpdaterFC
{
public:
	void *m_bfmeGrid;
	int m_bfmeAmount;
	bool m_bfmeAbsolute;
};

// ?bfmeRasterCircleFC@@YAXHHHVBfmeRangeUpdaterFC@@@Z --
// game/Libraries/Source/taintmanager/taintmanager_impl.cpp
extern void __cdecl bfmeRasterCircleFC( int arg1, int arg2, int arg3, BfmeRangeUpdaterFC s );

class Rva00881B90Class
{
public:
	void update( int arg1, int arg2, int arg3, int arg4, bool arg5 );
};

void Rva00881B90Class::update( int arg1, int arg2, int arg3, int arg4, bool arg5 )
{
	if ( arg3 >= 0 && (arg4 != 0 || arg5) )
	{
		BfmeRangeUpdaterFC s;
		s.m_bfmeGrid = this;
		s.m_bfmeAmount = arg4;
		s.m_bfmeAbsolute = arg5;
		bfmeRasterCircleFC( arg1, arg2, arg3, s );
	}
}
