// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <vector>

class WindowManager
{
public:
	void unidentified_0002e9a1( int value );

private:
	char m_unmodelled000[ 0x198 ];
	_STL::vector<int> m_values198;
	bool m_valuesChanged1A4;
};

// ?unidentified_0002e9a1@WindowManager@@QAEXH@Z
void WindowManager::unidentified_0002e9a1( int value )
{
	m_values198.push_back( value );
	m_valuesChanged1A4 = true;
}
