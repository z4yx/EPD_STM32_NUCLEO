#include "GDEW075T8.h"
#include "Ap_29demo.h"
#include "stm32l0xx_hal.h"
#include "stm32l0xx_ll_spi.h"

#define nCS_L    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET)
#define nCS_H    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET)

#define nDC_L    HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_RESET)
#define nDC_H    HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_SET)

#define nRST_L   HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_RESET)
#define nRST_H   HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_SET)

unsigned char k=0;

static void lcd_chkstatus(void)
{
    unsigned char busy;
    do
    {
        SPI4W_WRITECOM(0x71);
        busy = HAL_GPIO_ReadPin(BUSY_GPIO_Port, BUSY_Pin);
        busy =!(busy & 0x01);
    }
    while(busy);
    HAL_Delay(200);
}

static void EPD_W21_Init(void)
{
    // BS tied to GND
    // nBS_L;              //4 wire spi mode selected

    nRST_L;             //module reset
    HAL_Delay(1000);
    nRST_H;
    HAL_Delay(1000);

}

static inline void SPI_Write(unsigned char value)
{
    while(!LL_SPI_IsActiveFlag_TXE (SPI1));
    LL_SPI_TransmitData8(SPI1, value);
    while(!LL_SPI_IsActiveFlag_RXNE (SPI1));
    LL_SPI_ReceiveData8(SPI1);
}

void SPI4W_WRITECOM(unsigned char command)
{
    nCS_L;                   
    nDC_L;       // command write
    SPI_Write(command);
    nCS_H;
}

void SPI4W_WRITEDATA(unsigned char INIT_DATA)
{
    nCS_L;                   
    nDC_H;       // data write
    SPI_Write(INIT_DATA);
    nCS_H;
}

void color_bar_display (void)
{
    unsigned long int i;
    unsigned char j,temp1,temp2;

    if(k==0)
    {
        SPI4W_WRITECOM(0x10);          //开始传输图像
        for(i=0; i<30720; i++)
        {
            temp1 = 0xff; // all black
            for(j=0; j<8; j++)
            {
                if(temp1&0x80)
                    temp2 = 0x00;
                else
                    temp2 = 0x03;

                temp2 <<= 4;
                temp1 <<= 1;
                j++;

                if(temp1&0x80)
                    temp2 |= 0x00;
                else
                    temp2 |= 0x03;

                temp1 <<= 1;

                SPI4W_WRITEDATA(temp2);

            }

        }

    }
    if(k==1)
    {
        SPI4W_WRITECOM(0x10);          //开始传输图像
        for(i=0; i<30720; i++)
        {
            temp1 = (i&1)?0xff:0;
            for(j=0; j<8; j++)
            {
                if(temp1&0x80)
                    temp2 = 0x00;
                else
                    temp2 = 0x03;

                temp2 <<= 4;
                temp1 <<= 1;
                j++;

                if(temp1&0x80)
                    temp2 |= 0x00;
                else
                    temp2 |= 0x03;

                temp1 <<= 1;

                SPI4W_WRITEDATA(temp2);

            }

        }

    }

}

void pic_display (void)
{
    unsigned long int i;
    unsigned char j,temp1,temp2;

    if(k==0)
    {
        SPI4W_WRITECOM(0x10);          //开始传输图像
        for(i=0; i<30720; i++)
        {
            temp1 = G_Ultrachip1[i];
            for(j=0; j<8; j++)
            {
                if(temp1&0x80)
                    temp2 = 0x00;
                else
                    temp2 = 0x03;

                temp2 <<= 4;
                temp1 <<= 1;
                j++;

                if(temp1&0x80)
                    temp2 |= 0x00;
                else
                    temp2 |= 0x03;

                temp1 <<= 1;

                SPI4W_WRITEDATA(temp2);

            }

        }

    }
    if(k==1)
    {
        SPI4W_WRITECOM(0x10);          //开始传输图像
        for(i=0; i<30720; i++)
        {
            temp1 = G_Ultrachip2[i];
            for(j=0; j<8; j++)
            {
                if(temp1&0x80)
                    temp2 = 0x00;
                else
                    temp2 = 0x03;

                temp2 <<= 4;
                temp1 <<= 1;
                j++;

                if(temp1&0x80)
                    temp2 |= 0x00;
                else
                    temp2 |= 0x03;

                temp1 <<= 1;

                SPI4W_WRITEDATA(temp2);

            }

        }

    }

}

void GDE_Start(void)
{

    EPD_W21_Init();
    k=0;

    while(1)
    {
        EPD_W21_Init();

        if(k==0)
        {
            HAL_Delay(100);
        }
        else
        {
            /**********************************release flash sleep**********************************/
            // SPI4W_WRITECOM(0X65);           //FLASH CONTROL
            // SPI4W_WRITEDATA(0x01);

            // nCS_L;                  //MFCSB 拉低
            // MCU_write_flash(0xAB);
            // nCS_H;                  //MFCSB 拉高

            // SPI4W_WRITECOM(0X65);           //FLASH CONTROL
            // SPI4W_WRITEDATA(0x00);
            /**********************************release flash sleep**********************************/
        }
        SPI4W_WRITECOM(0x01);
        SPI4W_WRITEDATA (0x37);     //POWER SETTING
        SPI4W_WRITEDATA (0x00);

        SPI4W_WRITECOM(0X00);           //PANNEL SETTING
        SPI4W_WRITEDATA(0xCF);
        SPI4W_WRITEDATA(0x08);

        SPI4W_WRITECOM(0x06);         //boost设定
        SPI4W_WRITEDATA (0xc7);
        SPI4W_WRITEDATA (0xcc);
        SPI4W_WRITEDATA (0x28);


        SPI4W_WRITECOM(0x30);           //PLL setting
        SPI4W_WRITEDATA (0x3c);

        SPI4W_WRITECOM(0X41);           //TEMPERATURE SETTING
        SPI4W_WRITEDATA(0x00);

        SPI4W_WRITECOM(0X50);           //VCOM AND DATA INTERVAL SETTING
        SPI4W_WRITEDATA(0x77);

        SPI4W_WRITECOM(0X60);           //TCON SETTING
        SPI4W_WRITEDATA(0x22);

        SPI4W_WRITECOM(0x61);           //tres          单色640*384
        SPI4W_WRITEDATA (0x02);     //source 640
        SPI4W_WRITEDATA (0x80);
        SPI4W_WRITEDATA (0x01);     //gate 384
        SPI4W_WRITEDATA (0x80);

        SPI4W_WRITECOM(0X82);           //VDCS SETTING
        SPI4W_WRITEDATA(0x1E);      //decide by LUT file

        SPI4W_WRITECOM(0xe5);           //FLASH MODE
        SPI4W_WRITEDATA(0x03);

        color_bar_display();

        SPI4W_WRITECOM(0x04);           //POWER ON
        lcd_chkstatus();

        SPI4W_WRITECOM(0x12);           //display refresh
        HAL_Delay(100);
        lcd_chkstatus();

        /**********************************flash sleep**********************************/
        // SPI4W_WRITECOM(0X65);           //FLASH CONTROL
        // SPI4W_WRITEDATA(0x01);

        // nCS_L;                  //MFCSB 拉低
        // MCU_write_flash(0xB9);
        // nCS_H;                  //MFCSB 拉高

        // SPI4W_WRITECOM(0X65);           //FLASH CONTROL
        // SPI4W_WRITEDATA(0x00);
        /**********************************flash sleep**********************************/

        SPI4W_WRITECOM(0x02);
        lcd_chkstatus();

        SPI4W_WRITECOM(0x07);
        SPI4W_WRITEDATA(0xa5);

        if(k==1)
        {
            while(1);
        }
        else
        {
            k++;
        }
    }
}