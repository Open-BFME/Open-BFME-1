// ??0Rva00947170SkinContainer@@QAE@_N0@Z
// cl: /DNDEBUG /MD /EHsc
class DX8FVFCategoryContainer {
public:
	DX8FVFCategoryContainer(unsigned int fvf, bool sorting);
	virtual ~DX8FVFCategoryContainer();
	char m_body[0xf0 - 4];
};
class Rva00947170SkinContainer : public DX8FVFCategoryContainer {
public:
	int m_f0;
	int m_f4;
	int m_f8;
	int m_fc;
	bool m_skinned;
	Rva00947170SkinContainer(bool sorting, bool skinned);
};
Rva00947170SkinContainer::Rva00947170SkinContainer(bool sorting, bool skinned)
	: DX8FVFCategoryContainer(skinned ? 0x252 : 0x112, sorting),
	m_f0(0), m_f4(0), m_f8(0), m_fc(0), m_skinned(skinned)
{
}
