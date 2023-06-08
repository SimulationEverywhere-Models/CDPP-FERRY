[top]
components : perf@Monitor

out : oTsys oCPS oCPN oTPES oTPEN
in : iSysS iSysN iCS iCN idatos

Link : iSysS in_SalidaSys_S@perf
Link : iSysN in_SalidaSys_N@perf
Link : iCS in_CPS@perf
Link : iCN in_CPN@perf
Link : idatos in_datos@perf
Link : out_tsys@perf oTsys
Link : out_CPS@perf oCPS
Link : out_CPN@perf oCPN
Link : out_TPES@perf oTPES
Link : out_TPEN@perf oTPEN
