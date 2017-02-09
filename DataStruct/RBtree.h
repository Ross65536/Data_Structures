#ifndef __RBtreerk
#define __RBtreerk

#include <utility>
#include "BST.h"

namespace rk
{
	template <class T, class Compare_Less = std::less<T> >
	class RBtree;

	template <class T, class Compare_Less = std::less<T>>
	class RBNode 
	{
	private:
		friend class RBtree<T, Compare_Less>;
		friend class BST<T, Compare_Less, RBNode>;
		//data
		const T data;
		bool bred; ///< true - red node, false - black node
		RBNode<T, Compare_Less> * left;
		RBNode<T, Compare_Less> * right;
		RBNode<T, Compare_Less> * parent; ///< if NULL then node is the root
		//functions
		RBNode(const T &val, RBNode* parent, const bool bred = true) : data(val), left(0), right(0), parent(parent), bred(bred) {};
		RBNode(const RBNode<T, Compare_Less> &node) : data(node.data), bred(node.bred), left(0), right(0), parent(0) {};

	};

	template <class T, class Compare_Less = std::less<T> >
	class RBtree : public rk::BST<T, Compare_Less, RBNode<T, Compare_Less> >
	{
	private:
		typedef RBNode<T, Compare_Less> Node;
		enum Utility_Enum { NODE_FOUND, LEFT_NULL, RIGHT_NULL};
		typedef std::pair<Utility_Enum, Node*> RB_Utility_Pair;
		//functions
		inline RB_Utility_Pair insert_find(const T& val); ///< returns a pair with .first having special values
	public:
		
		RBtree(const T& fail_d = T()) : BST(fail_d) {};
		RBtree(const RBtree<T, Compare_Less> &rb) : BST(rb) { root = copy_Subtree(rb.root); };
		bool insert(const T& val);
	};

	

	template<class T, class Compare_Less>
	inline typename rk::RBtree<T, Compare_Less>::RB_Utility_Pair rk::RBtree<T, Compare_Less>::insert_find(const T & val)
	{
		Compare_Less less;

		for (Node * curr_node = root; ; )
		{

			if (less(val, curr_node->data))
			{
				if (curr_node->left == 0)
					return { LEFT_NULL, curr_node };
				else
					curr_node = curr_node->left;
			}
			else if (less(curr_node->data, val))
			{
				if (curr_node->right == 0)
					return { RIGHT_NULL, curr_node };
				else
					curr_node = curr_node->right;
			}
			else
			{
				return { NODE_FOUND, curr_node };
			}
		}
	}

	template<class T, class Compare_Less>
	inline bool rk::RBtree<T, Compare_Less>::insert(const T & val)
	{
		if (empty())
		{
			root = new Node(val, NULL, false); //root is black
			return true;
		}
		else
		{
			auto pair = insert_find(val);
			if (pair.first == NODE_FOUND) // val already in tree
				return false;
			

			if (pair.first == LEFT_NULL)
			{
				pair.second->left = new Node(val, pair.second);
			}
			else //right NULL
			{
				pair.second->right = new Node(val, pair.second);
			}

			//insert_rebalance();
			return true;
	
		}	
	}




}


#endif
