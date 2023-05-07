#include "sht30.h"

/* ADDR Pin Conect to VSS */
 
#define    SHT30_ADDR_WRITE    0x44<<1         //10001000�������û��ֲ��ָʾ���������SHT30��д���ַ
#define    SHT30_ADDR_READ        (0x44<<1)+1        //10001011�������û��ֲ��ָʾ���������SHT30�Ķ�ȡ��ַ
extern I2C_HandleTypeDef hi2c1;//����I2C3�Ľӿڣ����õ��ĸ��͸��ĸ�
 
typedef enum				//����Ķ���
{
    /* �����λ���� */
 
    SOFT_RESET_CMD = 0x30A2,
    /*
    ���β���ģʽ
    ������ʽ��Repeatability_CS_CMD
    CS�� Clock stretching
    */
    HIGH_ENABLED_CMD    = 0x2C06,
    MEDIUM_ENABLED_CMD  = 0x2C0D,
    LOW_ENABLED_CMD     = 0x2C10,
    HIGH_DISABLED_CMD   = 0x2400,
    MEDIUM_DISABLED_CMD = 0x240B,
    LOW_DISABLED_CMD    = 0x2416,
 
    /*
    ���ڲ���ģʽ
    ������ʽ��Repeatability_MPS_CMD
    MPS��measurement per second
    */
    HIGH_0_5_CMD   = 0x2032,
    MEDIUM_0_5_CMD = 0x2024,
    LOW_0_5_CMD    = 0x202F,
    HIGH_1_CMD     = 0x2130,
    MEDIUM_1_CMD   = 0x2126,
    LOW_1_CMD      = 0x212D,
    HIGH_2_CMD     = 0x2236,
    MEDIUM_2_CMD   = 0x2220,
    LOW_2_CMD      = 0x222B,
    HIGH_4_CMD     = 0x2334,
    MEDIUM_4_CMD   = 0x2322,
    LOW_4_CMD      = 0x2329,
    HIGH_10_CMD    = 0x2737,
    MEDIUM_10_CMD  = 0x2721,
    LOW_10_CMD     = 0x272A,
    /* ���ڲ���ģʽ��ȡ�������� */
    READOUT_FOR_PERIODIC_MODE = 0xE000,
} SHT30_CMD;
 
/**
 * @brief    ��SHT30����һ��ָ��(16bit)
 * @param    cmd ���� SHT30ָ���SHT30_MODE��ö�ٶ��壩
 * @retval    �ɹ�����HAL_OK
*/
static uint8_t    SHT30_Send_Cmd(SHT30_CMD cmd)
{
    uint8_t cmd_buffer[2];
    cmd_buffer[0] = cmd >> 8;
    cmd_buffer[1] = cmd;
    return HAL_I2C_Master_Transmit(&hi2c1, SHT30_ADDR_WRITE, (uint8_t*)cmd_buffer, 2, 0xFFFF);
}
 
/**
 * @brief    ��λSHT30
 * @param    none
 * @retval    none
*/
void SHT30_Reset(void)			
{
    SHT30_Send_Cmd(SOFT_RESET_CMD);
    HAL_Delay(20);
}
 
/**
 * @brief    ��ʼ��SHT30
 * @param    none
 * @retval    �ɹ�����HAL_OK
 * @note    ���ڲ���ģʽ
*/
uint8_t SHT30_Init(void)
{
    return SHT30_Send_Cmd(MEDIUM_2_CMD);
}
 
/**
 * @brief    ��SHT30��ȡһ������
 * @param    dat ���� �洢��ȡ���ݵĵ�ַ��6���ֽ����飩
 * @retval    �ɹ� ���� ����HAL_OK
*/
uint8_t SHT30_Read_Dat(uint8_t* dat)
{
    SHT30_Send_Cmd(READOUT_FOR_PERIODIC_MODE);
	HAL_Delay(20);
    return HAL_I2C_Master_Receive(&hi2c1, SHT30_ADDR_READ, dat, 6, 0xFFFF);
}
/*************************************************
 * �����������ѵ㣬CRC��֤��û���������е�������
 * �����˻��þ���
 */
 
#define CRC8_POLYNOMIAL 0x31
 
uint8_t CheckCrc8(uint8_t* const message, uint8_t initial_value)
{
    uint8_t  remainder;        //����
    uint8_t  i = 0, j = 0;  //ѭ������
 
    /* ��ʼ�� */
    remainder = initial_value;
 
    for(j = 0; j < 2;j++)
    {
        remainder ^= message[j];
 
        /* �����λ��ʼ���μ���  */
        for (i = 0; i < 8; i++)
        {
            if (remainder & 0x80)
            {
                remainder = (remainder << 1)^CRC8_POLYNOMIAL;
            }
            else
            {
                remainder = (remainder << 1);
            }
        }
    }
 
    /* ���ؼ����CRC�� */
    return remainder;
}
/**
 * @brief    ��SHT30���յ�6���ֽ����ݽ���CRCУ�飬��ת��Ϊ�¶�ֵ��ʪ��ֵ
 * @param    dat  ���� �洢�������ݵĵ�ַ��6���ֽ����飩
 * @retval    У��ɹ�  ���� ����0
 *             У��ʧ��  ���� ����1���������¶�ֵ��ʪ��ֵΪ0
*/
uint8_t SHT30_Dat_To_Float(uint8_t* const dat, float *temperature,float *humidity)
{
    uint16_t recv_temperature = 0;
    uint16_t recv_humidity = 0;
 
    /* У���¶����ݺ�ʪ�������Ƿ������ȷ */
    if(CheckCrc8(dat, 0xFF) != dat[2] || CheckCrc8(&dat[3], 0xFF) != dat[5])
        return 1;
 
    /* ת���¶����� */
    recv_temperature = ((uint16_t)dat[0]<<8)|dat[1];
    *temperature = -45 + 175*((float)recv_temperature/65535);
 
    /* ת��ʪ������ */
    recv_humidity = ((uint16_t)dat[3]<<8)|dat[4];
    *humidity = 100 * ((float)recv_humidity / 65535);
 
    return 0;
}