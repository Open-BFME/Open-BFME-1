// cl: /DNDEBUG /MD

class AddressObject001AFE20
{
public:
	AddressObject001AFE20 *returnThis(void *unused);
};

AddressObject001AFE20 *AddressObject001AFE20::returnThis(void *unused)
{
	return this;
}
