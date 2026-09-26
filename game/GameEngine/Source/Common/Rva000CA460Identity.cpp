// cl: /O2

// Retail 0x000CA460 returns its receiver unchanged in a three-byte body.
// The carved boundary and ILT thunk prove the body, but not a semantic owner.
class Rva000CA460Identity
{
public:
	Rva000CA460Identity *identity();
};

Rva000CA460Identity *Rva000CA460Identity::identity()
{
	return this;
}
