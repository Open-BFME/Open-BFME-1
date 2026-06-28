#include "memory_pool.h"

static int g_refCount;

void MemoryPool::_Exit()
{
    --g_refCount;
}

unsigned int MemoryPool::_GetBlockSize(void *block)
{
    if (block == 0) {
        return 0;
    }

    return ((unsigned int *)block)[-1];
}
