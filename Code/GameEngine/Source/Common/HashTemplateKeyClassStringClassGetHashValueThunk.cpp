// cl: /DNDEBUG /MD /EHsc
// HashTemplateKeyClass<StringClass>::Get_Hash_Value.
//
// BFME's StringClass specialization is the byte-wise FNV-ish hash of the
// WW3D2/meshmdl.cpp family (see Code/Libraries/Source/WWVegas/WW3D2/
// meshmdl_sidehash.cpp, whose Vector3 sibling at 0x0094DB70 is the identical
// body with a trip count of 12): it hashes sizeof(T) raw bytes of the object
// rather than the string contents, so the loop bound is a compile-time
// constant and MSVC unrolls it six-wide -- 24 / 6 == 4 loop iterations.
// StringClass itself is never dereferenced, so a forward declaration suffices
// and the wwstring.h/StringBase shims are not pulled in.

class StringClass;

template <class T>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/hashtemplate.h
class HashTemplateKeyClass
{
public:
	static unsigned int Get_Hash_Value(const T &);
};

// ?Get_Hash_Value@?$HashTemplateKeyClass@VStringClass@@@@SAIABVStringClass@@@Z
unsigned int HashTemplateKeyClass<StringClass>::Get_Hash_Value(const StringClass &s)
{
	const unsigned char *buffer = (const unsigned char *)&s;
	unsigned int hval = 0;
	for (unsigned int a = 0; a < 24U; ++a) {
		hval += 37 * hval + buffer[a];
	}
	return hval;
}
