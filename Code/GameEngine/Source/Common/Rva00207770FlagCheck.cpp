// cl: /DNDEBUG /MD /EHs-c-

struct Rva00207770FlagCheck
{
	unsigned char unused[0x1a4];
	unsigned char flags;

	bool is_set() const;
};

bool Rva00207770FlagCheck::is_set() const
{
	return (flags & 6) != 0;
}
