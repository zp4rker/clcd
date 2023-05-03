#include "DEV_Config.h"
#include "LCD_1in3.h"
#include "GUI_Paint.h"
#include "GUI_BMP.h"
#include "test.h"
#include <stdio.h>		//printf()
#include <stdlib.h>		//exit()
#include <signal.h>     //signal()

void LCD_1in3_test(void)
{
    // Exception handling:ctrl + c
    signal(SIGINT, Handler_1in3_LCD);
    
    /* Module Init */
	if(DEV_ModuleInit() != 0){
        DEV_ModuleExit();
        exit(0);
    }
	
    /* LCD Init */
	printf("1.3inch LCD demo...\r\n");
	LCD_1in3_Init(HORIZONTAL);
	LCD_1in3_Clear(WHITE);
    
    UWORD *BlackImage;
    UDOUBLE Imagesize = LCD_HEIGHT*LCD_WIDTH*2;
    if((BlackImage = (UWORD *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        exit(0);
    }
    // /*1.Create a new image cache named IMAGE_RGB and fill it with white*/
    Paint_NewImage(BlackImage, LCD_WIDTH, LCD_HEIGHT, 0, GRAY, 16);
    Paint_Clear(GRAY);

    // /* GUI */
    printf("drawing...\r\n");
    Paint_DrawLine(0, 210, 240, 210, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawString_EN(10, 10, "Hostname:", &Font16, GRAY, WHITE);
    Paint_DrawString_EN(10, 20, "IP:", &Font16, GRAY, WHITE);
        
    // /*3.Refresh the picture in RAM to LCD*/
    LCD_1in3_Display(BlackImage);
    DEV_Delay_ms(2000);
    
    // /* show bmp */
	// printf("show bmp\r\n");
	// GUI_ReadBmp("./pic/pic.bmp");
    
    // LCD_1in3_Display(BlackImage);
    // DEV_Delay_ms(2000);
    
    /* Module Exit */
    free(BlackImage);
    BlackImage = NULL;
	DEV_ModuleExit();
}

