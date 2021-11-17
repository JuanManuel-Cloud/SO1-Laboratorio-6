## INFORME LABORATORIO 6

*Aclaración: todo lo que se refiera a cuestiones de diseño y especificación del código está comentado en el mismo.*

**Punto 1**

El primer punto solicitaba hacer un mapeo de los datos que estaban en el binario de la carpeta raw en RAM y castearlos según su tipo. Esto se pudo realizar utilizando una struct con campos que son de los respectivos tipos de datos que se encuentran en el binario. Una vez que se tiene la struct lo que hay que hacer es definir una lista de la struct _data_struct_ de esta manera al hacer el map es posible guardar el void pointer (casteado al tipo de la struct) retornado por mmap en el puntero a la struct _data_struct_ (ahora una lista).

**Punto 2**

El punto 2 pedía averiguar el número de instancias que había de la struct dentro del binario, para eso se utilizó una útil función de la GNU lib que es _fstat_ la cuál devuelve cierta información de un archivo, como por ejemplo, tipo y modo del archivo, el id del usuario propietario, lo mismo con el grupo, y el que se uso que es _st_size_ que es el tamaño total del archivo en bytes. Con esta info más el tamaño de la struct que se puede conseguir gracias a la fucnión _size_of_ con una simple división es posible averiguar el número de instancias que hay en el binario.

**Punto 3**

Para el punto 3 se solicitaba calcular el promedio de la variable de _validSamples_ lo cual se realizó de la siguiente forma, se tenía una lista de instancias (struct) y como se sabía, gracias al punto anterior, que había 3 struct, por lo que se contaba con 3 instancias de _validSamples_ entonces se podía acceder a cada una de ellas gracias a su índice e ir sumandolas para luego dividirlas por la cantidad de instancias, con esta operación fue posible calcular la media de _validSample_
