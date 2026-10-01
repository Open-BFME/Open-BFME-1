#!/usr/bin/env python3
"""Audit selected PE import bindings; independent of retail closure metrics.

Names come from explicit import libraries, using import_binding's existing
archive readers. Pins and address-shaped names never establish identity.
Only an exact native IAT entry or a direct FF25 thunk is proved here; other
forwarding shapes remain unproved. No compiler, linker or Wine is invoked.
"""
import argparse
import collections
import hashlib
import json
import re
import struct
from pathlib import Path


def oracle(slots, libraries):
    from import_binding import short_imports, weak_aliases
    expected = set(slots.values())
    cells, thunks = collections.defaultdict(set), collections.defaultdict(set)
    aliases = collections.defaultdict(set)
    for path in libraries:
        if path.name.lower() == 'oldnames.lib':
            for alias, target in weak_aliases(path).items():
                aliases[alias].add(target)
            continue
        for symbol, dll, name, kind in short_imports(path):
            identity = (dll.lower(), name)
            # Keep foreign alternatives too: a conflicting library must not
            # silently overwrite a retail identity or become a name vote.
            cells['__imp_' + symbol].add(identity)
            if kind == 0:
                thunks[symbol].add(identity)
    for alias, targets in aliases.items():
        for target in targets:
            cells[alias].update(cells.get(target, ()))
    def retained(mapping):
        return {name: identities for name, identities in mapping.items()
                if identities & expected}
    return retained(cells), retained(thunks)


def map_symbols(lines):
    found = collections.defaultdict(set)
    pattern = re.compile(r'^\s+[0-9A-Fa-f]+:[0-9A-Fa-f]+\s+(\S+)\s+([0-9A-Fa-f]{8})\s')
    for line in lines:
        match = pattern.match(line)
        if match:
            found[match[1]].add((int(match[2], 16), line[match.end():].strip()))
    return dict(found)


def audit_binding(symbol, cells, thunks, selected, native_slots, read, executable=None):
    """Pure binding proof. native_slots keys are actual VA, never retail RVA.

    An IAT word on disk can be a lookup RVA/ordinal: directory identity is
    checked before reading any word, and its raw value is not a live pointer.
    """
    result = {'symbol': symbol, 'proved': False}
    candidates = cells.get(symbol) if symbol in cells else thunks.get(symbol)
    if not candidates:
        return dict(result, reason='no import-library retail identity')
    if len(candidates) != 1:
        return dict(result, reason='ambiguous import-library identity')
    identity = next(iter(candidates))
    result['expected'] = list(identity)
    addresses = selected.get(symbol, set())
    if len(addresses) != 1:
        return dict(result, reason='missing or ambiguous selected MAP address')
    record = next(iter(addresses))
    address = record[0] if isinstance(record, tuple) else record
    result['selected_va'] = f'0x{address:08X}'
    if symbol in cells:
        slot = address
        route = 'actual IAT slot'
    else:
        if executable is None or not executable(address, 6):
            return dict(result, reason='selected thunk is not in a proved executable section')
        body = read(address, 6)
        if body is None or len(body) != 6 or body[:2] != b'\xff\x25':
            return dict(result, reason='selected body is not a proved direct FF25 thunk')
        slot = struct.unpack_from('<I', body, 2)[0]
        route = 'direct FF25 thunk'
    result.update(slot_va=f'0x{slot:08X}', route=route)
    actual = native_slots.get(slot, set())
    result['actual'] = [list(pair) for pair in sorted(actual, key=repr)]
    if actual != {identity}:
        return dict(result, reason='selected slot is not the exact native DLL/name import')
    return dict(result, proved=True, reason='native import-directory identity and selected address agree')


def pe_slots(pe):
    slots = collections.defaultdict(set)
    for entry in getattr(pe, 'DIRECTORY_ENTRY_IMPORT', ()):
        dll = entry.dll.decode('latin-1').lower()
        for imported in entry.imports:
            if imported.name is None:
                continue  # Ordinal identity needs separate export evidence; never a named import proof.
            name = imported.name.decode('latin-1')
            slots[imported.address].add((dll, name))
    return dict(slots)


def virtual_reader(pe):
    """Bounded virtual section reader, including legitimate .bss zero fill."""
    base = pe.OPTIONAL_HEADER.ImageBase
    def read(va, size):
        rva = va - base
        if size < 0 or rva < 0 or rva + size > pe.OPTIONAL_HEADER.SizeOfImage:
            return None
        for section in pe.sections:
            start = section.VirtualAddress
            extent = max(section.Misc_VirtualSize, section.SizeOfRawData)
            if start <= rva and rva + size <= start + extent:
                raw = section.get_data()
                if len(raw) < section.SizeOfRawData:
                    return None  # Truncated raw bytes are not virtual .bss.
                offset = rva - start
                data = raw[offset:offset + size]
                return data + bytes(size - len(data))
        return None
    return read


def executable_reader(pe):
    def executable(va, size):
        rva = va - pe.OPTIONAL_HEADER.ImageBase
        if rva < 0 or rva + size > pe.OPTIONAL_HEADER.SizeOfImage:
            return False
        return any(section.Characteristics & 0x20000000 and section.VirtualAddress <= rva
                   and rva + size <= section.VirtualAddress + max(section.Misc_VirtualSize, section.SizeOfRawData)
                   for section in pe.sections)
    return executable


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--retail', type=Path, required=True)
    parser.add_argument('--selected', type=Path, required=True)
    parser.add_argument('--map', type=Path, required=True)
    parser.add_argument('--library', type=Path, action='append', required=True)
    parser.add_argument('--symbol', action='append')
    parser.add_argument('--json', type=Path)
    args = parser.parse_args(argv)
    import pefile
    files = [args.retail, args.selected, args.map, *args.library]
    before = {str(path): hashlib.sha256(path.read_bytes()).hexdigest() for path in files}
    retail, native = pefile.PE(str(args.retail)), pefile.PE(str(args.selected))
    retail_slots = {va - retail.OPTIONAL_HEADER.ImageBase: next(iter(pairs))
                    for va, pairs in pe_slots(retail).items()
                    if len(pairs) == 1 and next(iter(pairs))[1] is not None}
    cells, thunks = oracle(retail_slots, args.library)
    with args.map.open(encoding='latin-1') as handle:
        selected = map_symbols(handle)
    names = args.symbol or sorted(selected.keys() & (cells.keys() | thunks.keys()))
    rows = [audit_binding(name, cells, thunks, selected, pe_slots(native), virtual_reader(native), executable_reader(native))
            for name in names]
    after = {str(path): hashlib.sha256(path.read_bytes()).hexdigest() for path in files}
    if before != after:
        raise SystemExit('Selected import audit input changed during audit')
    receipt = {'scope': 'Selected PE import binding only; does not change retail closure metrics',
               'input_sha256': before, 'input_hash_equality': True,
               'proved': sum(row['proved'] for row in rows), 'unproved': sum(not row['proved'] for row in rows),
               'bindings': rows}
    encoded = json.dumps(receipt, indent=2) + '\n'
    if args.json:
        args.json.write_text(encoded)
    print(encoded, end='')
    return 0 if rows and all(row['proved'] for row in rows) else 1


if __name__ == '__main__':
    raise SystemExit(main())
