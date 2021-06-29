/*                            Filename: Stack.c                              */
/*                                                                           */
/*   EXPORT: Procedure Push: Put a search tree node onto the stack           */
/*           Procedure Pop:  Delete a search tree node from the stack        */
/* ************************************************************************* */

#include <alloc.h>
#include "datastruct.h"
#include "table.h"
#include "list.h"
#include "stack.h"


/* ************************************************************************* */
/*                           Procedure  Push()                               */
/*                                                                           */
/*  INPUT : -/-                                                              */
/*                                                                           */
/*  FUNCTION: Put ActualNode onto the Stack                                  */
/* ************************************************************************* */

void Push ()
{
  struct StackElement *NewElement;

  NewElement = (struct StackElement *) malloc(sizeof(struct StackElement));
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

void Pop ()
{

  struct StackElement  *savestack;
  struct BlockList     *blockhelp, *saveblock;
  struct BranchList    *branchhelp, *savebranch;

  if (ActualNode != NIL) {        
     blockhelp = ActualNode->blocks;
     while ( blockhelp != NIL ) {
        saveblock = blockhelp;
        blockhelp->elements = Makeempty(blockhelp->elements);
        blockhelp = blockhelp->next;
        free((void *) saveblock);
     }
     branchhelp = ActualNode->order;
     while (branchhelp != NIL) {
        savebranch = branchhelp;
        branchhelp = branchhelp->next;
        free((void *) savebranch);
     }
     free((void *) ActualNode);
  }
  ActualNode = FirstOfStack->node;     
  savestack = FirstOfStack;
  FirstOfStack = FirstOfStack->next;
  free((void *) savestack);
}


