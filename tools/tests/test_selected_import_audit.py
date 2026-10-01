import struct
from types import SimpleNamespace

from selected_import_audit import audit_binding, map_symbols, pe_slots, virtual_reader, executable_reader, oracle, main


IDENTITY = ('kernel32.dll', 'Sleep')
CELL, THUNK = '__imp__Sleep@4', '_Sleep@4'


def check(symbol=CELL, selected=None, slots=None, read=None, cells=None, executable=None):
    return audit_binding(symbol, cells or {CELL: {IDENTITY}}, {THUNK: {IDENTITY}},
                         selected if selected is not None else {CELL: {0x1000}, THUNK: {0x2000}},
                         slots if slots is not None else {0x1000: {IDENTITY}},
                         read or (lambda address, size: b'\xff\x25' + struct.pack('<I', 0x1000)),
                         executable if executable is not None else lambda address, size: True)


def test_canonical_iat_does_not_dereference_lookup_word():
    def unreadable(*args):
        raise AssertionError('IAT raw lookup word is not a live pointer')
    assert check(read=unreadable)['proved']


def test_direct_ff25_thunk():
    assert check(symbol=THUNK)['proved']


def test_absent_imports_and_shadow_cell():
    assert not check(slots={})['proved']
    assert not check(selected={CELL: {0x3000}})['proved']


def test_exact_dll_name_and_ordinal():
    for identity in [('other.dll', 'Sleep'), ('kernel32.dll', 'sleep'), ('kernel32.dll', None)]:
        assert not check(slots={0x1000: {identity}})['proved']


def test_wrong_slot_even_when_correct_import_exists_elsewhere():
    assert not check(slots={0x4000: {IDENTITY}})['proved']


def test_poison_thunk_and_zero_data():
    assert not check(symbol=THUNK, read=lambda a, n: b'\xff\x25' + struct.pack('<I', 0xCCCCCCCC))['proved']
    assert not check(symbol=THUNK, read=lambda a, n: bytes(n))['proved']


def test_unknown_route_and_bounds_fail_closed():
    for body in [None, b'\xff\x25', b'\xe9' + bytes(5), b'\x90' * 6]:
        assert not check(symbol=THUNK, read=lambda a, n: body)['proved']


def test_ambiguous_maps_and_library_identities():
    assert not check(selected={CELL: {0x1000, 0x2000}})['proved']
    assert not check(cells={CELL: {IDENTITY, ('other.dll', 'Sleep')}})['proved']
    assert not check(slots={0x1000: {IDENTITY, ('other.dll', 'Sleep')}})['proved']


def test_invented_alias_cannot_pass_by_address():
    assert not check(symbol='__imp__SleepIat@4', selected={'__imp__SleepIat@4': {0x1000}})['proved']


def test_map_parser_retains_ambiguity():
    assert map_symbols([' 0001:00000000 __imp__Sleep@4 00001000 <linker-defined>\n',
                        ' 0001:00000004 __imp__Sleep@4 00002000 <linker-defined>\n'])[CELL] == {(0x1000, '<linker-defined>'), (0x2000, '<linker-defined>')}


def test_pe_imports_normalize_only_dll_case():
    pe = SimpleNamespace(DIRECTORY_ENTRY_IMPORT=[SimpleNamespace(dll=b'KERNEL32.DLL', imports=[
        SimpleNamespace(address=0x1000, name=b'Sleep'), SimpleNamespace(address=0x1004, name=None)])])
    assert pe_slots(pe) == {0x1000: {IDENTITY}}


def test_virtual_reader_zero_fill_and_bounds():
    section = SimpleNamespace(VirtualAddress=0x1000, Misc_VirtualSize=8, SizeOfRawData=4,
                              get_data=lambda: b'abcd')
    pe = SimpleNamespace(OPTIONAL_HEADER=SimpleNamespace(ImageBase=0x400000, SizeOfImage=0x2000), sections=[section])
    read = virtual_reader(pe)
    assert read(0x401002, 6) == b'cd' + bytes(4)
    assert read(0x401004, 4) == bytes(4)
    assert read(0x401007, 2) is None
    assert read(0x3fffff, 1) is None


def test_same_address_different_owners_is_ambiguous():
    selected = map_symbols([' 0001:00000000 __imp__Sleep@4 00001000 first.obj\n',
                            ' 0001:00000000 __imp__Sleep@4 00001000 second.obj\n'])
    assert not check(selected=selected)['proved']


def test_ff25_in_data_is_not_a_thunk():
    assert not check(symbol=THUNK, executable=lambda address, size: False)['proved']


def test_truncated_raw_section_is_not_zero_fill():
    section = SimpleNamespace(VirtualAddress=0x1000, Misc_VirtualSize=8, SizeOfRawData=4,
                              get_data=lambda: b'ab')
    pe = SimpleNamespace(OPTIONAL_HEADER=SimpleNamespace(ImageBase=0x400000, SizeOfImage=0x2000), sections=[section])
    assert virtual_reader(pe)(0x401000, 4) is None
    assert virtual_reader(pe)(0x401004, 4) is None


def test_executable_bounds():
    section = SimpleNamespace(VirtualAddress=0x1000, Misc_VirtualSize=8, SizeOfRawData=8,
                              Characteristics=0x20000000)
    pe = SimpleNamespace(OPTIONAL_HEADER=SimpleNamespace(ImageBase=0x400000, SizeOfImage=0x2000), sections=[section])
    assert executable_reader(pe)(0x401000, 6)
    assert not executable_reader(pe)(0x401004, 6)
    section.Characteristics = 0x40000040
    assert not executable_reader(pe)(0x401000, 6)


def test_oracle_reuses_archive_identity_and_retains_conflicts(monkeypatch, tmp_path):
    import import_binding
    monkeypatch.setattr(import_binding, 'short_imports', lambda path: [
        ('_Sleep@4', 'kernel32.dll', 'Sleep', 0),
        ('_Sleep@4', 'other.dll', 'Sleep', 0),
        ('_AIL_3D_sample_status@4', 'mss32.dll', '_AIL_3D_sample_status@4', 0)])
    monkeypatch.setattr(import_binding, 'weak_aliases', lambda path: {'__imp__oldSleep': '__imp__Sleep@4'})
    miles = ('mss32.dll', '_AIL_3D_sample_status@4')
    cells, thunks = oracle({1: IDENTITY, 2: miles}, [tmp_path/'api.lib', tmp_path/'oldnames.lib'])
    assert cells['__imp__Sleep@4'] == {IDENTITY, ('other.dll', 'Sleep')}
    assert cells['__imp__oldSleep'] == cells['__imp__Sleep@4']
    assert cells['__imp__AIL_3D_sample_status@4'] == {miles}
    assert audit_binding('__imp__AIL_3D_sample_status@4', cells, thunks,
                         {'__imp__AIL_3D_sample_status@4': {0x1000}}, {0x1000: {miles}}, lambda *args: None)['proved']
    assert not audit_binding('__imp__FakeApi@4', cells, thunks,
                             {'__imp__FakeApi@4': {0x1000}}, {0x1000: {miles}}, lambda *args: None)['proved']


def test_cli_refuses_changed_inputs(monkeypatch, tmp_path):
    import pefile
    import selected_import_audit as audit
    paths = [tmp_path/name for name in ['retail.exe', 'selected.exe', 'selected.map', 'imports.lib']]
    for path in paths:
        path.write_bytes(b'fixture')
    fake = SimpleNamespace(OPTIONAL_HEADER=SimpleNamespace(ImageBase=0x400000, SizeOfImage=0x2000),
                           DIRECTORY_ENTRY_IMPORT=[], sections=[])
    monkeypatch.setattr(pefile, 'PE', lambda path: fake)
    def changed(slots, libs):
        paths[3].write_bytes(b'changed')
        return {}, {}
    monkeypatch.setattr(audit, 'oracle', changed)
    import pytest
    with pytest.raises(SystemExit, match='input changed'):
        main(['--retail', str(paths[0]), '--selected', str(paths[1]), '--map', str(paths[2]),
              '--library', str(paths[3])])
