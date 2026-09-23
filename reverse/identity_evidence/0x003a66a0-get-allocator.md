# Retail identity of 0x003A66A0

The retail vector copy at 0x003AA980 sets ECX to the source vector and pushes a pointer to the allocator result slot before it calls ILT 0x00013FC5. The ILT jumps to 0x003A66A0.

The seven-byte body at 0x003A66A0 loads the first stack argument into EAX and returns with `ret 4`. The vector copy passes that source and hidden result slot to the accessor.

The STLport `vector<T>::get_allocator() const` returns an allocator through the caller-provided result slot. The body at 0x003A66A0 matches that accessor's return behavior.
