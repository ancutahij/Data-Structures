#include "cctree.h"
#include "common.h"
#include"ccstack.h"
#include"ccqueue.h"
#include"ccgenericstack.h"
#include<malloc.h>
#include<stdlib.h>
int TreeCreate(CC_TREE **Tree)
{
	if (*Tree != NULL)
	{
		return -1;
	}

	*Tree = (CC_TREE*)malloc(sizeof(CC_TREE));
	if (*Tree == NULL)
	{
		return -1;
	}
	(*Tree)->root = NULL;
    return 0;
}

int TreeDestroy(CC_TREE **Tree)
{
	if (Tree == NULL || *Tree == NULL)
	{
		return -1;
	}


	TreeClear(*Tree);
	free(*Tree);
	return 0;

 
}
int TreeGetHeightNode(CC_TREE_NODE * nde)
{
	if (nde == NULL)
	{
		return -1;
	}
	CC_QUEUE *queue = NULL;
	QCreate(&queue);
	QPush(queue, nde);

	int height = 0;
	while (1)
	{
		int levelSize = QSize(queue);
		if (levelSize == 0)
		{
			QDestroy(&queue);
			return height - 1;
		}
		height++;
		while (levelSize > 0)
		{
			CC_TREE_NODE *node = NULL;
			QPop(queue, &node);
			if (node->leftChild != NULL)
			{
				QPush(queue, node->leftChild);
			}
			if (node->rightChild != NULL)
			{
				QPush(queue, node->rightChild);
			}
			levelSize--;

		}
	}
}

int maxim(int no1, int no2)
{
	return (no1 > no2) ? no1 : no2;
}

/*
	Rotate a subtree to right side whose root is the given root paramenter
	Return the new root
*/
static CC_TREE_NODE *rightRotation(CC_TREE_NODE* root)
{
	CC_TREE_NODE *left = root->leftChild;
	CC_TREE_NODE *T = left->rightChild;

	left->rightChild = root;
	root->leftChild = T;
	if (T != NULL)
	{
		T->parent = root;
	}
	root->parent = left;
	//recalculating the heights
	//root->height = maxim(TreeGetHeightNode(root->leftChild), TreeGetHeightNode(root->rightChild))+1;
	//left->height = maxim(TreeGetHeightNode(left->leftChild), TreeGetHeightNode(left->rightChild))+1;

	return left;
}


/*
Rotate a subtree to right side whose root is the given root paramenter
Return the new root
*/
static CC_TREE_NODE *leftRotation(CC_TREE_NODE* root)
{
	CC_TREE_NODE *right = root->rightChild;
	CC_TREE_NODE *T = right->leftChild;

	right->leftChild= root;
	root->rightChild = T;
	if (T != NULL)
	{
		T->parent = root;
	}
	root->parent = right;
	//recalculating the heights
	//root->height = maxim(TreeGetHeightNode(root->leftChild), TreeGetHeightNode(root->rightChild)) + 1;
	//right->height = maxim(TreeGetHeightNode(right->leftChild), TreeGetHeightNode(right->rightChild)) + 1;

	return right;
}


/*
	Return balance factor between left subtree and right subtree
*/
static int TreeGetBalance(CC_TREE_NODE * node)
{
	if (node == NULL)
	{
		return -1;
	}
	return(TreeGetHeightNode(node->leftChild) - TreeGetHeightNode(node->rightChild));
	
}



int TreeInsert(CC_TREE *Tree, int Value)
{
	
	if (Tree == NULL)
	{
		return -1;
	}
	if (Tree->root == NULL)
	{
		CC_TREE_NODE *newNode = malloc(sizeof(CC_TREE_NODE));
		if (newNode == NULL)
		{
			return -1;
		}
		newNode->parent = NULL;
		newNode->leftChild = NULL;
		newNode->rightChild = NULL;
		newNode->Value = Value;
		newNode->duplicationFactor = 1;
		Tree->root = newNode;
		return 0;

	}

	CC_TREE_NODE *parent_current= NULL;
	int leftSide = 1;
	CC_TREE_NODE *current = Tree->root;
	
	int done=0;

	
	while (done == 0)
	{
		if (current == NULL)
		{
			CC_TREE_NODE *newNode = malloc(sizeof(CC_TREE_NODE));
			if (newNode == NULL)
			{
				return -1;
			}
			newNode->parent = NULL;
			newNode->leftChild = NULL;
			newNode->rightChild = NULL;
			newNode->Value = Value;
			newNode->duplicationFactor = 1;


			if (parent_current->Value > Value)
			{
				parent_current->leftChild = newNode;
				newNode->parent = parent_current;
			}
			else
			{
				parent_current->rightChild = newNode;
				newNode->parent = parent_current;
			}

			done = 1;
		}
		else {
			if (current->Value < Value)
			{
				parent_current = current;
				leftSide = 0;
				current = current->rightChild;
			}
			else
			{
				if (current->Value > Value) {
					leftSide = 1;
					parent_current = current;
					current = current->leftChild;
				}
				else
				{
					current->duplicationFactor++;
					return 0;
				}
			}
		}


	}
	current = parent_current;
	parent_current = current->parent;
	while (parent_current != NULL)
	{
		current = parent_current;
		parent_current = current->parent;

		int balanceFactor = TreeGetBalance(current);

		// getting the correct size where to link connections
		if (parent_current != NULL)
		{
			if (parent_current->Value > Value)
				/*
					For instance:
					40
					/\
				   30  42
				    \
					 32
					 /
					31    <-------- this is the last node inserted  
					Balance factor is 2 . We have to perform a left rotation and a right rotation

					After left rotation:
					  40
					  /\
					30  42
					\
					31
					 \
				     32

					 After right rotation:
					   40
					   /\
					 31  42
					 /\
					30 32
					Now the tree is balanced.
					left side parameter gives the information where to link the new root (31) of subtree

				*/
			{
				leftSide = 1;
			}
			else
			{
				leftSide = 0;
			}
		}
		
		// single right rotation
		if (balanceFactor > 1 && Value < current->leftChild->Value) {
			if(parent_current != NULL)
			{
				if (leftSide == 1) {
					parent_current->leftChild = rightRotation(current);
					current = parent_current->leftChild;
					current->parent = parent_current; // setting new parent
				}
				else
				{
					parent_current->rightChild = rightRotation(current);
					current = parent_current->rightChild;
					current->parent = parent_current; // setting new parent
				}
			}
			else
			{
				Tree->root = rightRotation(current);
				Tree->root->parent = NULL;

			}
		}
		else
		{
			//single left rotation
			if (balanceFactor < -1 && Value > current->rightChild->Value) {
				if (parent_current != NULL)
				{
					if (leftSide == 1) {

						parent_current->leftChild = leftRotation(current);
						current = parent_current->leftChild;
						current->parent = parent_current;
					}
					else
					{
						parent_current->rightChild = leftRotation(current);
						current = parent_current->rightChild;
						current->parent = parent_current;
					}
				}
				else
				{
					Tree->root= leftRotation(current);
					Tree->root->parent = NULL;

				}
			}
			else
			{	// double rotation: left right rotation
				if (balanceFactor > 1 && Value > current->leftChild->Value)
				{
					current->leftChild = leftRotation(current->leftChild);
					current->leftChild->parent = current;
					if (parent_current != NULL) {
						
						if (leftSide == 1) {
							parent_current->leftChild = rightRotation(current);
							parent_current->leftChild->parent = parent_current;
						}
						else
						{
							parent_current->rightChild = rightRotation(current);
							parent_current->rightChild->parent = parent_current;
						}
					}
					else
					{
						Tree->root = rightRotation(current);
						Tree->root->parent = NULL;

					}
				}
				else
				{
					// double rotation:  right left rotation
					if (balanceFactor < -1  && Value < current->rightChild->Value)
					{
						current->rightChild= rightRotation(current->rightChild);
						current->rightChild->parent = current;

						if (parent_current != NULL) 
						{
							if (leftSide == 1)
							{
								parent_current->leftChild = leftRotation(current);
								parent_current->leftChild->parent = parent_current;
							}
							else
							{
								parent_current->rightChild = leftRotation(current);
								parent_current->rightChild->parent = parent_current;
							}
						}
						else
						{
							Tree->root = leftRotation(current);
							Tree->root->parent = NULL;


						}

					}
					

				}
			}
		}
			
	}
	return 0;
	
}

int TreeRemove(CC_TREE *Tree, int Value)
{
	if (Tree == NULL)
	{
		return -1;
	}

	if (TreeContains(Tree, Value) == 0)
	{
		return 0;
	}
	CC_TREE_NODE *current = Tree->root;
	CC_TREE_NODE *parent = NULL;
	int leftSide = 0; // 1 for left, 0 for right

	while (current != NULL)
	{
		if (Value == current->Value)
		{
			break;
		}
		else
		{
			if (Value<current->Value)
			{
				parent = current;
				leftSide = 1;
				current = current->leftChild;
			}
			else
			{
				parent = current;
				leftSide = 0;
				current = current->rightChild;
			}
		}

	}

	// current is a leaf
	if (current->leftChild == NULL && current->rightChild == NULL)
	{
		// current is also the root of the tree
		if (parent == NULL)
		{
			free(current);
			Tree->root = NULL;
		}
		else // just another leaf which is different from parent
		{
			free(current);
			if (leftSide == 1)
			{
				parent->leftChild = NULL;
			}
			else {
				parent->rightChild = NULL;
			}
		}
	}
	else
	{
		if (current->leftChild == NULL || current->rightChild == NULL) // current has a child
		{
			CC_TREE_NODE *child = NULL;
			if (current->leftChild != NULL)
				child = current->leftChild;
			else
				child = current->rightChild;

			if (parent == NULL) // root is beeing deleted
			{
				free(current);
				Tree->root = child;
			}
			else 
			{
				if (leftSide) {
					parent->leftChild = child;
					child->parent = parent;
				}
				else
				{
					parent->rightChild = child;
					child->parent = parent;
				}
				free(current);
			}
		}
		else // deleting a node with 2 children
		{
			CC_TREE_NODE *temp = current->leftChild;
			CC_TREE_NODE *parent_temp = NULL;

			leftSide = 1;
			// looking for the largest element in left subtree
			while (temp->rightChild != NULL)
			{
				parent_temp = temp;
				temp =temp->rightChild;
				leftSide = 0;
			}
			current->Value = temp->Value;

			if (leftSide)
			{
				current->leftChild = temp->leftChild;
				free(temp);
			}
			else
			{
				parent_temp->rightChild = temp->leftChild;
				free(temp);
			}

		}
	}

	//while (parent != NULL)
	{

	}
	return 0;
}

int TreeContains(CC_TREE *Tree, int Value)
{
	if (Tree == NULL)
	{
		return -1;
	}

	CC_TREE_NODE* current = Tree->root;
	if (current == NULL)
	{
		return 0;
	}
	

	while (current != NULL)
	{
		if (current->Value == Value)
		{
			return 1;
		}
		else
		{
			if (current->Value < Value)
			{
				current = current->rightChild;
			}
			else
			{
				current = current->leftChild;
			}
	
		}
	}
    return 0;
}

int TreeGetCount(CC_TREE *Tree)
{
	if (Tree == NULL)
	{
		return -1;
	}
	if (Tree->root == NULL)
	{
		return 0;
	}
	CC_QUEUE *queue = NULL;
	QCreate(&queue);
	QPush(queue, Tree->root);
	int noNodes = 0;
	while (QIsEmpty(queue) == 0)
	{
		noNodes++;
		CC_TREE_NODE *node = NULL;
		QPop(queue, &node);
		if (node->leftChild != NULL)
		{
			QPush(queue, node->leftChild);
		}
		if (node->rightChild != NULL)
		{
			QPush(queue, node->rightChild);
		}
	}
	QDestroy(&queue);

	return noNodes;
}

int TreeGetHeight(CC_TREE *Tree)
{
	if (Tree == NULL)
	{
		return -1;
	}
	

	return TreeGetHeightNode(Tree->root);
	
}

int TreeClear(CC_TREE *Tree)
{
	if (Tree == NULL)
	{
		return -1;
	}
	CC_TREE_NODE* current = Tree->root;
	if (current != NULL)
	{
		CC_GENERIC_STACK *stack = NULL; // a stack of CC_TREE_Node pointers
		GenStCreate(&stack);
		GenStPush(stack, current);
		while (GenStIsEmpty(stack) == 0)
		{
			GenStPop(stack, &current);
			if (current->rightChild != NULL)
			{
				GenStPush(stack, current->rightChild);

			}

			if (current->leftChild != NULL)
			{
				GenStPush(stack, current->leftChild);

			}
			free(current);
			current = NULL;
		}
		GenStDestroy(&stack);
		Tree->root = NULL;

	}
	return 0;
}

int TreeGetNthPreorder(CC_TREE *Tree, int Index, int *Value)
{
	if (Tree == NULL || Value == NULL)
	{
		return -1;
	}

	int noNodes = TreeGetCount(Tree);
	if (Index > noNodes || Index<=0)
	{
		return -1;
	}


	CC_TREE_NODE *current = Tree->root;
	CC_GENERIC_STACK *stack = NULL; // a stack of CC_TREE_Node pointers
	GenStCreate(&stack);
	GenStPush(stack, current);
	int done = 0;
	while (GenStIsEmpty(stack) == 0 && done == 0 )
	{
		Index--;
		GenStPop(stack, &current);
		if (Index == 0)
		{
			*Value = current->Value;
			done = 1;
		}
		if (current->rightChild != NULL) // push the right child into the stack
		{
			GenStPush(stack, current->rightChild);
		}


		if (current->leftChild != NULL)// push the left child into the stack
		{
			GenStPush(stack, current->leftChild);
		}
	}
	GenStDestroy(&stack);

    return 0;
}

int TreeGetNthInorder(CC_TREE *Tree, int Index, int *Value)
{
	

	if (Tree == NULL || Value == NULL)
	{
		return -1;
	}
	int noNodes = TreeGetCount(Tree);
	if (Index > noNodes || Index <1)
	{
		return -1;
	}
	
	CC_TREE_NODE *current = Tree->root;
	CC_GENERIC_STACK *stack= NULL;
	GenStCreate(&stack);
	int done = 0;
	while (!done) // the count of nodes starts from 1
	{
		
		if (current != NULL) // iterate till the left most node
		{
			GenStPush(stack, current);
			current = current->leftChild;
		}
		else // visit the node at the top of the stack
		{
			if (GenStIsEmpty(stack) == 0)
			{
				GenStPop(stack, &current);
				Index--;
				if (Index == 0)
				{
					*Value = current->Value;
					done = 1;

				}
				current = current->rightChild;
			}
		}
	}

	GenStDestroy(&stack);
    return 0;
}

int TreeGetNthPostorder(CC_TREE *Tree, int Index, int *Value)
{

	if (Tree == NULL || Value == NULL)
	{
		return -1;
	}
	int noNodes = TreeGetCount(Tree);
	if (Index > noNodes || Index <1)
	{
		return -1;
	}

	CC_TREE_NODE *current = Tree->root;
	CC_GENERIC_STACK *stack = NULL;
	GenStCreate(&stack);
	int done = 0;
	do
	{
		// iterate till the left most node from tree
		while (current != NULL)
		{
			if (current->rightChild != NULL)
			{
				GenStPush(stack, current->rightChild);
			}

			GenStPush(stack, current);
			current = current->leftChild;
		}
		GenStPop(stack, &current);

		// if the popped node has a right child which wasn't visited till now,
		// we have to process the right child before the root
		CC_TREE_NODE *rightCh = Tree->root;
		GenStPeek(stack, &rightCh);
		if (current->rightChild != NULL && rightCh == current->rightChild)
		{
			GenStPop(stack, &rightCh); // remove the right child from the stack
			GenStPush(stack, current);
			current = rightCh;

		}
		else // right child was visited
		{
			Index--;
			if (Index == 0)
			{
				*Value = current->Value;
				done = 0;
			}
			current = NULL;
		}
	} while (GenStIsEmpty(stack) == 0);
	GenStDestroy(&stack);
    return -1;
}

#include<stdio.h>
void TreeWeightTraversal(CC_TREE *tree)
{
	CC_QUEUE *queue = NULL;
	QCreate(&queue);
	printf("\n");
	QPush(queue, tree->root);
	while (QIsEmpty(queue) == 0)
	{
		CC_TREE_NODE *current = NULL;
		QPop(queue, &current);
		printf("%d ", current->Value);
		if (current->leftChild != NULL)
		{
			QPush(queue, current->leftChild);

		}
		if (current->rightChild!= NULL)
		{
			QPush(queue, current->rightChild);

		}
	}
	QDestroy(&queue);
}