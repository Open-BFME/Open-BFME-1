// cl: /DNDEBUG /MD /EHsc
// Retail 0x004368D0 (13 bytes) is StringInfo::StringInfo(): it zeroes the
// 8-byte { AsciiString label @+0; UnicodeString text @+4 } pair (BFME has
// no speech field, unlike Zero Hour). StringInfo array-news pass this
// body through ILT 0x00006604. The members are void* here so the
// default constructor compiles to exactly retail's two null stores;
// the string-typed views in the GameText consumers are layout-identical
// and keep the string semantics. Mirrors StringInfoDestructorThunk.cpp,
// which likewise keeps a TU-local member view for byte-exact emission.

struct StringInfo
{
	StringInfo();

	void *m_label;
	void *m_text;
};

// ??0StringInfo@@QAE@XZ
StringInfo::StringInfo()
{
	m_label = 0;
	m_text = 0;
}
