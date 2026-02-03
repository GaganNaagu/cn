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
    puts "Number of packets dropped:"
    exec grep -c "^d" out.tr
    exit 0
}

for {set i 0} {$i < 6} {incr i} {
    set n($i) [$ns node]
}

for {set i 0} {$i < 5} {incr i} {
    $ns duplex-link $n($i) $n([expr $i+1]) 0.1Mb 10ms DropTail
}

$ns queue-limit $n(2) $n(3) 2

set p0 [new Agent/Ping]
$p0 set class_ 1
$ns attach-agent $n(0) $p0

set p1 [new Agent/Ping]
$p1 set class_ 1
$ns attach-agent $n(5) $p1

$ns connect $p0 $p1

set tcp [new Agent/TCP]
$tcp set class_ 2
$ns attach-agent $n(2) $tcp

set sink [new Agent/TCPSink]
$ns attach-agent $n(4) $sink

$ns connect $tcp $sink

set ftp [new Application/FTP]
$ftp attach-agent $tcp

$ns at 0.2 "$p0 send"
$ns at 0.4 "$p1 send"
$ns at 0.6 "$ftp start"
$ns at 1.2 "$ftp stop"
$ns at 1.4 "$p0 send"
$ns at 1.6 "$p1 send"
$ns at 1.8 "finish"

$ns run