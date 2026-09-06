// cl: /DNDEBUG /MD /EHsc
// stlport

// Retail 0x000B0F00, 243 bytes.  This is the copy-assignment body for the
// two-slot BFME audio-info family whose constructor at 0x000B0D10 installs
// vtable 0x010818CC and whose destructor at 0x000B0DF0 tears down these same
// two strings and four vectors.  The assignment deliberately leaves the
// polymorphic prefix untouched, as retail does; this TU emits no vtable.

#include <vector>

template <typename T> class StringBase
{
	friend class AsciiString;
	private:
		StringBase() : m_data(0) {}
		StringBase(const StringBase<T> &other);
		~StringBase();
		void set(const StringBase<T> &other);
		void *m_data;
};

class AsciiString : private StringBase<char>
{
	public:
		AsciiString() : StringBase<char>() {}
		AsciiString(const AsciiString &other) : StringBase<char>(other) {}
		~AsciiString() {}
		AsciiString &operator=(const AsciiString &other)
		{
			StringBase<char>::set(other);
			return *this;
		}
};

struct Gen_t_000b0c00_p8cd
{
	int a[2];
	Gen_t_000b0c00_p8cd();
	Gen_t_000b0c00_p8cd(const Gen_t_000b0c00_p8cd &other);
	~Gen_t_000b0c00_p8cd();
	Gen_t_000b0c00_p8cd &operator=(const Gen_t_000b0c00_p8cd &other);
};

struct Gen_t_000b0560_p8pod
{
	int a[2];
};

class BfmeA1202
{
	public:
		virtual ~BfmeA1202();
		BfmeA1202 &operator=(const BfmeA1202 &other);

	private:
		char m_prefix[4];
		AsciiString m_name;
		AsciiString m_filename;
		int m_word10;
		int m_word14;
		int m_word18;
		int m_word1c;
		int m_word20;
		int m_word24;
		int m_word28;
		int m_word2c;
		int m_word30;
		int m_word34;
		int m_word38;
		int m_word3c;
		_STL::vector<Gen_t_000b0c00_p8cd> m_vector40;
		int m_word4c;
		_STL::vector<Gen_t_000b0c00_p8cd> m_vector50;
		int m_word5c;
		_STL::vector<Gen_t_000b0c00_p8cd> m_vector60;
		int m_word6c;
		int m_word70;
		int m_word74;
		int m_word78;
		int m_word7c;
		int m_word80;
		int m_word84;
		int m_word88;
		_STL::vector<Gen_t_000b0560_p8pod> m_vector8c;
};

BfmeA1202 &BfmeA1202::operator=(const BfmeA1202 &other)
{
	m_name = other.m_name;
	m_filename = other.m_filename;
	m_word10 = other.m_word10;
	m_word14 = other.m_word14;
	m_word18 = other.m_word18;
	m_word1c = other.m_word1c;
	m_word20 = other.m_word20;
	m_word24 = other.m_word24;
	m_word28 = other.m_word28;
	m_word2c = other.m_word2c;
	m_word30 = other.m_word30;
	m_word34 = other.m_word34;
	m_word38 = other.m_word38;
	m_word3c = other.m_word3c;
	m_vector40 = other.m_vector40;
	m_word4c = other.m_word4c;
	m_vector50 = other.m_vector50;
	m_word5c = other.m_word5c;
	m_vector60 = other.m_vector60;
	m_word6c = other.m_word6c;
	m_word70 = other.m_word70;
	m_word74 = other.m_word74;
	m_word78 = other.m_word78;
	m_word7c = other.m_word7c;
	m_word80 = other.m_word80;
	m_word84 = other.m_word84;
	m_word88 = other.m_word88;
	m_vector8c = other.m_vector8c;
	return *this;
}
