/* Name: Shahad Al Harrasi
   U#: U41606760

   Name: Dariya Alibi
   U#: U58222623
*/

#include "HuffmanBase.hpp"

char HuffmanNode::getCharacter() const
{
  return character;
}

size_t HuffmanNode::getFrequency() const
{
  return frequency;
}

bool HuffmanNode::Compare::operator()(const HuffmanNode &n1, const HuffmanNode &n2) const
{
  if (n1.frequency == n2.frequency) 
  {
      return lessThan ? n1.character < n2.character : n1.character >= n2.character;
  } 
  else 
  {
      return lessThan ? n1.frequency < n2.frequency : n1.frequency >= n2.frequency;
  }
  
}

bool HuffmanNode::Compare::operator()(const HuffmanNode *n1, const HuffmanNode *n2) const
{
  return operator()(*n1, *n2);
}

bool HuffmanNode::leafCheck() const
{
  return (left == nullptr && right == nullptr);
}

bool HuffmanNode::nodeCheck() const
{
  return (left != nullptr || right != nullptr);
};

bool HuffmanNode::parentCheck() const
{
  return (parent == nullptr);
};