// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
//
// Retail 0x005D5800 is the scalar-deleting wrapper for the thumbnail hash
// entry.  The matched destructor at 0x00013101 and vector-deleting wrapper at
// 0x0005E420 independently establish the template specialization identity.

class StringClass;
class ThumbnailClass;

template <class KeyType, class ValueType>
class HashTemplateClass
{
public:
	class Entry
	{
	public:
		~Entry();
	};
};

void DeleteThumbnailHashEntry(
	HashTemplateClass<StringClass, ThumbnailClass *>::Entry *entry)
{
	delete entry;
}
