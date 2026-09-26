// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// Open-BFME: TransitionGroup list append helper at retail 0x0048B390.
// The matched 0x0048B690 caller invokes this on each of four actual
// TransitionGroup objects.  The BFME layout has the real STLport
// list<TransitionWindow *> at this+0x04; the neutral rva spelling avoids
// claiming an unrecovered public declaration for this helper.

// stlport
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <list>

class TransitionWindow;

class TransitionGroup
{
public:
	void rva0048B390( void *destination );

private:
	bool m_fireOnce;
	unsigned char m_padding[3];
	_STL::list<TransitionWindow *> m_transitionWindowList;
};

// ?rva0048B390@TransitionGroup@@QAEXPAX@Z
void TransitionGroup::rva0048B390( void *destination )
{
	_STL::list<TransitionWindow *> *dest =
		(_STL::list<TransitionWindow *> *)destination;
	_STL::list<TransitionWindow *>::iterator it = m_transitionWindowList.begin();
	while (it != m_transitionWindowList.end())
	{
		TransitionWindow *window = *it;
		dest->push_back( window );
		++it;
	}
}
