/*                             Filename: Main.c                              */
/*                                                                           */
/*                               main program                                */
/*                                                                           */
/* ************************************************************************* */


#include <stdio.h>
#include "datastruct.h"
#include "table.h"
#include "list.h"
#include "init.h"
#include "readdata.h"
#include "headtail.h"
#include "heur.h"
#include "block.h"
#include "branch.h"
#include "stack.h"
#include "fix.h"
#include "select.h"
#include "low.h"


/* ************************************************************************* */
/*                                                                           */
/*                              main program                                 */
/*                                                                           */
/*  INPUT: command line parameters                                           */
/*                                                                           */
/*  FUNCTION: Calculation of the optimal solution for the problem given in   */
/*            file argv[1]                                                   */
/* ************************************************************************* */

int main(argc, argv)

int argc;
char *argv[];

{

  struct BranchList  *DeleteBranch;
 
  Initialize();
  if ( !Read_Data(argv[1]) ) {
     printf("Not able to read data !\n");
     return(1);
  }

  if ( Compute_Head_Tail() ) {
     printf("\n");
     Heuristic_Schedule();
     if ((SonNode->lower_bound = Additional_DisjArcs()) < UpperBound) {
        printf("\nLower Bound = %4d\n\n",SonNode->lower_bound);
        Compute_Blocks();
        Compute_BranchList();
        ActualNode = SonNode;
        Push();
        SonNode = (struct NodeType *) malloc(sizeof(struct NodeType));
        SonNode->blocks = NIL; SonNode->order = NIL;
     }
  }
  while (FirstOfStack != NIL) {
     Pop();          
     Update_DisjArcs();
     while (ActualNode->order != NIL && ActualNode->lower_bound < UpperBound) {
        Fix_Disjunctions(ActualNode->order->branch_op,
                                ActualNode->order->before_or_after);
        DeleteBranch = ActualNode->order;
        ActualNode->order = ActualNode->order->next;
        free((void *) DeleteBranch);     
        if ( Compute_Head_Tail() &&     
             Compute_LowerBound() < UpperBound && 
             (SonNode->lower_bound = Additional_DisjArcs()) < UpperBound) {
           Heuristic_Schedule();
           if ( SonNode->lower_bound < UpperBound ) {
              Compute_Blocks();         
              Compute_BranchList();    
              SearchTreeNodes++;
              Push();                 
              ActualNode = SonNode;  
              SonNode = (struct NodeType *) malloc(sizeof(struct NodeType));
              SonNode->blocks = NIL; SonNode->order = NIL;
           }
           else { 
              CriticalPath = Makeempty(CriticalPath); 
              Update_DisjArcs();     
           }
        }
        else Update_DisjArcs();                 
     }
  }
  printf("Upper Bound = %4d, SearchTreeNodes = %d\n",UpperBound,SearchTreeNodes);
  return 0;
}


