#include "stm32f0xx.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_can.h"
#include "stm32f0xx_misc.h"

void GPIOInit(void);
void CANInit(void);
void TransmitTrigger(void);
void display(int number);
void CEC_CAN_IRQHandler(void);
//void coolInitRoutine(int state);

static int i, z;
static int rev_high, rev_low, rev;


int main(void)
{

	SystemInit();
	GPIOInit();
	CANInit();

	SysTick_Config(SystemCoreClock/100); // 0,01s




    while(1)
    {








    }
}

void GPIOInit(void){

	GPIO_InitTypeDef GPIO_InitDef;

	// Ausgänge Schaltlichter
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

    GPIO_InitDef.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT; /*switched line with #31*/
    GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
    GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_DOWN; /*old: UP*/
    GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOB, &GPIO_InitDef);


	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    GPIO_InitDef.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT; /*switched line with #31*/
    GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
    GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_DOWN; /*old: UP*/
    GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitDef);
    // Ausgänge Schaltlichter Ende

    // Ausgänge 7 Segment
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,  ENABLE);

    GPIO_InitDef.GPIO_Pin =  GPIO_Pin_14 | GPIO_Pin_13;
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT; /*switched line with #31*/
    GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
    GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_DOWN; /*old: UP*/
    GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOC, &GPIO_InitDef);


    GPIO_InitDef.GPIO_Pin =  GPIO_Pin_15;
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
    GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitDef);

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

    GPIO_InitDef.GPIO_Pin =  GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
    GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOB, &GPIO_InitDef);

    // 7 Segment Ende

    // Can
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_4);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_4);

    GPIO_InitDef.GPIO_Pin =  GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOB, &GPIO_InitDef);
    // Can Ende


    // Digital In
    GPIO_InitDef.GPIO_Pin =  GPIO_Pin_15 | GPIO_Pin_14;
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
    GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOB, &GPIO_InitDef);
    // Digital In Ende


}

void CANInit(void){
	/*Initialisiert den CAN1
	 *Code wurde noch nie getestet
	 *Empfangsfilter fehlen noch*/


	NVIC_InitTypeDef  NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

	CAN_InitTypeDef CAN_InitStructure;


	CAN_DeInit(CAN1);
	CAN_StructInit(&CAN_InitStructure);

	CAN_InitStructure.CAN_Prescaler = 3;
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
	CAN_InitStructure.CAN_BS1 = CAN_BS1_10tq;
	CAN_InitStructure.CAN_BS2 = CAN_BS2_5tq;
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
	CAN_InitStructure.CAN_TTCM = DISABLE;
	CAN_InitStructure.CAN_ABOM = DISABLE;
	CAN_InitStructure.CAN_AWUM = DISABLE;
	CAN_InitStructure.CAN_NART = DISABLE;
	CAN_InitStructure.CAN_RFLM = DISABLE;
	CAN_InitStructure.CAN_TXFP = DISABLE;
	CAN_Init(CAN1, &CAN_InitStructure);





	CAN_FilterInitTypeDef CAN_FilterInitStructure;
	CAN_FilterInitStructure.CAN_FilterNumber = 0;
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x000;
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x000;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);

	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);


	NVIC_InitStructure.NVIC_IRQChannel = CEC_CAN_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}

void TransmitTrigger(void){

	CanTxMsg canMessage;

	canMessage.StdId = 0x600;
	canMessage.ExtId = 0;
	canMessage.RTR = CAN_RTR_DATA;
	canMessage.IDE = CAN_ID_STD;
	canMessage.DLC = 1;

	canMessage.Data[0] = 1;


 	CAN_Transmit(CAN1, &canMessage);

}

void display(int number){

	GPIO_ResetBits(GPIOB, GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6| GPIO_Pin_7);
	GPIO_ResetBits(GPIOA, GPIO_Pin_15);
	GPIO_ResetBits(GPIOC, GPIO_Pin_13 | GPIO_Pin_14);

	switch(number){

	case 0:
		GPIO_SetBits(GPIOB,  GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_3);
		break;

	case 1:
		GPIO_SetBits(GPIOB, GPIO_Pin_3);
		GPIO_SetBits(GPIOC, GPIO_Pin_14);
		break;

	case 2:
		GPIO_SetBits(GPIOB, GPIO_Pin_6| GPIO_Pin_5| GPIO_Pin_4);
		GPIO_SetBits(GPIOC, GPIO_Pin_13| GPIO_Pin_14);
		break;

	case 3:
		GPIO_SetBits(GPIOB, GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_6);
		GPIO_SetBits(GPIOC, GPIO_Pin_13| GPIO_Pin_14);
		break;

	case 4:
		GPIO_SetBits(GPIOB,GPIO_Pin_3 | GPIO_Pin_6| GPIO_Pin_7);
		GPIO_SetBits(GPIOC,GPIO_Pin_14);
		break;

	case 5:
		GPIO_SetBits(GPIOB, GPIO_Pin_6);

		break;







	}


}

void CEC_CAN_IRQHandler(void){



	CanRxMsg RxMessage;

	int gear, t_mot, t_oil;
//	int rev_high_new;

	CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);

	if( RxMessage.StdId == 0x777){
	gear = RxMessage.Data[0];
	display(gear);
	i=0;
	}

	if( RxMessage.StdId == 0x77B && RxMessage.Data[0]==3  ){

		GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_10 | GPIO_Pin_11);
		GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_6 );

		t_mot = RxMessage.Data[3] -40;




		if (t_mot >105){ // t_mot

			GPIO_SetBits(GPIOB, GPIO_Pin_10);
			//GPIO_SetBits(GPIOA, GPIO_Pin_7);
		}

		if (RxMessage.Data[6]& 1<<1){ // mittlerer Block = shLed2

			GPIO_SetBits(GPIOB, GPIO_Pin_1);
			GPIO_SetBits(GPIOA, GPIO_Pin_0);
		}

		if (RxMessage.Data[6]& 1<<2){ // oberer Block = shLed3

			GPIO_SetBits(GPIOB, GPIO_Pin_0);
			GPIO_SetBits(GPIOA, GPIO_Pin_6);
		}

		if (RxMessage.Data[6]& 1<<3){ // Blitz = shLed4

			GPIO_SetBits(GPIOB, GPIO_Pin_11);

		}

	}
//	if( RxMessage.StdId == 0x77B && RxMessage.Data[0]==2  ){


	//	GPIO_ResetBits(GPIOA,GPIO_Pin_7);

		//t_oil = RxMessage.Data[7] -40;




//		if (t_mot >115){ // t_oil


	//		GPIO_SetBits(GPIOA, GPIO_Pin_7);
		//}


//	}


/*	int z =0;
	while(z<7){


	if (rev_high & 1 << (7-z)){

		rev_high_new = rev_high_new | 1<<z;

	}
	else{
		rev_high_new = rev_high_new & 0<<z;
	}


	}

	rev = rev_high <<8 | rev_low;	//reiht beide Bits aneinander

	rev = rev*0.5;

	}*/

  }

void SysTick_Handler(void){
	i++;

/*	if (z<601){

		coolInitRoutine(z);
		z++;

	}
*/


	if (i>30 && z>600){	// Fragt ab ob das ECU noch an ist
		i=0;
		display(5);
		GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_10 | GPIO_Pin_11);
		GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_6 | GPIO_Pin_7);

	}

	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15) ==1 ){

		TransmitTrigger();
	}

	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) ==1 ){

		TransmitTrigger();
	}

/*
	if (rev<7900){

		GPIO_ResetBits(GPIOA, GPIO_Pin_0| GPIO_Pin_6| GPIO_Pin_7);
		GPIO_ResetBits(GPIOB, GPIO_Pin_0| GPIO_Pin_1| GPIO_Pin_10| GPIO_Pin_11);

	}

	if (rev>8000){

		GPIO_SetBits(GPIOA, GPIO_Pin_7);
		GPIO_SetBits(GPIOB, GPIO_Pin_10);

		GPIO_ResetBits(GPIOA, GPIO_Pin_6);
		GPIO_ResetBits(GPIOB, GPIO_Pin_1);
	}

	if (rev>9000){

		GPIO_SetBits(GPIOA, GPIO_Pin_6);
		GPIO_SetBits(GPIOB, GPIO_Pin_1);

		GPIO_ResetBits(GPIOA, GPIO_Pin_0);
		GPIO_ResetBits(GPIOB, GPIO_Pin_0);

	}

	if (rev>10000){

		GPIO_SetBits(GPIOA, GPIO_Pin_0);
		GPIO_SetBits(GPIOB, GPIO_Pin_0);

		GPIO_ResetBits(GPIOB, GPIO_Pin_11);

	}
	if (rev>11000){
		z++;
		GPIO_ResetBits(GPIOA, GPIO_Pin_0| GPIO_Pin_6| GPIO_Pin_7);
		GPIO_ResetBits(GPIOB, GPIO_Pin_0| GPIO_Pin_1| GPIO_Pin_10);

		GPIO_SetBits(GPIOB, GPIO_Pin_11);

	}
*/

}
/*
void coolInitRoutine(int state){
	int y;

	y = state;

	switch(y){

			case 0:
				GPIO_SetBits(GPIOA, GPIO_Pin_7);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);

				display(0);
				break;
			case 20:
				GPIO_SetBits(GPIOA, GPIO_Pin_6);
				GPIO_SetBits(GPIOB, GPIO_Pin_1);

				display(1);
				break;
			case 40:
				GPIO_SetBits(GPIOA, GPIO_Pin_0);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);

				display(2);
				break;
			case 60:


				display(3);
				break;
			case 80:
				GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_10 | GPIO_Pin_11);
				GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_6 | GPIO_Pin_7);

				display(4);
				break;
			case 100:
				GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_10 | GPIO_Pin_11);
				GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_6 | GPIO_Pin_7);

				display(5);
				break;
			case 120:
				GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_10 | GPIO_Pin_11);
				GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_6 | GPIO_Pin_7);


				break;
			}

}

*/

