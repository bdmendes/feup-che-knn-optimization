#!/bin/sh
lli=${LLVMINTERP-lli}
exec $lli \
    /home/sirze/repos/CHE/hardware-accelerator/solution1/csim/build/apcc_db_sirze/404901704472838837242/hw_testbench.ld.bc ${1+"$@"}
