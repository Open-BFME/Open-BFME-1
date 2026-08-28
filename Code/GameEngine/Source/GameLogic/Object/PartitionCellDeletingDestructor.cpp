// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionCell
{
    unsigned char data[0x98];

public:
    ~PartitionCell();
};

void deletePartitionCellArray(PartitionCell *cells)
{
    delete[] cells;
}
