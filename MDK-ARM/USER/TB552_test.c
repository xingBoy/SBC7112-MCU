/**********************************************************************************
File：
     1、主机通过串口2发送字符串，控制从机输出GPIO口（PD 0、1、14、15）的电平值；
     2、主机通过串口2获取GPIO口（PE 10、11、12、13）电平值。
**********************************************************************************/
#include "tb552_test.h"

char  U2_BUFF[10];
char  i=0;
char  Do=0;
char  Do_con=0;

//int   data_len=0;

/***************************************************************
	*函数名：comm
	*输  入：无
	*说  明：File 逻辑控制
	*返回值：无
  **/
void comm(void)
{
//	HAL_GPIO_WritePin ( GPIOF,PF9_Pin,GPIO_PIN_RESET);
//	HAL_Delay(500);
	
	Data_Turn();
	
//	HAL_GPIO_WritePin ( GPIOF,PF9_Pin,GPIO_PIN_SET);
//	HAL_Delay(600);
}

/***************************************************************
	*函数名：Data_Turn
	*输  入：无
	*说  明：接收串口的状态控制数据
	*返回值：无
  **/
void Data_Turn(void)
{

  if(recv_end_flag ==1)		
  {
      //printf("rx_len=%d\r\n",rx_len);											//打印接收长度
      //HAL_UART_Transmit(&huart2,rx_buffer, rx_len,200);		//接收数据打印出来
      for(uint8_t i=0;i<rx_len;i++)
      {
         rx_buffer[i]=0;//清接收缓存
      }
      rx_len=0;//清除计数
      recv_end_flag=0;//清除接收结束标志位
   }
   HAL_UART_Receive_DMA(&huart2,rx_buffer,BUFFER_SIZE);			//重新打开DMA接收     

/*
	HAL_UART_Receive_IT(&huart2,(uint8_t *)U2_BUFF,6);//串口中断要发送够6个字符串才会触发
	HAL_Delay(50);
	data_len=strlen(U2_BUFF);		//获取字符串长度
	printf("Len = %d \r\n",data_len);
	printf("U2_BUFF[1] = %d \r\n",U2_BUFF[1]);*/
	
  HAL_Delay(100);
	
	if( 73==rx_buffer[1] || 105==rx_buffer[1] ) 					//根据ASCII表，判断是要否进行读PE端口操作
	{
		i=(char)(rx_buffer[3]-48);
	  //printf("Read DI_%d \r\n",i);
		Get_Gpio(); 
	}
	else if( 79==rx_buffer[1] || 111==rx_buffer[1] )			//根据ASCII表，判断是要否进行读PD端口操作
	{
		Do=(char)(rx_buffer[3]-48);
		Do_con=(char)(rx_buffer[5]-48);
	  //printf("Control  DO_%d:%d \r\n",Do,Do_con);
		Cont_Gpio();
	}
	
 /*	数据清0	*/
	i=0;
	memset(&U2_BUFF,0,10);
//data_len=0;	
}

/***************************************************************
	*函数名：Cont_Gpio
	*输  入：无
	*说  明：控制输出GPIO口（PD 0、1、14、15）的电平值
	*返回值：无
  **/
void Cont_Gpio(void)
{
	//char j=0;
	
	if(Do==0)
	{
		if(Do_con==0) HAL_GPIO_WritePin ( GPIOD,GPIO_1_Pin,GPIO_PIN_RESET);
		else 					HAL_GPIO_WritePin ( GPIOD,GPIO_1_Pin,GPIO_PIN_SET);
		//j=HAL_GPIO_ReadPin(GPIOD,GPIO_1_Pin);			//读出引脚的写入转态，串口测试用
		//printf("PD_0 = %d \r\n",j);
	}
	else if(Do==1)
	{
		if(Do_con==0) HAL_GPIO_WritePin ( GPIOD,GPIO_2_Pin,GPIO_PIN_RESET);
		else 					HAL_GPIO_WritePin ( GPIOD,GPIO_2_Pin,GPIO_PIN_SET);
		//j=HAL_GPIO_ReadPin(GPIOD,GPIO_2_Pin);
		//printf("PD_1 = %d \r\n",j);
	}
	else if(Do==2)
	{
		if(Do_con==0) HAL_GPIO_WritePin ( GPIOD,GPIO_3_Pin,GPIO_PIN_RESET);
		else 					HAL_GPIO_WritePin ( GPIOD,GPIO_3_Pin,GPIO_PIN_SET);
		//j=HAL_GPIO_ReadPin(GPIOD,GPIO_3_Pin);
		//printf("PD_2 = %d \r\n",j);
	}
	else if(Do==3)
	{
		if(Do_con==0) HAL_GPIO_WritePin ( GPIOD,GPIO_4_Pin,GPIO_PIN_RESET);
		else 					HAL_GPIO_WritePin ( GPIOD,GPIO_4_Pin,GPIO_PIN_SET);
		//j=HAL_GPIO_ReadPin(GPIOD,GPIO_4_Pin);
		//printf("PD_3 = %d \r\n",j);
	}
}

/***************************************************************
	*函数名：Get_Gpio
	*输  入：无
	*说  明：获取GPIO口（PE 10、11、12、13）电平值，返回给主机
	*返回值：无
  **/
void Get_Gpio(void)
{
	char j=0;
	if(i==3)
	{
			j=HAL_GPIO_ReadPin(GPIOE ,GPIO_11_Pin );
			//printf("PE_GPIO_11 = %d \r\n",j);
			if(j==0)
			{
				char PE_BUFF[]="DI-3:0\r\n";
				HAL_UART_Transmit(&huart2, (uint8_t *)PE_BUFF,sizeof(PE_BUFF),100);
			}
			else if(j==1)
			{
				char PE_BUFF[10]="DI-3:1\r\n";	
				HAL_UART_Transmit(&huart2, (uint8_t *)PE_BUFF,sizeof(PE_BUFF),100);
			}
	}
	else if(i==2)
	{
			j=HAL_GPIO_ReadPin(GPIOE ,GPIO_10_Pin );
			//printf("PE_GPIO_10 = %d \r\n",j);
			if(j==0)
			{
				char PE_BUFF[10]="DI-2:0\r\n";
				HAL_UART_Transmit(&huart2, (uint8_t *)PE_BUFF,sizeof(PE_BUFF),100);
			}
			else if(j==1)
			{
				char PE_BUFF[10]="DI-2:1\r\n";	
				HAL_UART_Transmit(&huart2, (uint8_t *)PE_BUFF,sizeof(PE_BUFF),100);
			}
	}
	else if(i==1)
	{
			j=HAL_GPIO_ReadPin(GPIOE ,GPIO_9_Pin );
			//printf("PE_GPIO_9 = %d \r\n",j);
			if(j==0)
			{
				char PE_BUFF[10]="DI-1:0\r\n";
				HAL_UART_Transmit(&huart2, (uint8_t *)PE_BUFF,sizeof(PE_BUFF),100);
			}
			else if(j==1)
			{
				char PE_BUFF[10]="DI-1:1\r\n";	
				HAL_UART_Transmit(&huart2, (uint8_t *)PE_BUFF,sizeof(PE_BUFF),100);
			}
	}
	else if(i==0)
	{
			j=HAL_GPIO_ReadPin(GPIOE ,GPIO_8_Pin );
			//printf("PE_GPIO_8 = %d \r\n",j);
			if(j==0)
			{
				char PE_BUFF[10]="DI-0:0\r\n";
				HAL_UART_Transmit(&huart2, (uint8_t *)PE_BUFF,sizeof(PE_BUFF),100);
			}
			else if(j==1)
			{
				char PE_BUFF[10]="DI-0:1\r\n";	
				HAL_UART_Transmit(&huart2, (uint8_t *)PE_BUFF,sizeof(PE_BUFF),100);
			}
	}
	//printf("\r\n");
} 


/********************************File End****************************************/

