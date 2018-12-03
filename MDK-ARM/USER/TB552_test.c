/**********************************************************************************
File��
     1������ͨ������2�����ַ��������ƴӻ����GPIO�ڣ�PD 0��1��14��15���ĵ�ƽֵ��
     2������ͨ������2��ȡGPIO�ڣ�PE 10��11��12��13����ƽֵ��
**********************************************************************************/
#include "tb552_test.h"

char  U2_BUFF[10];
char  i=0;
char  Do=0;
char  Do_con=0;

//int   data_len=0;

/***************************************************************
	*��������comm
	*��  �룺��
	*˵  ����File �߼�����
	*����ֵ����
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
	*��������Data_Turn
	*��  �룺��
	*˵  �������մ��ڵ�״̬��������
	*����ֵ����
  **/
void Data_Turn(void)
{

  if(recv_end_flag ==1)		
  {
      //printf("rx_len=%d\r\n",rx_len);											//��ӡ���ճ���
      //HAL_UART_Transmit(&huart2,rx_buffer, rx_len,200);		//�������ݴ�ӡ����
      for(uint8_t i=0;i<rx_len;i++)
      {
         rx_buffer[i]=0;//����ջ���
      }
      rx_len=0;//�������
      recv_end_flag=0;//������ս�����־λ
   }
   HAL_UART_Receive_DMA(&huart2,rx_buffer,BUFFER_SIZE);			//���´�DMA����     

/*
	HAL_UART_Receive_IT(&huart2,(uint8_t *)U2_BUFF,6);//�����ж�Ҫ���͹�6���ַ����Żᴥ��
	HAL_Delay(50);
	data_len=strlen(U2_BUFF);		//��ȡ�ַ�������
	printf("Len = %d \r\n",data_len);
	printf("U2_BUFF[1] = %d \r\n",U2_BUFF[1]);*/
	
  HAL_Delay(100);
	
	if( 73==rx_buffer[1] || 105==rx_buffer[1] ) 					//����ASCII���ж���Ҫ����ж�PE�˿ڲ���
	{
		i=(char)(rx_buffer[3]-48);
	  //printf("Read DI_%d \r\n",i);
		Get_Gpio(); 
	}
	else if( 79==rx_buffer[1] || 111==rx_buffer[1] )			//����ASCII���ж���Ҫ����ж�PD�˿ڲ���
	{
		Do=(char)(rx_buffer[3]-48);
		Do_con=(char)(rx_buffer[5]-48);
	  //printf("Control  DO_%d:%d \r\n",Do,Do_con);
		Cont_Gpio();
	}
	
 /*	������0	*/
	i=0;
	memset(&U2_BUFF,0,10);
//data_len=0;	
}

/***************************************************************
	*��������Cont_Gpio
	*��  �룺��
	*˵  �����������GPIO�ڣ�PD 0��1��14��15���ĵ�ƽֵ
	*����ֵ����
  **/
void Cont_Gpio(void)
{
	//char j=0;
	
	if(Do==0)
	{
		if(Do_con==0) HAL_GPIO_WritePin ( GPIOD,GPIO_1_Pin,GPIO_PIN_RESET);
		else 					HAL_GPIO_WritePin ( GPIOD,GPIO_1_Pin,GPIO_PIN_SET);
		//j=HAL_GPIO_ReadPin(GPIOD,GPIO_1_Pin);			//�������ŵ�д��ת̬�����ڲ�����
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
	*��������Get_Gpio
	*��  �룺��
	*˵  ������ȡGPIO�ڣ�PE 10��11��12��13����ƽֵ�����ظ�����
	*����ֵ����
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

