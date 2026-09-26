// cl: /O2
struct Rva009F3010Allocator {};
struct Rva009F3010Proxy {
 Rva009F3010Proxy(const Rva009F3010Allocator &allocator, unsigned int value);
 unsigned int m_value;
};
struct Rva009F3250Owner {
 Rva009F3250Owner(const Rva009F3010Allocator &allocator);
 unsigned int m_first;
 unsigned int m_second;
 Rva009F3010Proxy m_proxy;
};
Rva009F3250Owner::Rva009F3250Owner(const Rva009F3010Allocator &allocator)
 : m_first(0), m_second(0), m_proxy(allocator, 0) {}

struct Rva009F4B30Allocator {};
struct Rva009F4B30Proxy {
 Rva009F4B30Proxy(const Rva009F4B30Allocator &allocator, unsigned int value);
 unsigned int m_value;
};
struct Rva009F52B0Owner {
 Rva009F52B0Owner(const Rva009F4B30Allocator &allocator);
 unsigned int m_first;
 unsigned int m_second;
 Rva009F4B30Proxy m_proxy;
};
Rva009F52B0Owner::Rva009F52B0Owner(const Rva009F4B30Allocator &allocator)
 : m_first(0), m_second(0), m_proxy(allocator, 0) {}
