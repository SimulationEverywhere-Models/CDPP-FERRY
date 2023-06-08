[top]
components : agente@Banderillero cola@Cola ciudad@Generador
out : out_b out_c1 out_c2
in : in_b1 in_b2 in_b3

Link : in_b1 in_ferry@agente
Link : in_b2 in_solic@agente
Link : in_b3 in_cerrarPaso@agente
Link : out_descargar@agente out_b
Link : out_ferry@cola out_c1
Link : out_perf@cola out_c2
Link : out_solic@agente in_solic@cola
Link : out_parar@agente in_parar@cola
Link : out_vehic@ciudad in_vehic@cola

[ciudad]
distribution : exponential
mean : 5
