[top]
components : capitan@Barco
out : oArribo_S oArribo_N oCargar oDescargar oHoraSalida
in : iHorario iPermiso iListo iCapComp

Link : iHorario in_horario@capitan
Link : iPermiso in_permiso@capitan
Link : iListo in_listo@capitan
Link : iCapComp in_capComp@capitan
Link : out_arribo_N@capitan oArribo_N
Link : out_arribo_S@capitan oArribo_S
Link : out_cargar@capitan oCargar
Link : out_descargar@capitan oDescargar
Link : out_horaSalida@capitan oHoraSalida

