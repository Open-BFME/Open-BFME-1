// cl: /DNDEBUG /MD /EHsc
// stlport
//
// LivingWorldLogic::reset, retail 0x003C1930, 231 bytes.
//
// Vtable slot 1 of LivingWorldLogic reaches this body through ILT 0x0001F94C.
// The reset clears the two owned collections, releases the current region name,
// and empties the two POD vectors at +0x84 and +0x94.

extern "C" __declspec(dllimport) void * __cdecl memmove(
	void *destination, const void *source, unsigned int bytes);

#pragma intrinsic(_ReadWriteBarrier)
extern "C" void _ReadWriteBarrier(void);

class Rva003C1A50
{
public:
	void clearOwned();
	void clearTwoVec();
};

class BFMERetailAsciiString
{
public:
	void releaseBuffer();

private:
	void *m_data;
};

template <typename T>
struct BfmeVector
{
	T *m_start;
	T *m_finish;
	T *m_end;
};

template <typename T>
inline T *bfmeCopyTrivial(T *destination, T *first, T *last)
{
	return first == last ? destination :
		(T *)((char *)memmove(destination, first,
			(unsigned int)((char *)last - (char *)first)) +
			((char *)last - (char *)first));
}

template <typename T>
inline T *bfmeCopyElements(T *destination, T *first, T *last)
{
	int count = last - first;
	while (count > 0)
	{
		*destination = *first;
		++first;
		++destination;
		--count;
	}
	return destination;
}

class LivingWorldLogic
{
public:
	void reset();

private:
	unsigned char m_unmodelled00[0x18];
	int m_at18;
	unsigned char m_unmodelled1C[0x0C];
	void *m_regionManager;
	unsigned char m_at2C;
	unsigned char m_at2D;
	unsigned char m_unmodelled2E[2];
	BFMERetailAsciiString m_currentRegionName;
	int m_at34;
	BfmeVector<unsigned short> m_at38;
	unsigned char m_at44;
	unsigned char m_unmodelled45[0x2F];
	int m_at74;
	unsigned char m_at78;
	unsigned char m_unmodelled79[7];
	unsigned char m_at80;
	unsigned char m_unmodelled81[3];
	BfmeVector<unsigned short> m_missionObjectiveStates;
	int m_at90;
	BfmeVector<int> m_at94;
	int m_atA0;
	int m_atA4;
	unsigned char m_unmodelledA8[0x20];
	unsigned char m_atC8;
	unsigned char m_unmodelledC9[3];
	int m_atCC;
};

// ?reset@LivingWorldLogic@@QAEXXZ
void LivingWorldLogic::reset()
{
	((Rva003C1A50 *)this)->clearOwned();
	((Rva003C1A50 *)this)->clearTwoVec();

	m_at18 = 0;
	m_at2C = 0;
	m_at2D = 1;
	m_at34 = 0;
	m_at78 = 0;
	m_atC8 = 1;
	m_atCC = 0x78;
	m_at90 = 1;
	m_at80 = 0;
	m_at44 = 0;
	m_at74 = 1;
	m_currentRegionName.releaseBuffer();

	m_at38.m_finish = bfmeCopyTrivial(
		m_at38.m_start, m_at38.m_finish, m_at38.m_finish);
	_ReadWriteBarrier();
	m_missionObjectiveStates.m_finish = bfmeCopyElements(
		m_missionObjectiveStates.m_start,
		m_missionObjectiveStates.m_finish,
		m_missionObjectiveStates.m_finish);
	_ReadWriteBarrier();
	m_at94.m_finish = bfmeCopyElements(
		m_at94.m_start, m_at94.m_finish, m_at94.m_finish);
	_ReadWriteBarrier();
	m_atA4 = 0;
	m_atA0 = 1;
}
