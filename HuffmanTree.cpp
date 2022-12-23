/* Name: Shahad Al Harrasi
   U#: U41606760

   Name: Dariya Alibi
   U#: U58222623
*/


#include "HuffmanTree.hpp"
#include<vector>
//Delete everything for new tree in constructor
HuffmanTree::HuffmanTree()
{	
	std::cout.setstate(std::ios_base::failbit);
        deinitializeTree(root);         //Delete whole tree from root
        deinitializeHeapQueue();        //Delete whole HeapQueue
}
//Function for deleting the whole binary tree
void HuffmanTree::deinitializeTree(HuffmanNode* temp)
{
        if(temp == nullptr)     //if current node is null, there's nothing to do
                return;

        while(!(temp -> parentCheck()))         //Iterative loop till temp node becomes parent
        {
                if(temp -> left != nullptr)
                        temp = temp -> left;    //if not null move to left
        
                if(temp -> right != nullptr)    //else move right
                        temp = temp -> right;
                else
                        delete temp;    //delete from leaf
        }

        root = nullptr;
        delete root;    //finally delete last root
}
//Function for deleting the whole heapqueue
void HuffmanTree::deinitializeHeapQueue()
{
        for(int i = 1; !sort.isEmptyQueue(); i++)
        {
                HuffmanNode* temp =  sort.min();
                sort.deleteMinimum();   //Delete from minimum
                temp = nullptr;
                delete temp;
        }
}

//Function for getting character codes stored in a map
void HuffmanTree::getCharCode(HuffmanNode* tempNode, string myStr, map<char,string>& myMap){
 
    if(tempNode->left != nullptr)       //if we move to left then add 0 in string
    {
        getCharCode(tempNode->left,myStr+"0", myMap);
    } 
    if(tempNode->right != nullptr)       //if we move to right then add 1 in string
    {
        getCharCode(tempNode->right,myStr+"1", myMap);
    }

    if(tempNode->leafCheck())   //finally if we get leaf then make a pair and add in map
    {
        pair<char,string> tempPair;
        tempPair.first = tempNode->getCharacter();
        tempPair.second = myStr;
        myMap.insert(tempPair);
        return;
    }

}

//Function for encoding and compressing the string
string HuffmanTree::compress(const string myStr)
{
        makeTree(myStr); //Make Binary tree using the string
        map<char,std::string> charMap;
        map<char, string>::iterator it;

        getCharCode(root,"",charMap);   //Save codes in charMap

        string returnStr = "";
        
        int i = 1;
        while(i < int(myStr.size()) + 1)        //Loop till max size
        {
                it = charMap.begin();   //Use Iterator and add to return str
                while(it != charMap.end())
                {
        
                        if(it->first != myStr[i - 1]) 
                                it++;
                        else
                        {
                                returnStr += it->second;
                                break;
                        }
                }
                i++;
        }
        //Deinitialize tree after post ordering it
        postOrderTree(root);
        deinitializeTree(root);

        return returnStr;
}
//Function for storing nodes in vector and return it
vector<HuffmanNode*> HuffmanTree::createNodeList(string serStr) const 
{
    bool flag = false;
    vector<HuffmanNode*> nodeVector;
        
    for(int i = 1; i < int(serStr.size()) + 1; i++) 
    {
        if(serStr[i - 1] == 'B' && !flag)
            nodeVector.push_back(new HuffmanNode('\0',0));

        else if(!flag && serStr[i - 1] == 'L')  //Change flag status if its L
        {
            flag = true;
            continue;
        } 
        //Pushback in vector
        else
        {
            nodeVector.push_back(new HuffmanNode(serStr[i - 1], 0));
            flag = false;       //Set flag back to false
        }
    }

        //print the vector & return it
    int i = 1; 
    while(i < int(nodeVector.size()) + 1)
    {
       // std::decompress << nodeVector[i - 1]->getCharacter() << " ";
        i++;
    }
        return nodeVector;
}

//Function for converting Postfix to infix
HuffmanNode* HuffmanTree::postFixToInFix(std::vector<HuffmanNode*> tempVec) const 
{
    std::stack<HuffmanNode*>  temp;
   int i = 1; 
   //Make A stack and push pop using it
   while(i < int(tempVec.size()) + 1)
   {
        HuffmanNode* tempNode = tempVec[i - 1];
        if(tempNode->getCharacter() == '\0' )   //If endl occurs pop top 2 elements
        {      
            HuffmanNode* a = temp.top();
            temp.pop();
            HuffmanNode* b = temp.top();
            temp.pop();
            //Pop top 2 elements and set their left and right and parent
            tempNode->right = a;
            a->parent = tempNode;
            tempNode->left = b;
            b->parent = tempNode;
            temp.push(tempNode);
        } 
        else 
            temp.push(tempNode);
        i++;
    }

    return temp.top();
}

//Function for decoding and decompressing the string
string HuffmanTree::decompress(const string inputStr, const string serializedTree)
{
        deinitializeTree(root); //Delete the whole tree by starting from root
        vector<HuffmanNode*> postOrderVector = HuffmanTree::createNodeList(serializedTree);

        HuffmanNode* tempNode = HuffmanTree::postFixToInFix(postOrderVector);
        HuffmanNode* temp_root = tempNode;
        string returnStr = "";

        int i = 1;
        while(i < int(inputStr.size()) + 1)
        {
                if(inputStr[i - 1] == '0')      //if 0 is found then move to left
                        temp_root = temp_root->left;

                if(inputStr[i - 1] == '1')      //else move right for 1
                        temp_root = temp_root->right;

                if(temp_root -> leafCheck())    //if we get a lef add it to return string
                {
                        returnStr += temp_root->getCharacter();
                        temp_root = tempNode;
                }

                i++;
        }

        return returnStr;
}

 //Function for getting the code stored map
map<char,size_t> HuffmanTree::getFrequencyMap(const string myStr)
{
    map<char,size_t> frequenyMap;
    map<char,size_t>::iterator it;
    pair<char,size_t> tempPair;

    for(unsigned int i = 1; i < myStr.length() + 1; i++) //loop till string length
    {
        char c = myStr[i - 1]; //read a single character
        if(frequenyMap.empty())  //if map is empty create a simple pair and add in map
        {
            tempPair.first = c;
            tempPair.second = 1;
            frequenyMap.insert(tempPair);
            continue;
        }
        //else find the specific character and pair it with 1 then insert
        it = frequenyMap.find(c);

        if(it != frequenyMap.end())
        {
            (*it).second++;
        }
        else
        {
            tempPair.first = c;
            tempPair.second = 1;
            frequenyMap.insert(tempPair);
        }
    }
 
    return frequenyMap;
}

//function for getting tree serial
string HuffmanTree::serializeTree() const
{
    return treeSerial;
}

//Function for inserting values in tree
void HuffmanTree::makeTree(string myStr)
{
    map<char,size_t> freqMap = getFrequencyMap(myStr); //Store the current map frequencies
    map<char,size_t>::iterator i = freqMap.begin();

    while(i != freqMap.end())   //use iterator to add in sorting queue
    {
        sort.AddToQueue(new HuffmanNode((*i).first, (*i).second));
        i++;
    }
        //add to queue according to its frequency
    for(int j = sort.size(); j > 1; j--)
    {
        HuffmanNode* temp1 = sort.min(); 
        sort.deleteMinimum(); 

        HuffmanNode *temp2 = sort.min();
        sort.deleteMinimum();

        HuffmanNode *addToQueue = new HuffmanNode('\0',temp1->getFrequency()+temp2->getFrequency());
        addToQueue->left = temp1;
        addToQueue->right = temp2;
        temp1->parent = addToQueue;
        temp2->parent = addToQueue;
        
        sort.AddToQueue(addToQueue);
    }
    //clear the map and queue
    HuffmanNode* tempRoot = root;
    root = sort.min();
    sort.deleteMinimum();
    delete tempRoot;

    freqMap.clear();
}

//Post order traversal of tree
void HuffmanTree::postOrderTree(HuffmanNode* temp)
{
        if (temp == nullptr)
                return;
        //recursive traversal
        if(temp->left != nullptr)
        {
               postOrderTree(temp->left);
        }
        if(temp->right != nullptr)
        {
                postOrderTree(temp->right);
        }
        //if leaf or parent or node is found break recursion
        if(temp->leafCheck())
        {
                treeSerial+="L";
                treeSerial+=temp -> getCharacter();
        }
        if(temp ->nodeCheck() || temp->parentCheck())
        {
                treeSerial+="B";
        }

}

//function for Searchoing a serial in tree with index
bool HuffmanTree::searchTree(string serStr, int n)
{
        n++;
        bool flag = false;
        bool LFlag = (serStr[n - 1] == 'L');
        bool BFlag = (serStr[n - 1] == 'B');

        if(n - 1== 0)
                return flag;

        else if(n - 1 == 1)
        {
                flag = true;
                return flag;
        }

        if( n <  serStr.size() + 1)
        {
                if((!BFlag && !LFlag) || (serStr[n-2] == 'L' && serStr[n-3] != 'L'))
                {
                        flag = true;
                        return flag;
                }
                else
                {
                        flag = false;
                        return flag;
                }
        
        }
        else
        {
                return flag;
        }
}

//Destructor
HuffmanTree::~HuffmanTree()
{
        //Clean all the data
        deinitializeTree(root);
        deinitializeHeapQueue();
}




