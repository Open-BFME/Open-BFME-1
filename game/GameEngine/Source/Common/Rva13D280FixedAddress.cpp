struct FieldParse;

unsigned char *rva_13d280_fixed_address();

class ThingTemplate
{
    friend unsigned char *rva_13d280_fixed_address();

protected:
    static const FieldParse s_objectFieldParseTable[];
};

unsigned char *rva_13d280_fixed_address()
{
    return reinterpret_cast<unsigned char *>(const_cast<FieldParse *>(ThingTemplate::s_objectFieldParseTable));
}
