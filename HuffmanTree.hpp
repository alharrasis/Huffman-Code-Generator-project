/* Name: Shahad Al Harrasi
   U#: U41606760

   Name: Dariya Alibi
   U#: U58222623
*/

/*****************
 //Huffman Tree Class Header File
*****************/
#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP
#include "HeapQueue.hpp"
#include "HuffmanBase.hpp"
#include <map>
#include <stack>
#include <iostream>
using namespace std;

class HuffmanTree : public HuffmanTreeBase  //Inherits Base Class
{
    public:
        HuffmanTree();  //Constructor
        string compress(const string inputStr);    //Function for encoding and compressing the string
        string serializeTree() const;    //Function for getting tree serial
        string decompress(const string inputCode, const string serializeTree);          //Function for decoding and decompressing the string
        ~HuffmanTree();  //Deconstructor
    private:
        HuffmanNode* root = new HuffmanNode('\0', 0);   //Root node initialized at 0 index with null
        string treeSerial = "";     //String for storing tree serial numebr 1 or 0
        void deinitializeTree(HuffmanNode* p);  //Function for deleting the whole binary tree
        void getCharCode(HuffmanNode* c, string s, map<char, string>& m);   //Function for getting character codes stored ina map
        map<char, size_t> getFrequencyMap(const string inputStr);   //Function for getting the code stored map
        void deinitializeHeapQueue();  //Function for deleting the whole heapqueue
        void makeTree(string myStr);     //Function for inserting values in tree
        std::vector<HuffmanNode *> createNodeList(std::string) const;   //Function for storing nodes in vector and return it
        void postOrderTree(HuffmanNode* p); //Post order traversal of tree
        HuffmanNode* postFixToInFix(std::vector<HuffmanNode*>) const;   //Postfix converter to infix
        bool searchTree(string serStr, int n);  //Search a serial in tree with index
        HeapQueue<HuffmanNode*, HuffmanNode::Compare> sort;     //Sorter queue for storing and comparing nodes values
};
#endif