// cl: /O2 /Ob2 /DNDEBUG /MD /EHs-c-

class Rva0008DEB0ReturnThis
{
public:
	void *returnThis();
};

void *Rva0008DEB0ReturnThis::returnThis()
{
	return this;
}
