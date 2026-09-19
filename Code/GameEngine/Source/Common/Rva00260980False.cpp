// The carved body at 0x00260980 returns false and has no semantic owner evidence.
typedef bool Bool;

class Rva00260980False
{
public:
	static Bool get();
};

Bool Rva00260980False::get()
{
	return false;
}
