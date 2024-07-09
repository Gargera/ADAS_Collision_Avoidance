#ifndef GPT_PRIVATE_H_
#define GPT_PRIVATE_H_

/************************TIMx_CCMR1 register bits******************************/
#define ARPE	7
#define DIR     4
#define UDIS    1
#define CEN 	0
/**********************TIMx_CCMR1 register bits*********************************/
#define CC1S 	0
#define IC1PSC 	2
#define IC1F	4
#define CC2S	8
#define CC2S_MSK
#define IC2PSC	10
#define IC2F	12

/**********************TIMx_CCMR2 register bits*********************************/
#define CC3S 	0
#define IC3PSC 	2
#define IC3F	4
#define CC4S	8
#define IC4PSC	10
#define IC4F	12

/*********************TIMC_CCER register bits**********************************/
#define	CC1E 0
#define CC1P 1
#define CC1P_MSK 0x02
#define CC2E 4
#define CC2P 5
#define CC2P_MSK 0x20
#define	CC3E 8
#define CC3P 9
#define CC3P_MSK 0x200
#define CC4E 12
#define CC4P 13
#define CC4P_MSK 0x2000

#endif /* GPT_PRIVATE_H_ */
