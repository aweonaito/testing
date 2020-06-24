#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/shm.h> 
#include <sys/stat.h> 
#include <sys/mman.h> 
#include <sys/types.h> 
#include <errno.h> 
#include <fcntl.h>

int main(int argc, char** argv) {

    pid_t pidc;
    int status;
    int fd[2];
    int fd2[2];
    // f[0] para leer - f[1] para escribir
    if (pipe(fd) == -1) {
        printf("Ocurrio un error");
        return 1;
    }
    if (pipe(fd2) == -1) {
        printf("Ocurrio un error");
        return 1;
    }

    pidc = fork();

    if (pidc > 0) { //Identidicador del proceso padre
        printf("soy el proceso %d \n", getpid(), getppid());

        int inint; //crea variable inint que sera nuesto N
        printf("introduzca un numero: \t");
        scanf("%d", &inint); //recibe el valor de la variable inint
        if (inint <= 2) { //si la variable no cumple el requisito se entrega informacion de uso al usuario
            printf("El programa requiere un numero mayor o igual a 2");
            return 0; //termina el programa
        }
        else {//si se puede utilizar inint en el algoritmo de criba
            printf("el numero es %d.\n", inint);
        }

        int i;
        int arr[inint - 2];
        for (i = 2; i < inint; i++) { //parte desde 2 hasta n-1
            arr[i - 2] = i; //-2 para partir de 0
            printf("[ %d ]", arr[i - 2]);
        }
        write(fd[1], &arr, sizeof (arr));
        close(fd[1]);
        int size = sizeof (arr) / sizeof (int);
        write(fd2[1], &size, sizeof (int));
        close(fd2[1]);

        waitpid(pidc, &status, 0);

        int lar;
        read(fd2[0], &lar, sizeof (int));
        close(fd2[0]);
        int pr[lar];
        read(fd[0], &pr, (sizeof (int)*lar));
        close(fd[0]);
        printf("\n \n");
        printf("La lista de numeros primos es: \n");
        for (i = 0; i < lar; i++) {
            printf("[ %d ]", pr[i]);
        }

        return 0;

    } else if (pidc == 0) {//Identificador del proceso hijo

        printf("soy el hijo de %d, soy %d \n", getppid(), getpid());
        int y, i;
        read(fd2[0], &y, sizeof (int));
        close(fd2[0]);
        int prim[y];
        read(fd[0], &prim, (sizeof (int)*y));
        close(fd[0]);

        for (i = 2; i * i <= y; ++i) {
            if (prim[i]) {
                int h;
                for (h = 2; i * h <= y; ++h)
                    prim[i * h] = 0;
            }
        }
        int cont = 0;
        for (i = 2; i < y; i++) {
            if (prim[i] = prim[i]) {
                cont++;
            }
        }
        int fin[cont];
        int con = 0;
        for (i = 2; i < y; i++) {
            if (prim[i] != 0) {
                fin[con] = i;
                con++;
            }
        }

        printf("\n ");

        write(fd[1], &fin, sizeof (fin));
        close(fd[1]);
        write(fd2[1], &cont, sizeof (int));
        close(fd2[1]);
        return 0;
    }
    else {
        printf("Ocurrio un error");
        return 1;
    }

    return (EXIT_SUCCESS);
}

