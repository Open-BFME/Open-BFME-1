class Rva001C3B50
{
public:
	unsigned int first;
	unsigned int second;
	unsigned int third;
	void or_with(const Rva001C3B50 *other);
};

void Rva001C3B50::or_with(const Rva001C3B50 *other)
{
	first |= other->first;
	second |= other->second;
	third |= other->third;
}
