/*
 * @file ApollonSwitcher.c
 * @brief TODO
 * @author Sami KOUATLI
 * @date 17/11/17.
 * @version 1.0
 */

#include "ApollonSwitcher.h"

static uint8_t apollonUV;
static uint32_t apollonBrightness;

/* Generates the states of the state-machine */
#define STATE_GENERATION S(S_FORGET) S(S_IDLE) S(S_INIT) S(S_COLLECT) S(S_SEND) S(S_SLEEP)
#define S(x) x,
typedef enum {STATE_GENERATION STATE_NB} state_e;
#undef S
#define S(x) #x,
const char * const stateName[] = { STATE_GENERATION };
#undef STATE_GENERATION
#undef S


/* Generates the actions of the state-machine */
#define ACTION_GENERATION S(A_START) S(A_COLLECT) S(A_SEND) S(A_SLEEP)
#define S(x) x,
typedef enum {ACTION_GENERATION ACTION_NB}  action_e;
#undef S
#define S(x) #x,
const char * const actionName[] = { ACTION_GENERATION };
#undef ACTION_GENERATION
#undef S

/**
 * @typedef transition_s
 * @struct transition_s  makes an action match a destination
 *                          state in the state machine.
 */
typedef struct
{
    state_e destinationState;
    action_e action;
} transition_s;


/* Function prototypes */
static void reorganize();
static void switcherRun();
static void actionStart();
static void actionCollect();
static void actionSend();
static void actionSleep();

/**
 * @brief state of the switcher
 */
static state_e switcherState;



/* Action pointer array */
typedef void (*actionPtr)();
static const actionPtr actionTab[ACTION_NB] = {&actionStart, &actionCollect, &actionSend, &actionSleep};


/** Transitions of the state-machine */
static transition_s mySm [STATE_NB_POSTMAN] =
        {
                [S_IDLE] = {S_INIT, A_START},
                [S_INIT] = {S_COLLECT,A_COLLECT},
                [S_COLLECT] = {S_SEND,A_SEND},
                [S_SEND] ={S_SLEEP,A_SLEEP},
                [S_SLEEP]={S_COLLECT,A_COLLECT}
        };

/**
 * See ApollonSwitcher.h
 */
extern void switcherInit()
{
    switcherState = S_IDLE;
    switcherRun();
}

/**
 * See ApollonSwitcher.h
 */
extern void switcherDestroy()
{
    reanimatorDestroy();
    switcherState = S_DEATH;
}

/**
 * See ApollonSwitcher.h
 */
extern void setUV(uint8_t UV)
{
    apollonUV = UV;
}

/**
 * See ApollonSwitcher.h
 */
extern void setBrightness(uint32_t brightness)
{
    apollonBrightness = brightness;
}

/**
 * See ApollonSwitcher.h
 */
extern uint32_t getBrightness(){
    return apollonBrightness;
}

/**
 * See ApollonSwitcher.h
 */
extern uint8_t getUV(){
    return apollonUV;
}




/**
 * @function static void switcherRun()
 * @brief manages the state-machine of switcherApollon
 *
 * @return void
 */
static void switcherRun()
{
    action_e act;
    while (switcherState != S_DEATH)
    {
        if (mySm[switcherState].destinationState != S_FORGET)
        {
            act = mySm[postmanState].action;
            postmanState = mySm[postmanState].destinationState;
            actionTabPostman[act]();
        }
    }
    return (0);
}

/**
 * @function static void actionStart()
 * @brief action A_START oof the state-machine
 *
 * @return void
 */
void actionStart(){
    reanimatorInit();
    dataSenderInit();
}

/**
 * @function static void actionCollect()
 * @brief action A_COLLECT oof the state-machine
 *
 * @return void
 */
void actionCollect(){
    launchCollector();
}

/**
 * @function static void actionSend()
 * @brief action A_SEND oof the state-machine
 *
 * @return void
 */
void actionSend(){
    sendData();
}

/**
 * @function static void actionSleep()
 * @brief action A_SLEEP oof the state-machine
 *
 * @return void
 */
void actionSleep(){
    putSleepMode();
    putActiveMode();
}