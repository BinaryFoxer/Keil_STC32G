#include  "iic.h"

#if	(USE_SOFT_IIC == 1)

static uint16 simiic_delay_time=100;   //ICM�ȴ�����Ӧ����Ϊ100

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ģ��IIC��ʱ ʱ������
//  @return     void						
//  @since      v1.0
//  Sample usage:				���IICͨѶʧ�ܿ��Գ�������simiic_delay_time��ֵ
//-------------------------------------------------------------------------------------------------------------------
void simiic_delay_set(uint16 time)
{
    simiic_delay_time = time;           //ICM�ȴ�����Ӧ����Ϊ100
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ģ��IIC��ʱ
//  @return     void						
//  @since      v1.0
//  Sample usage:				���IICͨѶʧ�ܿ��Գ�������simiic_delay_time��ֵ
//-------------------------------------------------------------------------------------------------------------------
void simiic_delay(void)
{
	uint16 delay_time;
    delay_time = simiic_delay_time;
	while(delay_time--);
}


//�ڲ�ʹ�ã��û��������
void simiic_start(void)
{
	SDA1();
	SCL1();
	simiic_delay();
	SDA0();
	simiic_delay();
	SCL0();
}

//�ڲ�ʹ�ã��û��������
void simiic_stop(void)
{
	SDA0();
	SCL0();
	simiic_delay();
	SCL1();
	simiic_delay();
	SDA1();
	simiic_delay();
}

//��Ӧ��(����ack:SDA=0��no_ack:SDA=0)
//�ڲ�ʹ�ã��û��������
void simiic_sendack(unsigned char ack_dat)
{
    SCL0();
	simiic_delay();
	if(ack_dat) SDA0();
    else    	SDA1();

    SCL1();
    simiic_delay();
    SCL0();
    simiic_delay();
}


static int sccb_waitack(void)
{
    SCL0();
	simiic_delay();
	
	SCL1();
    simiic_delay();
	
    if(SDA_GPIO_PIN)           //Ӧ��Ϊ�ߵ�ƽ���쳣��ͨ��ʧ��
    {
        SCL0();
        return 0;
    }
    SCL0();
	simiic_delay();
    return 1;
}

//�ֽڷ��ͳ���
//����c(����������Ҳ���ǵ�ַ)���������մ�Ӧ��
//�����Ǵ�Ӧ��λ
//�ڲ�ʹ�ã��û��������
void send_ch(uint8 c)
{
	uint8 i = 8;
    while(i--)
    {
        if(c & 0x80)	SDA1();//SDA �������
        else			SDA0();
        c <<= 1;
        simiic_delay();
        SCL1();                //SCL ���ߣ��ɼ��ź�
        simiic_delay();
        SCL0();                //SCL ʱ��������
    }
	sccb_waitack();
}

//�ֽڽ��ճ���
//�����������������ݣ��˳���Ӧ���|��Ӧ����|ʹ��
//�ڲ�ʹ�ã��û��������
uint8 read_ch(uint8 ack_x)
{
    uint8 i;
    uint8 c;
    c=0;
    SCL0();
    simiic_delay();
    SDA1();             
    for(i=0;i<8;i++)
    {
        simiic_delay();
        SCL0();         //��ʱ����Ϊ�ͣ�׼����������λ
        simiic_delay();
        SCL1();         //��ʱ����Ϊ�ߣ�ʹ��������������Ч
        simiic_delay();
        c<<=1;
        if(SDA_GPIO_PIN) 
        {
            c+=1;   //������λ�������յ����ݴ�c
        }
    }
	SCL0();
	simiic_delay();
	simiic_sendack(ack_x);
	
    return c;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ģ��IICд���ݵ��豸�Ĵ�������
//  @param      dev_add			�豸��ַ(����λ��ַ)
//  @param      reg_add			���Ŀ��Ĵ�����ַ������
//	@param		reg_num			�Ĵ��������ֽ���
//  @param      dat				д�������
//  @return     void						
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void simiic_write_reg(uint8 dev_add, uint8 reg_add, uint8 dat)
{
	simiic_start();
    send_ch( (dev_add<<1) | 0x00);   //����������ַ��дλ
	send_ch(reg_add);
	send_ch( dat );   				 //������Ҫд�������
	simiic_stop();
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ģ��IICд���ݵ��豸�Ĵ�������
//  @param      dev_add			�豸��ַ(����λ��ַ)
//  @param      reg_add			���Ŀ��Ĵ�����ַ������
//	@param		reg_num			�Ĵ��������ֽ���
//  @param      dat_add			д�����������ĵ�ַ
//	@param		dat_num			д��������ֽڸ���
//  @return     void						
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void simiic_write_regs(uint8 dev_add, uint8 reg, uint8 * dat_add, uint8 dat_num)
{
	simiic_start();
    send_ch((dev_add<<1) | 0x00);   //����������ַ��дλ
	send_ch(reg);
	while(dat_num--)
    {
		send_ch(*dat_add);   				 //������Ҫд�������
		dat_add++;
    }
	simiic_stop();
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ģ��IIC���豸�Ĵ�����ȡ����
//  @param      dev_add			�豸��ַ(����λ��ַ)
//  @param      reg				���Ŀ��Ĵ�����ַ������
//	@param		reg_num			�Ĵ��������ֽ���
//  @return     uint8			���ؼĴ���������			
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
uint8 simiic_read_reg(uint8 dev_add, uint8 reg_add)
{
	uint8 dat;
	simiic_start();
    send_ch( (dev_add<<1) | 0x00);  //����������ַ��дλ
	send_ch(reg_add);
	
	simiic_start();
	send_ch( (dev_add<<1) | 0x01);  //����������ַ�Ӷ�λ
	dat = read_ch(no_ack);   				//��ȡ����
	simiic_stop();
	
	return dat;
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ģ��IIC��ȡ���ֽ�����
//  @param      dev_add			�豸��ַ(����λ��ַ)
//  @param      reg				���Ŀ��Ĵ�����ַ������
//	@param		reg_num			�Ĵ��������ֽ���
//  @param      dat_add			���ݱ���ĵ�ַָ��
//  @param      dat_num			��ȡ�ֽ�����
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void simiic_read_regs(uint8 dev_add, uint8 reg, uint8 *dat_add, uint8 dat_num)
{
	simiic_start();
    send_ch( (dev_add<<1) | 0x00);  //����������ַ��дλ
	send_ch(reg);

	simiic_start();
	send_ch( (dev_add<<1) | 0x01);  //����������ַ�Ӷ�λ
    while(--dat_num)
    {
        *dat_add = read_ch(ack); //��ȡ����
        dat_add++;
    }
    *dat_add = read_ch(no_ack); //��ȡ����
	simiic_stop();
}
#define DL1B_DEV_ADDR                                           ( 0x52 >> 1 )
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ģ��IIC��д��������
//  @param      dev_add			�豸��ַ(����λ��ַ)
//  @param      write_add			�������ݴ�Ż�����
//	@param		write_num			���ͻ���������
//  @param      read_add			��ȡ���ݴ�Ż�����
//  @param      read_num			��ȡ����������
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void simiic_transfer(const uint8 dev_add, const uint8 *write_add, uint8 write_num, uint8 *read_add, uint8 read_num)
{
	simiic_start();
    send_ch(dev_add << 1);
    while(write_num --)
    {
        send_ch(*write_add ++);
    }
    simiic_start();
    send_ch(dev_add << 1 | 0x01);
    while(read_num --)
    {
		// ǰ��7λ��Ҫ�ظ�ack�����1λ����Ҫ�ظ�ack.
        *read_add ++ = read_ch(read_num != 0);
    }
    simiic_stop();
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ģ��IIC�˿ڳ�ʼ��
//  @param      NULL
//  @return     void	
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void simiic_init(void)
{
	//���ģʽ����Ϊ��©���
	GPIO_InitTypeDef IIC_PIN;
	IIC_PIN.Mode = GPIO_OUT_OD;		
	IIC_PIN.Pin = IIC_SCL_PIN;
	GPIO_Inilize(IIC_GPIO,&IIC_PIN);
	
	IIC_PIN.Pin = IIC_SDA_PIN;
	GPIO_Inilize(IIC_GPIO,&IIC_PIN);	
	
	//��©���������������
	switch (IIC_GPIO){
		case GPIO_P1 :P1_PULL_UP_ENABLE(IIC_SCL_PIN | IIC_SDA_PIN);
			break;
		case GPIO_P2 :P2_PULL_UP_ENABLE(IIC_SCL_PIN | IIC_SDA_PIN);
			break;
		case GPIO_P3 :P3_PULL_UP_ENABLE(IIC_SCL_PIN | IIC_SDA_PIN);
			break;
		default : 
			break;
	}
}

#else  //Use Hardware IIC

/*Hardware IIC codes write here*/

//========================================================================
// ����: void I2C_Init(I2C_InitTypeDef *I2Cx)
// ����: I2C��ʼ������.
// ����: I2Cx: �ṹ����,��ο�I2C.h��Ķ���.
// ����: none.
// �汾: V1.0, 2012-11-22
//========================================================================

void hardiic_init()
{
	//���ģʽ����Ϊ��©���
	GPIO_InitTypeDef IIC_PIN;
	IIC_PIN.Mode = GPIO_OUT_OD;		
	IIC_PIN.Pin = IIC_SCL_PIN;
	GPIO_Inilize(IIC_GPIO,&IIC_PIN);
	
	IIC_PIN.Pin = IIC_SDA_PIN;
	GPIO_Inilize(IIC_GPIO,&IIC_PIN);	
	
	//��©���������������
	switch (IIC_GPIO){
		case GPIO_P1 :P1_PULL_UP_ENABLE(IIC_SCL_PIN | IIC_SDA_PIN);
			break;
		case GPIO_P2 :P2_PULL_UP_ENABLE(IIC_SCL_PIN | IIC_SDA_PIN);
			break;
		case GPIO_P3 :P3_PULL_UP_ENABLE(IIC_SCL_PIN | IIC_SDA_PIN);
			break;
		default : 
			break;
	}
	Zf_IIC_init(IIC_2, IIC2_SCL_P25,IIC2_SDA_P24,500);
}

#endif


/* ============================== �ɵ��ú��� ============================ */

//-------------------------------------------------------------------------------------------------------------------
//  @brief      1. IICд���ݵ��豸�Ĵ�������
//  @param      dev_add			�豸��ַ(����λ��ַ)
//  @param      reg_add			��� Ŀ��Ĵ�����ַ ������
//	@param		reg_num			�Ĵ��������ֽ���
//  @param      dat				д�������
//  @return     void						
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void iic_write_reg(uint8 dev_add, uint8 reg, uint8 dat)
{
#if USE_SOFT_IIC
	simiic_write_reg(dev_add, reg, dat);				/* �豸��ַ(����λ��ַ)�����Ŀ��Ĵ�����ַ�����飬�Ĵ��������ֽ�����д������� */
#else	//use hardware IIC
	Zf_IIC_write_reg(dev_add, reg, dat);
#endif	//USE_SOFT_IIC
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      IICд���ֽ�����
//  @param      dev_add			�豸��ַ(����λ��ַ)
//  @param      reg_add			���Ŀ��Ĵ�����ַ������
//	@param		reg_num			�Ĵ��������ֽ���
//  @param      dat_add			Ҫд������ݱ���ĵ�ַָ��
//  @param      dat_num			��ȡ�ֽ�����
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void iic_write_regs(uint8 dev_add, uint8 reg, uint8 *dat_add, uint8 dat_num)
{
#if USE_SOFT_IIC
	simiic_write_regs(dev_add, reg, dat_add, dat_num);
#else	//use hardware IIC
	//I2C_WriteNbyte(dev_add, reg_add, reg_num, dat_add, dat_num);
#endif	//USE_SOFT_IIC
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      IIC��д��������
//  @param      dev_add			�豸��ַ(����λ��ַ)
//  @param      write_add			�������ݴ�Ż�����
//	@param		write_num			���ͻ���������
//  @param      read_add			��ȡ���ݴ�Ż�����
//  @param      read_num			��ȡ����������
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void iic_transfer(const uint8 dev_add, const uint8 *write_add, uint8 write_num, uint8 *read_add, uint8 read_num)
{
#if USE_SOFT_IIC
	simiic_transfer(dev_add, write_add, write_num, read_add, read_num);
#else	//use hardware IIC

#endif	//USE_SOFT_IIC
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      IIC�����ݵ��豸�Ĵ�������
//  @param      dev_add			�豸��ַ(����λ��ַ)
//  @param      reg_add			���Ŀ��Ĵ�����ַ������
//	@param		reg_num			�Ĵ��������ֽ���
//  @return     void						
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
uint8 iic_read_reg(uint8 dev_add, uint8 reg)
{
	uint8 recive = 0;
#if USE_SOFT_IIC
	recive = simiic_read_reg(dev_add, reg);
#else	//use hardware IIC
	Zf_IIC_read_reg(dev_add, reg, &recive);
#endif	//USE_SOFT_IIC
	return recive;
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      IIC��ȡ���ֽ�����
//  @param      dev_add			�豸��ַ(����λ��ַ)
//  @param      reg_add			���Ŀ��Ĵ�����ַ������
//	@param		reg_num			�Ĵ��������ֽ���
//  @param      dat_add			���ݱ���ĵ�ַָ��
//  @param      dat_num			��ȡ�ֽ�����
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void iic_read_regs(uint8 dev_add, uint8 reg, uint8 *dat_add, uint8 dat_num)
{
#if USE_SOFT_IIC
	simiic_read_regs(dev_add, reg, dat_add, dat_num);
#else	//use hardware IIC
	Zf_IIC_read_reg_bytes(dev_add, reg, dat_add, dat_num);
#endif	//USE_SOFT_IIC
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      4. IIC�˿ڳ�ʼ��
//  @param      NULL
//  @return     void	
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void iic_init(void)
{
#if USE_SOFT_IIC
	simiic_init();
#else	//use hardware IIC
	hardiic_init();
#endif	//USE_SOFT_IIC
}
