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
		void insert_rebalance(Node* inserted_Node);
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
	inline void rk::RBtree<T, Compare_Less>::insert_rebalance(Node * ins_Node)
	{
		while (ins_Node->parent != NULL && ins_Node->parent->parent!=NULL
			&& (ins_Node->bred && ins_Node->parent->bred))
		{
			bool bcurrent_left_of_parent;
			bool bparent_left_of_grandparent;

			auto parent_Node = ins_Node->parent;
			auto grandparent_Node = parent_Node->parent;

			if (ins_Node == parent_Node->left)
				bcurrent_left_of_parent = true;
			else
				bcurrent_left_of_parent = false;

			if (parent_Node == grandparent_Node->left)
				bparent_left_of_grandparent = true;
			else
				bparent_left_of_grandparent = false;

			Node * uncle_Node = (bparent_left_of_grandparent) ? grandparent_Node->right : grandparent_Node->left;

			if ((uncle_Node != NULL) && parent_Node->bred && uncle_Node->bred) // recolor - parent and uncle red
			{
				parent_Node->bred = false;
				uncle_Node->bred = false;
				grandparent_Node->bred = true;
				ins_Node = grandparent_Node;
			}
			else // returns from loop here
			{
				Node ** grandparent_Node_location;
				if (grandparent_Node->parent == NULL)
					grandparent_Node_location = &root;
				else if (grandparent_Node == grandparent_Node->parent->left)
					grandparent_Node_location = &grandparent_Node->parent->left;
				else
					grandparent_Node_location = &grandparent_Node->parent->right;

					
				if (bparent_left_of_grandparent == bcurrent_left_of_parent) // both Node and parent on the left or right side.  
				{
					if (bparent_left_of_grandparent) //left side. parent - red, grandparent - black, uncle - black
					{
						grandparent_Node->bred = true;
						parent_Node->bred = false;

						grandparent_Node->left = parent_Node->right;
						if (grandparent_Node->left != NULL)
							grandparent_Node->left->parent = grandparent_Node;

						parent_Node->right = grandparent_Node;
						parent_Node->parent = grandparent_Node->parent;
						grandparent_Node->parent = parent_Node;

						*grandparent_Node_location = parent_Node;
							

					}
					else  //right side. parent - red, grandparent - black, uncle - black
					{
						grandparent_Node->bred = true;
						parent_Node->bred = false;

						grandparent_Node->right = parent_Node->left;
						if (grandparent_Node->right != NULL)
							grandparent_Node->right->parent = grandparent_Node;

						parent_Node->left = grandparent_Node;
						parent_Node->parent = grandparent_Node->parent;
						grandparent_Node->parent = parent_Node;

						*grandparent_Node_location = parent_Node;
					}
				}
				else // Node and parent on different sides
				{
					if (bparent_left_of_grandparent) //parent - left, node - right. parent - red, grandparent - black,  uncle balck
					{
						grandparent_Node->bred = true;
						ins_Node ->bred = false;

						grandparent_Node->left = ins_Node->right;
						if (grandparent_Node->left != NULL)
							grandparent_Node->left->parent = grandparent_Node;

						parent_Node->right = ins_Node->left;
						if (parent_Node->right != NULL)
							parent_Node->right->parent = parent_Node;

						ins_Node->left = parent_Node;
						parent_Node->parent = ins_Node;

						ins_Node->right = grandparent_Node;
						grandparent_Node->parent = ins_Node;

						*grandparent_Node_location = ins_Node;
					}
					else //parent - right, node - left. parent - red, grandparent - black,  uncle balck
					{
						grandparent_Node->bred = true;
						ins_Node->bred = false;

						grandparent_Node->right = ins_Node->left;
						if (grandparent_Node->right != NULL)
							grandparent_Node->right->parent = grandparent_Node;

						parent_Node->left = ins_Node->right;
						if (parent_Node->left != NULL)
							parent_Node->left->parent = parent_Node;

						ins_Node->right = parent_Node;
						parent_Node->parent = ins_Node;

						ins_Node->left = grandparent_Node;
						grandparent_Node->parent = ins_Node;

						*grandparent_Node_location = ins_Node;

					}
				}

				return;
			}
		}

		if (ins_Node->parent == NULL) //root
			ins_Node->bred = false;

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
			const bool bred = pair.second->bred;

			if (pair.first == NODE_FOUND) // val already in tree
				return false;
			

			if (pair.first == LEFT_NULL)
			{
				pair.second->left = new Node(val, pair.second);
				pair.second = pair.second->left;
			}
			else //right NULL
			{
				pair.second->right = new Node(val, pair.second);
				pair.second = pair.second->right;
			}

			if (bred ) //rebalance if parent is red
				insert_rebalance(pair.second);

			return true;
	
		}	
	}




}


#endif
