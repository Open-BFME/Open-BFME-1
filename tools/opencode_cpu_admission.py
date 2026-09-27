"""Optional host-CPU-aware admission control for the router fleet.

The fleet already bounds concurrency by the configured global cap. This adds a
rolling, hysteretic ADMISSION LIMIT at or below that cap: it grows while the
host is underutilized and falls back while the host stays saturated.

It bounds NEW dispatch only. A worker that is already running is never stopped,
interrupted or restarted because the limit fell, so useful work drains
naturally. It never changes model concurrency, per-model reserves, cooldowns,
cost-aware selection, retry budgets or the shared Go budget; the existing
selection and budget gates are untouched. It is off unless
`cpu_admission.enabled` is true, and while off no host CPU is measured at all.

Host CPU is the kernel's /proc/stat aggregate line: the first eight jiffy
counters (user, nice, system, idle, iowait, irq, softirq, steal). guest and
guest_nice are excluded on purpose -- the kernel already counts guest time
inside user and nice, so including them would double count. iowait is counted
as idle, because waiting for IO is not host compute pressure. A host without a
readable /proc/stat reports an explicit unsupported measurement and keeps the
limit at the cap; it never claims CPU control it does not have.

Control is additive increase / faster decrease. The rolling mean must stay below
`grow_below` for `grow_samples` consecutive windows to add one admission slot,
and at or above `shrink_at` for `shrink_samples` consecutive windows to remove
`shrink_step`. Between the thresholds the limit is held, so a busy-but-not-
saturated host does not churn the fleet.

The configured worker cap is a hard ceiling: the limit starts there, so a fleet
that is not saturated behaves exactly as before, and `grow_below` only recovers
slots a sustained saturation removed. `max_admission` lowers that ceiling
deliberately, for a host that should never run the full cap. The limit is
`min(--workers, cap, admission limit)` at dispatch.

The published report is a separate file in the router state directory, exactly as
the Go budget cache is, so any client of the shared state sees the current
admission limit without touching router schema or any attempt row. Writing it
is the scheduler's job only: the status read is a real read-only SQLite
connection (`mode=ro`) with a bounded lock wait, so a status view of a state
directory with nothing published creates no directory, no file and no table,
and a scheduler holding the write lock is reported as busy rather than waited
on. Every published number is range- and type-checked on the way out, and the
status view names its own condition -- `disabled`, `unpublished`, `error`,
`unsupported`, `stale` or `controlling` -- instead of inferring control from
the presence of plausible numbers.

`cpu_percent` is a true 0..100 percentage. `window_mean` stays a 0..1 fraction
because it is what `grow_below` and `shrink_at` are compared against.
"""
from collections import deque
from contextlib import contextmanager
import json
import math
from pathlib import Path
import sqlite3
import time
import urllib.parse

PROC_STAT = '/proc/stat'
CACHE_NAME = 'cpu-admission.sqlite'
DEFAULTS = dict(enabled=False, grow_below=0.9, shrink_at=0.98, samples=4,
                grow_samples=3, shrink_samples=2, grow_step=1, shrink_step=2,
                min_admission=1, max_admission=None, interval_seconds=5.0)
STALE_INTERVALS = 3
# A status read waits this long for a shared lock, then reports the cache busy.
READ_LOCK_SECONDS = 0.25

_CONTROLS = {}


def config(c):
    options = c.get('cpu_admission', {})
    if not isinstance(options, dict) or set(options) - set(DEFAULTS):
        raise ValueError('unknown cpu_admission configuration field')
    p = {**DEFAULTS, **options}
    if type(p['enabled']) is not bool:
        raise ValueError('cpu_admission enabled must be a boolean')
    for key in ('grow_below', 'shrink_at', 'interval_seconds'):
        if type(p[key]) not in (int, float) or not math.isfinite(p[key]):
            raise ValueError(f'cpu_admission {key} must be a finite number')
    if not 0 < p['grow_below'] < p['shrink_at'] <= 1:
        raise ValueError('cpu_admission thresholds must satisfy 0 < grow_below < shrink_at <= 1')
    if p['interval_seconds'] < .5:
        raise ValueError('cpu_admission interval_seconds must be at least 0.5 seconds')
    for key in ('samples', 'grow_samples', 'shrink_samples', 'grow_step',
                'shrink_step', 'min_admission', 'max_admission'):
        value = p[key]
        if value is None:
            if key == 'max_admission':
                continue
            raise ValueError(f'cpu_admission {key} must be a positive integer')
        if type(value) is not int or value < 1:
            raise ValueError(f'cpu_admission {key} must be a positive integer')
    return p


def read_cpu_times(path=PROC_STAT):
    """Aggregate jiffy counters, guest time excluded. Raises when unavailable."""
    with open(path, 'rb') as handle:
        for line in handle:
            if not line.startswith(b'cpu '):
                continue
            fields = line.split()
            if len(fields) < 9:
                raise ValueError('aggregate cpu line lacks the eight jiffy counters')
            # fields[9:11] are guest and guest_nice, already inside user and nice.
            return [int(field) for field in fields[1:9]]
    raise ValueError('no aggregate cpu line')


def percent(fraction):
    """A 0..1 utilization fraction as a true 0..100 percentage, bounded."""
    return round(min(1.0, max(0.0, float(fraction))) * 100, 1)


class Sampler:
    """Two-point utilization sampler. None means "not measurable right now"."""

    def __init__(self, path=PROC_STAT):
        self.path = path
        self.previous = None
        self.error = None
        self.supported = None  # None: never measured, True/False: last read worked

    def sample(self):
        try:
            times = read_cpu_times(self.path)
        except OSError:
            self.previous = None
            self.error, self.supported = 'proc_stat_unavailable', False
            return None
        except (ValueError, IndexError):
            self.previous = None
            self.error, self.supported = 'proc_stat_malformed', False
            return None
        previous, self.previous = self.previous, times
        if previous is None:
            return None  # first reading only establishes a baseline
        deltas = [now - old for old, now in zip(previous, times)]
        if any(delta < 0 for delta in deltas):
            self.error, self.supported = 'counter_reset', False
            self.previous = times  # resynchronize instead of failing every tick
            return None
        total = sum(deltas)
        if total <= 0:
            return None  # no elapsed CPU time: no utilization can be computed
        self.error, self.supported = None, True
        idle = deltas[3] + deltas[4]  # idle, iowait
        return min(1.0, max(0.0, (total - idle) / total))


class Admission:
    """Deterministic rolling-window admission limit. IO only through the sampler."""

    def __init__(self, options, cap, sampler=None, clock=time.monotonic):
        if type(cap) is not int or cap < 1:
            raise ValueError('admission cap must be a positive integer')
        self.options = dict(options)
        self.cap = cap
        self.clock = clock
        self.sampler = sampler if sampler is not None else Sampler()
        self.source = getattr(self.sampler, 'path', 'injected sampler')
        # Never above the configured cap, and never above an explicit maximum.
        self.maximum = max(1, min(self.options['max_admission'] or cap, cap))
        # A configured floor above the cap would itself break the cap; clamp it.
        self.minimum = min(self.options['min_admission'], self.maximum)
        # Start at the cap: an idle or unknown host keeps today's behavior.
        self.limit = self.maximum
        self.window = deque(maxlen=self.options['samples'])
        self.mean = None
        self.cpu_percent = None
        self.error = None
        self.error_detail = None
        self.observed_at = None
        self.over = self.under = 0
        self.next_poll = 0.0
        self.dirty = False
        self.published = None  # the report the status file last accepted
        self.failed = False

    @property
    def interval(self):
        return self.options['interval_seconds']

    def feed(self, sample):
        """Fold one utilization fraction into the window. None is not a sample."""
        if sample is None:
            return self.limit
        sample = min(1.0, max(0.0, float(sample)))
        self.window.append(sample)
        self.mean = round(sum(self.window) / len(self.window), 4)
        sustained = self.mean
        if sustained >= self.options['shrink_at']:
            self.over, self.under = self.over + 1, 0
        elif sustained < self.options['grow_below']:
            self.under, self.over = self.under + 1, 0
        else:
            self.over = self.under = 0  # hysteresis band: hold the current limit
        limit = self.limit
        if self.over >= self.options['shrink_samples']:
            limit = max(self.minimum, self.limit - self.options['shrink_step'])
            self.over = 0
        elif self.under >= self.options['grow_samples']:
            limit = min(self.maximum, self.limit + self.options['grow_step'])
            self.under = 0
        if limit != self.limit:
            self.limit, self.dirty = limit, True
        return self.limit

    def poll(self, now=None):
        """Sample at most once per interval; returns the current admission limit."""
        now = self.clock() if now is None else now
        if now < self.next_poll:
            return self.limit
        self.next_poll = now + self.interval
        sample = self.sampler.sample()
        self.error = getattr(self.sampler, 'error', None)
        if sample is None:
            # An unmeasurable or unsupported tick never throttles. It is still
            # published, but only when the report actually says something new:
            # the scheduler loop calls this far more often than the interval.
            self.changed()
            return self.limit
        self.error_detail = None
        self.cpu_percent = percent(sample)
        self.observed_at = time.time()
        self.feed(sample)
        self.changed()
        return self.limit

    def fault(self, state, exc):
        """Record a monitoring failure explicitly, then publish it.

        The scheduler must never let host CPU monitoring stop dispatch or worker
        supervision, so it catches everything this module can raise. Swallowing
        the failure silently would be a different lie: a status view would keep
        reporting a healthy measurement that never happened. So the failure
        becomes an explicit `monitoring_error` in the published report, and the
        next working sample clears it. The limit is untouched -- a broken
        monitor never throttles.
        """
        self.error = 'monitoring_error'
        self.error_detail = f'{type(exc).__name__}: {exc}'[:200]
        self.changed()
        if self.dirty:
            self.publish(state)
        return self.limit

    def changed(self):
        """Mark the report publishable only when it differs from the last one."""
        report = self.report()
        if self.failed or report != self.published:
            self.published, self.dirty = report, True
        return self.dirty

    def report(self):
        return dict(enabled=True, source=self.source,
                    supported=getattr(self.sampler, 'supported', None),
                    cpu_percent=self.cpu_percent, window_mean=self.mean,
                    window_samples=len(self.window), admission_limit=self.limit,
                    admission_maximum=self.maximum, cap=self.cap,
                    min_admission=self.minimum, grow_below=self.options['grow_below'],
                    shrink_at=self.options['shrink_at'], grow_step=self.options['grow_step'],
                    shrink_step=self.options['shrink_step'], samples=self.options['samples'],
                    grow_samples=self.options['grow_samples'],
                    shrink_samples=self.options['shrink_samples'],
                    saturated_windows=self.over, idle_windows=self.under,
                    interval_seconds=self.interval, observed_at=self.observed_at,
                    error=self.error, error_detail=self.error_detail)

    def publish(self, state):
        report = self.report()
        self.dirty = False
        try:
            with database(state) as db:
                write(db, report)
        except (OSError, sqlite3.Error, TypeError, ValueError):
            # Reporting must never delay or stop dispatch. Retry on the next
            # interval, not on every scheduler iteration.
            self.failed = True
            return False
        self.failed, self.published = False, report
        return True


def control(state, c, cap, sampler=None, clock=time.monotonic):
    """The scheduler's controller, or None while CPU admission is disabled.

    One controller per state directory, cap and configuration, so the repeated
    `fleet` calls of a `run` keep their rolling window instead of restarting it.
    Only one scheduler owns a state directory at a time.
    """
    options = config(c)
    if not options['enabled']:
        return None
    key = (str(state), cap, json.dumps(options, sort_keys=True))
    if key not in _CONTROLS:
        _CONTROLS[key] = Admission(options, cap, sampler, clock)
    return _CONTROLS[key]


def reset():
    _CONTROLS.clear()


class CacheMissing(Exception):
    """No scheduler has published a report here. Not an error, and not a
    reason to create the directory, the file or the table."""


def cache_file(state):
    return Path(state) / CACHE_NAME


@contextmanager
def database(state):
    """The scheduler's WRITE handle: it owns creating the cache."""
    state = Path(state)  # the read path already accepts a str; keep both alike
    state.mkdir(parents=True, exist_ok=True, mode=0o700)
    db = sqlite3.connect(cache_file(state), timeout=READ_LOCK_SECONDS)
    try:
        db.execute('CREATE TABLE IF NOT EXISTS cache (id INTEGER PRIMARY KEY CHECK(id=1), value TEXT NOT NULL)')
        with db:
            yield db
    finally:
        db.close()


@contextmanager
def reader(state):
    """A genuinely read-only handle on the published cache.

    `mode=ro` cannot create the file, cannot create the table and cannot take a
    write lock, so a status read on a state directory with nothing published
    leaves the filesystem exactly as it found it -- and a read-only file is
    still readable. `busy_timeout` bounds the wait for the shared lock against a
    scheduler that is mid-publish, so contention is reported as busy instead of
    stalling whatever asked for the status.
    """
    path = cache_file(state)
    if not path.is_file():
        raise CacheMissing(str(path))
    uri = 'file:' + urllib.parse.quote(str(path)) + '?mode=ro'
    db = sqlite3.connect(uri, uri=True, timeout=READ_LOCK_SECONDS)
    try:
        db.execute(f'PRAGMA busy_timeout = {int(READ_LOCK_SECONDS * 1000)}')
        yield db
    finally:
        db.close()


def _number(value, low, high, allow_none=True):
    if value is None:
        if allow_none:
            return
        raise ValueError('missing number')
    if type(value) not in (int, float) or not math.isfinite(value) or not low <= value <= high:
        raise ValueError('number out of range')
    return value


def _integer(value, low=1, allow_none=False):
    if value is None:
        if allow_none:
            return
        raise ValueError('missing integer')
    if type(value) is not int or value < low:
        raise ValueError('integer out of range')
    return value


def _text(value, allow_none=True):
    if value is None:
        if allow_none:
            return
        raise ValueError('missing text')
    if type(value) is not str:
        raise ValueError('expected text')
    return value


def _boolean(value, allow_none=True):
    if value is None:
        if allow_none:
            return
        raise ValueError('missing boolean')
    if type(value) is not bool:
        raise ValueError('expected a boolean')
    return value


def read(db):
    """The published report, or {} when the row is absent.

    Every field that is present is type- and range-checked. A cache row is
    untrusted input: it is a file another process wrote, and a malformed string
    where a number belongs must be reported, not multiplied or compared.
    Unknown fields are tolerated so a newer scheduler can add to the report.
    """
    row = db.execute('SELECT value FROM cache WHERE id=1').fetchone()
    value = json.loads(row[0]) if row else {}
    if not isinstance(value, dict):
        raise ValueError('invalid cache')
    if 'enabled' in value and value['enabled'] is not True:
        raise ValueError('cache is not an enabled admission report')
    _text(value.get('source'))
    _boolean(value.get('supported'))
    _text(value.get('error'))
    _text(value.get('error_detail'))
    _number(value.get('cpu_percent'), 0, 100)  # true percent, not a fraction
    _number(value.get('window_mean'), 0, 1)  # fraction: the threshold scale
    _number(value.get('interval_seconds'), 0.5, 1e6, allow_none=True)  # config's floor
    _integer(value.get('window_samples'), 0, allow_none=True)
    _integer(value.get('admission_limit'), 1, allow_none=True)
    _integer(value.get('admission_maximum'), 1, allow_none=True)
    _integer(value.get('cap'), 1, allow_none=True)
    _integer(value.get('min_admission'), 1, allow_none=True)
    _number(value.get('observed_at'), -1e18, 1e18, allow_none=True)
    for key in ('samples', 'grow_samples', 'shrink_samples', 'grow_step', 'shrink_step'):
        _integer(value.get(key), 1, allow_none=True)
    for key in ('saturated_windows', 'idle_windows'):
        _integer(value.get(key), 0, allow_none=True)
    _number(value.get('grow_below'), 0, 1, allow_none=True)
    _number(value.get('shrink_at'), 0, 1, allow_none=True)
    if 'grow_below' in value and 'shrink_at' in value:
        if value['grow_below'] >= value['shrink_at']:
            raise ValueError('cached thresholds are not ordered')
    # A limit above the ceiling it is bounded by is not a limit anyone applied.
    if 'admission_limit' in value:
        for key in ('cap', 'admission_maximum'):
            if key in value and value['admission_limit'] > value[key]:
                raise ValueError('cached admission limit exceeds its ceiling')
        if 'min_admission' in value and value['admission_limit'] < value['min_admission']:
            raise ValueError('cached admission limit is below its floor')
    return value


def write(db, value):
    db.execute('INSERT INTO cache VALUES (1,?) ON CONFLICT(id) DO UPDATE SET value=excluded.value',
               (json.dumps(value),))


def published(state):
    """Read the published report. Returns (cache, error) with error a code.

    No exception escapes and nothing is created, so a status view cannot fail,
    cannot slow down to a lock wait and cannot leave an artifact behind.
    """
    try:
        with reader(state) as db:
            return read(db), None
    except CacheMissing:
        return {}, None  # nothing published yet, and that is not a failure
    except sqlite3.Error as exc:
        message = str(exc).lower()
        if 'lock' in message or 'busy' in message:
            return {}, 'cache_busy'  # a scheduler is publishing right now
        return {}, 'cache_unreadable'
    except (ValueError, TypeError, OverflowError):
        return {}, 'cache_invalid'
    except OSError:
        return {}, 'cache_unreadable'


# Why the status view is not controlling, per state. `controlling` is the gate.
REASONS = dict(
    disabled='cpu_admission disabled; the fleet uses its configured worker cap',
    unpublished='no scheduler has published a host CPU observation yet',
    cache_busy='a scheduler holds the published CPU report; the reading is not available now',
    cache_unreadable='the published CPU report could not be read; treating it as absent',
    cache_invalid='the published CPU report is not valid; treating it as absent',
)


def snapshot(state, c, now=None):
    """Read-only status view.

    Never measures, never writes, never creates, and never waits long for a
    writer. It also never claims CPU control it cannot evidence: `controlling`
    requires a readable, in-range, fresh report from a host that actually
    produced a measurement with no error attached.
    """
    now = time.time() if now is None else now
    p = config(c)
    view = dict(enabled=p['enabled'], state='disabled' if not p['enabled'] else 'unpublished',
                controlling=False, source=PROC_STAT, supported=None, cpu_percent=None,
                window_mean=None, admission_limit=None, admission_maximum=None,
                cap=c['workers'], min_admission=None, grow_below=p['grow_below'],
                shrink_at=p['shrink_at'], interval_seconds=p['interval_seconds'],
                observed_at=None, age_seconds=None, stale=None, error=None,
                reason=REASONS['disabled'] if not p['enabled'] else REASONS['unpublished'])
    if not p['enabled']:
        return view
    cache, failure = published(state)
    if failure:
        view.update(state='error', error=failure, reason=REASONS[failure])
        return view
    if not cache:
        return view
    # read() has already proved these are numbers in range, so arithmetic here
    # cannot raise on a malformed cache.
    observed = cache.get('observed_at')
    age = None if observed is None else now - observed
    interval = cache.get('interval_seconds') or p['interval_seconds']
    stale = age is None or age < 0 or age > STALE_INTERVALS * interval
    reported = cache.get('error')
    view.update(source=cache.get('source') or PROC_STAT, supported=cache.get('supported'),
                cpu_percent=cache.get('cpu_percent'), window_mean=cache.get('window_mean'),
                admission_limit=cache.get('admission_limit'),
                admission_maximum=cache.get('admission_maximum'),
                cap=cache.get('cap') or c['workers'],
                min_admission=cache.get('min_admission'),
                observed_at=observed, age_seconds=None if age is None else round(age, 1),
                stale=stale, error=reported)
    if cache.get('supported') is not True:
        # Numbers from an earlier successful sample are still readable, but a
        # host that is not measurable right now is not under CPU control.
        view.update(state='unsupported', reason=(
            'this host does not report a measurable CPU aggregate (%s); the last admission limit is retained'
            % (reported or 'no measurement yet')))
    elif reported:
        view.update(state='error', reason='the last host CPU monitoring tick failed: ' + reported)
    elif stale:
        view.update(state='stale', reason=(
            'the last published host CPU reading is %s; the fleet is not under CPU admission'
            % ('never timestamped' if age is None else
               'from the future' if age < 0 else '%ss old' % round(age, 1))))
    else:
        view.update(state='controlling', controlling=True, reason=None)
    return view
