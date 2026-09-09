// ?bfmeRunKD@BfmeTgtKD@@QAEDPAXVBfmeArgKD@@0@Z
// partial score=0.75 date=2026-09-08
class BfmeArgKD
{
public:
	BfmeArgKD(const BfmeArgKD &other) throw()
	{
		m_bfmeAKD = other.m_bfmeAKD;
		m_bfmeBKD = other.m_bfmeBKD;
		m_bfmeCKD = other.m_bfmeCKD;
	}
	~BfmeArgKD() throw() {}

	int m_bfmeAKD;
	int m_bfmeBKD;
	int m_bfmeCKD;
};

class BfmeTgtKD
{
public:
	char bfmeRunKD(void *first, BfmeArgKD arg, void *last);

private:
	struct BfmeRecordKD
	{
		union { int m_argA; float m_argAFloat; };
		union { int m_argB; float m_argBFloat; };
		union { int m_argC; float m_argCFloat; };
		float m_scale;
		int m_payload[12];
		int m_typeIndex;
		int m_padding44;
		union { int m_value0; float m_value0Float; };
		union { int m_value1; float m_value1Float; };
		union { int m_value2; float m_value2Float; };
		union { int m_value3; float m_value3Float; };
		void *m_owner;
		unsigned char m_padding5c[0x8c];
	};

	struct BfmeTypeKD
	{
		int m_value0;
		int m_value1;
		int m_value2;
		int m_value3;
		unsigned char m_padding10[0x4c];
	};

	unsigned char m_padding0000[0x1b0];
	BfmeRecordKD m_records[0x2ee0];
	int m_recordCount;
	unsigned char m_dirty;
	unsigned char m_padding2a7cb5[0x17];
	BfmeTypeKD m_types[64];
};

struct BfmePayloadKD
{
	int m_value[12];
};

char BfmeTgtKD::bfmeRunKD(void *first, BfmeArgKD arg, void *last)
{
	int index = 0;
	if (m_recordCount > 0)
	{
		void *needle = first;
		unsigned int owner = reinterpret_cast<unsigned int>(&m_records[0].m_owner);
		if (*reinterpret_cast<void **>(owner) != needle)
		{
			int count = m_recordCount;
			do
			{
				++index;
				owner += 0xe8;
				if (index >= count)
					return 0;
			} while (*reinterpret_cast<void **>(owner) != needle);
		}
	}
	else
	{
		return 0;
	}

	{
		m_records[index].m_argA = arg.m_bfmeAKD;
		m_records[index].m_argB = arg.m_bfmeBKD;
		m_records[index].m_argC = arg.m_bfmeCKD;
		const BfmePayloadKD *payload = static_cast<const BfmePayloadKD *>(last);
		m_records[index].m_payload[0] = payload->m_value[0];
		m_records[index].m_payload[1] = payload->m_value[1];
		m_records[index].m_payload[2] = payload->m_value[2];
		m_records[index].m_payload[3] = payload->m_value[3];
		m_records[index].m_payload[4] = payload->m_value[4];
		m_records[index].m_payload[5] = payload->m_value[5];
		m_records[index].m_payload[6] = payload->m_value[6];
		m_records[index].m_payload[7] = payload->m_value[7];
		m_records[index].m_payload[8] = payload->m_value[8];
		m_records[index].m_payload[9] = payload->m_value[9];
		m_records[index].m_payload[10] = payload->m_value[10];
		m_records[index].m_payload[11] = payload->m_value[11];

		BfmeTypeKD *type = m_types + m_records[index].m_typeIndex;
		m_records[index].m_value0 = type->m_value0;
		m_records[index].m_value1 = type->m_value1;
		m_records[index].m_value2 = type->m_value2;
		m_records[index].m_value3 = type->m_value3;
		float scale = m_records[index].m_scale;
		m_records[index].m_value0Float *= scale;
		m_records[index].m_value1Float *= scale;
		m_records[index].m_value2Float *= scale;
		m_records[index].m_value3Float *= scale;
		m_records[index].m_value0Float += m_records[index].m_argAFloat;
		m_records[index].m_value1Float += m_records[index].m_argBFloat;
		m_records[index].m_value2Float += m_records[index].m_argCFloat;
	}
	m_dirty = 1;
	return 1;
}

class BfmeOwnKD
{
public:
	char bfmeFwdKD(void *first, BfmeArgKD arg, void *last);

	unsigned char m_bfmeHeadKD[0x3094];
	BfmeTgtKD *m_bfmeTgtKD;
};

char BfmeOwnKD::bfmeFwdKD(void *first, BfmeArgKD arg, void *last)
{
	if (m_bfmeTgtKD)
		return m_bfmeTgtKD->bfmeRunKD(first, arg, last);

	return 0;
}
