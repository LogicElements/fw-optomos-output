/*
 * opm.c
 *
 *  Created on: 22. 2. 2024
 *      Author: hp
 */

/* Includes ------------------------------------------------------------------*/
#include "opm.h"
#include "reg_map.h"
#include "configuration.h"


/* Private defines -----------------------------------------------------------*/
#define OPM_CH1_PORT GPIOB
#define OPM_CH1_PIN GPIO_PIN_10
#define OPM_CH2_PORT GPIOB
#define OPM_CH2_PIN GPIO_PIN_2
#define OPM_CH3_PORT GPIOB
#define OPM_CH3_PIN GPIO_PIN_1
#define OPM_CH4_PORT GPIOB
#define OPM_CH4_PIN GPIO_PIN_0
#define OPM_CH5_PORT GPIOA
#define OPM_CH5_PIN GPIO_PIN_7
#define OPM_CH6_PORT GPIOA
#define OPM_CH6_PIN GPIO_PIN_6
#define OPM_CH7_PORT GPIOA
#define OPM_CH7_PIN GPIO_PIN_5
#define OPM_CH8_PORT GPIOA
#define OPM_CH8_PIN GPIO_PIN_4

#define OPM_CH9_PORT GPIOB
#define OPM_CH9_PIN GPIO_PIN_9
#define OPM_CH10_PORT GPIOB
#define OPM_CH10_PIN GPIO_PIN_8
#define OPM_CH11_PORT GPIOB
#define OPM_CH11_PIN GPIO_PIN_7
#define OPM_CH12_PORT GPIOB
#define OPM_CH12_PIN GPIO_PIN_6
#define OPM_CH13_PORT GPIOB
#define OPM_CH13_PIN GPIO_PIN_5
#define OPM_CH14_PORT GPIOB
#define OPM_CH14_PIN GPIO_PIN_4
#define OPM_CH15_PORT GPIOB
#define OPM_CH15_PIN GPIO_PIN_3
#define OPM_CH16_PORT GPIOA
#define OPM_CH16_PIN GPIO_PIN_12

GPIO_TypeDef* opm_ch_port[]={OPM_CH1_PORT,OPM_CH2_PORT,OPM_CH3_PORT,OPM_CH4_PORT,OPM_CH5_PORT,OPM_CH6_PORT,OPM_CH7_PORT,OPM_CH8_PORT,OPM_CH9_PORT,OPM_CH10_PORT,OPM_CH11_PORT,OPM_CH12_PORT,OPM_CH13_PORT,OPM_CH14_PORT,OPM_CH15_PORT,OPM_CH16_PORT};
uint16_t opm_ch_pin[]={OPM_CH1_PIN,OPM_CH2_PIN,OPM_CH3_PIN,OPM_CH4_PIN,OPM_CH5_PIN,OPM_CH6_PIN,OPM_CH7_PIN,OPM_CH8_PIN,OPM_CH9_PIN,OPM_CH10_PIN,OPM_CH11_PIN,OPM_CH12_PIN,OPM_CH13_PIN,OPM_CH14_PIN,OPM_CH15_PIN,OPM_CH16_PIN};



//1-16CH

Status_t OPM_Init(void)
{
	Status_t ret=STATUS_OK;
	GPIO_InitTypeDef GPIO_InitStruct={0};

	GPIO_InitStruct.Pin=OPM_CH1_PIN;
	GPIO_InitStruct.Mode=GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull=GPIO_NOPULL;
	HAL_GPIO_Init(OPM_CH1_PORT,&GPIO_InitStruct);

	GPIO_InitStruct.Pin=OPM_CH2_PIN;
	HAL_GPIO_Init(OPM_CH2_PORT,&GPIO_InitStruct);

	GPIO_InitStruct.Pin=OPM_CH3_PIN;
	HAL_GPIO_Init(OPM_CH3_PORT,&GPIO_InitStruct);

	GPIO_InitStruct.Pin=OPM_CH4_PIN;
	HAL_GPIO_Init(OPM_CH4_PORT,&GPIO_InitStruct);

	GPIO_InitStruct.Pin=OPM_CH5_PIN;
	HAL_GPIO_Init(OPM_CH5_PORT,&GPIO_InitStruct);

	GPIO_InitStruct.Pin=OPM_CH6_PIN;
	HAL_GPIO_Init(OPM_CH6_PORT,&GPIO_InitStruct);

	GPIO_InitStruct.Pin=OPM_CH7_PIN;
	HAL_GPIO_Init(OPM_CH7_PORT,&GPIO_InitStruct);

	GPIO_InitStruct.Pin=OPM_CH8_PIN;
	HAL_GPIO_Init(OPM_CH8_PORT,&GPIO_InitStruct);

	GPIO_InitStruct.Pin=OPM_CH9_PIN;
	HAL_GPIO_Init(OPM_CH9_PORT,&GPIO_InitStruct);

	GPIO_InitStruct.Pin=OPM_CH10_PIN;
	HAL_GPIO_Init(OPM_CH10_PORT,&GPIO_InitStruct);

	GPIO_InitStruct.Pin=OPM_CH11_PIN;
	HAL_GPIO_Init(OPM_CH11_PORT,&GPIO_InitStruct);

	GPIO_InitStruct.Pin=OPM_CH12_PIN;
	HAL_GPIO_Init(OPM_CH12_PORT,&GPIO_InitStruct);

	GPIO_InitStruct.Pin=OPM_CH13_PIN;
	HAL_GPIO_Init(OPM_CH13_PORT,&GPIO_InitStruct);

	GPIO_InitStruct.Pin=OPM_CH14_PIN;
	HAL_GPIO_Init(OPM_CH14_PORT,&GPIO_InitStruct);

	GPIO_InitStruct.Pin=OPM_CH15_PIN;
	HAL_GPIO_Init(OPM_CH15_PORT,&GPIO_InitStruct);

	GPIO_InitStruct.Pin=OPM_CH16_PIN;
	HAL_GPIO_Init(OPM_CH16_PORT,&GPIO_InitStruct);

	OPM_Def_State(); //seting Outputs to def. state

	return ret;
}

Status_t OPM_Handler(void)
{
	Status_t ret = STATUS_OK;


	OPM_State();
	OPM_Set();
	OPM_Clear();

	return ret;

}

Status_t OPM_State(void)
{
	Status_t ret = STATUS_OK;
	uint16_t state=0;
	for(uint8_t i=0;i<16;i++)
	{
		state |= (HAL_GPIO_ReadPin(opm_ch_port[i],opm_ch_pin[i]))<<i;
	}
	conf.out.state=state;
	return ret;
}

Status_t OPM_Set(void)
{
	Status_t ret = STATUS_OK;
	for(uint8_t i=0;i<16;i++)
	{
		if(((conf.out.set>>i)&0x01)&1)
		{
		HAL_GPIO_WritePin(opm_ch_port[i],opm_ch_pin[i],1);
		}
	}
	conf.out.set=0;
	return ret;
}

Status_t OPM_Clear(void)
{
	Status_t ret = STATUS_OK;

	for(uint8_t i=0;i<16;i++)
	{
		if(((conf.out.clear>>i)&0x01)&1)
		{
		HAL_GPIO_WritePin(opm_ch_port[i],opm_ch_pin[i],0);
		}
	}
	conf.out.clear=0;
	return ret;
}

Status_t OPM_Def_State(void)
{
	Status_t ret = STATUS_OK;
	for(uint8_t i=0;i<16;i++)
	{
		if(((conf.out.default_state>>i)&0x01)&1)
		{
		HAL_GPIO_WritePin(opm_ch_port[i],opm_ch_pin[i],1);
		}
	}
	return ret;
}


