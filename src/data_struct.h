#include <stdbool.h>

/*Creo la estructura con los datos de la tabla (lo que posee el archivo bin)*/
struct data_struct {
    short unsigned int version;
    short unsigned int drxVersion;
    char reservado_uno[4];
    double initCW;
    float azimuth;
    float elevation;
    short unsigned int idVolumen;
    short unsigned int idBarrido;
    short unsigned int idConjunto;
    short unsigned int idGrupo;
    short unsigned int idPulso;
    bool iniBarrido;
    bool finBarrido;
    bool finGrupo;
    bool inhibido;
    short unsigned int validSamples;
    short unsigned int nroAdquisicion;
    char reservado_dos[2];
    unsigned int nroSecuencia;
    long unsigned int readTime_high;
    long unsigned int readTime_low;
    char reservado_tres[64];
};