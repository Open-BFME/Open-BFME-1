// ?getFirstDword@Rva000B23D0@@QBEIXZ

class Rva000B23D0
{
public:
	__declspec(noinline) unsigned getFirstDword() const
	{
		return *(const unsigned *)this;
	}
};

unsigned keepRva000B23D0Method(const Rva000B23D0 *value)
{
	return value->getFirstDword();
}
