/* ************************************************************************* */
/*                            Filename: Stack.c                              */
/*                                                                           */
/*   EXPORT: Procedure Push: Put a search tree node onto the stack           */
/*           Procedure Pop:  Delete a search tree node from the stack        */
/* ************************************************************************* */
#include <cstdlib>

#include "datastruct.hpp"
#include "table.hpp"
#include "list.hpp"
#include "stack.hpp"

/* ************************************************************************* */
/*                           Procedure  Push()                               */
/*                                                                           */
/*  INPUT : -/-                                                              */
/*                                                                           */
/*  FUNCTION: Put ActualNode onto the Stack                                  */
/* ************************************************************************* */
void Push() {
  StackElement *NewElement;
  NewElement = (StackElement *) malloc(sizeof(StackElement));
  NewElement->next = FirstOfStack;
  NewElement->node = ActualNode;
  FirstOfStack = NewElement;
  ActualNode = NIL;
}

/* ************************************************************************* */
/*                           Procedure  Pop()                                */
/*                                                                           */
/*  INPUT : -/-                                                              */
/*                                                                           */
/*  FUNCTION: Delete ActualNode and assign the top of the stack to           */
/*            ActualNode                                                     */
/* ************************************************************************* */
void Pop() {
  StackElement *savestack;
  BlockList *blockhelp, *saveblock;
  BranchList *branchhelp, *savebranch;
  if (ActualNode != NIL) {
    blockhelp = ActualNode->blocks;
    while (blockhelp != NIL) {
      saveblock = blockhelp;
      blockhelp->elements = Makeempty(blockhelp->elements);
      blockhelp = blockhelp->next;
      free((void *) saveblock);
    } branchhelp = ActualNode->order;
    while (branchhelp != NIL) {
      savebranch = branchhelp;
      branchhelp = branchhelp->next;
      free((void *) savebranch);
    } free((void *) ActualNode);
  }
  ActualNode = FirstOfStack->node;
  savestack = FirstOfStack;
  FirstOfStack = FirstOfStack->next;
  free((void *) savestack);
}
