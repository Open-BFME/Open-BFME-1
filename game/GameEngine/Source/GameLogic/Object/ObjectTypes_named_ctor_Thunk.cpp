// cl: /DNDEBUG /MD /EHsc
// ObjectTypes::ObjectTypes(const AsciiString&). Sibling of the default ctor
// in ObjectTypes_ctor_Thunk.cpp. Retail copies m_listName at +4 through an
// out-of-line copy ctor, then zeroes the three-word vector overlay at +8.
// The empty base destructor is what gives the constructor its SEH frame
// (same trick as AttackNugget_ctor_Thunk.cpp).

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
// Retail's AsciiString derives from StringBase<char>: its own copy ctor is the
// forwarder at 0x0005EE50 and it holds nothing of its own, so a caller that
// copies a string encodes the base body at 0x00887B60 directly. The delegation
// has to be visible here for this TU to encode the same call.
template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase<T> &src);

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class AsciiString
{
public:
	// Retail inlines this forwarder, so the call site encodes
	// StringBase<char>'s copy ctor at 0x00887B60 directly.
	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}
	~AsciiString();

private:
	void *m_data;
};

class ObjectTypesBase
{
public:
	~ObjectTypesBase();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ObjectTypes.h
class ObjectTypes : public ObjectTypesBase
{
public:
	ObjectTypes(const AsciiString &listName);
	virtual ~ObjectTypes() {}

private:
	AsciiString m_listName;
	void *m_objTypesBegin;
	void *m_objTypesEnd;
	void *m_objTypesCap;
};

ObjectTypes::ObjectTypes(const AsciiString &listName)
	: m_listName(listName)
	, m_objTypesBegin(0)
	, m_objTypesEnd(0)
	, m_objTypesCap(0)
{
}
