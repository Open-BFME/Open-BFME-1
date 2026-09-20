// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ob1

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);
extern "C" __declspec(dllimport) int __cdecl isspace(int);
extern "C" unsigned int __cdecl strlen(const char *);
extern const char g_bfmeEmptyAscii[];

struct BFMERetailAsciiStringData {
    int ref_count;
    unsigned short length;
    unsigned short capacity;
    char data[1];
};

class BFMERetailAsciiString {
public:
    bool isEmpty() const { return m_data == 0 || m_data->length == 0; }
    int getLength() const { return m_data == 0 ? 0 : m_data->length; }
    const char *str() const {
        if (m_data != 0) {
            return m_data->data;
        }
        return g_bfmeEmptyAscii;
    }
    ~BFMERetailAsciiString() { releaseBuffer(); }

private:
    void releaseBuffer();
    BFMERetailAsciiStringData *m_data;
};

bool __cdecl rva00851BF0(BFMERetailAsciiString blockType,
                         BFMERetailAsciiString blockName,
                         const char *bufferToCheck) {
    bool retVal = true;
    char *tempBuff = const_cast<char *>(bufferToCheck);
    if (!tempBuff || blockType.isEmpty() || blockName.isEmpty()) {
        return false;
    }

    char restoreChar;
    int blockTypeLength = blockType.getLength();
    int blockNameLength = blockName.getLength();
    while (isspace(*tempBuff)) {
        ++tempBuff;
    }
    if (strlen(tempBuff) > static_cast<unsigned int>(blockTypeLength)) {
        restoreChar = tempBuff[blockTypeLength];
        tempBuff[blockTypeLength] = 0;
        if (_strcmpi(blockType.str(), tempBuff) != 0) {
            retVal = false;
        }
        tempBuff[blockTypeLength] = restoreChar;
        tempBuff += blockTypeLength;
    } else {
        retVal = false;
    }
    while (isspace(*tempBuff)) {
        ++tempBuff;
    }
    if (strlen(tempBuff) > static_cast<unsigned int>(blockNameLength)) {
        restoreChar = tempBuff[blockNameLength];
        tempBuff[blockNameLength] = 0;
        if (_strcmpi(blockName.str(), tempBuff) != 0) {
            retVal = false;
        }
        tempBuff[blockNameLength] = restoreChar;
        tempBuff += blockNameLength;
    } else {
        retVal = false;
    }
    while (strlen(tempBuff)) {
        retVal = retVal && isspace(tempBuff[0]);
        ++tempBuff;
    }
    return retVal;
}
