#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* left;
    struct node* right;
             };

typedef struct node Node;

// 初始化
Node* init(Node* root);

// 插入
Node* insert(Node* root, int data);

// 删除
Node* delete(Node* root, int data);

// 销毁
Node* deinit(Node* root);

// 中序遍历存放到数组arr中
Node* inorder(Node* root, int* arr);

// 判断一棵树是否为BST
int isValidBST(Node* root);

// 寻找BST中，两节点值之差的最小值
int getMinimumDifference(Node* root);

int main() {
    Node* root = NULL;
    root = init(root);

    root = insert(root,5);
    root = insert(root,4);
    root = insert(root,7);

    int tag = isValidBST(root);

    if (tag == 1)
    {
        int min = getMinimumDifference(root);
        printf("%d",min);
    }
    else
        printf("error");


    return 0;
}

Node* init(Node* root)
{
    root = NULL;
    return root;
}

Node* insert(Node* root, int data)
{
     if (!root)     //空树
     {
         root = (Node*)malloc(sizeof(Node));
         root->data = data;
         root->left = NULL;
         root->right = NULL;

         return root;
     }
     else   //非空树
     {
         if (data <= root->data)
             root->left = insert(root->left, data);
         else
             root->right = insert(root->right, data);
     }

    return root;
}

Node* delete(Node* root, int data)
{
    int find = 0;
    Node* p = root;
    Node* p_parent = NULL;

    //查找该节点
    while (p && !find)
    {
        if (data == p->data)
            find = 1;

        else if (data < p->data)
        {
            p_parent = p;
            p = p->left;
        }

        else
        {
            p_parent = p;
            p = p->right;
        }
    }

    //查找失败
    if (p == NULL)
    {
        printf("no such node in the tree!\n");
        return root;
    }

    //查找成功
    if (p->left == NULL && p->right == NULL)    //叶子结点
    {
        if (p_parent->left == p)
            p_parent->left == NULL;
        else
            p_parent->right == NULL;
        free(p);
    }
    else if (p->left == NULL || p->right == NULL)   //单支树
    {
        if (p == root)  //p为根结点
        {
            if (p->left = NULL)
                root = p->right;
            else
                root = p->left;
        }
        else    //p有父节点
        {
            if (p_parent->left == p && p->left)
               p_parent->left =  p->left;

            else if (p_parent->left == p && p->right)
                p_parent->left =  p->right;

            else if (p_parent->right == p && p->left)
                p_parent->right =  p->left;

            else if (p_parent->right == p && p->right)
                p_parent->right =  p->right;
        }
        free(p);
    }
    else    //p左右子树都有
    {
        //找到p的前驱
        Node* temp = p;
        Node* temp_r = temp->right;

        while (temp_r->right)
        {
            temp = temp_r;
            temp_r = temp_r->right;
        }

        //把p的前驱移动到p处
        p->data = temp_r->data;
        temp->right = temp_r->left;

        free(temp_r);
    }

    return root;
}

Node* deinit(Node* root)
{
    if (root == NULL)
       return NULL;

    deinit(root->left);
    deinit(root->right);

    free(root);
    return NULL;
}

Node* inorder(Node* root, int* arr)
{
    static int i = 0;
    if (root)
    {
        inorder(root->left, arr);

        arr[i] = root->data;
        i++;

        inorder(root->right, arr);
    }
}

int isValidBST(Node* root)
{
    static Node* pre = NULL;

    if (root)
    {
        isValidBST(root->left);

        if (pre!= NULL && pre->data >= root->data )
            return 0;
        pre = root;

        isValidBST(root->right);
    }
    else    //空树
        return 0;

    return 1;
}

int getMinimumDifference(Node* root)
{
    static int diff = INT_MAX;
    static Node* pre = NULL;

    if (root)
    {
        getMinimumDifference(root->left);

        if (pre == NULL && root->left == NULL)
            pre = root;
        else
        {
            if ((root->data - pre->data) < diff)
            {
                diff = root->data - pre->data;
                pre = root;
            }
        }
        getMinimumDifference(root->right);
    }

    return diff;
}
