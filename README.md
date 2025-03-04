# Documentación del proyecto: Creación de una llamada al sistema en Linux

Este proyecto documenta el proceso de crear una nueva llamada al sistema en el kernel de Linux 4.17.4 en una máquina virtual con Ubuntu 16.04 LTS.

## Instalación de Ubuntu 16.04 LTS en VirtualBox

Descarga la imagen ISO de Ubuntu 16.04 LTS. 

## Instalación de dependencias

Ejecuta los siguientes comandos para instalar las herramientas necesarias:

```sh
sudo apt-get install gcc
sudo apt-get install libncurses5-dev
sudo apt-get install bison
sudo apt-get install flex
sudo apt-get install libssl-dev
sudo apt-get install libelf-dev
sudo apt-get install make
sudo apt-get update
sudo apt-get upgrade
```

## Verificación de la versión del kernel y acceso root

```sh
uname -r
sudo -s
```

## Descarga y descompresión del Kernel 4.17.4

```sh
cd /usr/src
wget https://www.kernel.org/pub/linux/kernel/v4.x/linux-4.17.4.tar.xz
tar -xvf linux-4.17.4.tar.xz
```

## Creación de la nueva llamada al sistema

1. Crea un nuevo archivo dentro del directorio `kernel`:

```sh
nano my_suma.c
```

2. Añade el siguiente código:

```c
#include <linux/kernel.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE2(my_suma, int, a, int, b) {
    printk(KERN_INFO "Syscall suma: sumando %d y %d\n", a, b);
    return a + b;
}
```

3. Modifica el `Makefile` de la carpeta `kernel` añadiendo la siguiente línea:

```sh
obj-y += my_suma.o
```

## Registro de la nueva llamada en el kernel

1. Edita la tabla de llamadas al sistema:

```sh
cd arch/x86/entry/syscalls/
nano syscall_64.tbl
```

2. Añade la siguiente línea al final del archivo:

```sh
548 64 my_suma __x64_sys_my_suma
```

3. Edita el archivo de encabezados de syscalls:

```sh
cd /usr/src/linux-4.17.4/include/linux/
nano syscalls.h
```

4. Escribe la siguiente línea antes del último `#endif`:

```c
asmlinkage long sys_my_suma(int a, int b);
```

## Compilación del kernel

1. Configura el kernel:
```sh
cd /usr/src/linux-4.17.4
make menuconfig
```

2. Compila el kernel:
```sh
make -j$(nproc)
```

3. Instala los módulos y el nuevo kernel:
```sh
make modules_install install
```

4. Verifica que el nuevo kernel se haya instalado:
```sh
cd /boot/
ls vmlinuz-4.17.4
```

5. Reinicia el sistema:
```sh
shutdown -r now
```

6. Comprueba la versión del kernel tras el reinicio:
```sh
uname -r
```

## Prueba de la nueva llamada al sistema

1. Crea un archivo de prueba en el escritorio:
```sh
nano test_syscall.c
```

2. Añade el siguiente código:
```c
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

#define SYS_my_suma 548

int main() {
    int resultado = syscall(SYS_my_suma, 5, 3);
    printf("El resultado de my_suma es: %d\n", resultado);
    return 0;
}
```

3. Compila y ejecuta el archivo:
```sh
gcc test_syscall.c -o test_syscall
./test_syscall
```

Si el resultado es correcto, la nueva llamada al sistema ha sido implementada con éxito.

---

Este README documenta todo el proceso de creación de una nueva syscall en Linux. Puedes subir los archivos de código por separado en el repositorio de GitHub.

