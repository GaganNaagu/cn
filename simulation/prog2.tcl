set ns [new Simulator]

# Colors
$ns color 1 Blue      ;# Ping
$ns color 2 Red       ;# TCP Congestion

# Trace & NAM files
set tf [open out.tr w]
$ns trace-all $tf
set nf [open out.nam w]
$ns namtrace-all $nf

proc finish {} {
    global ns tf nf
    $ns flush-trace
    close $tf
    close $nf
    exec nam out.nam &

    puts "Number of ping packets dropped:"
    exec grep -c "^d" out.tr

    exit 0
}

# Create 6 nodes
for {set i 0} {$i < 6} {incr i} {
    set n($i) [$ns node]
}

# Connect nodes
for {set i 0} {$i < 5} {incr i} {
    $ns duplex-link $n($i) $n([expr $i+1]) 0.1Mb 10ms DropTail
}

# Force congestion
$ns queue-limit $n(2) $n(3) 2

# Ping agents (Blue)
set p0 [new Agent/Ping]
$p0 set class_ 1
$ns attach-agent $n(0) $p0
set p1 [new Agent/Ping]
$p1 set class_ 1
$ns attach-agent $n(5) $p1
$ns connect $p0 $p1

# TCP congestion traffic (Red)
set tcp [new Agent/TCP]
$tcp set class_ 2
$ns attach-agent $n(2) $tcp
set sink [new Agent/TCPSink]
$ns attach-agent $n(4) $sink
$ns connect $tcp $sink

set cbr [new Application/Traffic/CBR]
$cbr set packetSize_ 500
$cbr set rate_ 1Mb
$cbr attach-agent $tcp

# Schedule
$ns at 0.2 "$p0 send"
$ns at 0.4 "$p1 send"
$ns at 0.4 "$cbr start"
$ns at 0.8 "$p0 send"
$ns at 1.0 "$p1 send"
$ns at 1.2 "$cbr stop"
$ns at 1.4 "$p0 send"
$ns at 1.6 "$p1 send"
$ns at 1.8 "finish"

$ns run
