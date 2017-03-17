#include <iostream>
#include <cstdlib>
#include <queue>

using namespace std;

struct Node	{
	double x;
	double y;
	struct Node* left;
	struct Node* right;
	int depth;
} ;
struct Node* root=NULL;

struct Node* makeNode(double x, double y)	{
	struct Node* temp = new Node;
	temp->x = x;
	temp->y = y;
	temp->left = NULL;
	temp->right = NULL;
	temp->depth = 0;
	return temp;
}

class KDtree	{
public:
    //check to see if two Node structs are equal
    bool equalCoordinates(struct Node* temp, struct Node* toBeInserted)	{
		if(temp->x == toBeInserted->x && temp->y == toBeInserted->y)	{
			return true;
		}
		else	{
			return false;
		}
	}

    //return the successive direction where toBeInserted will be further inserted
	struct Node* getDirection(struct Node* temp, struct Node* toBeInserted)	{
	    if(temp->depth % 2 == 0)    {
	         if(toBeInserted->x <= temp->x) {
	             return temp->left;
	         }
	         else   {
	             return temp->right;
	         }
	    }
	    else    {
	        if(toBeInserted->y <= temp->y) {
	             return temp->left;
	         }
	         else   {
	             return temp->right;
	         }
	    }
	}

	//insert into the final direction found
    struct Node* insertPointInFinalDirection(struct Node* temp, struct Node* toBeInserted)	{
		if(temp->depth % 2 == 0)    {
	         if(toBeInserted->x <= temp->x) {
	             temp->left = toBeInserted;
	         }
	         else   {
	             temp->right = toBeInserted;
	         }
	    }
	    else    {
	        if(toBeInserted->y <= temp->y) {
	             temp->left = toBeInserted;
	         }
	         else   {
	             temp->right = toBeInserted;
	         }
	    }
	}

    //insert: @return true for successful search, false for unsuccessful search
    bool insert(struct Node* toBeInserted)   {
        if(root == NULL)	{
				root = toBeInserted;
				return true;
		}

        struct Node *temp = root;
			while(temp != NULL && !equalCoordinates(temp, toBeInserted))	{
			    toBeInserted->depth = toBeInserted->depth + 1;
				struct Node* direction = getDirection(temp, toBeInserted);
				if(direction == NULL)    {
				    insertPointInFinalDirection(temp, toBeInserted);
				    temp = NULL;
				    return true;
				}
				else    {
				    temp = direction;
				}
			}

			return false;

    }

    //insert: @return true for successful search, false for unsuccessful search
    bool insert(double x, double y) {
        struct Node* temp = makeNode(x, y);
        return insert(temp);
    }

    //sample input for testing
    void sampleInput()   {
        insert(4,4);
    	insert(3,3);
    	insert(2,2);
    	insert(1,1);
    	insert(0,0);
    	insert(5,6);
    	insert(7,8);
    }

        //searching: @return true for successful search, false for unsuccessful search
    bool search(struct Node* toBeSearched) {
        if(root == NULL)	{
			return false;
		}

		if(equalCoordinates(root, toBeSearched))    {
		    return true;
		}

        struct Node *temp = root;
        while(temp != NULL) {
            if(equalCoordinates(temp, toBeSearched))    {
                return true;
            }
            else    {
                temp = getDirection(temp, toBeSearched);
            }
        }
        return false;
    }

    //searching: @return true for successful search, false for unsuccessful search
    bool search(double x, double y) {
        struct Node* temp = makeNode(x,y);
		return search(temp);
    }

    //function for level order traversal using BFS
	void levelOrderTraversal(struct Node* temp) {
	    queue<struct Node*> q;
	    if(q.empty())
	        q.push(temp);

	    while(!q.empty())   {
	    	struct Node* popped = q.front();
	        q.pop();
	        cout << "(" << popped->x <<", " << popped->y << ") ";
	        if(popped->left != NULL)
	            q.push(popped->left);
	        if(popped->right != NULL)
	            q.push(popped->right);
	    }
	}
};

int main()  {

    KDtree kDTree;
    kDTree.sampleInput();

    //searching
    cout << kDTree.search(4,4) << endl;
	cout << kDTree.search(1,1) << endl;
	cout << kDTree.search(7,8) << endl;
	cout << kDTree.search(7,7) << endl;
	cout << kDTree.search(80,44) << endl;

    //traverse tree using level order traversal
	cout << "Level Order Traversal using BFS: ";
	kDTree.levelOrderTraversal(root);

    return 0;
}
