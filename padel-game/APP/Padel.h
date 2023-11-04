 


#ifndef PADEL_H_
#define PADEL_H_

typedef enum {
	BL_UP,
	BL_DOWN,
	BR_UP,
	BR_DOWN,
	NOT_PRESSED
	}BUTTON_STATUS_t;

void Padel_Init(void);

void Padel_Runnable(void);

void winner_dis(void);

void reset_game(void);

BUTTON_STATUS_t Get_R_Button(void);

BUTTON_STATUS_t Get_L_Button(void);



#define PUZ PINC6

#define HEART  2

#define HAMOKSHA 1

#endif /* PADEL_H_ */