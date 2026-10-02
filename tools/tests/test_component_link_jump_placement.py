"""A named native jump body and its ILT entry have different identities."""
import collections
import csv
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import component_link as c


def jump(source, target):
    return b"\xe9" + struct.pack("<i", target - source - 5)


def symbol(index, name, section, value=0):
    return dict(index=index, name=name, section=section, value=value, storage=c.EXTERNAL)


def placement(offset=0, anchors=(0x3000,), body=b"\xe9\0\0\0\0"):
    p = c.Placement.__new__(c.Placement)
    # Cleanup at 0x2000 calls ILT 0x1000 -> native dtor 0x3000 -> release 0x4000.
    caller = dict(number=1, name=".text", size=5, body=b"\xe9\0\0\0\0",
                  flags=0x20, relocs=[(1, 1, c.REL32)])
    dtor = dict(number=2, name=".text", size=offset + len(body), body=b"\x90" * offset + body,
                flags=0x20, relocs=[(offset + 1, 2, c.REL32)] if body[:1] == b"\xe9" else [])
    syms = {0: symbol(0, '_cleanup', 1), 1: symbol(1, '_dtor', 2, offset),
            2: symbol(2, '_release', 0)}
    p.objs = {'one.obj': ([caller, dtor], syms)}
    p.base, p.why, p.conflicts, p.imports = {}, {}, [], []
    p.defined = {'_dtor': ('one.obj', 2, offset)}
    p.anchor_obj = collections.defaultdict(lambda: collections.defaultdict(set))
    p.anchor_obj['one.obj']['_cleanup'] = {0x2000}
    p.anchor_ext = collections.defaultdict(set, {'_dtor': set(anchors)})
    p.anchors = collections.defaultdict(set, {'_release': {0x4000}})
    p.outside = collections.defaultdict(set)
    memory = {0x1000: jump(0x1000, 0x3000), 0x2000: jump(0x2000, 0x1000),
              0x3000 - offset: b"\x90" * offset + jump(0x3000, 0x4000),
              0x3000: jump(0x3000, 0x4000)}
    p.read = lambda rva, size: memory.get(rva, b'')[:size] or None
    return p


def test_ilt_relocation_reaches_independently_named_jump_body():
    p = placement()
    p.run()
    assert p.base[('one.obj', 2)] == 0x3000
    assert p.outside['_release'] == {0x4000}
    assert p.conflicts == []



def test_dir32_function_pointer_relocation_reaches_native_jump_body():
    p = placement()
    pointer = p.objs['one.obj'][0][0]
    pointer.update(name='.data', size=4, body=b'\0' * 4,
                   flags=0x40, relocs=[(0, 1, c.DIR32)])
    read = p.read
    p.read = lambda rva, size: (struct.pack('<I', c.BASE + 0x1000)[:size]
                                if rva == 0x2000 else read(rva, size))
    p.run()
    assert p.base[('one.obj', 2)] == 0x3000
    assert p.outside['_release'] == {0x4000}
    assert p.conflicts == []


def test_native_jump_body_does_not_follow_its_own_tail_jump():
    p = placement()
    assert p.through_stub(('one.obj', 2), 0x3000, p.objs['one.obj'][1][1]) == 0x3000


def test_real_ilt_thunk_keeps_its_named_identity():
    p = placement(anchors=(0x1000,))
    assert p.through_stub(('one.obj', 2), 0x1000, p.objs['one.obj'][1][1]) == 0x1000


def test_unanchored_jump_is_not_assumed_to_be_an_ilt():
    p = placement(anchors=())
    assert p.through_stub(('one.obj', 2), 0x1000, p.objs['one.obj'][1][1]) == 0x1000


def test_wrong_route_still_conflicts():
    p = placement(anchors=(0x5000,))
    p.run()
    assert p.conflicts
    assert '0x00005000' in p.conflicts[0]
    assert '0x00001000' in p.conflicts[0]


def test_multiple_native_anchors_do_not_choose_a_convenient_destination():
    p = placement(anchors=(0x3000, 0x5000))
    p.run()
    assert p.conflicts
    assert p.through_stub(('one.obj', 2), 0x1000, p.objs['one.obj'][1][1]) == 0x1000


def test_symbol_offset_uses_entry_anchor_and_places_the_section_base():
    p = placement(offset=3)
    p.run()
    assert p.base[('one.obj', 2)] == 0x2ffd
    assert p.outside['_release'] == {0x4000}
    assert p.conflicts == []


def test_non_jump_target_retains_existing_ilt_following():
    p = placement(anchors=(), body=b'\xc3')
    assert p.through_stub(('one.obj', 2), 0x1000, p.objs['one.obj'][1][1]) == 0x3000


def test_only_matched_named_definition_rows_supply_native_anchors(tmp_path, monkeypatch):
    reverse = tmp_path / 'targets/game/reverse'
    reverse.mkdir(parents=True)
    (reverse / 'dir32_addresses.csv').write_text('name,va\n')
    with (reverse / 'functions.csv').open('w', newline='') as f:
        fields = ['name', 'target_rva', 'status', 'notes']
        writer = csv.DictWriter(f, fieldnames=fields)
        writer.writeheader()
        writer.writerows([
            dict(name='_dtor', target_rva='0x3000', status='matched', notes=''),
            dict(name='_other', target_rva='0x5000', status='unmatched', notes=''),
            dict(name='_alias', target_rva='0x6000', status='matched', notes='gen-alias'),
        ])
    syms = {i: symbol(i, name, 1) for i, name in enumerate(('_dtor', '_other', '_alias'))}
    monkeypatch.setattr(c, 'ROOT', tmp_path)
    monkeypatch.setattr(c, 'coff', lambda obj: ([], syms))
    monkeypatch.setattr(c.build, 'exe_image', lambda: (b'', []))
    monkeypatch.setattr(c.link_census, 'retail_import_slots', lambda: [])
    p = c.Placement([tmp_path / 'one.obj'], [])
    assert p.anchor_ext['_dtor'] == {0x3000}
    assert not p.anchor_ext['_other']
    assert not p.anchor_ext['_alias']
