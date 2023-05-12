#ifndef _FLASH_H_
#define _FLASH_H_
#include "main.h"
#include "stm32f1xx_hal_flash_ex.h" 
#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t


#define STM32_FLASH_SIZE 	64 	 	//��ѡSTM32��FLASH������С(��λΪK)
    #if     STM32_FLASH_SIZE < 256      //����������С
    #define STM_SECTOR_SIZE     1024    //1K�ֽ�
    #else 
    #define STM_SECTOR_SIZE	    2048    //2K�ֽ�
#endif

#define STM32_FLASH_BASE            0x08000000 		//STM32 FLASH����ʼ��ַ
#define FLASH_USER_START_ADDR   ( STM32_FLASH_BASE + STM_SECTOR_SIZE * 62 ) //дFlash�ĵ�ַ������ӵ�62ҳ��ʼ
#define FLASH_USER_END_ADDR     ( STM32_FLASH_BASE + STM_SECTOR_SIZE * 64 ) //дFlash�ĵ�ַ�������Ե�64ҳ����


void Flash_Erase(void); 
void Flash_Write(u32 *pBuffer,u32 NumToWrite);
void Flash_Read(u32 *pBuffer,u32 NumToRead);


#endif

