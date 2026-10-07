// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

void __cdecl operator delete(void *);

// The name's teardown is a direct call to StringBase<char>::releaseBuffer
// (0x00887940), as retail emits it; this TU-local view keeps that private
// member's mangling and grants this class access.
class BfmeOwnedStringState;
template <class T> class StringBase
{
	friend class BfmeOwnedStringState;
	void releaseBuffer();
	T *m_data;
};

class Gen_dtor_0034dd90
{
public:
	virtual ~Gen_dtor_0034dd90();
};

class BfmeOwnedStringState
{
public:
	void resetOwnedObject();

private:
	int m_head;
	StringBase<char> m_name;
	int m_reset;
	Gen_dtor_0034dd90 *m_owned;
};

void __cdecl j_0001cdcd();

void BfmeOwnedStringState::resetOwnedObject()
{
	m_name.releaseBuffer();
	Gen_dtor_0034dd90 *owned = m_owned;
	m_reset = 1;
	if (owned != 0) {
		reinterpret_cast<void (__fastcall *)(Gen_dtor_0034dd90 *)>(j_0001cdcd)(owned);
		operator delete(owned);
		m_owned = 0;
	}
}
