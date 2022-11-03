# Comandos para MPI

1. mpiexec: nombre del comando base
2. -np [repeticiones]: Bandera para repetir un proceso
3. -f [arch_sincr]: Se indica arrchivo con la distribucion de ejecuciones

Ejemplo de ejecucion:

```
mpiexec -np 10 -f /etc/skel/hosts-mpich hostname args
```

## Archivo de sincronizacion

Indica cuantos procesos se desean dividir en un closter

### Foemato Open MPI

```
node1 slots=4
node2 slots=4
node3 slots=2
```

### Formato MPICH

```
node1:4
node2:4
node3:2
```

Existen formatos para el mpi creados de antemanos en los arenales
Lo podemos ver con `ls -la /etc/skel`

## Ejecuta mis programas
 
### Normal

```
M_Pich

mpiexec -np # -f doc bin/ejecutable param

OpenMPI

mpiexec --oversubscribe -np # --hostfile doc ejecutable param

```

### Sanitizer

```
mpiexec -np # Sanitizer bin/ejecutable param
```

### Ejemplo mpich

hosts-mpich

```
compute-0-0:1
#compute-0-1:1
compute-0-2:1
compute-0-3:1
```

```
mpiexec -np 5 -f hosts-mpich bin/hello
```

### Ejemplo OpenMPI

hosts-openmpi

```
compute-0-0 slots=1
#compute-0-1 slots=1
compute-0-2 slots=1
compute-0-3 slots=1
```

```
mpiexec --oversubscribe -np 10 --hostfile hosts-openmpi bin/hello
```
