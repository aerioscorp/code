/*
 * @file ApollonSwitcher.c
 * @brief TODO
 * @author Sami
 * @date 17/11/17.
 * @version 1.0
 */

#include "ApollonSwitcher.h"

//TODO
static const SLEEPING_TIME = 1000;

//TODO
static int apollonUV, apollonBrightness;





/* Generates the states of the state-machine */
#define STATE_GENERATION S(S_FORGET) S(S_INIT) S(S_SLEEPING)                  //TODO
#define S(x) x,
typedef enum {STATE_GENERATION STATE_NB} state_e;
#undef S
#define S(x) #x,
const char * const stateName[] = { STATE_GENERATION };
#undef STATE_GENERATION
#undef S

/* Generates the events of the state-machine */
#define EVENT_GENERATION S(E_START) S(E_STOP)                                   //TODO
#define S(x) x,
typedef enum {EVENT_GENERATION EVENT_NB}  event_e;
#undef S
#define S(x) #x,
const char * const eventName[] = { EVENT_GENERATION };
#undef EVENT_GENERATION
#undef S

/* Generates the actions of the state-machine */
#define ACTION_GENERATION S(A_START) S(A_STOP) S(A_COMMUNICATE)                 //TODO
#define S(x) x,
typedef enum {ACTION_GENERATION ACTION_NB}  action_e;
#undef S
#define S(x) #x,
const char * const actionName[] = { ACTION_GENERATION };
#undef ACTION_GENERATION
#undef S

/**
* @typedef mqEventMsg_s
* @struct mqEventMsg_s  message format of the state machine message queue.
*/
typedef struct
{
    event_e event;
} mqEventMsg_s;

/**
 * @typedef mqEventMsgAdapter_u
 * @union mqEventMsgAdapter_u  message adapter of the
 *                                    state-machine message queue.
 */
typedef union
{
    char buffer[256];
    mqEventMsg_s data;
} mqEventMsgAdapter_u;

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
static void* switcherRun();
static mqEventMsg_s postmanStateReceive();
static void postmanStateSend (mqEventMsg_s aMsg);
//TODO Prototype des méthodes-actions de la MAE

/**
 * @brief state of the postmanMC
 */
static state_e switcherState;

/*
 * Configuration parameter of message queues
 */
#define NAME_MQ_BOX_STATEMACHINE  "/switcherStateMachine"

/**
 * @brief threads used in the postmanMC
 */
static pthread_t stateMachineThread;




/* Action pointer array */
typedef void (*actionPtr)();
static const actionPtr actionTab[ACTION_NB] = {&actionStartServer, &actionStopServer, &actionCommunicate}; //TODO


/** Transitions of the state-machine */
static transition_s mySm [STATE_NB_POSTMAN][EVENT_NB_POSTMAN] =
        {
                [S_IDLE][E_START]= {S_CONNECTION,A_START},
                [S_CONNECTION][E_CONNECTION_ACCEPTED]= {S_COMMUNICATION,A_COMMUNICATE},                     //TODO
                [S_COMMUNICATION][E_DISCONNECT]= {S_CONNECTION,A_DISCONNECT},
                [S_COMMUNICATION][E_STOP]={S_DEATH,A_SHUTDOWN},
                [S_CONNECTION][E_STOP]={S_DEATH,A_STOP}
        };

//TODO A Utiliser pour tester puis à supprimer
/*
static const char * actionGetName(int i)
{
    return actionName[i];
}

static const char * eventGetName(int i)
{
    return eventName[i];
}

static const char * stateGetName(int i)
{
    return stateName[i];
}
*/



/**
 * See ApollonSwitcher.h
 */
extern void switcherInit()
{
    //TODO

    //TODO Lancer le thread switcherRUn()
}

/**
 * See ApollonSwitcher.h
 */
extern void switcherDestroy()
{
    //TODO
}

/**
 * See ApollonSwitcher.h
 */
extern void setUV(int UV)
{
    apollonUV = UV;
}

/**
 * See ApollonSwitcher.h
 */
extern void setBrightness(int brightness)
{
    apollonBrightness = brightness;
}






/**
 * @function static void reorganize()
 * @brief organizes the data to be "ready to send"
 */
static void reorganize()
{
    //TODO
}

/**
 * @function static void* switcherRun()
 * @brief manages the state-machine of switcherApollon
 *
 * This method is a thread created by switcherInit()
 *
 * @return void*
 */
static void switcherRun()
{
    mqEventMsg_s msg;
    action_e act;
   // printf("postman MAE started@n");
    while (postmanState != S_DEATH)
    {
        msg = postmanStateReceive();
        if (mySm[postmanState][msg.event].destinationState != S_FORGET)
        {
           // printf("[POSTMAN] Evenement %s@n", stateGetName(msg.event));          //TODO Enlever les commentaires
           // printf("[POSTMAN] En changement @n");
            act = mySm[postmanState][msg.event].action;
           // printf("[POSTMAN] Action %s@n", actionGetName(act));
            postmanState = mySm[postmanState][msg.event].destinationState;
            //printf("[POSTMAN] changement état %s@n", stateGetName(postmanState));
            actionTabPostman[act]();
        }
    }
    return (0);
}

/**
 * @function static mqEventMsg_s switcherStateReceive ()
 * @brief receives the state sent
 *
 * This method is called by switcherRun()
 *
 * @return the state received
 */
static mqEventMsg_s switcherStateReceive()
{
    int check;
    mqd_t mq;
    mqEventMsgAdapter_u msg;
    mq = mq_open(NAME_MQ_BOX_STATEMACHINE, O_RDONLY);
    assert(mq != -1);
    check = mq_receive(mq, msg.buffer, MQ_MSG_SIZE, 0);
    check = mq_close(mq);
    assert(check == 0);
    return msg.data;
}

/**
 * @function static void switcherStateSend (mqEventMsg_s aMsg)
 * @brief send a state to the state-machine
 *
 * This method is called by the events
 *
 * @param [in] aMsg  the state to send
 */
static void switcherStateSend(mqEventMsg_s aMsg)
{
    int check;
    mqEventMsgAdapter_u msg;
    mqd_t mq;
    msg.data = aMsg;
    mq = mq_open(NAME_MQ_BOX_STATEMACHINE, O_WRONLY);
    assert(mq != -1);
    check = mq_send(mq, msg.buffer, sizeof (msg.buffer), 0);
    assert(check == 0);
    check = mq_close(mq);
    assert(check == 0);
}

/*TODO Ajouter les actions et (appel d'evenement ?)
 * (si pas d'appel d'evenement : supprimer switcherStateSend et switcherStateReceive + BAL */