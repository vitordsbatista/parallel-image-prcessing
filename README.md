# parallel-image-processing
Processamento paralelo de imagens com MPI e OpenMP.

No exemplo utilizado é realizado a paralelização da transformação de uma imagem colorida em escala de cinza.

#Pré-requisitos
OpenCV 3.0 

MPI

OpenMP

GCC

#Notas
Tem um arquivo chamado "alocacao.c" que serve para alocar arrays dinâmicos sem estourar a memória. Este arquivo pertence ao meu professor e ele não me permitiu disponibilizar o arquivo. Avisarei onde foi necessária a utilização dele

#Compilação e Execução
##Sequencial
gcc gray.c -o gray `pkg-config --libs --cflags opencv` -ldl -lm

./gray
##Paralelo
###MPI
mpicc gray_mpi.c -o gray_mpi -O -lm `pkg-config --libs --cflags opencv` -ldl -lm

./gray_mpi
###OpenMP*
gcc gray_omp.c -o gray_omp `pkg-config --libs --cflags opencv` -ldl -lm -fopenmp

lamboot -v maquinas 

mpirun C gray_mpi
