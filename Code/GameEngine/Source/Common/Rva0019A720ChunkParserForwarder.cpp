// cl: /DNDEBUG /MD /EHsc
// RVA 0019A720 forwards two parser arguments and a zero third argument.
// Evidence: reverse/identity_evidence/0019a720.md.
class DataChunkInput;
struct DataChunkInfo;

class Rva0019A470Owner
{
public:
    bool parse(DataChunkInput &input, DataChunkInfo *info, int value);
    bool parseAt0019A720(DataChunkInput &input, DataChunkInfo *info);
};

bool Rva0019A470Owner::parseAt0019A720(DataChunkInput &input, DataChunkInfo *info)
{
    return parse(input, info, 0);
}
