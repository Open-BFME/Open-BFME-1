// ?ensureUniqueBufferOfSize@?$StringBase@D@@AAEXH_NPBDH1H@Z
// partial score=0.97 date=2026-09-27
// ensureUniqueBufferOfSize template attempt: insert into StringBase.cpp after set(const StringBase&); TU needs /EHs-c- and <stdlib.h>

template <typename T>
void StringBase<T>::ensureUniqueBufferOfSize(int newLen, bool keepData, const T *src1, int src1Len, const T *src2, int src2Len)
{
	if (m_data)
	{
		if (m_data->capacity > newLen)
		{
			if (m_data->ref_count == 1)
			{
				// already unique and large enough: build in place
				if (src1)
				{
					memcpy(m_data->data, src1, src1Len * sizeof(T));
					m_data->length = src1Len;
				}
				if (src2)
				{
					memcpy(m_data->data + m_data->length, src2, src2Len * sizeof(T));
					m_data->length += src2Len;
				}
				m_data->data[m_data->length] = 0;
				return;
			}
		}
		else if (src2)
		{
			// concatenation grows by half again to amortize appends
			int grown = m_data->capacity + m_data->capacity / 2 - 1;
			if (grown > newLen)
				newLen = grown;
		}
	}

	int bytes = sizeof(int) + 2 * sizeof(unsigned short) + (newLen + 1) * sizeof(T);
	if (bytes > 0x7fff)
		throw 1;
	bytes = (bytes + 3) / 4 * 4;

	Header *newData = (Header *)malloc(bytes);
	newData->ref_count = 1;
	newData->capacity = (unsigned short)((bytes - 8) / sizeof(T));
	if (m_data && keepData)
	{
		memcpy(newData->data, m_data->data, m_data->length * sizeof(T));
		newData->length = m_data->length;
	}
	else
	{
		newData->length = 0;
	}
	if (src1)
	{
		memcpy(newData->data, src1, src1Len * sizeof(T));
		newData->length = src1Len;
	}
	if (src2)
	{
		memcpy(newData->data + newData->length, src2, src2Len * sizeof(T));
		newData->length += src2Len;
	}
	newData->data[newData->length] = 0;

	releaseBuffer();
	m_data = newData;
}
