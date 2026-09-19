// The carved leaf returns this, but its anonymous thunk caller does not prove
// a semantic owner.
class Rva00150250Self
{
public:
	void *getSelf();
};

void *Rva00150250Self::getSelf()
{
	return this;
}
