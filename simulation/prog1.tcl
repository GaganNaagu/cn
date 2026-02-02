set ns [new Simulator]

set tf [open out.tr w]
$ns trace-all $tf
set nf [open out.nam w]
$ns namtrace-all $nf

proc finish {} {
    global ns tf nf
    $ns flush-trace
    close $tf
    close $nf
    puts "Number of packets dropped:"
    if {[catch {exec grep -c "^d" out.tr} drops]} {
        puts "0"
    } else {
        puts $drops
    }
    exec nam out.nam &
    exit 0
}

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]

$n0 label "Source"
$n2 label "Sink"

$ns duplex-link $n0 $n1 0.5Mb 10ms DropTail
$ns duplex-link $n1 $n2 1Mb 10ms DropTail

$ns duplex-link-op $n0 $n1 orient right
$ns duplex-link-op $n1 $n2 orient right

$ns queue-limit $n0 $n1 10
$ns queue-limit $n1 $n2 10

set udp [new Agent/UDP]
$ns attach-agent $n0 $udp
set null [new Agent/Null]
$ns attach-agent $n2 $null
$ns connect $udp $null

set cbr [new Application/Traffic/CBR]
$cbr set packetSize_ 100
$cbr set rate_ 1Mb
$cbr attach-agent $udp

$ns at 0.0 "$cbr start"
$ns at 5.0 "finish"

$ns run
