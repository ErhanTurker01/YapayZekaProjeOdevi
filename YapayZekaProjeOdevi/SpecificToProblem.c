/* 
    These functions are compulsory for search algorithms but they are specific
    to problems. More clearly, you must must update their blocks but do not change
    their input and output parameters.
    
    Also, you can add new functions at the end of file by declaring them in GRAPH_SEARCH.h
*/

#include "GRAPH_SEARCH.h"
#include "data_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//______________________________________________________________________________
State* Create_State(void)
{
    State *state = (State*)malloc(sizeof(State));
    if(state==NULL)
        Warning_Memory_Allocation();
    printf("Select a point: ");
    printf("A, B, C...");
    printf("%c\n",'A' -1 + chessTableSize);
    printf("1, 2, 3...");
    printf("%d\n",chessTableSize);
    printf("Selection: ");
    scanf("%s",&state->posStr);
    if ((state->pos_x == 'X' || state->pos_x == 'x') && state->pos_y[0] == '\0') {
        free(state);
        return NULL;
    }
    if (state->pos_x <= 'z' && state->pos_x >= 'a') state->pos_x += 'A' - 'a';
    if (state->pos_x > 'Z' || state->pos_x < 'A') {
        printf("NOT A VALID STATE!");
        exit(-1);        
    }
    if (state->pos_y[0] > '9' || state->pos_y[0] < '0') {
        printf("NOT A VALID STATE!");
        exit(-1);
    }
    if ((state->pos_y[1] > '9' || state->pos_y[1] < '0') && state->pos_y[1] != '\0') {
        printf("NOT A VALID STATE!");
        exit(-1);
    }
    if (state->pos_y[0] == 0 && state->pos_y[1] == 0) {
        printf("NOT A VALID STATE!");
        exit(-1);
    }
    if(state->pos_y[1] == '\0'){
        state->pos_y_int = state->pos_y[0] - '0';
        state->pos_y[1] = state->pos_y[0];
        state->pos_y[0] = '0';
    }
    else{
        state->pos_y_int = (state->pos_y[0] - '0') * 10 + state->pos_y[1] - '0';
    }
    state->h_n = 0;
    state->nullChar = '\0';
    return state;
}

//______________________________________________________________________________
void Print_State(const State *const state)
{
    printf("%s",state->posStr);
}

//______________________________________________________________________________
void Print_Action(const enum ACTIONS action)
{
   switch(action){
         case  Move1d2l:        printf("Knight jumps 1 down 2 left"); break;
         case  Move1d2r:        printf("Knight jumps 1 down 2 right"); break;
         case  Move1u2l:        printf("Knight jumps 1 up 2 left"); break;
         case  Move1u2r:        printf("Knight jumps 1 up 2 right"); break;
         case  Move2d1l:        printf("Knight jumps 2 down 1 left"); break;
         case  Move2d1r:        printf("Knight jumps 2 down 1 right"); break;
         case  Move2u1l:        printf("Knight jumps 2 up 1 left"); break;
         case  Move2u1r:        printf("Knight jumps 2 up 1 right"); break;
    }
}

//______________________________________________________________________________
int Result(const State *const parent_state, const enum ACTIONS action, Transition_Model *const trans_model)
{
    State new_state;
    int action_x;
    int action_y;
    switch(action){
        case  Move1d2l:        action_y = -1; action_x = -2; break;
        case  Move1d2r:        action_y = -1; action_x = 2; break;
        case  Move1u2l:        action_y = 1; action_x = -2; break;
        case  Move1u2r:        action_y = 1; action_x = 2; break;
        case  Move2d1l:        action_y = -2; action_x = -1; break;
        case  Move2d1r:        action_y = -2; action_x = 1; break;
        case  Move2u1l:        action_y = 2; action_x = -1; break;
        case  Move2u1r:        action_y = 2; action_x = 1; break;
     }
    if (parent_state->pos_x+action_x < 'A' || parent_state->pos_x+action_x > 'A' - 1 + chessTableSize) {
        return FALSE;
    }
    if(parent_state->pos_y_int+action_y < 1 || parent_state->pos_y_int+action_y > chessTableSize){
        return FALSE;
    }
    for (int i=0; i < sizeOfRestrictedKeys; i++) {
        if(!strcmp(restrictedKeys[i], parent_state->posStr)) return FALSE;
    }
    new_state.pos_x = parent_state->pos_x + action_x;
    new_state.pos_y_int = parent_state->pos_y_int + action_y;
    new_state.pos_y[0] = new_state.pos_y_int/10 + '0';
    new_state.pos_y[1] = new_state.pos_y_int%10 + '0';
    new_state.nullChar = '\0';
    trans_model->new_state = new_state;
    trans_model->step_cost = 1;
    return TRUE;
}

//______________________________________________________________________________
float Compute_Heuristic_Function(const State *const state, const State *const goal)
{
    return (abs(state->pos_x - goal->pos_x) + abs(state->pos_y_int - goal->pos_y_int))/3;
}

//_______________ Update if your goal state is not determined initially ___________________________________
int Goal_Test(const State *const state, const State *const goal_state)
{
	if(PREDETERMINED_GOAL_STATE)	
		return Compare_States(state, goal_state); 
	else
		return 1;
}

// ==================== WRITE YOUR OPTIONAL FUNCTIONS (IF REQUIRED) ==========================
