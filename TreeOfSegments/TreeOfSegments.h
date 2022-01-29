#pragma once

typedef enum{
  Variants_less = -1,
  Variants_equal = 0,
  Variants_bigger = 1,
}Variants;

typedef struct tag_NodeData{
  int leftBoard;
  int rightBoard;
  int maxRightBoard;
}NodeData;
 
typedef struct tag_TreeNode{
  struct tag_TreeNode *leftChild;
  struct tag_TreeNode *rightChild;
  NodeData data;
}TreeNode;

typedef struct tag_Tree{
  TreeNode *head;
}Tree;

Tree *CreateTreeOfSegments();
void AddElement(Tree *tree, NodeData data);
void DelElement(Tree *tree, NodeData data);
TreeNode *SearchElement(Tree *tree, NodeData data);
TreeNode *Intersections(Tree *tree, int leftBoard, int rightBoard);
void DeleteTree(Tree *Tree);