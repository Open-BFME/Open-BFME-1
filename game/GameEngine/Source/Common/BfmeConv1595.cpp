// Open-BFME5 conversions.

// The string members are retail's StringBase<char> (one 4-byte Header*), and the
// clear call at 0x00887940 is the matched StringBase<char>::releaseBuffer body
// (StringBase.cpp), which retail declares private, so each caller here is its
// friend. Declared, not defined: this TU calls that body, it does not own it.
template <typename T>
class StringBase
{
protected:
	T *m_data;

private:
	void releaseBuffer();

	friend class BfmeStrVSV;
	friend class BfmeOwnVSV;
};

class BfmeStrVSV : private StringBase<char>
{
public:
	BfmeStrVSV() { m_data = 0; }
	~BfmeStrVSV() { releaseBuffer(); }
};

class BfmeOwnVSV
{
public:
	BfmeOwnVSV();
	virtual void bfmeSlot0VSV() = 0;
	BfmeStrVSV m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	char m_bfme10;
	BfmeStrVSV m_bfme14;
	BfmeStrVSV m_bfme18;
	int m_bfme1c;
};

BfmeOwnVSV::BfmeOwnVSV()
	: m_bfme08(0), m_bfme0c(0), m_bfme10(0), m_bfme1c(0)
{
	m_bfme04.releaseBuffer();
}
