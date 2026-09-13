// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// Open-BFME5: BFME WorldHeightMap::ParseSizeOnly at retail 0x0074EF50.
// The BFME parser stores height samples as unsigned shorts.  This TU keeps
// that ABI view local because the older public WorldHeightMap header describes
// the Zero Hour byte-buffer layout.

typedef int Int;
typedef bool Bool;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

// The retail body calls the game's array operators directly.  Keeping these
// declarations explicit preserves their distinct relocation identities:
// operator new[] 0x00881F70, operator delete[] 0x00881EF0, and scalar delete
// 0x00881EB0 for the temporary byte buffer.
void *__cdecl operator new[](unsigned int size);
void __cdecl operator delete[](void *ptr);
void __cdecl operator delete(void *ptr);

class DataChunkInput
{
public:
	Int readInt(void);
	void readArrayOfBytes(char *ptr, Int len);
};

struct DataChunkInfo
{
	char m_header[8];
	UnsignedShort version;
};

struct ICoord2D
{
	Int x;
	Int y;
};

namespace _STL
{
	template <class Type>
	class allocator {};

	template <class Type, class Allocator>
	class vector
	{
	public:
		typedef unsigned int size_type;
		typedef Type *iterator;

		void resize(size_type newSize);
		iterator begin(void)
		{
			return m_start;
		}

		Type &operator[](size_type index)
		{
			return *(begin() + index);
		}

	private:
		Type *m_start;
		Type *m_finish;
		Type *m_endOfStorage;
	};
}

class WorldHeightMap
{
	protected:
	Bool ParseSizeOnly(DataChunkInput &file, DataChunkInfo *info);

	private:
	char m_base[8];
	Int m_width;
	Int m_height;
	Int m_borderSize;
	_STL::vector<ICoord2D, _STL::allocator<ICoord2D> > m_boundaries;
	Int m_dataSize;
	UnsignedShort *m_data;
};

// ?ParseSizeOnly@WorldHeightMap@@IAE_NAAVDataChunkInput@@PAUDataChunkInfo@@@Z
Bool WorldHeightMap::ParseSizeOnly(DataChunkInput &file, DataChunkInfo *info)
{
	Int numBorders;
	Int i, j;
	Int sample;
	m_width = file.readInt();
	m_height = file.readInt();
	if (info->version >= 3)
		m_borderSize = file.readInt();
	else
		m_borderSize = 0;

	if (info->version >= 4)
	{
		numBorders = file.readInt();
		m_boundaries.resize(numBorders);
		for (i = 0; i < numBorders; ++i)
		{
			m_boundaries[i].x = file.readInt();
			m_boundaries[i].y = file.readInt();
		}
	}
	else
	{
		m_boundaries.resize(1);
		m_boundaries[0].x = m_width - 2 * m_borderSize;
		m_boundaries[0].y = m_height - 2 * m_borderSize;
	}

	m_dataSize = file.readInt();
	if (m_data != 0)
		operator delete[]((void *)m_data);
	m_data = (UnsignedShort *)operator new[]((unsigned int)(m_dataSize * 2));
	if (m_dataSize <= 0 || m_dataSize != m_width * m_height)
		throw 0xDEAD0005;

	if (info->version == 4)
	{
		UnsignedByte *source = (UnsignedByte *)operator new[]((unsigned int)m_dataSize);
		file.readArrayOfBytes((char *)source, m_dataSize);
		for (Int i = 0; i < m_dataSize; ++i)
		{
			sample = source[i];
			m_data[i] = (UnsignedShort)(sample * *(const float *)0x01121BA0
				+ *(const float *)0x0107533C);
		}
		operator delete((void *)source);
	}
	else
	{
		file.readArrayOfBytes((char *)m_data, m_dataSize * 2);
	}

	if (info->version == 1)
	{
		Int newWidth = (m_width + 1) / 2;
		Int newHeight = (m_height + 1) / 2;
		i = 0;
		j = 0;
		for (i = 0; i < newHeight; ++i)
		{
			for (j = 0; j < newWidth; ++j)
				m_data[i * newWidth + j] =
					m_data[2 * i * m_width + 2 * j];
		}
		m_width = newWidth;
		m_height = newHeight;
	}
	return true;
}
