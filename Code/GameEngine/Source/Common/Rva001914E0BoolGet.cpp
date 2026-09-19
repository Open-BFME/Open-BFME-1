// cl: /DNDEBUG /MD

class Rva001914E0Owner
{
public:
	bool get() const;

private:
	char padding[0x24];
	bool value;
};

bool Rva001914E0Owner::get() const
{
	return value;
}
