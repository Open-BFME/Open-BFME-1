// cl: /O2
// BFME LineEmissionVolumeInfo vector-deleting destructor at retail RVA
// 0x005D5B60. Its scalar destructor is matched at 0x005D5A80 and the wrapper
// reaches it through ILT 0x0002F03B.

void operator delete[](void *block);

namespace FXParticleSystem
{
class LineEmissionVolumeInfo
{
public:
	virtual ~LineEmissionVolumeInfo();

private:
	unsigned char m_data[0x1c];
};

LineEmissionVolumeInfo *MakeLineEmissionVolumeInfoArray()
{
	return new LineEmissionVolumeInfo[2];
}

void DeleteLineEmissionVolumeInfoArray(LineEmissionVolumeInfo *array)
{
	delete[] array;
}
}
