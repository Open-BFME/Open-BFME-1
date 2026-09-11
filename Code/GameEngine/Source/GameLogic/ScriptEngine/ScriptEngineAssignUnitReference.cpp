// cl: /DNDEBUG /MD /EHsc
// Open-BFME: ScriptEngine::assignUnitReference at retail 0x003450F0.
// ScriptActions callers and the 0x0003D663 ILT target identify this as the
// unit-valued twin of ScriptEngineAssignTeamReference.cpp.

class AsciiString;

template <class T> class StringBase
{
private:
	friend class AsciiString;

	struct Data
	{
		int refs;
		int length;
		T data[1];
	};

	Data *m_data;
	StringBase() : m_data(0) {}
	StringBase(const StringBase &other);
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString();
};

class Object
{
public:
	char m_beforeReference[0x74];
	void *m_reference;
};

struct ScriptReferenceKey
{
	__forceinline ScriptReferenceKey(const AsciiString &canonical,
		const AsciiString &name) : m_canonical(canonical), m_name(name) {}

	AsciiString m_canonical;
	AsciiString m_name;
};

struct ScriptReferenceBuiltRecord
{
	AsciiString m_canonical;
	AsciiString m_name;
	int m_nameData;
};

struct ScriptReferenceRecordBase
{
	__forceinline ScriptReferenceRecordBase(
		const ScriptReferenceBuiltRecord &record) :
		m_canonical(record.m_canonical), m_name(record.m_name),
		m_nameData(record.m_nameData) {}

	AsciiString m_canonical;
	AsciiString m_name;
	int m_nameData;
};

struct ScriptReferenceRecord : ScriptReferenceRecordBase
{
	__forceinline ScriptReferenceRecord(
		const ScriptReferenceBuiltRecord &record) :
		ScriptReferenceRecordBase(record) {}
};

struct ScriptReferenceNode
{
	char m_beforeValue[0x18];
	void *m_value;
};

struct ScriptReferenceInsertResult
{
	ScriptReferenceNode *m_node;
	bool m_inserted;
};

extern void j_00016e64();
extern void j_000268be();

class ScriptReferenceMap
{
};

class ScriptEngine
{
public:
	void assignUnitReference(const AsciiString &name, Object *object);
};

typedef ScriptReferenceBuiltRecord (__cdecl *MakeReferenceRecord)(
	const ScriptReferenceKey &, const AsciiString *const &);

void ScriptEngine::assignUnitReference(const AsciiString &name, Object *object)
{
	ScriptReferenceKey source(
		*(const AsciiString *)((const char *)this + 0x17088), name);

	typedef void (ScriptReferenceMap::*InsertReference)(
		ScriptReferenceInsertResult *, const ScriptReferenceRecord &);
	union
	{
		void (*raw)();
		InsertReference typed;
	} insertReference;
	insertReference.raw = j_000268be;

	ScriptReferenceInsertResult result;
	(((*(ScriptReferenceMap *)((char *)this + 0x16058)).*
		insertReference.typed)(&result,
			ScriptReferenceRecord(((MakeReferenceRecord)j_00016e64)(
				source, 0))));

	void *reference = object->m_reference;
	ScriptReferenceNode *node = result.m_node;
	node->m_value = reference;
}
