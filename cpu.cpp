#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_write.h"

#include <time.h>

int main(void)
{	

	char const * const filename = "image02.jpg";
	char const * const filename1 = "cpu.png";

	int width =0, height=0, nchannels=0;
	int const desired_channels =1;//convert image to gray

	//load image
	unsigned char * image_data = stbi_load(filename,&width,&height,&nchannels,desired_channels);
	
	//check for errors
	if(!image_data || !width || !height || !nchannels)
	{
		printf("Error loading image %s \n", filename);
		return -1;
	}

	float temps;
    clock_t t1, t2;     
   
    //use the image data
    //filtre
    float b[3][3]={-1,-1,-1,-1,8,-1,-1,-1,-1};
	float a[height][width];
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			a[i][j]=(float)image_data[i*width+j];
			
		}	
	}
	//calcul
    float c[height][width];

    t1 = clock();	
	for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
			if((i*j)>0){
				c[i][j]= a[i-1][j-1]*b[0][0]+a[i-1][j]*b[0][1]+a[i-1][j+1]*b[0][2]
						+a[i][j-1]*b[1][0]+a[i][j]*b[1][1]+a[i][j]*b[1][2]
						+a[i+1][j-1]*b[2][0]+a[i+1][j]*b[2][1]+a[i+1][j+1]*b[2][2];
			}
			else{
				c[i][j]=0;
			}
		}	
	}
 
    t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps = %f\n", temps);
 
	//save image
	int stride = width * desired_channels;
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			image_data[i*width+j]=(unsigned char)c[i][j];
		}	
	}
	if(!stbi_write_png(filename1,width,height,desired_channels,image_data,stride))
	{
		printf("Error saving image %s \n", filename1);
		return (-1);
	}
    //release the image memory buffer
	free(image_data);
	return 0;
}



