#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "file_loader.h"

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

int loadFileInMemomory(const char *file_name) {
    unsigned int len_of_file;
    unsigned int len_of_struct;
    unsigned int num_of_instance;
    unsigned int prom;
    struct stat buf;

    struct data_struct *data;
    /*Abro el archivo*/
    int fd = open(file_name, O_RDWR, S_IRUSR | S_IWUSR);

    /*Chequeo que se haya abierto bien el archivo*/
    if (fd < 0) {
        perror("ERROR: ocurrió un problema al abrir el archivo");
        return EXIT_FAILURE;
    }

    /**
     * fstat es una función de la glib nos va a dar información sobre el archivo
     * para más info ver la struct stat, o recurrir al man
     */
    if (fstat(fd,&buf) < 0) {
        perror("ERROR: Ocurrió un problema al determinar el tamaño del archivo");
        return EXIT_FAILURE;
    }

    /*Guardo el tamaño del archivo en bytes*/
    len_of_file = (unsigned int)buf.st_size;
    /*Guardo el tamaño de la struct en bytes*/
    len_of_struct = sizeof(data[0]);
    /*Calculo el número de instancias*/
    num_of_instance = len_of_file / len_of_struct;

    /*Imprimo los tamaños*/
    printf("\tLen of file: %d\n\n\tLen of struct: %d\n\n\tNum of instances: %d\n\n", len_of_file, len_of_struct, num_of_instance);

    /*Hago el mapeo en RAM*/
    data = (struct data_struct*) mmap(NULL,len_of_file,PROT_READ,MAP_FILE|MAP_PRIVATE,fd,0);
    if (data == MAP_FAILED) {
        perror("ERROR: Ocurrió un error al realizar el mapeo en RAM");
        close(fd);
        return EXIT_FAILURE;
    }

    /*Calculo el promedio*/
    prom = (data[0].validSamples + data[1].validSamples + data[2].validSamples) / num_of_instance;

    /*Imprimo los resultados*/
    printf("\tValid samples Nº1: %d\n\n\tValid samples Nº2: %d\n\n\tValid samples Nº3: %d\n\n\tAverage: %d", data[0].validSamples, data[1].validSamples, data[2].validSamples, prom);

    /*Hago el unmap de la memoria en RAM*/
    munmap (data, len_of_file);
    close(fd);
    
    return EXIT_SUCCESS;
}
