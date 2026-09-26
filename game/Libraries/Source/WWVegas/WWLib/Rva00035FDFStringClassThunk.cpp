// Retail RVA 0x00035FDF is an incremental-link tail thunk to
// StringClass::operator=(const StringClass &) at 0x0013B600.

class StringClass
{
public:
	const StringClass &operator= (const StringClass &string);
};

class Rva00035FDFStringClassThunk
{
public:
	const StringClass &forward(const StringClass &string);
};

// ?forward@Rva00035FDFStringClassThunk@@QAEABVStringClass@@ABV2@@Z
const StringClass &Rva00035FDFStringClassThunk::forward(
	const StringClass &string)
{
	return ((StringClass *)this)->operator= (string);
}
