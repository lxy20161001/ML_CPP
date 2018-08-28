#ifndef BLACK_REDTREE_RBTREE_H
#define BLACK_REDTREE_RBTREE_H

#include <iostream>
#include <vector>
using namespace std;



template <typename K,typename V>
class RBtree{
private:
    vector<vector<K>> temp;
    const static bool RED = true;
    const static bool BLACK = false;
    class Node{
    public:
        K key;
        V value;
        Node *left;
        Node *right;
        bool color;

        Node(K key,V value){
            this->key = key;
            this->value = value;
            left = 0;
            right = 0;
            color = RED;
        }

        ~Node(){
            delete left;
            delete right;
        }
    };

private:
    Node* root;
    int size;

public:
    RBtree(){
        root = 0;
        size = 0;
    }
    ~RBtree(){
        delete  root;
    }


    int getSize(){
        return size;
    }

    bool isEmpty(){
        return size == 0;
    }

private:
    bool isRed(Node *node){
        if(node == 0) return BLACK;

        return node->color;
        //如果Node为空，那么节点颜色是BLACK
        //否则返回node的本身颜色
    }

public:
    void add(K key,V value){
        root = addRec(root,key,value);
        root->color = BLACK;
    }

private:

    Node* addRec(Node *node,K key,V value){
        if(node==0){
            size++;
            return new Node(key,value);
            //节点空，实例化一个新的节点，并且size++
        }

        if(key<node->key){
            node->left = addRec(node->left,key,value);
        }
        else if(key > node->key){
            node->right = addRec(node->right,key,value);
        }
        else{
            node->value = value;
        }

        if(isRed(node->right) && !isRed(node->left))//右节点是红色，同时左边节点不是红色
        {
                node = leftRotate(node);
        }

        if(isRed(node->left) && isRed(node->left->left))//左子树的左子树和左子树都是红色
        {
                node = rightRotate(node);
        }

        if(isRed(node->left) && isRed(node->right)){
                flipColors(node);
        }

        return node;
    }


    void flipColors(Node *node){
        //三节点同时还要向上融合的情况下
        node->color = RED;
        node->left->color=BLACK;
        node->right->color=BLACK;
    }


    Node* leftRotate(Node *node){
        Node *x = node->right;//创造x用于存储node->right

        node->right = x->left;
        x->left = node;

        x->color = node->color;
        node->color = RED;//cause node->color is the left node of x,and
        // is 3-point-node;

        return x;
    }

    Node* rightRotate(Node* node){
        Node *x = node->left;

        node->left = x->right;//把x的右节点赋予node
        x->right = node;//x的右节点现在为空，可以链接新的节点，就是原先的node

        x->color = node->color;

        node->color = RED;

        return x;
    }

public:
    bool contains(K key){
        return getNode(root,key)!= 0;
    }

    V get(K key) {
        Node *node = getNode(root,key);
        return node==0?0:node->value;
    }

    V getK(K key) {
        Node *node = getNode(root,key);
        return node==0?0:node->key;
    }


    void set(K key,V NewValue){
        Node* node = getNode(root,key);
        if(node == 0){

        }
        else{
            node->value = NewValue;
        }
    }

private:
    Node* getNode(Node* node,K key){
        if(node == 0) return 0;
        if(key==node->key){
            return node;
        }else if(key<node->key){
            return getNode(node->left,key);
        }else{
            return getNode(node->right,key);
        }
    }

public:
    void toString(){
        cout<<"{";
        for (int i = 0; i < getSize(); ++i) {
            if(i<getSize()-1)
                cout << get(i) << ":" << getK(i)<<",";
            else
                cout << get(i) << ":" << getK(i);
        }
        cout<<"}";
        cout<<endl;
    }

public:
    vector<vector<K>>  PreOrder(){
        PreOrderRec(root);
        return temp;
    }
    void PrintNode(Node* node){
        if(node == NULL)
            return;
        temp.push_back({node->value,node->key});
    }
private:
    void PreOrderRec(Node* node){
        if(node == NULL){
            return;}
        PrintNode(node);
        PreOrderRec(node->left);
        PreOrderRec(node->right);
    }
};
