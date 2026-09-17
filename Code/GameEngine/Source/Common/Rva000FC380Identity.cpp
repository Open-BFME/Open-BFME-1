// cl: /O2

// Retail 0x000FC380 returns its receiver unchanged in a three-byte body.
// The carved boundary provides no stronger semantic identity.
struct Rva000FC380Identity
{
    Rva000FC380Identity *identity();
};

Rva000FC380Identity *Rva000FC380Identity::identity()
{
    return this;
}
