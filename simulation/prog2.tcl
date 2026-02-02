set ns [new Simulator]

$ns color 1 Blue
$ns color 2 Red

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
    exit 0
}

for {set i 0} {$i < 6} {incr i} {
    set n($i) [$ns node]
}

for {set i 0} {$i < 5} {incr i} {
    $ns duplex-link $n($i) $n([expr $i+1]) 0.1Mb 10ms DropTail
}

$ns queue-limit $n(2) $n(3) 2

set udp_ping [new Agent/UDP]
$udp_ping set class_ 1
$ns attach-agent $n(0) $udp_ping

set null_ping [new Agent/Null]
$ns attach-agent $n(5) $null_ping

$ns connect $udp_ping $null_ping

set cbr_ping [new Application/Traffic/CBR]
$cbr_ping set packetSize_ 64
$cbr_ping set rate_ 0.05Mb
$cbr_ping attach-agent $udp_ping

set udp [new Agent/UDP]
$udp set class_ 2
$ns attach-agent $n(2) $udp

set null [new Agent/Null]
$ns attach-agent $n(4) $null

$ns connect $udp $null

set cbr [new Application/Traffic/CBR]
$cbr set packetSize_ 500
$cbr set rate_ 1Mb
$cbr attach-agent $udp

$ns at 0.2 "$cbr_ping start"
$ns at 0.6 "$cbr start"
$ns at 1.2 "$cbr stop"
$ns at 1.6 "$cbr_ping stop"
$ns at 1.8 "finish"

$ns run
