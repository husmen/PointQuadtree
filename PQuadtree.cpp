#include <iostream>
#include <cstdlib>
#include <queue>
#define NULL 0

using namespace std;

struct Node	{
public:
	double x;
	double y;
	Node* NW;
	Node* NE;
	Node* SE;
	Node* SW;

	//constructor
	//Node(double x, double y):  x(x),y(y),NW(NULL),NE(NULL),SE(NULL),SW(NULL) {}
} ;
struct Node* root;

struct Node* makeNode(double x, double y)	{
	struct Node* temp = new Node;
	temp->x = x;
	temp->y = y;
	temp->NW = NULL;
	temp->NE = NULL;
	temp->SE = NULL;
	temp->SW = NULL;
	return temp;
}


class PointQuadtree	{
public:
	bool equalCoordinates(struct Node* temp, struct Node* toBeInserted)	{
		if(temp->x == toBeInserted->x && temp->y == toBeInserted->y)	{
			return true;
		}
		else	{
			return false;
		}
	}

	//return the successive quadrant where toBeInserted will be further inserted
	Node* getQuadrant(struct Node* temp, struct Node* toBeInserted)	{
		cout<<temp->x<<" ";
		if(temp->x < toBeInserted->x)	{
			if(temp->y < toBeInserted->y)	{
				return temp->SW;
			}
			else	{
				return temp->NW;
			}
		}

		if(temp->y < toBeInserted->y)	{
			return temp->SE;
		}
		else	{
			return temp->NE;
		}


	}

	bool insert(struct Node* root, struct Node* toBeInserted)	{
			if(root == NULL)	{
				cout<<toBeInserted->x<<" ";
				root = toBeInserted;
				return true;
			}

			struct Node* temp = root;
			while(temp != NULL && !equalCoordinates(temp, toBeInserted))	{
				//Node* temp_ = temp;
				struct Node* quadrant = getQuadrant(temp, toBeInserted);
				insert(quadrant, toBeInserted);
			}
			return true;
	}

	bool insert(struct Node* root, double x, double y)	{
		struct Node* temp = makeNode(x,y);
		return insert(root, temp);
	}

	queue<struct Node*> q;
	void levelOrderTraversal(struct Node* temp) {
	    if(q.empty())
	        q.push(temp);

	    while(!q.empty())   {
	    	struct Node* popped = q.front();
	        q.pop();
	        cout << "(" << popped->x <<", " << popped->y << ") ";
	        if(popped->NW != NULL)
	            q.push(popped->NW);
	        if(popped->NE != NULL)
	            q.push(popped->NE);
	        if(popped->SE != NULL)
	        	q.push(popped->SE);
	        if(popped->SW != NULL)
	        	q.push(popped->SW);
	    }
	}

};

int main()	{
	cout<<"HI"<<endl;
	PointQuadtree pointQuadtree;
	//struct Node* root = NULL;

	pointQuadtree.insert(root, 4,4);
	pointQuadtree.insert(root, 3,3);
	pointQuadtree.insert(root, 2,2);
	pointQuadtree.insert(root, 1,1);
	pointQuadtree.insert(root, 0,0);
	pointQuadtree.insert(root, 5,6);

	//traverse tree using level order traversal
	//pointQuadtree->levelOrderTraversal(root);


	return 0;
}
