"""Host CPU admission: deterministic controller and sampler, no inference.

The controller is exercised through a scripted sampler and a scripted clock, so
these tests never depend on the machine they run on. The one real-host check
only asserts that a readable /proc/stat yields a usable fraction, and it skips
elsewhere. The two fleet tests launch the real fake CLI in real cgroups, exactly
like test_opencode_router.py, and skip where containment is unavailable.
"""
from pathlib import Path
import contextlib
import copy
import io
import json
import sqlite3
import sys
import tempfile
import time
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import opencode_cpu_admission as a
import opencode_router as r

FAKE = '''#!/usr/bin/env python3
import json,sys,time
from pathlib import Path
if '--version' in sys.argv:
 print('opencode v2.0.18'); sys.exit()
model=sys.argv[sys.argv.index('--model')+1]
Path('selected-model.txt').write_text(model)
prompt=sys.stdin.read()
Path('received.txt').write_text(prompt)
print(json.dumps({'type':'step_start','sessionID':'cpu-session'}),flush=True)
if 'SLOW' in prompt: time.sleep(2)
else: time.sleep(.2)
print(json.dumps({'type':'text','part':{'text':'ROUTER_RESULT '+json.dumps({'outcome':'success','summary':'fixture completed'})}}),flush=True)
'''


class ScriptedSampler:
    """Replays a list of utilization fractions; None is an unmeasurable tick."""

    def __init__(self, values, error=None, supported=True):
        self.values = list(values)
        self.error = error
        self.supported = supported
        self.path = 'scripted'

    def sample(self):
        return self.values.pop(0) if self.values else 0.5


class FadingSampler(ScriptedSampler):
    """Saturated and supported, then the host stops being measurable at all."""

    def __init__(self, ticks=4):
        super().__init__([1.0] * ticks)
        self.ticks, self.calls = ticks, 0

    def sample(self):
        self.calls += 1
        if self.calls > self.ticks:
            self.error, self.supported = 'proc_stat_unavailable', False
            return None
        return super().sample()


class BrokenSampler:
    """A monitor that raises: the scheduler must keep dispatching and say so."""

    path = '/proc/stat'
    error = None
    supported = True

    def sample(self):
        raise RuntimeError('sampler exploded')


class Ticks:
    """A clock that advances one fixed step per read: no sleeping, no wall time.

    The step defaults to the controller's own interval, so every poll lands on
    the next scripted sample; a smaller step exercises the interval gate.
    """

    def __init__(self, step, start=0.0):
        self.now, self.step = start, step

    def __call__(self):
        now, self.now = self.now, self.now + self.step
        return now


def cpu_config(**kw):
    return {'cpu_admission': {'enabled': True, **kw}}


def controller(values, cap, step=None, **kw):
    """A controller whose every poll lands on the next scripted sample."""
    options = a.config(cpu_config(**kw))
    return a.Admission(options, cap, ScriptedSampler(values),
                       clock=Ticks(options['interval_seconds'] if step is None else step))


def drain(controller, windows=60):
    for _ in range(windows):
        controller.poll()
    return controller.limit


class ConfigTests(unittest.TestCase):
    def test_disabled_by_default_and_no_sampler_is_built(self):
        c = dict(workers=4)
        self.assertFalse(a.config(c)['enabled'])
        with patch.object(a, 'Sampler', side_effect=AssertionError('measured while disabled')):
            self.assertIsNone(a.control(Path('/nonexistent'), c, 4))
        snapshot = a.snapshot(Path('/nonexistent'), c)
        self.assertFalse(snapshot['enabled'])
        self.assertFalse(snapshot['controlling'])
        self.assertIsNone(snapshot['cpu_percent'])
        self.assertIsNone(snapshot['admission_limit'])
        self.assertIn('disabled', snapshot['reason'])
        # A disabled install reports the configured cap, and reads nothing.
        self.assertEqual(snapshot['cap'], 4)
        self.assertFalse((Path('/nonexistent') / 'cpu-admission.sqlite').exists())

    def test_defaults_match_the_documented_thresholds(self):
        p = a.config(cpu_config())
        self.assertEqual(p['grow_below'], 0.9)     # add capacity below 90%
        self.assertGreaterEqual(p['shrink_at'], 0.95)  # back off near 100%
        self.assertLess(p['grow_below'], p['shrink_at'])
        self.assertLessEqual(p['shrink_step'], p['grow_step'] * 2)  # back off faster
        self.assertIsNone(p['max_admission'])      # the cap is the ceiling
        self.assertEqual(p['min_admission'], 1)    # never stall the fleet

    def test_invalid_configuration_fails_closed(self):
        bad = [
            {'grow_below': 0.99},                    # above the shrink threshold
            {'shrink_at': 1.5},
            {'grow_below': 0},
            {'shrink_at': 0},
            {'enabled': 'yes'},
            {'samples': 0},
            {'samples': 2.5},
            {'samples': True},
            {'grow_samples': 0},
            {'shrink_samples': 0},
            {'grow_step': 0},
            {'shrink_step': 0},
            {'min_admission': 0},
            {'max_admission': 0},
            {'interval_seconds': 0.1},
            {'interval_seconds': 'fast'},
            {'unknown_knob': 1},
        ]
        for options in bad:
            with self.subTest(options=options):
                with self.assertRaises(ValueError):
                    a.config({'cpu_admission': options})
        with self.assertRaises(ValueError):
            a.config({'cpu_admission': {'enabled': True, 'samples': None}})
        with self.assertRaises(ValueError):
            a.config({'cpu_admission': 'yes'})

    def test_router_config_rejects_invalid_cpu_admission(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / 'config.json'
            base = copy.deepcopy(r.config(r.DEFAULT_CONFIG))
            self.assertNotIn('cpu_admission', base)  # the shipped sample stays off
            base['cpu_admission'] = {'enabled': True, 'shrink_at': 0.5}
            path.write_text(json.dumps(base))
            with self.assertRaises(ValueError):
                r.config(path)
            base['cpu_admission'] = {'enabled': True}
            path.write_text(json.dumps(base))
            self.assertTrue(r.config(path)['cpu_admission']['enabled'])


class SamplerTests(unittest.TestCase):
    def stat(self, tmp, *lines):
        path = Path(tmp) / 'stat'
        path.write_text('\n'.join(lines) + '\n')
        return path

    def test_guest_time_is_not_double_counted(self):
        with tempfile.TemporaryDirectory() as tmp:
            # guest/guest_nice columns are appended; the first eight are used.
            path = self.stat(tmp, 'cpu  100 10 50 800 20 5 5 3 40 7', 'cpu0 1 1 1 1 0 0 0 0 0 0', 'intr 1')
            self.assertEqual(a.read_cpu_times(path), [100, 10, 50, 800, 20, 5, 5, 3])
            sampler = a.Sampler(path)
            self.assertIsNone(sampler.sample())  # baseline only
            # Exactly half the elapsed time is user, half idle, while the guest
            # columns jump by 5000 jiffies: guest is not host busy time.
            path.write_text('cpu  1000 10 50 1700 20 5 5 3 5040 5007\n')
            self.assertEqual(sampler.sample(), 0.5)
            self.assertIsNone(sampler.error)
            self.assertTrue(sampler.supported)

    def test_iowait_is_not_host_compute_pressure(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = self.stat(tmp, 'cpu 0 0 0 0 0 0 0 0')
            sampler = a.Sampler(path)
            sampler.sample()
            path.write_text('cpu 0 0 0 100 900 0 0 0\n')
            self.assertEqual(sampler.sample(), 0.0)  # all elapsed time was idle+iowait

    def test_steal_counts_as_busy_and_result_is_bounded(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = self.stat(tmp, 'cpu 0 0 0 0 0 0 0 0')
            sampler = a.Sampler(path)
            sampler.sample()
            path.write_text('cpu 0 0 0 0 0 0 0 1000\n')
            self.assertEqual(sampler.sample(), 1.0)  # the hypervisor took every cycle

    def test_unreadable_or_malformed_is_explicit_not_silent(self):
        with tempfile.TemporaryDirectory() as tmp:
            sampler = a.Sampler(Path(tmp) / 'absent')
            self.assertIsNone(sampler.sample())
            self.assertEqual(sampler.error, 'proc_stat_unavailable')
            self.assertFalse(sampler.supported)
            short = self.stat(tmp, 'cpu 100 200')
            sampler = a.Sampler(short)
            self.assertIsNone(sampler.sample())
            self.assertEqual(sampler.error, 'proc_stat_malformed')
            self.assertFalse(sampler.supported)
            # A file with only per-CPU lines has no aggregate line.
            only = self.stat(tmp, 'cpu0 1 2 3 4', 'cpu1 1 2 3 4')
            per_cpu = a.Sampler(only)
            self.assertIsNone(per_cpu.sample())
            self.assertEqual(per_cpu.error, 'proc_stat_malformed')

    def test_counter_reset_resynchronizes(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = self.stat(tmp, 'cpu 1000 0 0 1000 0 0 0 0')
            sampler = a.Sampler(path)
            sampler.sample()
            path.write_text('cpu 10 0 0 10 0 0 0 0\n')  # counters went backwards
            self.assertIsNone(sampler.sample())
            self.assertEqual(sampler.error, 'counter_reset')
            self.assertFalse(sampler.supported)
            # The next tick measures from the rebuilt baseline, not from garbage.
            path.write_text('cpu 20 0 0 20 0 0 0 0\n')
            self.assertEqual(sampler.sample(), 0.5)
            self.assertIsNone(sampler.error)
            self.assertTrue(sampler.supported)

    def test_no_elapsed_time_is_not_a_sample(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = self.stat(tmp, 'cpu 100 0 0 100 0 0 0 0')
            sampler = a.Sampler(path)
            sampler.sample()
            self.assertIsNone(sampler.sample())  # same jiffies: nothing to measure
            self.assertIsNone(sampler.error)
            self.assertIsNone(sampler.supported)  # never claimed as supported


class ControllerTests(unittest.TestCase):
    def setUp(self):
        self.addCleanup(a.reset)
        a.reset()

    def test_underutilized_host_grows_back_to_the_cap(self):
        # Saturation removed 7 slots; a quiet host gives one back per 3 windows.
        c = controller([1.0] * 20 + [0.05] * 200, 8, samples=2, grow_samples=3)
        self.assertEqual(c.limit, 8)  # an idle host starts at the cap
        self.assertEqual(drain(c), 8)
        self.assertEqual(c.maximum, 8)
        self.assertEqual(c.cpu_percent, 5.0)  # a true 0..100 percentage
        # One or two quiet windows are not a reason to add a slot.
        fresh = controller([0.05] * 10, 4, samples=2, grow_samples=3)
        fresh.limit = fresh.maximum - 1
        self.assertEqual(fresh.feed(0.05), fresh.maximum - 1)
        self.assertEqual(fresh.feed(0.05), fresh.maximum - 1)
        self.assertEqual(fresh.feed(0.05), fresh.maximum)

    def test_underutilized_host_never_exceeds_its_ceilings(self):
        c = controller([0.1] * 200, 20, max_admission=2)
        self.assertEqual(c.maximum, 2)  # a configured ceiling below the cap
        self.assertEqual(drain(c), 2)
        self.assertLessEqual(c.limit, 20)
        # The scheduler's own cap is the ceiling: --workers 4 of a 20-worker config.
        c = controller([0.1] * 200, 4)
        self.assertEqual(c.maximum, 4)
        self.assertEqual(drain(c), 4)

    def test_sustained_saturation_reduces_the_admission_limit(self):
        c = controller([0.99] * 200, 6, samples=2, shrink_samples=1, shrink_step=1)
        self.assertEqual([drain(c, 1) for _ in range(5)], [5, 4, 3, 2, 1])
        self.assertEqual(drain(c, 30), 1)  # held at the floor, not oscillating
        self.assertGreaterEqual(c.report()['window_mean'], 0.98)
        self.assertEqual(c.report()['admission_maximum'], 6)
        # The default shrink step is twice the default growth step: back off faster.
        d = controller([1.0] * 60, 8, samples=2, shrink_samples=1)
        self.assertEqual(drain(d, 2), 4)  # 8 -> 6 -> 4

    def test_saturation_respects_the_floor_and_the_cap(self):
        c = controller([1.0] * 200, 5, samples=2, min_admission=3, shrink_step=4)
        self.assertEqual(drain(c), 3)
        self.assertGreaterEqual(c.limit, 3)
        # A floor above the cap must not become a floor above the cap.
        over = controller([1.0] * 200, 4, samples=2, min_admission=50)
        self.assertEqual(over.minimum, 4)
        self.assertEqual(drain(over), 4)
        # Neither may a ceiling below the floor.
        crossed = controller([0.1] * 200, 4, min_admission=3, max_admission=1)
        self.assertEqual(crossed.maximum, 1)
        self.assertEqual(crossed.minimum, 1)
        self.assertEqual(drain(crossed), 1)

    def test_hysteresis_band_holds_the_limit(self):
        self.assertEqual(drain(controller([0.93] * 200, 5)), 5)  # between the thresholds
        mixed = [0.99, 0.2] * 100  # alternating: neither side is sustained
        self.assertEqual(drain(controller(mixed, 5)), 5)

    def test_threshold_boundaries_are_half_open(self):
        # At or above shrink_at is saturated; grow_below is not "below" itself.
        at_shrink = controller([0.98] * 60, 4, samples=1, shrink_samples=1, shrink_step=1)
        self.assertEqual(drain(at_shrink), 1)
        at_grow = controller([0.9] * 60, 4, samples=1, grow_samples=1)
        self.assertEqual(drain(at_grow), 4)  # 90% is not below 90%
        just_below = controller([0.89] * 60, 4, samples=1, grow_samples=1)
        self.assertEqual(drain(just_below), 4)  # already at the cap, nothing to add

    def test_unsupported_measurement_never_throttles(self):
        with tempfile.TemporaryDirectory() as tmp:
            sampler = ScriptedSampler([None] * 200, error='proc_stat_unavailable',
                                      supported=False)
            c = a.Admission(a.config(cpu_config()), 5, sampler, clock=Ticks(5.0))
            self.assertEqual(drain(c), 5)
            report = c.report()
            self.assertFalse(report['supported'])
            self.assertEqual(report['error'], 'proc_stat_unavailable')
            self.assertIsNone(report['cpu_percent'])
            self.assertEqual(report['admission_limit'], 5)  # the cap, not a guess
            self.assertTrue(c.dirty)  # reported, not hidden
            self.assertTrue(c.publish(Path(tmp)))
            self.assertFalse(c.dirty)
            c.poll()
            self.assertFalse(c.dirty)  # nothing new to say, so nothing to rewrite

    def test_poll_respects_its_interval(self):
        sampler = ScriptedSampler([0.1, 0.1, 0.1])
        c = a.Admission(a.config(cpu_config(interval_seconds=5)), 4, sampler,
                        clock=Ticks(step=0, start=0.0))
        c.poll()
        self.assertEqual(len(sampler.values), 2)  # one sample consumed
        c.poll()  # inside the interval
        c.poll()
        self.assertEqual(len(sampler.values), 2)
        c.clock.now = 10.0  # 10s later
        c.poll()
        self.assertEqual(len(sampler.values), 1)

    def test_cpu_percent_is_a_percentage_and_the_mean_is_a_fraction(self):
        c = a.Admission(a.config(cpu_config(samples=1)), 4, ScriptedSampler([1.0, 0.5, 0.0]),
                        clock=Ticks(5.0))
        for expected in (100.0, 50.0, 0.0):
            c.poll()
            self.assertEqual(c.report()['cpu_percent'], expected)
            self.assertEqual(c.report()['window_mean'], expected / 100)
        # The two scales cannot be confused: a 0.9 window mean is 90 percent.
        self.assertEqual(a.percent(0.9), 90.0)
        self.assertEqual(a.percent(2), 100.0)  # bounded, never a nonsense percent
        self.assertEqual(a.percent(-1), 0.0)

    def test_a_broken_monitor_is_reported_not_swallowed(self):
        """The scheduler's catch is a no-op for dispatch, never for the report."""
        with tempfile.TemporaryDirectory() as tmp:
            state = Path(tmp)
            c = a.Admission(a.config(cpu_config(samples=1)), 4, ScriptedSampler([0.9]),
                            clock=Ticks(5.0))
            c.poll()
            self.assertEqual(c.publish(state), True)
            c.sampler = BrokenSampler()
            c.next_poll = 0.0
            try:
                c.poll()  # what the scheduler loop does inside its catch
                raised = None
            except RuntimeError as exc:
                raised = exc
            self.assertIsNotNone(raised)  # the sampler failure is real, not hidden
            c.fault(state, raised)
            self.assertEqual(c.error, 'monitoring_error')
            self.assertIn('RuntimeError', c.error_detail)
            self.assertEqual(c.limit, 4)  # a blind monitor never throttles
            snapshot = a.snapshot(state, dict(workers=4, **cpu_config()))
            self.assertEqual(snapshot['state'], 'error')
            self.assertEqual(snapshot['error'], 'monitoring_error')
            self.assertFalse(snapshot['controlling'])
            self.assertIn('monitoring_error', snapshot['reason'])
            # The next working sample clears the fault and control resumes.
            c.sampler, c.next_poll = ScriptedSampler([0.2]), 0.0
            c.poll()
            self.assertIsNone(c.report()['error'])
            self.assertTrue(c.publish(state))
            self.assertEqual(a.snapshot(state, dict(workers=4, **cpu_config()))['state'],
                             'controlling')

    def test_control_is_reused_per_state_and_cap(self):
        c = dict(workers=4, **cpu_config())
        first = a.control('/state', c, 4)
        self.assertIs(first, a.control('/state', c, 4))
        self.assertIsNot(first, a.control('/state', c, 2))
        self.assertIsNot(first, a.control('/other', c, 4))
        with self.assertRaises(ValueError):
            a.Admission(a.config(cpu_config()), 0, ScriptedSampler([]))


class SnapshotTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.state = Path(self.tmp.name)
        self.addCleanup(a.reset)
        a.reset()

    def publish(self, **kw):
        with a.database(self.state) as db:
            a.write(db, kw)

    def test_unpublished_enabled_install_says_so(self):
        snapshot = a.snapshot(self.state, dict(workers=4, **cpu_config()))
        self.assertTrue(snapshot['enabled'])
        self.assertFalse(snapshot['controlling'])
        self.assertIsNone(snapshot['admission_limit'])
        self.assertIsNone(snapshot['supported'])
        self.assertEqual(snapshot['cap'], 4)  # the configured cap, not a claim
        self.assertIn('no scheduler has published', snapshot['reason'])

    def test_missing_cache_creates_nothing(self):
        """A status read is not a writer: no directory, no file, no table."""
        nested = self.state / 'never-created' / 'state'
        snapshot = a.snapshot(nested, dict(workers=4, **cpu_config()))
        self.assertFalse(snapshot['controlling'])
        self.assertEqual(snapshot['state'], 'unpublished')
        self.assertFalse(nested.exists())  # not even the directory
        self.assertFalse((nested / a.CACHE_NAME).exists())
        # An existing but empty state directory is equally untouched.
        self.state.mkdir(exist_ok=True)
        before = sorted(p.name for p in self.state.iterdir())
        a.snapshot(self.state, dict(workers=4, **cpu_config()))
        self.assertEqual(sorted(p.name for p in self.state.iterdir()), before)
        # And the status view of a whole router state creates nothing either.
        c = r.config(r.DEFAULT_CONFIG)
        c.update(cpu_admission={'enabled': True})
        r.compact_status(self.state, c)
        self.assertFalse((self.state / a.CACHE_NAME).exists())

    def test_a_state_path_is_accepted_as_text_or_as_a_path(self):
        """The read and the write must not disagree about what a state is."""
        c = controller([0.25] * 4, 4, samples=1)
        c.poll()
        for state in (self.state, str(self.state)):
            self.assertTrue(c.publish(state))
            snapshot = a.snapshot(state, dict(workers=4, **cpu_config()))
            self.assertEqual(snapshot['state'], 'controlling')
            self.assertEqual(snapshot['cpu_percent'], 25.0)

    def test_status_read_never_takes_a_write_lock(self):
        """A read-only file is still readable, and reading it changes nothing."""
        c = controller([0.4] * 10, 4, samples=1)
        c.poll()
        self.assertTrue(c.publish(self.state))
        path = self.state / a.CACHE_NAME
        before = (path.stat().st_size, path.stat().st_mtime_ns)
        path.chmod(0o444)  # the writer's handle can no longer open this file
        try:
            snapshot = a.snapshot(self.state, dict(workers=4, **cpu_config()))
            self.assertEqual(snapshot['state'], 'controlling')
            self.assertEqual(snapshot['cpu_percent'], 40.0)
            # The read left no journal, no WAL and no size change behind.
            self.assertEqual(sorted(p.name for p in self.state.iterdir()), [a.CACHE_NAME])
            self.assertEqual((path.stat().st_size, path.stat().st_mtime_ns), before)
            # A writer, unlike the reader, cannot use a read-only cache.
            self.assertFalse(c.publish(self.state))
            self.assertTrue(c.failed)
        finally:
            path.chmod(0o644)

    def test_published_report_round_trips_its_own_validation(self):
        c = controller([0.1, 0.2, 0.3, 0.25] * 5, 4, samples=2)
        c.poll()
        c.poll()
        self.assertTrue(c.publish(self.state))
        with a.reader(self.state) as db:  # the read path accepts what we write
            self.assertEqual(a.read(db), c.report())
        snapshot = a.snapshot(self.state, dict(workers=4, **cpu_config()))
        self.assertEqual(snapshot['state'], 'controlling')
        self.assertEqual(snapshot['window_mean'], c.mean)  # 0..1 fraction
        self.assertEqual(snapshot['cpu_percent'], 20.0)  # the latest sample, as a percent
        self.assertLess(snapshot['window_mean'], snapshot['cpu_percent'] / 100)

    def test_invalid_typed_cache_is_reported_not_multiplied(self):
        now = time.time()
        bad = {
            'interval string': dict(interval_seconds='fast', observed_at=now),
            'percent string': dict(cpu_percent='high', observed_at=now),
            'percent above 100': dict(cpu_percent=100.5, observed_at=now),
            'mean is a fraction': dict(window_mean=1.5, observed_at=now),
            'negative interval': dict(interval_seconds=-5, observed_at=now),
            'zero limit': dict(admission_limit=0, observed_at=now),
            'limit above the cap': dict(admission_limit=9, cap=4, observed_at=now),
            'limit below the floor': dict(admission_limit=0, min_admission=2, observed_at=now),
            'boolean is not a number': dict(cpu_percent=True, observed_at=now),
            'string is not a boolean': dict(supported='yes', observed_at=now),
            'unordered thresholds': dict(grow_below=0.99, shrink_at=0.5, observed_at=now),
            'observed_at is text': dict(observed_at='now'),
            'not an enabled report': dict(enabled=False, observed_at=now),
            'source is a number': dict(source=17, observed_at=now),
        }
        for label, value in bad.items():
            with self.subTest(cache=label):
                self.publish(**value)
                snapshot = a.snapshot(self.state, dict(workers=4, **cpu_config()))
                self.assertEqual(snapshot['state'], 'error')
                self.assertEqual(snapshot['error'], 'cache_invalid')
                self.assertFalse(snapshot['controlling'])
                self.assertIsNone(snapshot['admission_limit'])
                self.assertIn('not valid', snapshot['reason'])
        # Malformed JSON and a non-object payload are rejected the same way.
        for raw in ('[]', 'null', 'not json at all', '"text"'):
            with self.subTest(raw=raw):
                with a.database(self.state) as db:
                    a.write(db, {})
                    db.execute('UPDATE cache SET value=? WHERE id=1', (raw,))
                snapshot = a.snapshot(self.state, dict(workers=4, **cpu_config()))
                self.assertEqual(snapshot['error'], 'cache_invalid')
                self.assertFalse(snapshot['controlling'])

    def test_invalid_cache_reaches_status_without_crashing_it(self):
        """The compact status view is the real caller: it must not raise."""
        c = r.config(r.DEFAULT_CONFIG)
        c.update(cpu_admission={'enabled': True}, go_overage_disabled=True)
        with r.database(self.state) as db:
            db.execute('INSERT INTO settings VALUES (?,?)', ('claims_root', str(self.state)))
            db.execute("INSERT INTO jobs (id,target,task,category,tier,status,created) "
                       "VALUES ('j','t','task','bulk','bulk','queued',0)")
        self.publish(enabled=True, supported=True, interval_seconds='fast', observed_at=time.time())
        for data in (r.compact_status(self.state, c), r.status(self.state, c)):
            self.assertEqual(data['cpu_admission']['state'], 'error')
            self.assertEqual(data['cpu_admission']['error'], 'cache_invalid')
            self.assertFalse(data['cpu_admission']['controlling'])
        out = io.StringIO()
        with contextlib.redirect_stdout(out):
            r.print_status(r.status(self.state, c))
        text = out.getvalue()
        self.assertIn('Host CPU admission: error', text)
        self.assertIn('the published CPU report is not valid', text)
        self.assertIn('controlling=False', text)

    def test_read_lock_contention_is_bounded_and_reported(self):
        """A scheduler mid-publish must not stall or break the status read."""
        c = controller([0.3] * 5, 4, samples=1)
        c.poll()
        self.assertTrue(c.publish(self.state))
        holder = sqlite3.connect(self.state / a.CACHE_NAME, timeout=5)
        self.addCleanup(holder.close)
        # BEGIN EXCLUSIVE holds the only lock a reader needs, and does not
        # commit: this is what a scheduler's publish looks like to a client.
        holder.execute('BEGIN EXCLUSIVE')
        holder.execute('UPDATE cache SET value=? WHERE id=1',
                       (json.dumps(dict(enabled=True, supported=True, interval_seconds=5,
                                        admission_limit=1, admission_maximum=4, cap=4,
                                        observed_at=time.time())),))
        started = time.monotonic()
        snapshot = a.snapshot(self.state, dict(workers=4, **cpu_config()))
        elapsed = time.monotonic() - started
        self.assertLess(elapsed, 5, 'the status read waited on the writer')
        self.assertFalse(snapshot['controlling'])
        self.assertEqual(snapshot['state'], 'error')
        self.assertEqual(snapshot['error'], 'cache_busy')
        self.assertIn('not available now', snapshot['reason'])
        self.assertIsNone(snapshot['admission_limit'])  # nothing was half-read
        holder.rollback()
        holder.close()
        # The contention neither corrupted nor lost the committed report.
        recovered = a.snapshot(self.state, dict(workers=4, **cpu_config()))
        self.assertEqual(recovered['state'], 'controlling')
        self.assertEqual(recovered['admission_limit'], 4)
        self.assertEqual(recovered['cpu_percent'], 30.0)

    def test_published_limit_is_visible_and_goes_stale(self):
        now = time.time()
        self.publish(enabled=True, source='/proc/stat', supported=True, cpu_percent=42.0,
                     admission_limit=6, admission_maximum=8, cap=8, min_admission=1,
                     interval_seconds=5, observed_at=now, error=None)
        fresh = a.snapshot(self.state, dict(workers=8, **cpu_config()), now)
        self.assertTrue(fresh['controlling'])
        self.assertEqual(fresh['state'], 'controlling')
        self.assertFalse(fresh['stale'])
        self.assertEqual(fresh['admission_limit'], 6)
        self.assertEqual(fresh['cpu_percent'], 42.0)
        stale = a.snapshot(self.state, dict(workers=8, **cpu_config()), now + 60)
        self.assertFalse(stale['controlling'])
        self.assertTrue(stale['stale'])
        self.assertEqual(stale['state'], 'stale')
        self.assertIn('old', stale['reason'])
        back = a.snapshot(self.state, dict(workers=8, **cpu_config()), now - 5)
        self.assertTrue(back['stale'])  # clock rollback is not a fresh observation
        self.assertEqual(back['admission_limit'], 6)  # the value stays readable

    def test_unsupported_measurement_survives_the_round_trip(self):
        now = time.time()
        self.publish(enabled=True, source='/proc/stat', supported=False, cpu_percent=None,
                     admission_limit=8, admission_maximum=8, cap=8, min_admission=1,
                     interval_seconds=5, observed_at=now, error='proc_stat_unavailable')
        snapshot = a.snapshot(self.state, dict(workers=8, **cpu_config()), now)
        self.assertFalse(snapshot['supported'])
        self.assertEqual(snapshot['error'], 'proc_stat_unavailable')
        self.assertEqual(snapshot['admission_limit'], 8)  # the cap, not a guess
        self.assertIsNone(snapshot['cpu_percent'])

    def test_fresh_numbers_from_an_unmeasurable_host_are_not_control(self):
        """A supported=false report is not CPU control, however recent it is."""
        now = time.time()
        self.publish(enabled=True, source='/proc/stat', supported=False, cpu_percent=99.4,
                     admission_limit=1, admission_maximum=4, cap=4, min_admission=1,
                     interval_seconds=5, observed_at=now, error='proc_stat_unavailable')
        snapshot = a.snapshot(self.state, dict(workers=4, **cpu_config()), now)
        self.assertFalse(snapshot['controlling'])
        self.assertEqual(snapshot['state'], 'unsupported')
        self.assertFalse(snapshot['stale'])  # fresh, and still not controlling
        self.assertEqual(snapshot['error'], 'proc_stat_unavailable')
        self.assertIn('does not report a measurable CPU aggregate', snapshot['reason'])
        self.assertEqual(snapshot['admission_limit'], 1)  # readable, just not believed

    def test_loss_of_support_after_a_valid_saturated_sample_stops_claiming_control(self):
        """The controller keeps its limit, and the report stops claiming support."""
        c = a.Admission(a.config(cpu_config(samples=1, shrink_samples=1)), 4, FadingSampler(),
                        clock=Ticks(5.0))
        for _ in range(4):
            c.poll()
        self.assertLess(c.limit, 4)  # saturation already lowered the limit
        self.assertEqual(c.report()['supported'], True)
        c.poll()  # the host becomes unmeasurable
        report = c.report()
        self.assertFalse(report['supported'])
        self.assertEqual(report['error'], 'proc_stat_unavailable')
        # The last real measurement stays readable, and its own timestamp keeps
        # ageing, so a blind host cannot keep the status view fresh forever.
        self.assertEqual(report['cpu_percent'], 100.0)
        self.assertLessEqual(report['observed_at'], time.time())
        self.assertTrue(c.publish(self.state))
        published = a.snapshot(self.state, dict(workers=4, **cpu_config()))
        self.assertFalse(published['controlling'])
        self.assertEqual(published['state'], 'unsupported')
        # The limit is not revoked and no worker is disturbed by a blind monitor.
        self.assertEqual(published['admission_limit'], c.limit)

    def test_publish_never_raises_and_retries_once_per_interval(self):
        c = controller([0.1] * 20, 4, samples=1)
        with patch.object(a, 'database', side_effect=OSError('read-only state')):
            self.assertFalse(c.publish(self.state))
            self.assertFalse(c.dirty)
        c.poll()
        self.assertTrue(c.dirty)  # a failed write is retried, not lost
        self.assertTrue(c.publish(self.state))
        self.assertFalse(c.dirty)
        # A fresh observation is republished so the status view stays fresh.
        c.poll()
        self.assertTrue(c.dirty)

    def test_status_exposes_admission_without_touching_attempts(self):
        c = r.config(r.DEFAULT_CONFIG)
        with tempfile.TemporaryDirectory() as tmp:
            state = Path(tmp)
            with r.database(state) as db:
                db.execute('INSERT INTO settings VALUES (?,?)', ('claims_root', tmp))
                db.execute("INSERT INTO jobs (id,target,task,category,tier,status,created) "
                           "VALUES ('j','t','task','bulk','bulk','queued',0)")
            data = r.status(state, c)
            self.assertIn('cpu_admission', data)
            self.assertFalse(data['cpu_admission']['enabled'])
            # The job row is untouched by a status read.
            self.assertEqual(data['jobs'][0]['note'], '')
            self.assertIsNone(data['attempts'][0]['admission'] if data['attempts'] else None)
            out = io.StringIO()
            with contextlib.redirect_stdout(out):  # the human line must render
                r.print_status(data)
        self.assertIn('Host CPU admission: off', out.getvalue())


class HostTests(unittest.TestCase):
    def test_this_host_can_measure(self):
        if not Path('/proc/stat').exists():
            self.skipTest('no /proc/stat on this platform')
        sampler = a.Sampler()
        self.assertIsNone(sampler.sample())
        busy = []
        for _ in range(3):
            time.sleep(.05)
            busy.append(sampler.sample())
        measured = [x for x in busy if x is not None]
        if not measured:
            self.skipTest('no CPU time elapsed between samples')
        for value in measured:
            self.assertGreaterEqual(value, 0.0)
            self.assertLessEqual(value, 1.0)
        self.assertIsNone(sampler.error)


class SaturatedSampler:
    """Idle at first, then a fully saturated host for the rest of the run."""

    path = '/proc/stat'
    error = None
    supported = True

    def __init__(self, quiet_ticks=2):
        self.quiet_ticks = quiet_ticks

    def sample(self):
        if self.quiet_ticks > 0:
            self.quiet_ticks -= 1
            return 0.1
        return 1.0


@unittest.skipUnless(sys.platform.startswith('linux'), 'Linux cgroup v2 delegation')
class FleetAdmissionTests(unittest.TestCase):
    """The dispatch gate honors the limit, and no running worker is stopped."""

    def setUp(self):
        try:
            probe = r.fleet_cgroup.CgroupV2Unit.create('router-cpu-test-' + r.uuid.uuid4().hex)
            probe.remove()
        except r.fleet_cgroup.ContainmentUnavailable as exc:
            self.skipTest(str(exc))
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        self.state = self.root / 'state'
        self.fake = self.root / 'opencode'
        self.fake.write_text(FAKE)
        self.fake.chmod(0o755)
        self.c = r.config(r.DEFAULT_CONFIG)
        self.c.update(cost_aware=False, opencode=str(self.fake), go_overage_disabled=True,
                      timeout=20, cooldown=.3, failure_cooldown=.05, workers=4,
                      variant_discovery=False, cpu_admission={'enabled': True})
        self.c['models'] = [dict(id='opencode-go/one', tier='bulk', enabled=True, concurrency=4,
                                 reserve=0, weight=1)]
        with r.go_budget.database(self.state) as db:
            r.go_budget.write(db, dict(windows=r.go_budget.parse_usage(
                {'usage': {k: {'percent': 20, 'status': 'ok',
                               'resetsAt': __import__('datetime').datetime.fromtimestamp(
                                   time.time() + 10000, __import__('datetime').timezone.utc).isoformat()}
                            for k in ('rolling', 'weekly', 'monthly')}}),
                observed_at=time.time(), next_refresh=time.time() + 10000))
        with r.database(self.state) as db:
            db.execute('INSERT INTO settings VALUES (?,?)', ('claims_root', str(self.root)))
        self.addCleanup(a.reset)
        a.reset()

    def job(self, text='cpu test'):
        cwd = self.root / ('cwd-' + str(time.time_ns()))
        cwd.mkdir()
        return r.enqueue(self.state, 'bulk', text, cwd=cwd, redundant=True)

    def attempts(self):
        with r.database(self.state) as db:
            return [dict(row) for row in db.execute('SELECT * FROM attempts ORDER BY started')]

    def test_saturated_host_bounds_dispatch_and_never_kills_a_worker(self):
        for _ in range(4):
            self.job('SLOW')  # each worker outlives several admission windows
        c = a.Admission(a.config(self.c), 4, SaturatedSampler(),
                        clock=Ticks(step=self.c['cpu_admission'].get('interval_seconds', 5)))
        with patch.object(a, 'control', return_value=c):
            r.fleet(self.root, self.state, self.c, 20)
        self.assertLess(c.limit, 4)  # a saturated host lowered the limit
        rows = self.attempts()
        self.assertTrue(rows)
        # Nothing was stopped to make room: every admitted worker finished.
        self.assertEqual([row['status'] for row in rows], ['success'] * len(rows))
        # Every attempt records the limit that admitted it, and none exceeds the cap.
        recorded = [json.loads(row['result'])['admission'] for row in rows]
        for entry in recorded:
            self.assertLessEqual(entry['limit'], 4)
            self.assertIsNone(entry['error'])
            self.assertIn(entry['cpu_percent'], (10.0, 100.0))  # true percent
        # The queue drained, so the limit alone never stalled the fleet.
        self.assertEqual(len(rows), 4)
        # A worker is never killed to reduce concurrency.
        with r.database(self.state) as db:
            self.assertEqual(db.execute(
                "SELECT COUNT(*) FROM attempts WHERE status IN ('needs_review','interrupted')"
            ).fetchone()[0], 0)
        # The status interface reports the limit without touching attempt rows.
        published = a.snapshot(self.state, self.c)
        self.assertTrue(published['controlling'])
        self.assertEqual(published['admission_limit'], c.limit)
        self.assertLessEqual(published['admission_limit'], published['cap'])

    def test_fleet_works_without_cpu_admission(self):
        self.c['cpu_admission'] = {'enabled': False}
        a.reset()
        with patch.object(a, 'Sampler', side_effect=AssertionError('measured while disabled')):
            self.assertIsNone(a.control(self.state, self.c, 4))
            for _ in range(2):
                self.job()
            r.fleet(self.root, self.state, self.c, 5)
        rows = self.attempts()
        self.assertEqual(len(rows), 2)
        for row in rows:
            self.assertIsNone(json.loads(row['result'])['admission'])
        snapshot = a.snapshot(self.state, self.c)
        self.assertFalse(snapshot['enabled'])
        self.assertFalse((self.state / a.CACHE_NAME).exists())

    def saturated_controller(self, **options):
        """A controller that a saturated host drives down on the first window."""
        self.c['cpu_admission'] = {'enabled': True, 'samples': 1, 'shrink_samples': 1,
                                   'shrink_step': 3, 'interval_seconds': 1, **options}
        return a.Admission(a.config(self.c), 4, SaturatedSampler(quiet_ticks=0),
                           clock=Ticks(step=1.0))

    def test_a_limit_of_one_serializes_dispatch_and_still_drains(self):
        for _ in range(3):
            self.job('SLOW')
        c = self.saturated_controller()
        self.assertEqual(c.limit, 4)  # an idle host starts at the cap
        with patch.object(a, 'control', return_value=c):
            r.fleet(self.root, self.state, self.c, 25)
        c.poll()
        self.assertEqual(c.limit, 1)  # saturation drove the limit to the floor
        rows = self.attempts()
        self.assertEqual([row['status'] for row in rows], ['success'] * 3)
        # The floor serialized dispatch: no two attempts ever overlapped.
        for earlier, later in zip(rows, rows[1:]):
            self.assertLessEqual(earlier['ended'], later['started'])
        for row in rows:
            self.assertEqual(json.loads(row['result'])['admission']['limit'], 1)

    def test_admission_does_not_override_the_quota_gate(self):
        """A lowered admission limit and an exhausted Go budget both still bind."""
        for _ in range(2):
            self.job('SLOW')
        self.exhaust_the_go_budget()
        c = self.saturated_controller()
        with patch.object(a, 'control', return_value=c):
            r.fleet(self.root, self.state, self.c, 4)
        self.assertEqual(self.attempts(), [])  # the quota gate stopped every dispatch
        with r.database(self.state) as db:
            notes = [row['note'] for row in db.execute('SELECT note FROM jobs')]
        self.assertEqual(notes, ['budget.account_exhausted'] * 2)
        # The CPU report is still published, and it does not claim to be why.
        published = a.snapshot(self.state, self.c)
        self.assertTrue((self.state / a.CACHE_NAME).exists())
        self.assertIsNone(published['error'])

    def test_a_broken_monitor_never_stops_dispatch_and_is_reported(self):
        """The scheduler's monitoring catch: dispatch continues, the report does not lie."""
        for _ in range(2):
            self.job()
        c = a.Admission(a.config(self.c), 4, BrokenSampler(), clock=Ticks(step=0, start=0.0))
        with patch.object(a, 'control', return_value=c):
            r.fleet(self.root, self.state, self.c, 10)
        rows = self.attempts()
        self.assertEqual([row['status'] for row in rows], ['success'] * 2)  # unaffected
        for row in rows:
            admission = json.loads(row['result'])['admission']
            self.assertEqual(admission['error'], 'monitoring_error')
            self.assertIsNone(admission['cpu_percent'])  # nothing was ever measured
        # The published status says the monitor failed, instead of implying control.
        published = a.snapshot(self.state, self.c)
        self.assertEqual(published['state'], 'error')
        self.assertEqual(published['error'], 'monitoring_error')
        self.assertFalse(published['controlling'])
        with a.reader(self.state) as db:  # the failure is published, not swallowed
            self.assertIn('RuntimeError', a.read(db)['error_detail'])
        self.assertEqual(c.limit, 4)  # a blind monitor never throttles

    def exhaust_the_go_budget(self, percent=100):
        resets = __import__('datetime').datetime.fromtimestamp(
            time.time() + 10000, __import__('datetime').timezone.utc).isoformat()
        with r.go_budget.database(self.state) as db:
            r.go_budget.write(db, dict(windows=r.go_budget.parse_usage(
                {'usage': {k: {'percent': percent, 'status': 'ok', 'resetsAt': resets}
                           for k in ('rolling', 'weekly', 'monthly')}}),
                observed_at=time.time(), next_refresh=time.time() + 10000))


if __name__ == '__main__':
    unittest.main()
