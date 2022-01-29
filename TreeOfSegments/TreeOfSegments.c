#include <stdio.h>
#include <stdlib.h>
#include "TreeOfSegments.h"

TreeNode *f_CreateNode(NodeData data);
void f_DestroyNode(TreeNode *node);
void f_CopyData(TreeNode *from, TreeNode *to);

TreeNode **f_CreatePathVariable(int lenght);
void f_DestroyPathVariable(TreeNode **path);

void f_ModifyMaxRightBoardOnPath(TreeNode **path, int newMaxRightBoard, int pathLenght);
TreeNode *f_SearchPlaceForAdd(Tree *tree, NodeData data, TreeNode **Path, int *realLenght /* out */);
int f_GetTreeHeight(Tree *tree);


Tree *CreateTreeOfSegments(){
  Tree *newTree = (Tree*)malloc(sizeof(Tree));
  newTree->head = NULL;
  return newTree;
}

Variants Comparator(NodeData newElementData, NodeData treeNodeData){
  if (newElementData.leftBoard > treeNodeData.leftBoard){
    return Variants_bigger;
  }
  else if (newElementData.leftBoard < treeNodeData.leftBoard){
    return Variants_less;
  }
  else{
    return Variants_equal;
  }
}

void AddElement(Tree *tree, NodeData data){
  //TreeNode *tmp = tree->head;

  if (tree->head == NULL){
    TreeNode *newNode = f_CreateNode(data);
    tree->head = newNode;
  }
  else{
    int maxLenght = f_GetTreeHeight(tree);
    TreeNode **path = f_CreatePathVariable(maxLenght);
    int realLenght = 0;
    TreeNode *parentNode = f_SearchPlaceForAdd(tree, data, path, &realLenght);
    if (parentNode == NULL){
      return;
    }
    else{
      TreeNode *newNode = f_CreateNode(data);
      if (newNode->data.leftBoard > parentNode->data.leftBoard){
        parentNode->rightChild = newNode;
      }
      else{
        parentNode->leftChild = newNode;
      }
      f_ModifyMaxRightBoardOnPath(path, newNode->data.maxRightBoard, realLenght);
      f_DestroyPathVariable(path);
      return;
    }
  }
}

TreeNode *SearchElement(Tree *tree, NodeData data){
  TreeNode *tmp = tree->head;
  while (tmp != NULL){
    if (data.leftBoard > tmp->data.leftBoard){
      tmp = tmp->rightChild;
    }
    else if (data.leftBoard < tmp->data.leftBoard){
      tmp = tmp->leftChild;
    }
    else if (data.leftBoard == tmp->data.leftBoard){
      return tmp;
    }
  }
  return NULL;
}

void PostOrder(TreeNode *CurEl, void(*Function) (TreeNode *Node)){
  if (CurEl != NULL)
  {
    PostOrder(CurEl->leftChild, Function);
    PostOrder(CurEl->rightChild, Function);
    Function(CurEl);
  }
}

void DeleteTree(Tree *Tree){
  PostOrder(Tree->head, &(f_DestroyNode));
  free(Tree);
}


void DelElement(Tree *tree, NodeData data){
  if (tree->head == NULL){
    return;
  }
  TreeNode *delElement = SearchElement(tree, data);
  if (delElement == NULL){
    return;
  }
  TreeNode *place = delElement;
  TreeNode *instead = delElement->rightChild;
  while (instead->leftChild != NULL){
    instead = instead->leftChild;
  }
  f_CopyData(instead, place);
  f_DestroyNode(instead);
  return;
}

TreeNode *Intersections(Tree *tree, int leftBoard, int rightBoard){
  TreeNode *tmp = NULL;
  TreeNode *head = tree->head;
  while (head != NULL && (head->data.leftBoard > rightBoard || head->data.rightBoard < leftBoard)){
    tmp = head->leftChild;
    if (tmp != NULL && tmp->data.maxRightBoard > leftBoard){
      head = head->leftChild;
    }
    else{
      head = head->rightChild;
    }
  }
  return head;
}

void f_DestroyNode(TreeNode *node){
  free(node);
}

void f_CopyData(TreeNode *from, TreeNode *to){
  to->data.leftBoard = from->data.leftBoard;
  to->data.rightBoard = from->data.rightBoard;
  return;
}

void f_ModifyMaxRightBoardOnPath(TreeNode **path, int newMaxRightBoard, int pathLenght){
  if (path[pathLenght - 1]->data.maxRightBoard < newMaxRightBoard){
    path[pathLenght - 1]->data.maxRightBoard = newMaxRightBoard;
    for (int i = pathLenght - 1; i > 0; i--){
      if (path[i]->data.maxRightBoard > path[i - 1]->data.maxRightBoard){
        path[i - 1]->data.maxRightBoard = path[i]->data.maxRightBoard;
      }
      else{
        return;
      }
    }
  }
  else{
    return;
  }
}

void f_DestroyPathVariable(TreeNode **path){
  free(path);
}

TreeNode **f_CreatePathVariable(int lenght){
  TreeNode **path = (TreeNode**)malloc(sizeof(TreeNode*) * lenght);
  for (int i = 0; i < lenght; i++){
    path[i] = NULL;
  }
  return path;
}

int f_GetTreeHeight(Tree *tree){
  tree;
  return 10;
}

TreeNode *f_CreateNode(NodeData data){
  TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
  newNode->data = data;
  newNode->leftChild = NULL;
  newNode->rightChild = NULL;
  return newNode;
}

TreeNode *f_SearchPlaceForAdd(Tree *tree, NodeData data, TreeNode **Path, int *realLenght /* out */){
  TreeNode *tmp = tree->head, *prevNode = NULL;

  for (int i = 0; tmp != NULL; i++){
    (*realLenght)++;
    Path[i] = tmp;
    Variants result = Comparator(data, tmp->data);
    prevNode = tmp;

    if (result == Variants_bigger){
      tmp = tmp->rightChild;
    }
    else if (result == Variants_less){
      tmp = tmp->leftChild;
    }
    else if (result == Variants_equal){
      return NULL;
    }
  }
  return prevNode;
}