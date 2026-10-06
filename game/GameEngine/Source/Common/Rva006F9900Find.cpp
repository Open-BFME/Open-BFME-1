// cl: /DNDEBUG /MD /O2 /EHsc

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

template <> inline int StringBase<char>::compare(const StringBase<char> &str) const
{
	int otherLength = str.m_data ? str.m_data->length : 0;
	const char *otherData = str.m_data ? str.m_data->data : (const char *)"";
	int length = m_data ? m_data->length : 0;
	const char *data = m_data ? m_data->data : (const char *)"";
	int result = memcmp(data, otherData, length < otherLength ? length : otherLength);
	return result ? result : length - otherLength;
}

class Rva006F9900Entry
{
public:
    char m_beforeKind[0x48];
    int m_kind;
    char m_beforeName[0x3c];
    AsciiString m_name;
};

struct Rva006F9900Node
{
    Rva006F9900Node *m_next;
    Rva006F9900Node *m_previous;
    Rva006F9900Entry *m_entry;
};

struct Rva006F9900List
{
    Rva006F9900Node *m_head;
};

class Rva006F9900Owner
{
public:
    Rva006F9900Entry *find(int kind, AsciiString name);

private:
    char m_beforeList[0x20];
    Rva006F9900List m_list;
};

Rva006F9900Entry *Rva006F9900Owner::find(int kind, AsciiString name)
{
    Rva006F9900Node *head = m_list.m_head;
    Rva006F9900Node *node = head->m_next;
    while (node != head)
    {
        if (kind == node->m_entry->m_kind && node->m_entry->m_name.StringBase<char>::compare(name) == 0)
            return node->m_entry;

        node = node->m_next;
    }

    return 0;
}
