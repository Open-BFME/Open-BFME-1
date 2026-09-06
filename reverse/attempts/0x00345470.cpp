// ?assignTeamReference@ScriptEngine@@QAEXABVAsciiString@@PAVTeam@@@Z
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc

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

class Team
{
public:
	char m_beforeReference[8];
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
	__forceinline ScriptReferenceRecordBase(const ScriptReferenceBuiltRecord &record) :
		m_canonical(record.m_canonical), m_name(record.m_name),
		m_nameData(record.m_nameData) {}

	AsciiString m_canonical;
	AsciiString m_name;
	int m_nameData;
};

struct ScriptReferenceRecord : ScriptReferenceRecordBase
{
	__forceinline ScriptReferenceRecord(const ScriptReferenceBuiltRecord &record) :
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

extern void j_00001ccb();
extern void j_00022be2();

class ScriptReferenceMap
{
};

class ScriptEngine
{
public:
	void assignTeamReference(const AsciiString &name, Team *team);
};

typedef ScriptReferenceBuiltRecord (__cdecl *MakeReferenceRecord)(
	const ScriptReferenceKey &, const AsciiString *const &);

void ScriptEngine::assignTeamReference(const AsciiString &name, Team *team)
{
	ScriptReferenceKey source(
		*(const AsciiString *)((const char *)this + 0x17088), name);

	typedef void (ScriptReferenceMap::*InsertReference)(
		ScriptReferenceInsertResult *, const ScriptReferenceRecord &);
	union
	{
		void (*raw)();
		InsertReference typed;
	} insert_reference;
	insert_reference.raw = j_00022be2;
	ScriptReferenceInsertResult result;
	(((*(ScriptReferenceMap *)((char *)this + 0x16064)).*
		insert_reference.typed)(&result,
			ScriptReferenceRecord(((MakeReferenceRecord)j_00001ccb)(
				source, &name))));
	result.m_node->m_value = team->m_reference;
}
