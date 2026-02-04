set ns [new Simulator]

set topo [new Topography]
$topo load_flatgrid 1500 1500

set tf [open out.tr w]
$ns trace-all $tf

set nf [open out.nam w]
$ns namtrace-all $nf
$ns namtrace-all-wireless $nf 1500 1500

$ns node-config -adhocRouting DSDV \
    -llType LL \
    -macType Mac/802_11 \
    -ifqType Queue/DropTail \
    -ifqLen 20 \
    -phyType Phy/WirelessPhy \
    -channelType Channel/WirelessChannel \
    -propType Propagation/TwoRayGround \
    -antType Antenna/OmniAntenna \
    -topoInstance $topo \
    -agentTrace ON \
    -routerTrace ON

create-god 6

set n0 [$ns node]
$n0 set X_ 600
$n0 set Y_ 500
$n0 set Z_ 0.0
$ns initial_node_pos $n0 20

set n1 [$ns node]
$n1 set X_ 400
$n1 set Y_ 300
$n1 set Z_ 0.0
$ns initial_node_pos $n1 20

set n2 [$ns node]
$n2 set X_ 800
$n2 set Y_ 300
$n2 set Z_ 0.0
$ns initial_node_pos $n2 20

set n3 [$ns node]
$n3 set X_ 200
$n3 set Y_ 200
$n3 set Z_ 0.0
$ns initial_node_pos $n3 20

set n4 [$ns node]
$n4 set X_ 500
$n4 set Y_ 100
$n4 set Z_ 0.0
$ns initial_node_pos $n4 20

set n5 [$ns node]
$n5 set X_ 1000
$n5 set Y_ 200
$ns initial_node_pos $n5 20

set udp [new Agent/UDP]
$ns attach-agent $n0 $udp
set null1 [new Agent/Null]
$ns attach-agent $n4 $null1
$ns connect $udp $null1
$udp set packetSize_ 1500

set tcp [new Agent/TCP]
$ns attach-agent $n3 $tcp
set sink [new Agent/TCPSink]
$ns attach-agent $n5 $sink
$ns connect $tcp $sink

set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp
$cbr set packetSize_ 1000
$cbr set rate_ 1.0Mb
$cbr set random_ null

set ftp [new Application/FTP]
$ftp attach-agent $tcp

proc finish {} {
    global ns tf nf
    $ns flush-trace
    close $tf
    close $nf
    exec nam out.nam &
    exec echo "Number of packets dropped is : " &
    exec grep -c "^d" out.tr &
    exit 0
}

$ns at 0.1 "$cbr start"
$ns at 0.2 "$ftp start"
$ns at 18.0 "$ftp stop"
$ns at 20.0 "$cbr stop"
$ns at 20.0 "finish"
$ns at 7.0 "$n4 setdest 100 60 20"
$ns at 10.0 "$n4 setdest 700 300 20"
$ns at 15.0 "$n4 setdest 900 200 20"

$ns run
