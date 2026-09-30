// cl: /DNDEBUG /MD /EHsc

struct FieldParse;

class SpecialPowerTemplate
{
	friend void *Rva000EB100Get();

private:
	static const FieldParse m_specialPowerFieldParse[];
};

void *Rva000EB100Get()
{
	return (void *)SpecialPowerTemplate::m_specialPowerFieldParse;
}
