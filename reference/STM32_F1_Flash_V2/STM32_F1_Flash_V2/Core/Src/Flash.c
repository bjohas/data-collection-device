#include "Flash.h"
#include <stdio.h>

static FLASH_EraseInitTypeDef EraseInitStruct;
u32 PAGEError = 0;
 /**********************************************************************************
  * ��������: ҳ����
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������ 
  */
void Flash_Erase(void)
{  	
    EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
    EraseInitStruct.PageAddress = FLASH_USER_START_ADDR;
    EraseInitStruct.NbPages     = (FLASH_USER_END_ADDR - FLASH_USER_START_ADDR) / STM_SECTOR_SIZE;
    
     if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK)  
	 {
		 HAL_FLASH_Lock();  
		 printf(" Error...1\r\n");
         Error_Handler( );
	 }
}
 /**********************************************************************************
  * ��������: ����д��
  * �������: д�����ݻ�������ָ�롢д��������
  * �� �� ֵ: ��
  * ˵    ������ 
  */    
void Flash_Write(u32 *pBuffer,u32  NumToWrite)
{

    u16  i=0;
    u32 Address = FLASH_USER_START_ADDR;
    HAL_FLASH_Unlock();	    //����
    Flash_Erase( );         //�Ȳ���
                            //��д��
       printf(" ������ɣ�׼��д��......\r\n");
     while ( (Address < FLASH_USER_END_ADDR) && (i<NumToWrite)  )    
    {
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, pBuffer[i]) == HAL_OK)
        {
            Address = Address + 4;  //��ַ����4���ֽ�
            i++;
        }
        else
		{  
			printf(" Error...2\r\n"); 
            Error_Handler( );            
		}
    }
  
    HAL_FLASH_Lock();   //����


}

 /**********************************************************************************
  * ��������: ���ݶ�ȡ
  * �������: ��ȡ���ݻ�������ָ�롢����������
  * �� �� ֵ: ��
  * ˵    ������
  */
void Flash_Read(u32  *pBuffer,u32  NumToRead)
{
    u16  i=0;
    u32 Address = FLASH_USER_START_ADDR;
    
    while ( (Address < FLASH_USER_END_ADDR) && (i<NumToRead)  )
  {
    pBuffer[i++]= *(__IO u32 *)Address;  
    Address = Address + 4;   //��ַ����4���ֽ�
  }
  
}





