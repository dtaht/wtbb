# WTBB - Where's the bloat?
"It is important to point fingers at the real source of the problem' - Matt Mathis
-- a test tool for finding where bufferbloat is accumulating on the network
-- implementing Apple's internet responsiveness tool and compatible with their backend

#  where's the bloat?

After generating and analyzing "responsiveness under working conditions",
the next step is to figure out where all that data is accumulating.

* In the application?
* Socket Buffer?
* network stack?
* Local qdisc?
* The device driver?
* Next hop? or other hop?
* The receiving application?

# Prior Work

mtr
flent
tcptrace

Most of these tools reward fair queuing, not AQM, and it takes some setup to successfully monitor tcp RTTs in the flent tool. They also are fragile.

# Methods

## Probing mechanism

An ICMP unreachable message 
Monitoring TCP_INFO
 - packets in flight

# Procedural outline

## Warm up phase

turn off garbage collection
commit memory for entire test (calloc)

## Cool Down phase

wait for completion
get final socket statistics
close file descriptors
join critical data
analyze the results

## Reporting

Bottleneck detection
AQM detection
FQ detection
CC detection
Jitter Metric
RPM output
Loss/ECN marking output

# data

tcpi_snd_msstcpi_snd_cwnd*tcpi_snd_unacked*ioctl(SIOCOUTQ)OS X**tcpi_maxsegtcpi_snd_cwnd-tcpi_snd_sbbytesFreeBSDtcpi_snd_msstcpi_snd_cwnd-ioctl(FIONWRITE)NetBSDtcpi_snd_msstcpi_snd_cwnd*-ioctl(FIONWRITE)17■calculate either of:⁃CWND - inflight⁃min(CWND - (inflight + unsent), 0)■units used in the calculation must be the same⁃NetBSD: fail*: units of values marked are packets, unmarked are octets **: sometimes the values of tcpi_* are returned as zeros

size_t get_suggested_write_size() {    getsockopt(fd, IPPROTO_TCP, TCP_INFO, &tcp_info, sizeof(tcp_info));    if (tcp_info.tcpi_rtt < min_rtt || tcp_info.tcpi_snd_cwnd > max_cwnd)        return UNKNOWN;    switch (SSL_get_current_cipher(ssl)->id) {    case TLS1_CK_RSA_WITH_AES_128_GCM_SHA256:    case ...:        tls_overhead = 5 + 8 + 16;        break;    default:        return UNKNOWN;    }    packets_sendable = tcp_info.tcpi_snd_cwnd > tcp_info.tcpi_unacked ?        tcp_info.tcpi_snd_cwnd - tcp_info.tcpi_unacked : 0;    return (packets_sendable + 2) * (tcp_info.tcpi_snd_mss - tls_overhead);}10


# Possible implementation Tricks

cmsg SO_TIMESTAMP
SO_PACING
map the linux time page on top of itself to get kernel timestamps dynamically
ringbuffer I/O (uring)
packet exits and drops from the interface /sys/class/net/device

# futures

override TCP's congestion window

pacing


