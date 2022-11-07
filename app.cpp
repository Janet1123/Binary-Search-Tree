//REFERENCES
//[1] Text and reference books for UCCD1024

#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include	"BST.h"
#include    "Student.h"
#include    "Stack.h"

using namespace std;



int main()
{
	BST t1;
	
	readFile("student2.txt", &t1);
	t1.TreeOperation();

	return 0;
}
void checkDuplicate(BTNode* cur, int Id, bool& duplicate)
{
	if (cur == NULL)return;
	Student item = cur->item;
	if (item.compare3(Id))
	{
		duplicate = true; //the id have been exist
		return;
	}
	checkDuplicate(cur->left, Id, duplicate);
	checkDuplicate(cur->right, Id, duplicate);
}

bool readFile(const char* filename, BST* t1)
{
	char r[999];
	int count = 0; //count the number of student inserted
	cout << "Reading File..." << endl;
	ifstream in(filename);
	if (!in)
	{
		cout << "Unable to open this file!\n\n";
		return false;
	}
	else
	{
		int duplicate_count = 0; // to count number of duplicate result(s) found
		while (!in.eof())
		{
			Student* stuNode = new Student; // new memory space for student node
			if (!stuNode)
			{
				return false;
			}
			char Name[30];
			char Address[100];
			in >> r >> r >> r; // ignore "Student Id ="
			in >> stuNode->id;
			in >> r >> r;

			in >> Name; //read first name
			in.getline(r, 30); //read remaining name
			strcat(Name, r); // combine first name and remaining name to become a full name
			strcpy(stuNode->name, Name);
			in >> r >> r;
			in >> Address; //read first word of address
			in.getline(r, 100); // read the remaining address
			strcat(Address, r);
			strcpy(stuNode->address, Address);
			in >> r >> r;
			in >> stuNode->DOB;
			in >> r >> r >> r;
			in >> stuNode->phone_no;
			in >> r >> r;
			in >> stuNode->course;
			in >> r >> r;
			in >> stuNode->cgpa;

			//check duplicate before insert into BST
			bool duplicate = false;

			checkDuplicate(t1->root, stuNode->id, duplicate);
			if (!duplicate)
			{
				//if no existing record, then insert record
				t1->insert(*stuNode);
				count++;
			}
			else
			{
				duplicate_count++;
				cout << duplicate_count << " Duplicate result(s) found...unable insert from the file!" << endl;

			}
		}
		cout << endl;
		cout << count << " record of students have been successfully read.\n\n";
	}
	return true;
}
