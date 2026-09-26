// Rva8CD490Target::consume, retail RVA 0x008BD490 (56 bytes).
// The target is the non-virtual wrapper stored at +0x24 by the Apt holder.

class BfmeQuery1279
{
public:
	void bfmeQuery1279(void *value, int zero, void **other, void **result);
};

class BfmeWrapper1279
{
public:
	void bfmeProcess1279(void *value);

protected:
	BfmeQuery1279 *m_query;
};

class Rva8CCCE0Value
{
public:
	char m_padding00[8];
	void *m_bfme08;
};

class Rva8CD490Target : public BfmeWrapper1279
{
public:
	void consume(Rva8CCCE0Value *value);
};

void Rva8CD490Target::consume(Rva8CCCE0Value *value)
{
	void *other;
	void *result = 0;
	m_query->bfmeQuery1279(value->m_bfme08, 0, &other, &result);
	bfmeProcess1279(result);
}

// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
