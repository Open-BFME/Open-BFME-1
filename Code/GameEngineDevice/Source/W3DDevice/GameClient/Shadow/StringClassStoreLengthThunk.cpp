// cl: /DNDEBUG /MD /EHsc

class StringClass
{
    void Store_Length(int);
};

// ?Store_Length@StringClass@@AAEXH@Z
void StringClass::Store_Length(int length)
{
	unsigned char *data = *reinterpret_cast<unsigned char **>(this);
	if (data != *reinterpret_cast<unsigned char **>(0x012d9124)) {
		*reinterpret_cast<int *>(data - 4) = length;
	}
}
