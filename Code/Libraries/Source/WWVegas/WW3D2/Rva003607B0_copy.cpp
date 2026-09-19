// cl: /O2 /DNDEBUG /MD /EHsc

// The carved body copies six dwords from this+0xa8 into its destination.
struct Rva003607B0Words {
	unsigned int words[6];
};

class Rva003607B0 {
public:
	Rva003607B0Words copy();

private:
	unsigned char pad[0xa8];
	Rva003607B0Words words;
};

Rva003607B0Words Rva003607B0::copy()
{
	return words;
}
