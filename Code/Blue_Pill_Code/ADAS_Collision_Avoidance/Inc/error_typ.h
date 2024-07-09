#ifndef ERRTYPE_H_
#define ERRTYPE_H_

typedef enum{
	OK,
	NOK,
	NULL_POINTER
}ErrorState_t;

#define NULL                ((void*)0)
#define F_CPU				8000000 /* 8Mhz */

typedef void(*fptr_t)(void);


#endif
