#include <stdio.h>
#include <sys/mman.h>
#include "file_loader.h"

int main(int argc, char **argv) {
    return loadFileInMemomory("../rawdata/datos");
}
