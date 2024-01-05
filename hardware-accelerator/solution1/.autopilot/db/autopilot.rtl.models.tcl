set SynModuleInfo {
  {SRCNAME hw_get_eucledean_distances MODELNAME hw_get_eucledean_distances RTLNAME hw_get_eucledean_distances IS_TOP 1
    SUBMODULES {
      {MODELNAME hw_get_eucledean_distances_dsub_64ns_64ns_64_7_full_dsp_1 RTLNAME hw_get_eucledean_distances_dsub_64ns_64ns_64_7_full_dsp_1 BINDTYPE op TYPE dsub IMPL fulldsp LATENCY 6 ALLOW_PRAGMA 1}
      {MODELNAME hw_get_eucledean_distances_dadd_64ns_64ns_64_7_full_dsp_1 RTLNAME hw_get_eucledean_distances_dadd_64ns_64ns_64_7_full_dsp_1 BINDTYPE op TYPE dadd IMPL fulldsp LATENCY 6 ALLOW_PRAGMA 1}
      {MODELNAME hw_get_eucledean_distances_dmul_64ns_64ns_64_7_max_dsp_1 RTLNAME hw_get_eucledean_distances_dmul_64ns_64ns_64_7_max_dsp_1 BINDTYPE op TYPE dmul IMPL maxdsp LATENCY 6 ALLOW_PRAGMA 1}
      {MODELNAME hw_get_eucledean_distances_flow_control_loop_pipe RTLNAME hw_get_eucledean_distances_flow_control_loop_pipe BINDTYPE interface TYPE internal_upc_flow_control INSTNAME hw_get_eucledean_distances_flow_control_loop_pipe_U}
    }
  }
}
