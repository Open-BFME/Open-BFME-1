// cl: /O2 /MD
// Address-derived data owner: dir32_addresses.csv records
// ?TheBfmeObject_00C6FF10@@3VGen_00C6FF10Target@@A at VA 0x012F10DC, the same
// cell as the recorded ?g_rva012F10DCTree STLport tree spelling. Under the
// owner's build flags sizeof(Rva0040AC30Tree) is 12 B, retail .data holds
// zeros there, and TheCloudSystem at 0x012F10F0 bounds the cell.

class Gen_00C6FF10Target
{
public:
	unsigned char m_storage[12];
};

// The initializer TU provides the same 12-byte select-any cell.
__declspec(selectany) Gen_00C6FF10Target TheBfmeObject_00C6FF10;
