// Open-BFME5: clean C++ conversion of the 12-byte-record heap insertion.

struct Rva00570DE0Record
{
	int m_key;
	int m_keyCopy;
	int m_payload;
};

void __cdecl rva00570DE0PushHeap(Rva00570DE0Record *records, int holeIndex,
	int topIndex, Rva00570DE0Record value)
{
	int parent = (holeIndex - 1) / 2;
	while (holeIndex > topIndex) {
		Rva00570DE0Record *parentRecord = records + parent;
		if (parentRecord->m_key >= value.m_key) {
			break;
		}

		records[holeIndex] = *parentRecord;
		holeIndex = parent;
		parent = (holeIndex - 1) / 2;
	}

	records[holeIndex] = value;
}
