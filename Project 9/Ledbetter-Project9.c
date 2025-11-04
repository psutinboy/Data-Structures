#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// the purpose of this code sample is to demonstrate the linked binary tree structure...
// for code simplicity, I have not placed the malloc statements in try-catch blocks
// best practice for production code would be to include the malloc statements in try-catch blocks.

// binary tree structs
typedef struct TreeNode
{
	char data;
	struct TreeNode *parent;
	struct TreeNode *leftChild;
	struct TreeNode *rightChild;
} TreeNode;

typedef struct BinaryTree
{
	int nodeCount;
	TreeNode *rootNode;
} BinaryTree;

TreeNode *newNode(char x)
{
	TreeNode *node = malloc(sizeof(TreeNode));
	node->data = x;
	node->parent = NULL;
	node->rightChild = NULL;
	node->leftChild = NULL;
	return node;
}

BinaryTree *newTree()
{
	BinaryTree *tree = malloc(sizeof(BinaryTree));
	tree->rootNode = NULL;
	tree->nodeCount = 0;

	return tree;
}
////////////////////////////

char postfix[100];
int length;
BinaryTree *exprTree;


void getUserInput();
void buildExpressionTree();
void postOrderTraversal();
void preOrderTraversal();
void inOrderTraversal();
void freeMemory();

int isLetter(char ch);

int main()
{
	getUserInput();
	buildExpressionTree();
	postOrderTraversal(exprTree->rootNode); printf("\n");
	preOrderTraversal(exprTree->rootNode); printf("\n");
	inOrderTraversal(exprTree->rootNode); printf("\n");

	freeMemory();

	return 0;
}

void buildExpressionTree()
{
	// missing code
  exprTree = newTree();
  TreeNode* stack[100];
  int top = -1;
  //go through each character of postfix
  int i;
  for (i = 0; i < length; i++) {
    char ch = postfix[i];
    if (isLetter(ch)) {
      // create a new node for the letter
      TreeNode *node = newNode(ch);
      top++;
      stack[top] = node;
    } else // its an operator
    {
      // create a new node for the operator
      TreeNode* node1 = stack[top];
      top--;
      TreeNode* node2 = stack[top];
      top--;

      TreeNode *operatorNode = newNode(ch);
      // set children
      operatorNode->leftChild = node2;
      operatorNode->rightChild = node1;
      // set parent
      node1->parent = operatorNode;
      node2->parent = operatorNode;
      // push op node on stack
      top++;
      stack[top] = operatorNode;
    }
  }
  // set root node
  exprTree->rootNode = stack[0];
}

void postOrderTraversal(TreeNode *node)
{
	// missing code
  if (node == NULL)
    return;
  postOrderTraversal(node->leftChild);
  postOrderTraversal(node->rightChild);
  printf("%c", node->data);
}

void preOrderTraversal(TreeNode *node)
{
	// missing code
  if (node == NULL)
    return;
  printf("%c", node->data);
  preOrderTraversal(node->leftChild);
  preOrderTraversal(node->rightChild);
}

void inOrderTraversal(TreeNode *node)
{
	if (node == NULL)
		return;

	// missing code
  inOrderTraversal(node->leftChild);
  printf("%c", node->data);
  inOrderTraversal(node->rightChild);

}

void freeMemory()
{
	// missing code
  freeNode(exprTree->rootNode);
  free(exprTree);
}

void freeNode(TreeNode *node)
{
  if (node == NULL)
    return;
  freeNode(node->leftChild);
  freeNode(node->rightChild);
  free(node);
}

void getUserInput()
{
	printf("Supported operations: +,*,-,/ \n");
	printf("Enter a postfix expression in variables a,b,c,d:\n");
	fgets(postfix, sizeof(postfix), stdin); // Read string with spaces

	// Remove trailing newline character from fgets if present
	postfix[strcspn(postfix, "\n")] = '\0';

	length = strlen(postfix); // Calculate length

	printf("You entered: \"%s\"\n", postfix);
	printf("Length of the string: %d\n", length);
}

int isLetter(char ch)
{
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


