// ?dup_003c3700@@YAXXZ
// Retail RVA 0x003C3700. The owning class and method name remain unknown.

struct BfmePair003C3700
{
	char m_first;
	char m_second;
};

namespace Gen003C2EE0Stl
{
	template <class Type>
	class allocator
	{
	};

	template <class Type, class Allocator>
	class vector
	{
	public:
		void resize(unsigned int target, Type pair);
	};
}

typedef Gen003C2EE0Stl::vector<unsigned short,
	Gen003C2EE0Stl::allocator<unsigned short> > Gen003C2EE0Vector;

class Rva003C3700 : public Gen003C2EE0Vector
{
public:
	void rva003c3700(void *target);
};

void Rva003C3700::rva003c3700(void *target)
{
	BfmePair003C3700 pair;

	pair.m_first = 1;
	pair.m_second = 0;

	resize((unsigned int)target, *(unsigned short *)&pair);
}
