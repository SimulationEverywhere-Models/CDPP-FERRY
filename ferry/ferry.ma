[top]
components : puertoSur Ferry puertoNorte monitor@Monitor
out : Tsys CPS CPN TPES TPEN
in : in
Link : in in_datos@monitor
Link : out_tsys@monitor Tsys
Link : out_CPS@monitor CPS
Link : out_CPN@monitor CPN
Link : out_TPES@monitor TPES
Link : out_TPEN@monitor TPEN

Link : out_psb@puertoSur in_br@Ferry
Link : out_psc1@puertoSur in_cl@Ferry

Link : out_hss@Ferry in_psb3@puertoSur
Link : out_cs@Ferry in_psb2@puertoSur
Link : out_as@Ferry in_psb1@puertoSur
Link : out_psc2@puertoSur in_SalidaSys_S@monitor

Link : out_pnb@puertoNorte in_br@Ferry
Link : out_pnc1@puertoNorte in_cl@Ferry

Link : out_hsn@Ferry in_pnb3@puertoNorte
Link : out_cn@Ferry in_pnb2@puertoNorte
Link : out_an@Ferry in_pnb1@puertoNorte
Link : out_pnc2@puertoNorte in_SalidaSys_N@monitor

[Ferry]
components : capitan@Barco marinero@Cola_F
out : out_as out_an out_cs out_cn
out : out_hss out_hsn
in : in_br in_cl

Link : in_cl in_vehic@marinero
Link : in_br in_permiso@capitan

Link : out_listo@marinero in_listo@capitan
Link : out_Full@marinero in_capComp@capitan
Link : out_enHoraSalida@marinero in_horario@capitan
Link : out_descargar@capitan in_inicio@marinero

Link : out_arribo_N@capitan out_an
Link : out_arribo_S@capitan out_as
Link : out_cargar_S@capitan out_cs
Link : out_cargar_N@capitan out_cn
Link : out_horaSalida_S@capitan out_hss
Link : out_horaSalida_N@capitan out_hsn

[puertoSur]
components : agentes@Banderillero colas@Cola ciudads@Generador
out : out_psb out_psc1 out_psc2
in : in_psb1 in_psb2 in_psb3

Link : in_psb1 in_ferry@agentes
Link : in_psb2 in_solic@agentes
Link : in_psb3 in_cerrarPaso@agentes
Link : out_descargar@agentes out_psb
Link : out_ferry@colas out_psc1
Link : out_perf@colas out_psc2
Link : out_solic@agentes in_solic@colas
Link : out_parar@agentes in_parar@colas
Link : out_vehic@ciudads in_vehic@colas

[ciudads]
distribution : exponential
mean : 5

[puertoNorte]
components : agente@Banderillero cola@Cola ciudad@Generador
out : out_pnb out_pnc1 out_pnc2
in : in_pnb1 in_pnb2 in_pnb3

Link : in_pnb1 in_ferry@agente
Link : in_pnb2 in_solic@agente
Link : in_pnb3 in_cerrarPaso@agente
Link : out_descargar@agente out_pnb
Link : out_ferry@cola out_pnc1
Link : out_perf@cola out_pnc2
Link : out_solic@agente in_solic@cola
Link : out_parar@agente in_parar@cola
Link : out_vehic@ciudad in_vehic@cola

[ciudad]
distribution : exponential
mean : 5

