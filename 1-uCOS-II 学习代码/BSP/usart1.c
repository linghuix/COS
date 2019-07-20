/**
  ******************************************************************************
  * @file    delay.c
  * @author  Linghui Xu
  * @version V1.0
  * @date    2019.4.27
  * @brief   ��3.5.0�汾�⽨�Ĺ���ģ��
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
	

#include "usart1.h"
#include <stdarg.h>

/**
  * @brief  ����1���ж�����
  * @param  None
  * @retval None
  */
void USART1_NVIC_Configuration(void){

    NVIC_InitTypeDef NVIC_InitStructure;

    /*����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	

    /*TIM3�ж�*/
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; 

    /*��ռ���ȼ�0��*/	
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 

    /*�����ȼ�3��*/	
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; 

    /*IRQͨ����ʹ��*/	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 

    /*����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���*/
    NVIC_Init(&NVIC_InitStructure);  
}


/**
  * @brief  USART1 GPIO ����,����ģʽ���á�115200 8-N-1
  * @param  None
  * @retval None
  */
void USART1_Config(void){
    
    USART_InitTypeDef USART_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    /* ����1����ģʽ��USART1 mode������ */
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART1, &USART_InitStructure); 

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                  //���������ж�

    USART_Cmd(USART1, ENABLE);                                      //ʹ�ܴ���

    //USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);                  //USART1��DMA����Tx���󣬴�ʱCPU�ǿ��е�,,��������������
}


/**
  * @brief  �ض���c�⺯��printf��USART1,��printf����
  * @param  None
  * @retval None
  */
int fputc(int ch, FILE *f){
    
    USART_SendData(USART1, (unsigned char) ch);                     /* ��Printf���ݷ������� */
    while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);
    return (ch);
}


/**
  * @brief  ���ض���c�⺯��scanf��USART1, ��scanf����
  * @param  None
  * @retval None
  */
int fgetc(FILE *f){

    while( USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == RESET);     //�ȴ�������������
    return (int) USART_ReceiveData(USART1);
}
