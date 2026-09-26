// cl: /DNDEBUG /MD

class AddressObject001503F0
{
public:
	AddressObject001503F0 *returnThis(void *unused);
};

AddressObject001503F0 *AddressObject001503F0::returnThis(void *unused)
{
	return this;
}
