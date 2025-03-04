#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

#define SYS_my_suma 548

int main() {
    int resultado = syscall(SYS_my_suma, 5, 3);
    printf("El resultado de my_suma es: %d\n", resultado);
    return 0;
}