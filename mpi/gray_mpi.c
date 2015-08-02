//Local do OpenCV em sua máquina
#include "/usr/local/include/opencv/cv.h"
#include </usr/local/include/opencv/highgui.h>
#include </usr/local/include/opencv/cxcore.h>
#include <stdio.h>
#include <mpi.h>
//Arquivo que não posso disponibilizar TT_TT
#include "alocacao.c"

int main( int argc, char *argv[] ){

//Leitura da imagem
  IplImage *input_file = cvLoadImage("image.jpg", CV_LOAD_IMAGE_COLOR);
  int height = input_file->height;
  int width = input_file->width;
//Criacao da imagem de saida
  IplImage *output_file = cvCreateImage( cvSize( width, height), IPL_DEPTH_8U, 1 );
  array2d(x, height, width);
  array2d(y, height, width);
  int h, w, r, g, b, pixel, tmp, a;
  
//Variaveis MPI
  int CPU, ret, size;

//Inicializacao MPI
  MPI_Status status;
  ret = MPI_Init(&argc, &argv);
  ret = MPI_Comm_rank(MPI_COMM_WORLD, &CPU);
  ret = MPI_Comm_size(MPI_COMM_WORLD, &size);

/*
	Variavel da divisao
	A imagem sera dividida e metade dela sera executada na CPU0 e a outra metade na CPU1
*/
  if (CPU == 0) {
    tmp = 0;
  }
  if (CPU == 1) {
    tmp = width/2;
  }

//Processamento da imagem
  for( h = 0; h < height; ++h ){
    for( w = 0 + tmp; w <= ((width/2)+tmp); ++w ){
      b = CV_IMAGE_ELEM( input_file, uchar, h, w * 3 );
      g = CV_IMAGE_ELEM( input_file, uchar, h, w * 3 + 1 );
      r = CV_IMAGE_ELEM( input_file, uchar, h, w * 3 + 2 );
      pixel = 0.299 * r + 0.587 * g + 0.114 * b;
      y[h][w] = pixel;
    }
  }
  
//Liberando a imagem da memoria
  cvReleaseImage( &input_file );
//Troca de menssagem
  if (CPU != 0) {
//Envio da CPU1 para a CPU0
    cvReleaseImage( &output_file );
    MPI_Send(&(y[0][0]), height*width, MPI_INT, (0), 0, MPI_COMM_WORLD);
  }else{ //(CPU == 0)
//Recebimento da menssagem (imagem)
//Uma boa forma de visualizar a troca de mensasgens ocorre quando se comenta a recepcao da menssagem
//Quando isso ocorre a imagem final gerada e metade preta pois a outra metade nao foi recebida 
      MPI_Recv(&(x[0][0]), height*width, MPI_INT, (1), 0, MPI_COMM_WORLD, &status);
//Juncao das imagens
      for(h = 0; h < height; ++h) {
        for(w = 0; w < width; ++w){
          if(w <= width/2){
            CV_IMAGE_ELEM(output_file, uchar, h, w) = y[h][w];
          }else{
            CV_IMAGE_ELEM(output_file, uchar, h, w) = x[h][w];
          }
        }
      }
  }
  if(CPU==0){
    cvSaveImage("image-gray", output_file, NULL);
  }
//Fim
  MPI_Finalize();
}


//mpicc gray_mpi.c -o gray_mpi -O -lm `pkg-config --libs --cflags opencv` -ldl -lm
//mpirun C gray_mpi
