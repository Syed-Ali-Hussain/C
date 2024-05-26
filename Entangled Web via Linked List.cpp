#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *up;
    Node *down;
    Node *right;
    Node *left;

    Node()
    {
        data = 0;
        up = NULL;
        down = NULL;
        right = NULL;
        left = NULL;
    }

    Node(int data1)
    {
        data = data1;
        up = NULL;
        down = NULL;
        left = NULL;
        right = NULL;
    }

    Node(int data1, Node *&u, Node *&d, Node *&r, Node *&l)
    {
        data = data1;
        up = u;
        down = d;
        left = l;
        right = r;
    }

    ~Node(){};
};

class LinkedList
{
    Node *head;
    int rowws;
    int columns;

public:
    LinkedList()
    {
        head = NULL;
        rowws = 0;
        columns = 0;
    }

    ~LinkedList()
    {
        Node *current = head;
        while (current != NULL)
        {
            Node *r = current->right;
            while (r != NULL)
            {
                Node *d = r->down;
                delete r;
                r = d;
            }
            delete current;
            current = r;
        }
    }

    void insertAtHead()
    {
        Node *new_node = new Node;
        head = new_node;
    }
    // Function to attach a node at a given position of a specified node
    void attachNode(Node *baseNode, int val, char position)
    {
        if (!baseNode)
        {
            cout << "Base node is nullptr!" << endl;
            return;
        }

        Node *newNode = new Node(val);

        switch (position)
        {
        case 'U':
            newNode->down = baseNode;
            if (baseNode->up)
            {
                baseNode->up->down = newNode;
            }
            newNode->up = baseNode->up;
            baseNode->up = newNode;
            break;
        case 'D':
            newNode->up = baseNode;
            if (baseNode->down)
                baseNode->down->up = newNode;
            newNode->down = baseNode->down;
            baseNode->down = newNode;
            break;
        case 'L':
            newNode->right = baseNode;
            if (baseNode->left)
                baseNode->left->right = newNode;
            newNode->left = baseNode->left;
            baseNode->left = newNode;
            break;
        case 'R':
            newNode->left = baseNode;
            if (baseNode->right)
                baseNode->right->left = newNode;
            newNode->right = baseNode->right;
            baseNode->right = newNode;
            break;
        default:
            cout << "Invalid position specified!" << endl;
        }
    }

    void createGrid(int rows, int cols)
    {
        rowws = rows;
        columns = cols;
        head = new Node(); // Create head node
        Node *current = head;

        // Create grid horizontally
        for (int i = 0; i < cols; i++)
        {
            current->right = new Node();
            current->right->left = current;
            current = current->right;
        }

        Node *temp = head;

        // Create grid vertically and connect nodes
        for (int i = 0; i < rows; i++)
        {
            temp->down = new Node();
            temp->down->up = temp;
            temp = temp->down;

            Node *currentRow = temp;
            current = temp->up;

            for (int j = 0; j < cols; j++)
            {
                current = current->right;
                currentRow->right = new Node();
                currentRow->right->left = currentRow;
                currentRow->right->up = current;
                current->down = currentRow->right;
                currentRow = currentRow->right;
            }
        }

        // Now taking user input
        Node *puter = head;
        Node *c = head;
        for (int i = 0; i < rows; i++)
        {
            cout << "Enter your row" << endl;
            for (int j = 0; j < cols; j++)
            {
                cout << "Number : " << j << endl;
                int data_input;
                cin >> data_input;
                puter->data = data_input;
                puter = puter->right;
            }
            c = c->down;
            puter = c;
        }
    }

    void printCol()
    {
        Node *temp = head;
        while (temp->down != NULL)
        {
            cout << temp->data << endl;
            temp = temp->down;
        }
    }

    void printEntagledWeb() // for printing the whole web, passing a Node pointer is not required at all.
    {
        Node *printer = head;
        Node *c = head;
        while (c->down != NULL)
        {
            while (printer->right != NULL)
            {
                cout << printer->data << " ";
                printer = printer->right;
            }
            c = c->down;
            printer = c;
            cout << endl;
        }
        cout << endl;
    }

    void changeNode(int data, int value)
    {
        Node *temp = head;
        Node *temp2 = head;
        while (temp2->down != NULL)
        {
            while (temp->right != NULL)
            {
                if (temp->data == data)
                {
                    temp->data = value;
                    return;
                }
                temp = temp->right;
            }
            temp2 = temp2->down;
            temp = temp2;
        }
    }

    bool isNodePresent(int data)
    {
        Node *temp = head;
        Node *temp2 = head;
        while (temp2->down != NULL)
        {
            while (temp->right != NULL)
            {
                if (temp->data == data)
                {
                    return true;
                }
                temp = temp->right;
            }
            temp2 = temp2->down;
            temp = temp2;
        }
        return false;
    }

    int nextRow(int data)
    {
        // Row of next node = (sum of all digits in data % number of rows) + 1
        int sum = 0;
        while (data != 0)
        {
            sum += data % 10;
            data = data / 10;
        }
        int next_row = (sum % rowws) + 1;
        return next_row;
    }

    int nextColumn(int data)
    {
        // Column of next node = number of digits
        int c = 0;
        while (data != 0)
        {
            data = data / 10;
            c++;
        }
        return c;
    }

    int getColumn(int data1)
    {
        Node *c = head;
        Node *r = head;
        int column = 1;
        while (c->right != NULL)
        {
            while (r->down != NULL)
            {
                if (r->data == data1)
                {
                    return column;
                }
                r = r->down;
            }
            c = c->right;
            column++;
            r = c;
        }
    }

    int getRow(int data1)
    {
        Node *c = head;
        Node *r = head;
        int row = 1;
        while (c->right != NULL)
        {
            while (r->down != NULL)
            {
                if (r->data == data1)
                {
                    return row;
                }
                row++;
                r = r->down;
            }
            row = 1;
            c = c->right;
            r = c;
        }
    }

    void visited(Node *Current)
    {
        Node *temp = Current;
        int array[100];

        for (int i = 0; i < 100; i++)
        {
            array[i] = 0;
        }

        int row_steps_from_head = getRow(Current->data);
        int col_steps_from_head = getColumn(Current->data);

        while ((row_steps_from_head != nextRow(temp->data) && col_steps_from_head != nextColumn(temp->data)))
        {
            int count = 0;
            int n_r = nextRow(temp->data);
            int n_c = nextColumn(temp->data);

            // moving to next node via rows
            for (int i = 0; i < n_r; i++)
            {
                if (n_r > row_steps_from_head)
                {
                    temp = temp->down;
                    row_steps_from_head++;
                }
                else if (n_r < row_steps_from_head)
                {
                    temp = temp->up;
                    row_steps_from_head--;
                }
            }
            // moving via columns now
            for (int i = 0; i < n_c; i++)
            {
                if (n_c > col_steps_from_head)
                {
                    temp = temp->right;
                    col_steps_from_head++;
                }
                else if (n_c < col_steps_from_head)
                {
                    temp = temp->left;
                    col_steps_from_head--;
                }
            }

            count++;
            cout << temp->data << " -> ";

            for (int i = 0; i < 100; i++)
            {
                if (array[i] == temp->data)
                {
                    cout << "Crossed over same data so closing" << endl;
                    count = 100;
                }
            }
            for (int i = 0; i < 100; i++)
            {
                if (array[i] == 0)
                {
                    array[i] = temp->data;
                    break;
                }
            }

            if (count == 100)
            {
                cout << "Stopping as of condition";
                break; // stopping the process if target not found after 100 shots
            }
        }
        cout << "Target Found" << endl;
        cout << endl;
        printEntagledWeb();
    }

    Node *getNode(int data1)
    {
        if (isNodePresent(data1))
        {
            Node *temp = head;
            Node *temp2 = head;
            while (temp2 != NULL)
            {
                while (temp != NULL)
                {
                    if (temp->data == data1)
                    {
                        return temp;
                    }
                    temp = temp->right;
                }
                temp2 = temp2->down;
                if (temp2 != NULL)
                {
                    temp = temp2;
                }
            }
        }
        else
        {
            cout << "No node with such data found" << endl;
        }
        return nullptr; // Return nullptr if node not found
    }
};

int main()
{
    LinkedList list_test;
    list_test.createGrid(4, 4);
    list_test.printEntagledWeb();
    // list_test.changeNode(3, 110);
    list_test.printEntagledWeb();
    cout << list_test.isNodePresent(77) << endl;
    cout << "next row is : " << list_test.nextRow(3401) << endl;
    cout << "next column is : " << list_test.nextColumn(3401) << endl;

    Node *node = list_test.getNode(3401); // I am using a value in between the path so that it works from anywhere not just start point.

    list_test.visited(node);

    // Node *node1 = list_test.getNode(97);
    // list_test.visited(node1);
}