//Local do OpenCV em sua máquina
#include "/usr/local/include/opencv/cv.h"
#include </usr/local/include/opencv/highgui.h>
#include </usr/local/include/opencv/cxcore.h>
#include <stdio.h>
//Arquivo que não posso disponibilizar TT_TT
#include "alocacao.c"

int main( ){
//Leitura da imagem
  IplImage *input_file = cvLoadImage("image.jpg", CV_LOAD_IMAGE_COLOR);
  int height = input_file->height;
  int width = input_file->width;
//Criacao da imagem de saida
  IplImage *output_file = cvCreateImage( cvSize( width, height), IPL_DEPTH_8U, 1 );
//Outras Variaveis
  int h, w, pixel, r, g, b;
//Aqui fica a alocacao utilizada pelo arquivo "alocacao.c"
//A socucao e criar um vetor 'y' com as dimensoes de 'heigh' e 'width' 
  array2d(y, height, width);
  
//Processamento da imagem
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
  cvSaveImage( "image-gray.jpg", output_file, NULL );

  return 0;
}
