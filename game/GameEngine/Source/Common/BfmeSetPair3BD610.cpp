// cl: /O2
// A by-value pair copied into the object, and a second copy taken into a frame
// slot nothing reads. That dead copy is the whole body's shape: written as a
// plain local it is eliminated and the function is 17 bytes, so the local has to
// be volatile for the two stores to survive. The third argument is unused.

struct BfmePair3BD610
{
	int m_first;
	int m_second;
};

class BfmeThing3BD610
{
public:
	void bfmeSet3BD610(BfmePair3BD610 value, int extra);

private:
	char m_pad[0xc];
	BfmePair3BD610 m_value;
};

void BfmeThing3BD610::bfmeSet3BD610(BfmePair3BD610 value, int extra)
{
	volatile BfmePair3BD610 held = value;

	m_value = value;
}
