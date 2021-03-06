/* ************************************************************************* */
/*                           Filename: HeadTail.c                            */
/*                                                                           */
/*  Export: Procedure Compute_ Compute_Head_Tail:                            */
/*                    Calculation of heads and tail based on fixed           */
/*                    disjunctions.                                          */
/* ************************************************************************* */


#include "datastruct.h"
#include "table.h"
#include "list.h"
#include "sort.h"
#include "headtail.h"



static void Compute_Head(ActualOp)	int ActualOp;
{

  register struct List  *help;
  int op_array[MaxOpProMachine+1];
  register int i, max = 0, num, new;

  help = ConjArcs->pred[ActualOp]; 
  while (help != NIL) {
     if ((new = OpData[help->number].process_time + head[help->number]) > max)
        max = new;
     help = help->next;
  }
  help = DisjArcs->pred[ActualOp]; 
  if (help != NIL) {
     num = 0;
     while (help != NIL) {
        op_array[++num] = help->number;
        help = help->next;
     }
     Sort(head, op_array, num);
     new = head[op_array[1]] + OpData[op_array[1]].process_time;
     for (i = 2; i <= num; ++i) {
        new = (new < head[op_array[i]])? head[op_array[i]] : new;
        new += OpData[op_array[i]].process_time;
     }
  }
  head[ActualOp] = (max < new)? new : max;
}



static void Compute_Tail(ActualOp)	int ActualOp;
{

  register struct List  *help;
  int op_array[MaxOpProMachine+1];
  register int i, max = 0, num, new;

  help = ConjArcs->succ[ActualOp];
  while (help != NIL) {
     if ((new = OpData[help->number].process_time + tail[help->number]) > max)
        max = new;
     help = help->next;
  }
  help = DisjArcs->succ[ActualOp];
  if (help != NIL) {
     num = 0;
     while (help != NIL) {
        op_array[++num] = help->number;
        help = help->next;
     }
     Sort(tail, op_array, num);
     new =  OpData[op_array[1]].process_time + tail[op_array[1]];
     for (i = 2; i <= num; ++i) {
        new = (new < tail[op_array[i]])? tail[op_array[i]] : new;
        new += OpData[op_array[i]].process_time;
     }
  }
  tail[ActualOp] = (max < new)? new : max ;
}



/* ************************************************************************* */
/*                      Procedure Compute_Head_Tail()                        */
/*                                                                           */
/*  INPUT: -/-                                                               */
/*                                                                           */
/*                                                                           */
/*  FUNCTION: Calculation of the heads and tails                             */
/* ************************************************************************* */

boolean Compute_Head_Tail ()
{

  register struct List  *help;
  int          num_of_disj[MaxNumOfOperations + 1],
               cut[MaxNumOfJobs+1];  

  register int i, ActualOp, pos;

  for (i = 1; i <= NumOfOperations; ++i)
     num_of_disj[i] = SonNode->num_of_pred[i] + 1;
  num_of_disj[MaxNumOfOperations] = NumOfJobs;

  head[0] = 0;
  pos = 1;
  help = ConjArcs->succ[0];
  while (help != NIL) {
     num_of_disj[help->number]--;
     if (num_of_disj[help->number] == 0)
         cut[pos++] = help->number;
     help = help->next;
  }
  while (pos > 1) {
     ActualOp = cut[--pos];
     Compute_Head(ActualOp);
     if (ActualOp != MaxNumOfOperations) {
        num_of_disj[ConjArcs->succ[ActualOp]->number]--;
     if (!num_of_disj[ConjArcs->succ[ActualOp]->number])
        cut[pos++] = ConjArcs->succ[ActualOp]->number;
     }
     help = DisjArcs->succ[ActualOp];
     while (help != NIL) {
        num_of_disj[help->number]--;
        if (!num_of_disj[help->number])
           cut[pos++] = help->number;
        help = help->next;
     }
  }
  if (num_of_disj[MaxNumOfOperations] != 0 ||
     head[MaxNumOfOperations] >= UpperBound) return(false);


  for (i = 1; i <= NumOfOperations; ++i)
     num_of_disj[i] = SonNode->num_of_succ[i] + 1;
  num_of_disj[0] = NumOfJobs;

  tail[MaxNumOfOperations] = 0;
  pos = 1;
  help = ConjArcs->pred[MaxNumOfOperations];
  while (help != NIL) {
     num_of_disj[help->number]--;
     if (num_of_disj[help->number] == 0)
         cut[pos++] = help->number;
     help = help->next;
  }
  while (pos > 1) {
     ActualOp = cut[--pos];
     Compute_Tail(ActualOp);
     if (ActualOp != 0) {
        num_of_disj[ConjArcs->pred[ActualOp]->number]--;
        if (!num_of_disj[ConjArcs->pred[ActualOp]->number])
           cut[pos++] = ConjArcs->pred[ActualOp]->number;
     }
     help = DisjArcs->pred[ActualOp];
     while (help != NIL) {
        num_of_disj[help->number]--;
        if (!num_of_disj[help->number])
           cut[pos++] = help->number;
        help = help->next;
     }
  }
  if (num_of_disj[0] != 0 || tail[0] >= UpperBound) return(false);
  return (true);
}

