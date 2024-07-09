#ifndef STM32F103XX_H
#define STM32F103XX_H


/***************************    various Memories Base Addresses    **********************/ 

#define FLASH_BASE_ADDRESS                 0x08000000UL
#define SRAM_BASE_ADDRESS                  0x20000000UL
#define ROM_BASE_ADDRESS                   0x1FFF0000UL


/*************************    CORE PERIPHERAL Base Addresses    ***********************/ 

#define SYSTICK_BASE_ADDRESS               0xE000E010UL

#define NVIC_BASE_ADDRESS                  0xE000E100UL

/*************************    AHB PERIPHERAL Base Addresses    ***********************/

#define RCC_BASE_ADDRESS                   0x40021000UL


/*************************    APB1 Peripheral Base Addresses    *************************/

#define TIMER2_u32_BASE_ADDRESS			   0x40000000UL
#define TIMER3_u32_BASE_ADDRESS			   0x40000400UL
#define TIMER4_u32_BASE_ADDRESS			   0x40000800UL

#define USART2_BASE_ADDRESS                0x40004400UL
#define USART3_BASE_ADDRESS                0x40004800UL

/**************************    APB2 Peripheral Base Addresses    **************************/

#define GPIOA_BASE_ADDRESS                 0x40010800UL
#define GPIOB_BASE_ADDRESS                 0x40010C00UL
#define GPIOC_BASE_ADDRESS                 0x40011000UL
#define GPIOD_BASE_ADDRESS                 0x40011400UL
#define GPIOE_BASE_ADDRESS                 0x40011800UL
#define GPIOF_BASE_ADDRESS                 0x40011C00UL
#define GPIOG_BASE_ADDRESS                 0x40012000UL

#define TIMER1_u32_BASE_ADDRESS			   0x40012C00UL

#define USART1_BASE_ADDRESS                0x40013800UL

/*************************   RCC Register Definition Structure    ***********************/

typedef struct
{
	volatile uint32_t   CR;                  /*RCC clock control register*/
	volatile uint32_t   CFGR;                /*RCC clock configuration register*/
	volatile uint32_t   CIR;                 /*RCC clock interrupt register*/
	volatile uint32_t   APB2RSTR;           /*RCC APB2 peripheral reset register*/
	volatile uint32_t   APB1RSTR;          /*RCC APB1 peripheral reset register*/
	volatile uint32_t   AHBENR;           /*RCC AHB peripheral clock register*/
	volatile uint32_t   APB2ENR;           /*RCC APB2 peripheral clock enable register*/
	volatile uint32_t   APB1ENR;           /*RCC APB1 peripheral clock enable register*/
	volatile uint32_t   BDCR;              /*RCC Backup domain control register*/
	volatile uint32_t   CSR;               /*RCC clock control & status register*/
}RCC_Reg_t;


/*************************   RCC Peripheral Definitions     ***************************/ 

#define RCC                              ((volatile RCC_Reg_t*)RCC_BASE_ADDRESS)

/**********************   GPIO Register Definition Structure    ***************************/ 


typedef struct
{
	volatile uint32_t GPIOx_CRL;
	volatile uint32_t GPIOx_CRH;
	volatile uint32_t GPIOx_IDR;
	volatile uint32_t GPIOx_ODR;
	volatile uint32_t GPIOx_BSRR;
	volatile uint32_t GPIOx_BRR;
	volatile uint32_t GPIOx_LCKR;
	volatile uint32_t AFIO_EVCR;
	volatile uint32_t AFIO_MAPR;
	volatile uint32_t AFIO_EXTICR1;
	volatile uint32_t AFIO_EXTICR2;
	volatile uint32_t AFIO_EXTICR3;
	volatile uint32_t AFIO_EXTICR4;
	volatile uint32_t AFIO_MAPR2;

}GPIO_RegDef_t;

/*************************   GPIO Peripheral Definitions     ***************************/ 

#define GPIOA         ((GPIO_RegDef_t*)GPIOA_BASE_ADDRESS)
#define GPIOB         ((GPIO_RegDef_t*)GPIOB_BASE_ADDRESS)
#define GPIOC         ((GPIO_RegDef_t*)GPIOC_BASE_ADDRESS)
#define GPIOD         ((GPIO_RegDef_t*)GPIOD_BASE_ADDRESS)
#define GPIOE         ((GPIO_RegDef_t*)GPIOE_BASE_ADDRESS)
#define GPIOF         ((GPIO_RegDef_t*)GPIOF_BASE_ADDRESS)
#define GPIOG         ((GPIO_RegDef_t*)GPIOG_BASE_ADDRESS)


/**********************   SYSTICK Register Definition Structure    ***************************/ 

typedef struct
{
	volatile uint32_t CSR;             /* SysTick control & status register */
	volatile uint32_t RVR;             /* SysTick reload value register */
	volatile uint32_t CVR;            /* SysTick current value register */
	volatile uint32_t CALIB;          /* SysTick calibration value register */
}SYSTICK_RegDef_t;

/*************************   SYSTICK Peripheral Definitions     ***************************/ 

#define SYSTICK            ((SYSTICK_RegDef_t *)SYSTICK_BASE_ADDRESS)

/**********************   NVIC Register Definition Structure    ***************************/ 

typedef struct
{
	volatile uint32_t ISER[8];
	volatile uint32_t Reserved_0[24];
	volatile uint32_t ICER[8];
	volatile uint32_t Reserved_1[24];
	volatile uint32_t ISPR[8];
	volatile uint32_t Reserved_2[24];
	volatile uint32_t ICPR[8];
	volatile uint32_t Reserved_3[24];
	volatile uint32_t IABR[8];
	volatile uint32_t Reserved_4[56];
	volatile uint32_t IPR[240];
	volatile uint32_t Reserved_5[643];
	volatile uint32_t STIR;
}NVIC_RegDef_t;

/*************************   NVIC Peripheral Definitions     ***************************/ 

#define  NVIC                ((NVIC_RegDef_t *)NVIC_BASE_ADDRESS)

/*************************   USART Register Definition Structure    ***********************/

typedef struct
{
	volatile uint32_t  SR;                 	 /*USART Status register*/
	volatile uint32_t  DR;            		 /*USART Data register*/
	volatile uint32_t  BRR;               	 /*USART Baud rate register*/
	volatile uint32_t  CR1;                	 /*USART Control register 1*/
	volatile uint32_t  CR2;           		 /*USART Control register 2*/
	volatile uint32_t  CR3;           		 /*USART Control register 3*/
	volatile uint32_t  GTPR;           		 /*USART Guard time and pre-scaler register*/


}USART_Reg_Def_t;

/*************************   USART Peripheral Definitions     ***************************/

#define USART_USART1                              ((USART_Reg_Def_t*)USART1_BASE_ADDRESS)
#define USART_USART2                              ((USART_Reg_Def_t*)USART2_BASE_ADDRESS)
#define USART_USART3                              ((USART_Reg_Def_t*)USART3_BASE_ADDRESS)

/*************************   GPT Register Definition Structure    ***********************/

typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	volatile uint32_t CCMR2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	volatile uint32_t :32;
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
	volatile uint32_t :32;
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
}GPT_RegDef_t;

/*************************   GPT Peripheral Definitions    ***********************/

#define TIMER2				((GPT_RegDef_t *)TIMER2_u32_BASE_ADDRESS)
#define TIMER3				((GPT_RegDef_t *)TIMER3_u32_BASE_ADDRESS)
#define TIMER4				((GPT_RegDef_t *)TIMER4_u32_BASE_ADDRESS)

/*************************   TIMER1 Register Definition Structure     ***************************/

typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	volatile uint32_t CCMR2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	volatile uint32_t RCR;
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
	volatile uint32_t BDTR;
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
}TIMER1_RegDef_t;

/*************************   TIMER1 Peripheral Definitions     ***************************/

#define TIMER1				((TIMER1_RegDef_t *)TIMER1_u32_BASE_ADDRESS)


#endif  /* STM32F103XX_H_*/













