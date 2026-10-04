// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/buildlistinfo /Iinputs/reference/shims/moduledata /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail RVA 0x0019DB40, 527 bytes. Adapted from ZH SidesList's
// WriteSidesDataChunk field order; BFME has a receiver, version 6 and
// a leading byte at +0x668, and omits the ZH trailing team section.
// The receiver's 0x28 count and 24-byte side entries at 0x2C are witnessed
// by retail. Keep address-derived owner/fields; do not apply the ZH layout.
// BuildListInfo uses the existing BFME shim: linked-list stride and each
// serialized getter offset agree with retail, including angle +0x20.

#include "PreRTS.h"
#include "Common/DataChunk.h"
#include "GameLogic/SidesList.h"

// Retail inlines ~AsciiString: temporaries are released by a direct call to
// StringBase<char>::releaseBuffer (0x00887940), not the ??1AsciiString stub.
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
struct SideEntry0019DB40 {
    BuildListInfo* field00;
    Dict field04;
    char field08[16];
    Dict* getDict() { return &field04; }
    BuildListInfo* getBuildList() { return field00; }
};
class SidesChunkWriter0019DB40 {
    char field00[0x28];
    int field28;
public:
    int getNumSides() { return field28; }
    SideEntry0019DB40* getSide(int i) {
        if(i >= 0 && i < field28) return ((SideEntry0019DB40*)((char*)this+0x2c))+i;
        return 0;
    }
    void write(DataChunkOutput& chunkWriter);
};
void SidesChunkWriter0019DB40::write(DataChunkOutput& chunkWriter) {
    ((SidesList*)this)->validateSides();
    chunkWriter.openDataChunk("SidesList",6);
    chunkWriter.writeByte(*(char*)((char*)this+0x668));
    chunkWriter.writeInt(getNumSides());
    for(int i=0; i<getNumSides(); ++i) {
        chunkWriter.writeDict(*getSide(i)->getDict());
        BuildListInfo* pBuildList = getSide(i)->getBuildList();
        int count=0;
        while(pBuildList) { ++count; pBuildList=pBuildList->getNext(); }
        chunkWriter.writeInt(count);
        pBuildList = getSide(i)->getBuildList();
        while(pBuildList) {
            chunkWriter.writeAsciiString(pBuildList->getBuildingName());
            chunkWriter.writeAsciiString(pBuildList->getTemplateName());
            chunkWriter.writeReal(pBuildList->getLocation()->x);
            chunkWriter.writeReal(pBuildList->getLocation()->y);
            chunkWriter.writeReal(pBuildList->getLocation()->z);
            chunkWriter.writeReal(pBuildList->getAngle());
            chunkWriter.writeByte(pBuildList->isInitiallyBuilt());
            chunkWriter.writeInt(pBuildList->getNumRebuilds());
            chunkWriter.writeAsciiString(pBuildList->getScript());
            chunkWriter.writeInt(pBuildList->getHealth());
            chunkWriter.writeByte(pBuildList->getWhiner());
            chunkWriter.writeByte(pBuildList->getUnsellable());
            chunkWriter.writeByte(pBuildList->getRepairable());
            pBuildList = pBuildList->getNext();
        }
    }
    chunkWriter.closeDataChunk();
}

typedef char SideWidth0019DB40[(sizeof(SideEntry0019DB40)==24)?1:-1];
