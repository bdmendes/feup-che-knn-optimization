############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
## Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
############################################################
open_project hardware-accelerator
set_top hw_get_eucledean_distances
add_files src/io.c
add_files src/io.h
add_files src/key-READ1-k20.dat
add_files src/key-READ1-k3.dat
add_files src/knn.c
add_files src/knn.h
add_files src/hardware-accelerator/knn_hw_accel.c
add_files src/params.h
add_files src/preprocess.c
add_files src/preprocess.h
add_files src/test.dat
add_files src/timer.c
add_files src/timer.h
add_files src/train.dat
add_files src/types.h
add_files src/utils.c
add_files src/utils.h
add_files src/hardware-accelerator/knn_hw_accel.c
add_files -tb src/hardware-accelerator/hw_testbench.c
add_files -tb src/hardware-accelerator
open_solution "solution1" -flow_target vivado
set_part {xc7z020clg484-1}
create_clock -period 10 -name default
source "./hardware-accelerator/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
