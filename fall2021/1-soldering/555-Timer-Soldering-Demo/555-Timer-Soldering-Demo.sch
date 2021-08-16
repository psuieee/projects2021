EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "555 Timer - Soldering Demo"
Date "2021-08-15"
Rev "A"
Comp "PSU IEEE 2021"
Comment1 "Designed by Ethan Tabler"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Timer:LM555xM U1
U 1 1 6119CD20
P 3850 2800
F 0 "U1" H 3600 3150 50  0000 C CNN
F 1 "LM555xM" H 3850 2800 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 4700 2400 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm555.pdf" H 4700 2400 50  0001 C CNN
	1    3850 2800
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 6119E1AF
P 4400 1700
F 0 "J1" H 4480 1692 50  0000 L CNN
F 1 "BatteryTerminal" H 4480 1601 50  0000 L CNN
F 2 "" H 4400 1700 50  0001 C CNN
F 3 "~" H 4400 1700 50  0001 C CNN
	1    4400 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 1800 4150 1800
Wire Wire Line
	4150 1800 4150 1850
$Comp
L power:GND #PWR?
U 1 1 6119ECAD
P 3850 3300
F 0 "#PWR?" H 3850 3050 50  0001 C CNN
F 1 "GND" H 3855 3127 50  0000 C CNN
F 2 "" H 3850 3300 50  0001 C CNN
F 3 "" H 3850 3300 50  0001 C CNN
	1    3850 3300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6119F121
P 4150 1850
F 0 "#PWR?" H 4150 1600 50  0001 C CNN
F 1 "GND" H 4155 1677 50  0000 C CNN
F 2 "" H 4150 1850 50  0001 C CNN
F 3 "" H 4150 1850 50  0001 C CNN
	1    4150 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 3300 3850 3200
Wire Wire Line
	4200 1700 3850 1700
Wire Wire Line
	3850 1700 3850 2400
$EndSCHEMATC
