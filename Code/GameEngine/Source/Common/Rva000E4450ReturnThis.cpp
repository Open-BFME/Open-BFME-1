// Retail 0x000E4450 returns this and removes one dword argument.
class Rva000E4450Object
{
public:
	Rva000E4450Object *returnThis(int value);
};

Rva000E4450Object *Rva000E4450Object::returnThis(int value)
{
	return this;
}
