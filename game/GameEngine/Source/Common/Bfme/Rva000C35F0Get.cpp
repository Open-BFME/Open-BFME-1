// cl: /DNDEBUG /MD /EHsc

struct FieldParse;

class WaterSetting
{
public:
	static const FieldParse m_waterSettingFieldParseTable[];
};

void *Rva000C35F0Get()
{
	return (void *)WaterSetting::m_waterSettingFieldParseTable;
}
