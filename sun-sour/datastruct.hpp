/* ************************************************************************* */
/*                       Filename: Datastruct.h                              */
/*                                                                           */
/*    Export: Global constants and datastructures                            */
/* ************************************************************************* */
#pragma once

#define MaxNumOfOperations  310
#define MaxNumOfMachines     17
#define MaxNumOfJobs         32
#define MaxOpProMachine      32
#define NIL                   0

struct List {
  int number;
  List *next;
};

struct Operation {
  int process_time;
  int machine_nr;
};

struct ArcList {
  List *pred[MaxNumOfOperations + 1], *succ[MaxNumOfOperations + 1];
};

struct BlockList {
  List *elements;
  BlockList *next;
  int last_of_block;
  char fi_mi_la;		/* first - middle - last */
};

struct BranchList {
  int branch_op;
  char before_or_after;
  BranchList *next;
};

struct NodeType {
  int num_of_succ[MaxNumOfOperations + 1], num_of_pred[MaxNumOfOperations + 1],  lower_bound;
  BlockList *blocks;
  BranchList *order;
};

struct StackElement {
  NodeType *node;
  StackElement *next;
};
