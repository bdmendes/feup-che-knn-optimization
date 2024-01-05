#!/bin/sh
lli=${LLVMINTERP-lli}
exec $lli \
    /home/sirze/repos/CHE/hardware-accelerator/solution1/csim/build/apcc_db_sirze/406791704472848802087/knn_hw_accel.ld.bc ${1+"$@"}
