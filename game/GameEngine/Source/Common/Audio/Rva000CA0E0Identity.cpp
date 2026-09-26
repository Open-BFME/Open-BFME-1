// cl: /O2

// Retail 0x000CA0E0 returns its receiver unchanged in a three-byte body.
// The carved boundary and nearby STLport helpers provide no stronger identity.
struct Rva000CA0E0Identity
{
    Rva000CA0E0Identity *identity();
};

Rva000CA0E0Identity *Rva000CA0E0Identity::identity()
{
    return this;
}
