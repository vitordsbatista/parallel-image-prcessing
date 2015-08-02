//Local do OpenCV em sua máquina
#include "/usr/local/include/opencv/cv.h"
#include </usr/local/include/opencv/highgui.h>
#include </usr/local/include/opencv/cxcore.h>
#include <stdio.h>
//Arquivo que não posso disponibilizar TT_TT
#include "alocacao.c"
//Numero de threads 
#define thread 2

int main( ){

  //Variaveis Sequencial
  int CPU;

  //Feedback para inicializacao da CPU*/
  printf("Executando CPU=%d...\n",CPU);

  //Feedback para inicializacao da CPU e Thread
  //----------OpenMP---------------------------------------------------------------------------------
  printf("\n-----Existem %d processadores livres da CPU %d!-----\n\n", omp_get_num_procs(), CPU);

//Leitura da imagem
  IplImage *input_file = cvLoadImage("satelite.jpg", CV_LOAD_IMAGE_COLOR);
  int height = input_file->height;
  int width = input_file->width;
//Criacao da imagem de saida
  IplImage *output_file = cvCreateImage( cvSize( width, height), IPL_DEPTH_8U, 1 );
//Outras Variaveis
  int h, w, pixel, r, g, b;

//Definindo a quantidade de threads para a execucao do programa
  omp_set_num_threads(thread);
  
  #pragma omp parallel
  { printf("--------- Thread %d executando na CPU %d! ----------\n", omp_get_thread_num(), CPU); }
  
//Processamento da imagem
  #pragma omp parallel for \
  shared(input_file, output_file, height, width) \ //Variaveis compartilhadas
  private(h, w, pixel, r, g, b) //Variaveis privadas
  for( h = 0; h < height; ++h ){
    for( w = 0; w <= width; ++w ){
      b = CV_IMAGE_ELEM( input_file, uchar, h, w * 3 );
      g = CV_IMAGE_ELEM( input_file, uchar, h, w * 3 + 1 );
      r = CV_IMAGE_ELEM( input_file, uchar, h, w * 3 + 2 );
      pixel = 0.299 * r + 0.587 * g + 0.114 * b;
      CV_IMAGE_ELEM(output_file, uchar, h, w) = pixel;
    }
  }
  
//Salvando a imagem e escrevendo ela em 'image-gray.jpg'
  cvReleaseImage( &input_file );
  if(CPU==0){
    cvSaveImage( "test-gray.jpg", output_file, NULL );
  }
  return 0;
}