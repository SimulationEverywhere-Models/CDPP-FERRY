[top]
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

