// cl: /DNDEBUG /MD /EHsc
// ObjectTypes::ObjectTypes(const AsciiString&). Sibling of the default ctor
// in ObjectTypes_ctor_Thunk.cpp. Retail copies m_listName at +4 through an
// out-of-line copy ctor, then zeroes the three-word vector overlay at +8.
// The empty base destructor is what gives the constructor its SEH frame
// (same trick as AttackNugget_ctor_Thunk.cpp).

class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();

private:
	void *m_data;
};

class ObjectTypesBase
{
public:
	~ObjectTypesBase();
};

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
