#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "can.h"

//ָʾ�Ƴ�ʼ�������ڲ鿴���պͷ����Ƿ�ɹ�
void LED_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOFʱ��

  //GPIOF9,F10��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14|GPIO_Pin_15;//LED0��LED1��ӦIO��
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIO
	
	GPIO_SetBits(GPIOE,GPIO_Pin_13 | GPIO_Pin_14|GPIO_Pin_15);//PE13,PE14���øߣ�����
}


/*--------------------------------------���շ�---------------------------------------------*/
//int main(void)
//{ 
//	u8 receiveflag,send8b[8];
//	LED_Init();
//	delay_init(168);    //��ʼ����ʱ����
////	uart_init(115200);	//��ʼ�����ڲ�����Ϊ115200
////	USART_SendData(USART1,1111);
//	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_Normal);//CAN��ʼ����ͨģʽ,������500Kbps    
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
//	
////PE13,PE14�����һ��
//	GPIO_ResetBits(GPIOE,GPIO_Pin_13);
//	delay_ms(500);
//	GPIO_ResetBits(GPIOE,GPIO_Pin_14);
//	delay_ms(500);
//	GPIO_ResetBits(GPIOE,GPIO_Pin_15);
//	delay_ms(500);
//	GPIO_SetBits(GPIOE,GPIO_Pin_13 | GPIO_Pin_14|GPIO_Pin_15);
//	delay_ms(1000);
//	while(1)
//	{
//		receiveflag=CAN1_Receive_Msg(send8b);
//		if(receiveflag==0)                             //����ʧ������13,receiveflag=0
//			{
//			  int i;
//			  for(i=0;i>10;i++)
//			    {
//							GPIO_ResetBits(GPIOE,GPIO_Pin_13);
//						  delay_ms(500);
//							GPIO_SetBits(GPIOE,GPIO_Pin_13);
//						  delay_ms(500);
//			    }
//	  	}
//		else
//			{
//				GPIO_ResetBits(GPIOE,GPIO_Pin_13);         //���ճɹ�����13,receiveflag>0
//		  }
//	}
//	
//}






/*--------------------------------------���ͷ�--------------------------------------------*/
//int main(void)
//{ 
//	u8 sendflag,send8b[8],i=0,cnt;
//	LED_Init();
//	delay_init(168);    //��ʼ����ʱ����
////	uart_init(115200);	//��ʼ�����ڲ�����Ϊ115200
////	USART_SendData(USART1,1111);
//	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_Normal);//CAN��ʼ����ͨģʽ,������500Kbps    
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
//	
////PE13,PE14�����һ��
//	GPIO_ResetBits(GPIOE,GPIO_Pin_13);
//	delay_ms(500);
//	GPIO_ResetBits(GPIOE,GPIO_Pin_14);
//	delay_ms(500);
//	GPIO_ResetBits(GPIOE,GPIO_Pin_15);
//	delay_ms(500);
//	GPIO_SetBits(GPIOE,GPIO_Pin_13 | GPIO_Pin_14|GPIO_Pin_15);
//	delay_ms(1000);
//	
//	
//	while(1)
//	{
//		for(i=0;i<8;i++)
//			{
//				send8b[i]=cnt+i;//��䷢������
// 			}

//		sendflag=CAN1_Send_Msg(send8b,8);
//			
//	  if(sendflag==0)GPIO_ResetBits(GPIOE,GPIO_Pin_15); //���ͳɹ�����15,sendflag=0
//    else GPIO_SetBits(GPIOE,GPIO_Pin_15);          //����ʧ������15,sendflag=1
//		
//		delay_ms(1000);
//	
//  }
//}







/*--------------------------------------����ģʽ�����ڲ���(Test success!)----------------------------------------*/
int main(void)
{ 
	u8 sendflag,receiveflag,send8b[8],i=0,cnt;
	LED_Init();
	delay_init(168);    //��ʼ����ʱ����
//	uart_init(115200);	//��ʼ�����ڲ�����Ϊ115200
//	USART_SendData(USART1,1111);
	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_LoopBack);//CAN��ʼ������ģʽ,������500Kbps    
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	
//PE13,PE14�����һ��
	GPIO_ResetBits(GPIOE,GPIO_Pin_13);
	delay_ms(500);
	GPIO_ResetBits(GPIOE,GPIO_Pin_14);
	delay_ms(500);
	GPIO_ResetBits(GPIOE,GPIO_Pin_15);
	delay_ms(500);
	GPIO_SetBits(GPIOE,GPIO_Pin_13 | GPIO_Pin_14|GPIO_Pin_15);
	delay_ms(1000);
	
	
	while(1)
	{
		for(i=0;i<8;i++)
			{
				send8b[i]=cnt+i;//��䷢������
 			}

		sendflag=CAN1_Send_Msg(send8b,8);
			
	  if(sendflag==0)GPIO_ResetBits(GPIOE,GPIO_Pin_15); //���ͳɹ�����15,sendflag=0
    else GPIO_SetBits(GPIOE,GPIO_Pin_15);             //����ʧ������15,sendflag=1
		
		delay_ms(1000);
	
		receiveflag=CAN1_Receive_Msg(send8b);
		if(receiveflag>0)                                 //����ʧ������13,receiveflag=0
			{
					GPIO_ResetBits(GPIOE,GPIO_Pin_14); 
	  	}
		else
			{
				  GPIO_ResetBits(GPIOE,GPIO_Pin_13);          //���ճɹ�����13,receiveflag>0
		  }		
  }
}
