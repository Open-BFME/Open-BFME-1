// cl: /DNDEBUG /MD /EHsc

struct FieldParse;

class WaterTransparencySetting
{
public:
	static const FieldParse m_waterTransparencySettingFieldParseTable[];
};

void *Rva000C3600Get()
{
	return (void *)WaterTransparencySetting::m_waterTransparencySettingFieldParseTable;
}
