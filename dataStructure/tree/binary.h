//
// Created by liududu on 17-12-4.
//

#ifndef DATASTRUCTURE_BINARY_H
#define DATASTRUCTURE_BINARY_H

#include <iostream>
#include <cstdlib>

using namespace std;
template <typename T>
class BinaryTree;

/*
 * 节点
 * */
template <typename T>
class TreeNode{
    friend class BinaryTree<T>;
private:
    //T data;
public:
    T data;
    TreeNode<T>* left;
    TreeNode<T>* right;
    TreeNode(T data){
        this->data = data;
        left = NULL;
        right = NULL;
    }
};

template <typename T>
class BinaryTree{
private:
    TreeNode<T>* root;
    void _preOrder(TreeNode<T>* root, void (*handle)(T)){
        if(root == NULL)
            return;
        _preOrder(root->left,handle);
        handle(root->data);
        _preOrder(root->right,handle);
    }
    void _postOrder(TreeNode<T>* root, void (*handle)(T)){
        if(root == NULL)
            return;
        _postOrder(root->left,handle);
        _postOrder(root->right,handle);
        handle(root->data);
    };
    void _middleOrder(TreeNode<T>* root, void (*handle)(T)){
        if(root == NULL)
            return;
        handle(root->data);
        _middleOrder(root->left,handle);
        _middleOrder(root->right,handle);
    };
    TreeNode<T>* _createTree(TreeNode<T>* &root){
        T temp;
        cin>>temp;
        if(temp == 'z')
            return root;
        root = new TreeNode<T>(temp);
        _createTree(root->left);
        _createTree(root->right);
        return root;
    }
public:
    void createTree(){
        root = _createTree(root);
    };
    void preOrder(void handle(T)){
        _preOrder(root,handle);
    };
    void postOrder(void handle(T)){
        _postOrder(root, handle);
    };
    void middleOrder(void handle(T)){
        _middleOrder(root,handle);
    };
};

#endif //DATASTRUCTURE_BINARY_H
