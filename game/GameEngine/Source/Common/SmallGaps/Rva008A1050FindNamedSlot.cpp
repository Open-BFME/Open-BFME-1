// ?findNamedSlot@Rva008A1050Owner@@QAEHPBD@Z
extern "C" int __cdecl strcmp(const char*, const char*);
#pragma intrinsic(strcmp)
struct Rva008A1050Entry { const char* m_name; int m_slot; };
struct Rva008A1050Table {
	char m_pad[0x18];
	int* m_values;
	char m_pad2[0x30 - 0x1c];
	int m_count;
	Rva008A1050Entry* m_entries;
};
struct Rva008A1050Owner {
	char m_pad[0x10];
	Rva008A1050Table* m_table;
	int findNamedSlot(const char* name);
};
int Rva008A1050Owner::findNamedSlot(const char* name)
{
	for (int i = 0; i < m_table->m_count; ++i) {
		if (strcmp(name, m_table->m_entries[i].m_name) == 0)
			return m_table->m_values[m_table->m_entries[i].m_slot];
	}
	return 0;
}
