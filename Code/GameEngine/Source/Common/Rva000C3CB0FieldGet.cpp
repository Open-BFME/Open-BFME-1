// cl: /DNDEBUG /MD

class Rva000C3CB0Owner
{
public:
	int get() const;

private:
	char padding[0x10];
	int value;
};

int Rva000C3CB0Owner::get() const
{
	return value;
}
