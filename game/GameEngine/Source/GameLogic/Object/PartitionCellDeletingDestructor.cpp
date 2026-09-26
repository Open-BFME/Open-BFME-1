// cl: /DNDEBUG /MD /EHsc

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
// MSVC 7.1 folds `delete []` onto the scalar ??3@YAXPAX@Z unless the array
// form is declared where it can see it; retail calls ??_V@YAXPAX@Z here.
void operator delete[]( void *block );

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
