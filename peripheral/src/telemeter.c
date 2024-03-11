#include "telemeter.h"
//#pragma userclass (near=CEVENT)	
//	CEVENT_EXPORT(0,dl1b_init,NULL);
//#pragma userclass (near=default)
/*********************************************************************************************************************
* �ļ�����          zf_device_dl1b
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          MDK 5.37
* ����ƽ̨          MM32F527X_E9P
* ��������          https://seekfree.taobao.com/
* 
* �޸ļ�¼
* ����              ����                ��ע
* 2022-08-10        Teternal            first version
********************************************************************************************************************/
/*********************************************************************************************************************
* ���߶��壺
*                   ------------------------------------
*                   ģ��ܽ�            ��Ƭ���ܽ�
*                   SCL                 �鿴 zf_device_dl1b.h �� DL1B_SCL_PIN  �궨��
*                   SDA                 �鿴 zf_device_dl1b.h �� DL1B_SDA_PIN  �궨��
*                   XS                  �鿴 zf_device_dl1b.h �� DL1B_XS_PIN  �궨��
*                   VCC                 5V ��Դ
*                   GND                 ��Դ��
*                   ------------------------------------
********************************************************************************************************************/


uint8 dl1b_init_flag = 0;
uint8 dl1b_finsh_flag = 0;			//������־���ģ���Ƿ�ɹ���þ�������

#define dl1b_transfer_8bit_array(tdata, tlen, rdata, rlen)      (dl1b_iic_transfer_8bit_array((tdata), (tlen), (rdata), (rlen)))


#define GET_DL1B_SDA   		 		DL1B_SDA_PIN
#define DL1B_SDA_LOW()         		DL1B_SDA_PIN = 0		//IO������͵�ƽ
#define DL1B_SDA_HIGH()        		DL1B_SDA_PIN = 1		//IO������ߵ�ƽ

#define DL1B_SCL_LOW()          	DL1B_SCL_PIN = 0		//IO������͵�ƽ
#define DL1B_SCL_HIGH()         	DL1B_SCL_PIN = 1		//IO������ߵ�ƽ

#define ack 1      //��Ӧ��
#define no_ack 0   //��Ӧ��	

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ģ��IIC��ʱ
//  @return     void						
//  @since      v1.0
//  Sample usage:				���IICͨѶʧ�ܿ��Գ�������j��ֵ
//-------------------------------------------------------------------------------------------------------------------
static void dl1b_simiic_delay(void)
{
    uint16 j=DL1B_SOFT_IIC_DELAY;   
	while(j--);
}

//�ڲ�ʹ�ã��û��������
static void dl1b_simiic_start(void)
{
	DL1B_SDA_HIGH();
	DL1B_SCL_HIGH();
	dl1b_simiic_delay();
	DL1B_SDA_LOW();
	dl1b_simiic_delay();
	DL1B_SCL_LOW();
}

//�ڲ�ʹ�ã��û��������
static void dl1b_simiic_stop(void)
{
	DL1B_SDA_LOW();
	DL1B_SCL_LOW();
	dl1b_simiic_delay();
	DL1B_SCL_HIGH();
	dl1b_simiic_delay();
	DL1B_SDA_HIGH();
	dl1b_simiic_delay();
}

//��Ӧ��(����ack:SDA=0��no_ack:SDA=0)
//�ڲ�ʹ�ã��û��������
static void dl1b_simiic_sendack(unsigned char ack_dat)
{
    DL1B_SCL_LOW();
	dl1b_simiic_delay();
	if(ack_dat) DL1B_SDA_LOW();
    else    	DL1B_SDA_HIGH();

    DL1B_SCL_HIGH();
    dl1b_simiic_delay();
    DL1B_SCL_LOW();
    dl1b_simiic_delay();
}


static int dl1b_sccb_waitack(void)
{
    DL1B_SCL_LOW();

	dl1b_simiic_delay();
	
	DL1B_SCL_HIGH();
    dl1b_simiic_delay();
	
    if(GET_DL1B_SDA)           //Ӧ��Ϊ�ߵ�ƽ���쳣��ͨ��ʧ��
    {

        DL1B_SCL_LOW();
        return 0;
    }

    DL1B_SCL_LOW();
	dl1b_simiic_delay();
    return 1;
}

//�ֽڷ��ͳ���
//����c(����������Ҳ���ǵ�ַ)���������մ�Ӧ��
//�����Ǵ�Ӧ��λ
//�ڲ�ʹ�ã��û��������
static void dl1b_send_ch(uint8 c)
{
	uint8 i = 8;
    while(i--)
    {
        if(c & 0x80)	DL1B_SDA_HIGH();//SDA �������
        else			DL1B_SDA_LOW();
        c <<= 1;
        dl1b_simiic_delay();
        DL1B_SCL_HIGH();                //SCL ���ߣ��ɼ��ź�
        dl1b_simiic_delay();
        DL1B_SCL_LOW();                //SCL ʱ��������
    }
	dl1b_sccb_waitack();
}


//�ֽڽ��ճ���
//�����������������ݣ��˳���Ӧ���|��Ӧ����|ʹ��
//�ڲ�ʹ�ã��û��������
static uint8 dl1b_read_ch(uint8 ack_x)
{
    uint8 i;
    uint8 c;
    c=0;
    DL1B_SCL_LOW();
    dl1b_simiic_delay();
    DL1B_SDA_HIGH();             

    for(i=0;i<8;i++)
    {
        dl1b_simiic_delay();
        DL1B_SCL_LOW();         //��ʱ����Ϊ�ͣ�׼����������λ
        dl1b_simiic_delay();
        DL1B_SCL_HIGH();         //��ʱ����Ϊ�ߣ�ʹ��������������Ч
        dl1b_simiic_delay();
        c<<=1;
        if(GET_DL1B_SDA) 
        {
            c+=1;   //������λ�������յ����ݴ�c
        }
    }

	DL1B_SCL_LOW();
	dl1b_simiic_delay();
	dl1b_simiic_sendack(ack_x);
	
    return c;
}


//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC �ӿڴ��� 8bit ���� ��д���ȡ
// ����˵��     *write_data     �������ݴ�Ż�����
// ����˵��     write_len       ���ͻ���������
// ����˵��     *read_data      ��ȡ���ݴ�Ż�����
// ����˵��     read_len        ��ȡ����������
// ���ز���     void            
// ʹ��ʾ��     iic_transfer_8bit_array(IIC_1, addr, data, 64, data, 64);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void dl1b_iic_transfer_8bit_array (const uint8 *write_data, uint32 write_len, uint8 *read_data, uint32 read_len)
{

    dl1b_simiic_start();
    dl1b_send_ch(DL1B_DEV_ADDR << 1);
    while(write_len --)
    {
        dl1b_send_ch(*write_data ++);
    }
    dl1b_simiic_start();
    dl1b_send_ch(DL1B_DEV_ADDR << 1 | 0x01);
    while(read_len --)
    {
		// ǰ��7λ��Ҫ�ظ�ack�����1λ����Ҫ�ظ�ack.
        *read_data ++ = dl1b_read_ch(read_len != 0);
    }
    dl1b_simiic_stop();
}





//-------------------------------------------------------------------------------------------------------------------
// �������     �����Ժ���Ϊ��λ�ķ�Χ����
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     dl1b_get_distance();
// ��ע��Ϣ     �ڿ�ʼ������̲�����Ҳ���ô˺���
//-------------------------------------------------------------------------------------------------------------------
uint16 dl1b_get_distance (void)
{     
	uint8 data_buffer[3];
	int16 dl1b_distance_temp = 0;
	uint16 dl1b_distance_mm = 3333;
    if(dl1b_init_flag)
    {
        data_buffer[0] = DL1B_GPIO__TIO_HV_STATUS >> 8;
        data_buffer[1] = DL1B_GPIO__TIO_HV_STATUS & 0xFF;
        dl1b_transfer_8bit_array(data_buffer, 2, &data_buffer[2], 1);

        if(data_buffer[2])
        {

            data_buffer[0] = DL1B_SYSTEM__INTERRUPT_CLEAR >> 8;
            data_buffer[1] = DL1B_SYSTEM__INTERRUPT_CLEAR & 0xFF;
            data_buffer[2] = 0x01;
            dl1b_transfer_8bit_array(data_buffer, 3, data_buffer, 0);// clear Interrupt

            data_buffer[0] = DL1B_RESULT__RANGE_STATUS >> 8;
            data_buffer[1] = DL1B_RESULT__RANGE_STATUS & 0xFF;
            dl1b_transfer_8bit_array(data_buffer, 2, &data_buffer[2], 1);
            
            if(0x89 == data_buffer[2])
            {
                data_buffer[0] = DL1B_RESULT__FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0 >> 8;
                data_buffer[1] = DL1B_RESULT__FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0 & 0xFF;
                dl1b_transfer_8bit_array(data_buffer, 2, data_buffer, 2);
                dl1b_distance_temp = data_buffer[0];
                dl1b_distance_temp = (dl1b_distance_temp << 8) | data_buffer[1];
                
                if(dl1b_distance_temp > 4000 || dl1b_distance_temp < 0)
                {
                    dl1b_distance_mm = 4444;
                    dl1b_finsh_flag = 0;
                }
                else
                {
                    dl1b_distance_mm = dl1b_distance_temp;
                    dl1b_finsh_flag = 1;
                }
            }
            else
            {
                dl1b_distance_mm = 5555;
                dl1b_finsh_flag = 0;
            }
        }
        else
        {
            dl1b_distance_mm = 6666;
            dl1b_finsh_flag = 0;
        }
    }
	return dl1b_distance_mm;
}



//-------------------------------------------------------------------------------------------------------------------
// �������     ��ʼ�� DL1B
// ����˵��     void
// ���ز���     uint8           1-��ʼ��ʧ�� 0-��ʼ���ɹ�
// ʹ��ʾ��     dl1b_init();
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
uint8 dl1b_init (void)
{
    uint8   return_state    = 0;
    uint8   data_buffer[2 + sizeof(dl1b_default_configuration)]; 
    uint16  time_out_count  = 0;

    do
    {
        delay_ms(50);
        DL1B_XS_PIN = 0;
        delay_ms(10);
        DL1B_XS_PIN = 1;
        delay_ms(50);

        data_buffer[0] = DL1B_FIRMWARE__SYSTEM_STATUS >> 8;
        data_buffer[1] = DL1B_FIRMWARE__SYSTEM_STATUS & 0xFF;
        dl1b_transfer_8bit_array(data_buffer, 2, &data_buffer[2], 1);
        return_state = (0x01 == (data_buffer[2] & 0x01)) ? (0) : (1);
        if(1 == return_state)
        {
            break;
        }

        data_buffer[0] = DL1B_I2C_SLAVE__DEVICE_ADDRESS >> 8;
        data_buffer[1] = DL1B_I2C_SLAVE__DEVICE_ADDRESS & 0xFF;
        memcpy(&data_buffer[2], (uint8 *)dl1b_default_configuration, sizeof(dl1b_default_configuration));
        dl1b_transfer_8bit_array(data_buffer, 2 + sizeof(dl1b_default_configuration), data_buffer, 0);

        while(1)
        {
            data_buffer[0] = DL1B_GPIO__TIO_HV_STATUS >> 8;
            data_buffer[1] = DL1B_GPIO__TIO_HV_STATUS & 0xFF;
            dl1b_transfer_8bit_array(data_buffer, 2, &data_buffer[2], 1);
            if(0x00 == (data_buffer[2] & 0x01))
            {
                time_out_count = 0;
                break;
            }
            if(DL1B_TIMEOUT_COUNT < time_out_count ++)
            {
                return_state = 1;
                break;
            }
            delay_ms(1);
        }

        dl1b_init_flag = 1;
    }while(0);


    return return_state;
}
