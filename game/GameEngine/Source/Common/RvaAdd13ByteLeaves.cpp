// Open-BFME: two identical 13-byte __stdcall addition leaves.

int __stdcall Rva00523E10Add(volatile int left, volatile int right)
{
    int first = left;
    int second = right;
    return first + second;
}

int __stdcall Rva0056B610Add(volatile int left, volatile int right)
{
    int first = left;
    int second = right;
    return first + second;
}
