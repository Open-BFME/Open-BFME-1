// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Open-BFME: GeometryRecord scalar-deleting destructor at retail RVA
// 0x000FD6F0 (30 bytes). The wrapper calls the exact 8-byte record destructor
// at 0x000FD020 through ILT 0x0001B207. GeometryInfo's vector copy/erase
// family proves the 0x10-byte three-int-plus-AsciiString layout.

class GeometryRecord
{
public:
	~GeometryRecord();
};

void forceGeometryRecordDeletingDestructor(GeometryRecord *value)
{
	delete value;
}
