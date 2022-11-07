#include <iostream>
#include <fstream>
#include <algorithm>
#include "BST.h"
#include<iomanip>

using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;

	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode *cur, int &count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode *cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)){

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode *cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode			*cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode	*cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode *cur, BTNode *newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)){
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode *pre, BTNode *cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)){
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode *pre, BTNode *cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode *cur) {
	BTNode		*is, *isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}

//******************************* self create function for assignment ********************************

int BST::Depth(BTNode* root)
{
	if (root == NULL)
	{
		return 0;
	}
	int leftHeight = Depth(root->left);
	int rightHeight = Depth(root->right);

	return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1; 
}

bool BST::deepestNodes()
{
	if (root == NULL) //check special case
	{
		cout << "The BST is empty!" << endl;
		return false;
	}
	int depth = Depth(root);
	cout << "\n--------------------------------------------------------------------------------------------\n";
	cout << "                          The deepest node(s) is/are printed as below                               ";
	cout << "\n--------------------------------------------------------------------------------------------\n";

	printDeepestNode(root, depth, 1);
}

void BST::printDeepestNode(BTNode* root, int depth, int level)
{
	if (level < 1)return;
	if (root == NULL)return;

	if (depth != level) // always find the deepest level when depth not equal to current level
	{
		printDeepestNode(root->left, depth, level + 1);
		printDeepestNode(root->right, depth, level + 1);
	}
	else
	{
		cout << "Student ID for the deepest node is: " << root->item.id << endl << endl;
	}
}

void BST::Ascending(BTNode* cur, ostream& out)
{
	if (cur == NULL)return;

	Ascending(cur->left, out);
	cur->item.print(out);
	Ascending(cur->right, out);
}

void BST::Descending(BTNode* cur, ostream& out)
{
	if (cur == NULL)return;

	Descending(cur->right, out);
	cur->item.print(out);
	Descending(cur->left, out);
}

bool BST::display(int order, int source)
{
	//check whether the user enter invalid number and the BST is empty
	if (root == NULL)
	{
		cout << "\nThe BST is empty!" << endl << endl;
		if (root == NULL && (order <= 0 || order >= 3))
		{
			cout << "You can only insert '1' and '2'!\n\n";
		}
		return false;
	}
	if (order <= 0 || order >= 3)//check the choice of user whether insert '1' and '2' only
	{
		cout << "You can only insert '1' and '2'!\n\n";
		return false;
	}

	if (source == 1) // print on screen
	{
		cout << "\n--------------------------------------------------------------------------------------------\n";
		cout << "                                    Student(s) Information                                " << endl;
		cout << "\n--------------------------------------------------------------------------------------------\n";
		if (order == 1)
		{
			Ascending(root, cout);
		}
		else if (order == 2)
		{
	
			Descending(root, cout);
		}
		cout << "\n---------------------------------- Printed successfully! ----------------------------------\n";
		return true;
	}
	else if (source == 2) // print on file
	{
		ofstream out("student-info.txt",ios::trunc);
		out << "\n--------------------------------------------------------------------------------------------\n";
		out << "                                    Student(s) Information                                ";
		out << "\n--------------------------------------------------------------------------------------------\n";
		if (order == 1)
		{
			Ascending(root, out);
		}
		else if (order == 2)
		{
			Descending(root, out);
		}
		out << "\n---------------------------------- printed successfully! ----------------------------------\n";
		return true;
	}
	else
	{
		//if source not equal to '1' and '2', then return false
		return false;
	}
}

bool BST::CloneSubtree(BST t1, type item)
{
	if (t1.root == NULL)
	{
		cout << "The BST is empty!" << endl;
		return false;
	}

	CloneSubtree2(t1.root, item);
	return true;
}

void BST::CloneSubtree2(BTNode* cur, type item)
{
	if (cur == NULL)
	{
		return;
	}
	if (item.compare2(cur->item))
	{
		root = new BTNode(cur->item);
		CloneSubtree3(root, cur);

		return;
	}

	CloneSubtree2(cur->left, item);
	CloneSubtree2(cur->right, item);
}

void BST::CloneSubtree3(BTNode* cur_t2, BTNode*cur_t1)
{
	if (cur_t1 == NULL) return;	//Base case

	//Haven't copy the whole subtree
	if (cur_t1->left != NULL || cur_t1->right != NULL) {

		//Copy left node
		if (cur_t1->left != NULL) {
			cur_t2->left = new BTNode(cur_t1->left->item);
		}

		//Copy right node
		if (cur_t1->right != NULL) {
			cur_t2->right = new BTNode(cur_t1->right->item);
		}
	}

	CloneSubtree3(cur_t2->left, cur_t1->left); //Recursive case
	CloneSubtree3(cur_t2->right, cur_t1->right);
}

bool BST::printLevelNodes()
{
	BTNode* cur;
	Queue queue;
	int level = 0; //count the level of nodes
	int count = 0; // count the node in each level

	if (empty())return false;
	cout << "\n--------------------------------------------------------------------------------------------\n";
	cout << "                                   All level node(s) is/are printed                               ";
	cout << "\n--------------------------------------------------------------------------------------------\n";

	level++; //if not empty, there is a root in BST so add level by 1
	queue.enqueue(root); // store address of root
	while (!queue.empty())
	{
		count = queue.size();
		cout << "Level " << level << " nodes: ";
		while (count > 0)
		{
			queue.dequeue(cur);
			cout << setw(6) << left << cur->item.id;
			
			if (cur->left != NULL) 
			{
				queue.enqueue(cur->left);
			}
		
			if (cur->right != NULL)
			{
				queue.enqueue(cur->right);
			}
			count--;
		}
		level++;
		cout << endl;
	}
	return true;
}

bool BST::printPath()
{
	BTNode* cur = root;
	int path[1000];
	printPathRecur(cur, path, 0);
	return true;
}

bool BST::printPathRecur(BTNode* cur, int path[], int length)
{
	if (cur == NULL)
	{
		return false;
	}
	if (cur == root)
	{
		cout << "Below are all the external paths for the tree:\n" << endl;
	}
	path[length] = cur->item.id;
	length++;
	if (cur->left == NULL && cur->right == NULL)
	{
		printPath2(path, length);
	}
	else
	{
		printPathRecur(cur->left, path, length);
		printPathRecur(cur->right, path, length);
	}
}

void BST::printPath2(int path[], int length)
{
	int i;
	for (i = 0; i < length; i++)
	{
		cout << setw(6) << left << path[i];
	}
	cout << endl;
}

void TreeOperation(BTNode* node)
{
	BTNode* oldLeft;
	if (node == NULL)return;
	TreeOperation(node->left);
	TreeOperation(node->right);
	oldLeft = node->left;
	node->left = new BTNode(node->item);
	node->left->left = oldLeft;
}