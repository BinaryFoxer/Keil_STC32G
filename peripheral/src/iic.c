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
void simiic_write_reg(uint8 dev_add, uint8 * reg_add, uint8 reg_num, uint8 dat)
{
	simiic_start();
    send_ch( (dev_add<<1) | 0x00);   //����������ַ��дλ
    while(reg_num--)
    {
		send_ch(*reg_add);
		reg_add++;
    }
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
void simiic_write_regs(uint8 dev_add, uint8 * reg_add, uint8 reg_num, uint8 * dat_add, uint8 dat_num)
{
	simiic_start();
    send_ch( (dev_add<<1) | 0x00);   //����������ַ��дλ
    while(reg_num--)
    {
		send_ch(*reg_add);
		reg_add++;
    }
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
uint8 simiic_read_reg(uint8 dev_add, uint8 * reg_add, uint8 reg_num)
{
	uint8 dat;
	simiic_start();
    send_ch( (dev_add<<1) | 0x00);  //����������ַ��дλ
    while(reg_num--)
    {
		send_ch(*reg_add);
		reg_add++;
    }
	
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
void simiic_read_regs(uint8 dev_add, uint8 * reg_add, uint8 reg_num, uint8 *dat_add, uint8 dat_num)
{
	simiic_start();
    send_ch( (dev_add<<1) | 0x00);  //����������ַ��дλ
    while(reg_num--)
    {
		send_ch(*reg_add);
		reg_add++;
    }
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
	I2C_InitTypeDef		I2C_InitStructure;

	I2C_InitStructure.I2C_Mode      = I2C_Mode_Master;	//����ѡ��   I2C_Mode_Master, I2C_Mode_Slave
	I2C_InitStructure.I2C_Enable    = ENABLE;			//I2C����ʹ��,   ENABLE, DISABLE
	I2C_InitStructure.I2C_MS_WDTA   = DISABLE;			//����ʹ���Զ�����,  ENABLE, DISABLE
	I2C_InitStructure.I2C_Speed     = 63;				//�����ٶ�=Fosc/2/(Speed*2+4),      0~63
	I2C_Init(&I2C_InitStructure);
	NVIC_I2C_Init(I2C_Mode_Master,DISABLE,Priority_0);		//����ģʽ, I2C_Mode_Master, I2C_Mode_Slave; �ж�ʹ��
	
	switch (IIC_GPIO){
	case GPIO_P1 :I2C_SW(I2C_P14_P15);;
		break;
	case GPIO_P2 :I2C_SW(I2C_P24_P25);;
		break;
	case GPIO_P3 :I2C_SW(I2C_P33_P32);;
		break;
	default : 
		break;
	}
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
void iic_write_reg(uint8 dev_add, uint8 * reg_add, uint8 reg_num, uint8 dat)
{
#if USE_SOFT_IIC
	simiic_write_reg(dev_add, reg_add, reg_num, dat);				/* �豸��ַ(����λ��ַ)�����Ŀ��Ĵ�����ַ�����飬�Ĵ��������ֽ�����д������� */
#else	//use hardware IIC
	I2C_WriteNbyte(dev_add, reg_add, reg_num��dat, 1);
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
void iic_write_regs(uint8 dev_add, uint8 * reg_add, uint8 reg_num, uint8 *dat_add, uint8 dat_num)
{
#if USE_SOFT_IIC
	simiic_write_regs(dev_add, reg_add, reg_num, dat_add, dat_num);
#else	//use hardware IIC
	I2C_WriteNbyte(dev_add, reg_add, reg_num, dat_add, dat_num);
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
uint8 iic_read_reg(uint8 dev_add, uint8 * reg_add, uint8 reg_num)
{
	uint8 recive = 0;
#if USE_SOFT_IIC
	recive = simiic_read_reg(dev_add, reg_add, reg_num);
#else	//use hardware IIC
	I2C_ReadNbyte(dev_add, reg_add, reg_num, &recive, 1);
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
void iic_read_regs(uint8 dev_add, uint8 * reg_add, uint8 reg_num, uint8 *dat_add, uint8 dat_num)
{
#if USE_SOFT_IIC
	simiic_read_regs(dev_add, reg_add, reg_num, dat_add, dat_num);
#else	//use hardware IIC
	I2C_ReadNbyte(dev_add, reg_add, reg_num, dat_add, dat_num);
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
