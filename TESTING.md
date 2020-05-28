# Testing

## Overview

The core purpose of DAWN is the processing of information relating
to the set of access points (AP) and clients (STA - meaning stations in 802.11
vernacular) that form the wi-fi network under DAWN's management.

The required data storage and processing capabilites are generally held in the 'storage'
part of DAWN's source code tree.  The remaining parts are mainly for
interfacing with resources of the AP environment provide updated information and allow
DAWN to indicate to stations what they should do next following processing of the latest data.
Specifically, this means components such as iwinfo, ubus and uci that are commonly found on an
AP running OpenWRT variant of Linux.

## Testing Approach
The principle focus of DAWN's test harness is on the storage and processing components.  This is achieved by
having a build target named test_storage which builds the core data storage and processing parts
without the environment interaction dependencies.  This "test harness" can then be executed on the
build host (e.g. a Linux desktop development environment) or on the target AP.

To configure the imaginary AP (SUT, or "system under test" in testing parlance)
a script that mimics many of the messages from ubus and other sources is created to represent
the simulated network by describing APs, connected STAs and DAWN's own configuration parameters.
The data evaluation algorithms are then executed, and resultant outputs to stations are simulated as
text output.

For example consider a simple network of two AP with 2 stations.  The following (simplifed) script is
used to configure what one AP will be aware of:

    SELF 01:01:01:01:01:01
    AP 02:02:02:02:02:02
    CONNECT 99:99:99:99:99:99 01:01:01:01:01:01 -78dB
    HEARING 99:99:99:99:99:99 02:02:02:02:02:02 -65dB
    CONNECT 88:88:88:88:88:88 01:01:01:01:01:01 -65dB
    HEARING 88:88:88:88:88:88 02:02:02:02:02:02 -65dB

This means our test AP has the BSSID 01:..., and there is another AP in the network with BSSID 02:.... 
Two stations with MAC 99:... and 88:... are in the network, both connected to AP01:... but also
able to see AP02:....  The dB values indicate RSSI levels, and will be evalutated.  We'll also configure
AP01:... to have an RSSI transition threshold of 10dB.  When "kicking evaluation" is performed
STA99:... can improve its RSSI by over 10dB by switching to AP02:..., so will be instructed to do
so, resulting in the output:

    KICK 99:99:99:99:99:99 01:01:01:01:01:01 02:02:02:02:02:02
	
## Types of Testing
Three main areas of testing are performed by the supplied test scripts:
* Data management: Ensuring data is stored correctly and soes not cause buffer overruns, etc
* Algorithm functionality: Review the outcomes of evaluation for somple and complex network data
* Scalability: Evaluate the ability of DAWN to sacle linearly to hundreds and thousands of AP and STA

A number of scenarios re defined for each type of testing, along with scripts to execute them.

### Data Management Scenarios

### Algorithm Functionality Scenarios

### Scalability Scenarios