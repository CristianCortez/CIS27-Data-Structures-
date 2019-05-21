#include "MovementStack.h"


TStackPtr createPosStack(glm::vec3 positionTL, glm::vec3 positionBL,
	glm::vec3 positionBR, glm::vec3 positionTR) {
	TStackPtr newLvl;
	newLvl = (TStackPtr)malloc(sizeof(TStack));
	newLvl->block.ltop = positionTL;
	newLvl->block.lbottom = positionBL;
	newLvl->block.rbottom = positionBR;
	newLvl->block.rtop = positionTR;
	newLvl->next = NULL;
	return newLvl;
}
void push(TStackAddr* myStackAddr, TStackPtr newLvl) {
	if (*myStackAddr) {
		newLvl->next = *myStackAddr;
		(*myStackAddr) = newLvl;
	}
	else {
		*myStackAddr = newLvl;
	}
}
TStackPtr pop(TStackAddr* myStackAddr) {
	TStackPtr popped = NULL;
	if (*myStackAddr) {
		popped = *myStackAddr;
		*myStackAddr = (*myStackAddr)->next;
	}
	return popped;
}

void destroyStack(TStackAddr* byeNode) {
	//TStackPtr byeNode = pop(myStackAddr);	
	(*byeNode)->next = NULL;
	(*byeNode) = NULL;
	free(*byeNode);
}