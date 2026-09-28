// cl: /DNDEBUG /MD /EHs-c-
// Retail 0x00887920: wide less-than through StringBase<wchar_t>::
// compareNoCase. The callee rides the ILT thunk j_0001609f (route
// b_0009efe0) to the wide compareNoCase at 0x0009EFE0, declared out
// of line the way the languagefilter shim routes retail's call.
// __stdcall is what makes the epilogue (ret 8) and size (26 B);
// the cdecl template operator< at 0x0054EB50 ends in a bare ret.

template <typename T>
class StringBase
{
public:
	int compareNoCase(const StringBase &src) const;
};

bool __stdcall Rva00887920LessNoCase(const StringBase<unsigned short> &left, const StringBase<unsigned short> &right)
{
	return left.compareNoCase(right) < 0;
}
