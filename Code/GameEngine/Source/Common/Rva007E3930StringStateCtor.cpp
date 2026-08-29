// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x007E3930.  The surrounding type identity is not yet recovered, so
// this reconstruction keeps an address-derived name.  The body constructs its
// StringBase<char> base from the first character of the caller's text, clears
// two state fields, selects mode 4, and forwards all three constructor inputs
// to the derived initializer at 0x007E35E0 through ILT 0x00005C0E.

class Rva007E3930StringState;

template <typename T>
class StringBase
{
    friend class Rva007E3930StringState;

private:
	StringBase(const T *text, int length);
	~StringBase(void);

private:
	void *m_data;
};

class Rva007E3930StringState : public StringBase<char>
{
public:
	Rva007E3930StringState(const char *text, int valueA, int valueB);

private:
	void _bfme_initialize_007E35E0(const char *text, int valueA, int valueB);

	int m_value4;
	int m_mode;
	int m_valueC;
};

// ??0Rva007E3930StringState@@QAE@PBDHH@Z
Rva007E3930StringState::Rva007E3930StringState(const char *text, int valueA, int valueB) :
	StringBase<char>(text, 1)
{
	m_value4 = 0;
	m_valueC = 0;
	m_mode = 4;
	_bfme_initialize_007E35E0(text, valueA, valueB);
}
