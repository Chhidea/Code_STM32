#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "can.h"

//指示灯初始化，用于查看接收和发送是否成功
void LED_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOF时钟

  //GPIOF9,F10初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14|GPIO_Pin_15;//LED0和LED1对应IO口
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIO
	
	GPIO_SetBits(GPIOE,GPIO_Pin_13 | GPIO_Pin_14|GPIO_Pin_15);//PE13,PE14设置高，灯灭
}


/*--------------------------------------接收方---------------------------------------------*/
//int main(void)
//{ 
//	u8 receiveflag,send8b[8];
//	LED_Init();
//	delay_init(168);    //初始化延时函数
////	uart_init(115200);	//初始化串口波特率为115200
////	USART_SendData(USART1,1111);
//	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_Normal);//CAN初始化普通模式,波特率500Kbps    
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
//	
////PE13,PE14亮灭各一秒
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
//		if(receiveflag==0)                             //接收失败则闪13,receiveflag=0
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
//				GPIO_ResetBits(GPIOE,GPIO_Pin_13);         //接收成功则亮13,receiveflag>0
//		  }
//	}
//	
//}






/*--------------------------------------发送方--------------------------------------------*/
//int main(void)
//{ 
//	u8 sendflag,send8b[8],i=0,cnt;
//	LED_Init();
//	delay_init(168);    //初始化延时函数
////	uart_init(115200);	//初始化串口波特率为115200
////	USART_SendData(USART1,1111);
//	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_Normal);//CAN初始化普通模式,波特率500Kbps    
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
//	
////PE13,PE14亮灭各一秒
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
//				send8b[i]=cnt+i;//填充发送数组
// 			}

//		sendflag=CAN1_Send_Msg(send8b,8);
//			
//	  if(sendflag==0)GPIO_ResetBits(GPIOE,GPIO_Pin_15); //发送成功则亮15,sendflag=0
//    else GPIO_SetBits(GPIOE,GPIO_Pin_15);          //发送失败则灭15,sendflag=1
//		
//		delay_ms(1000);
//	
//  }
//}







/*--------------------------------------环回模式，串口测试(Test success!)----------------------------------------*/
int main(void)
{ 
	u8 sendflag,receiveflag,send8b[8],i=0,cnt;
	LED_Init();
	delay_init(168);    //初始化延时函数
//	uart_init(115200);	//初始化串口波特率为115200
//	USART_SendData(USART1,1111);
	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_LoopBack);//CAN初始化环回模式,波特率500Kbps    
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	
//PE13,PE14亮灭各一秒
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
				send8b[i]=cnt+i;//填充发送数组
 			}

		sendflag=CAN1_Send_Msg(send8b,8);
			
	  if(sendflag==0)GPIO_ResetBits(GPIOE,GPIO_Pin_15); //发送成功则亮15,sendflag=0
    else GPIO_SetBits(GPIOE,GPIO_Pin_15);             //发送失败则灭15,sendflag=1
		
		delay_ms(1000);
	
		receiveflag=CAN1_Receive_Msg(send8b);
		if(receiveflag>0)                                 //接收失败则闪13,receiveflag=0
			{
					GPIO_ResetBits(GPIOE,GPIO_Pin_14); 
	  	}
		else
			{
				  GPIO_ResetBits(GPIOE,GPIO_Pin_13);          //接收成功则亮13,receiveflag>0
		  }		
  }
}
