#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include "file_loader.h"
#include "data_struct.h"

int loadFileInMemomory(const char *file_name)
{
    unsigned int len_of_file;
    unsigned int len_of_struct;
    unsigned int num_of_instance;
    unsigned int prom;
    /*Estructura para el buffer de stats*/
    struct stat buf;
    /*Estructura con los datos*/
    struct data_struct *data;
    /*Abro el archivo con permisos de lectura, */
    int fd = open(file_name, O_RDWR, S_IRUSR | S_IWUSR);

    /*Chequeo que se haya abierto bien el archivo*/
    if (fd < 0)
    {
        perror("ERROR: ocurrió un problema al abrir el archivo");
        return EXIT_FAILURE;
    }

    /**
     * fstat es una función de la glib nos va a dar información sobre el archivo
     * para más info ver la struct stat, o recurrir al man.
     * Guardo los stats en el buffer
     */
    if (fstat(fd, &buf) < 0)
    {
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
    printf("\tLen of file: %d bytes\n\n\tLen of struct: %d bytes\n\n\tNum of instances: %d\n\n", len_of_file, len_of_struct, num_of_instance);

    /*Hago el mapeo en RAM*/
    data = (struct data_struct *)mmap(NULL, len_of_file, PROT_READ, MAP_FILE | MAP_PRIVATE, fd, 0);
    if (data == MAP_FAILED)
    {
        perror("ERROR: Ocurrió un error al realizar el mapeo en RAM");
        close(fd);
        return EXIT_FAILURE;
    }

    /*Calculo el promedio*/
    prom = (data[0].validSamples + data[1].validSamples + data[2].validSamples) / num_of_instance;

    /*Imprimo los resultados*/
    printf("\tValid samples Nº1: %d\n\n\tValid samples Nº2: %d\n\n\tValid samples Nº3: %d\n\n\tAverage: %d", data[0].validSamples, data[1].validSamples, data[2].validSamples, prom);

    /*Hago el unmap de la memoria en RAM*/
    munmap(data, len_of_file);
    close(fd);

    return EXIT_SUCCESS;
}