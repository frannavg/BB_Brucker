/* ************************************************************************* */
/*                             Filename: Main.c                              */
/*                                                                           */
/*                               main program                                */
/*                                                                           */
/* ************************************************************************* */
#include <cstdlib>
#include <cstdio>

#include "datastruct.hpp"
#include "table.hpp"
#include "list.hpp"
#include "init.hpp"
#include "readdata.hpp"
#include "headtail.hpp"
#include "heur.hpp"
#include "block.hpp"
#include "branch.hpp"
#include "stack.hpp"
#include "fix.hpp"
#include "select.hpp"
#include "low.hpp"

/* ************************************************************************* */
/*                                                                           */
/*                              main program                                 */
/*                                                                           */
/*  INPUT: command line parameters                                           */
/*                                                                           */
/*  FUNCTION: Calculation of the optimal solution for the problem given in   */
/*            file argv[1]                                                   */
/* ************************************************************************* */
int main(int argc, char *argv[]) {
  BranchList *DeleteBranch;

  // (1) initialize global variables
  Initialize();

  // (2) read input
  if (!Read_Data(argv[1])) {
    printf("Not able to read data !\n");
    return 1;
  }

  // (3) initial lower and upper bound
  if (Compute_Head_Tail()) {
    Heuristic_Schedule();
    if ((SonNode->lower_bound = Additional_DisjArcs()) < UpperBound) {
      printf("\nLower Bound = %4d\n\n", SonNode->lower_bound);
      Compute_Blocks();
      Compute_BranchList();
      ActualNode = SonNode;
      Push();
      SonNode = (NodeType *) malloc(sizeof(NodeType));
      SonNode->blocks = NIL;
      SonNode->order = NIL;
    }
  }

  // (4) branch-and-bound
  while (FirstOfStack != NIL) {
    Pop();
    Update_DisjArcs();
    while (ActualNode->order != NIL && ActualNode->lower_bound < UpperBound) {
      Fix_Disjunctions(ActualNode->order->branch_op, ActualNode->order->before_or_after);
      DeleteBranch = ActualNode->order;
      ActualNode->order = ActualNode->order->next;
      free((void *) DeleteBranch);
      if (Compute_Head_Tail() && Compute_LowerBound() < UpperBound && (SonNode->lower_bound = Additional_DisjArcs()) < UpperBound) {
	Heuristic_Schedule();
	if (SonNode->lower_bound < UpperBound) {
	  Compute_Blocks();
	  Compute_BranchList();
	  SearchTreeNodes++;
	  Push();
	  ActualNode = SonNode;
	  SonNode = (NodeType *) malloc(sizeof(NodeType));
	  SonNode->blocks = NIL;
	  SonNode->order = NIL;
	} else {
	  CriticalPath = Makeempty(CriticalPath);
	  Update_DisjArcs();
	}
      } else
	Update_DisjArcs();
    }
  }

  // (5)
  printf("Upper Bound = %4d, SearchTreeNodes = %d\n", UpperBound, SearchTreeNodes);
  return 0;
}
