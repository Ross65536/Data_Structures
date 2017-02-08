#ifndef __BSTrk
#define __BSTrk

#include <iterator>

#include "vector.h"

namespace rk
{
	template <class T, class Compare_Less = std::less<T>>
	class BSTNode;

	template <class T, class Compare_Less = std::less<T>, class Node_Type = class BSTNode<T, Compare_Less> >
	class BST;

	//Class - Node
	template <class T, class Compare_Less = std::less<T>>
	class BSTNode
	{
	protected:
		friend class BST<T, Compare_Less>;
		//data
		const T data;
		BSTNode<T, Compare_Less> * left;
		BSTNode<T, Compare_Less> * right;
		//functions
		BSTNode(const T &val) : data(val), left(0), right(0) {};
		BSTNode(const BSTNode<T, Compare_Less> &node) : data(node.val), left(0), right(0) {};
	};

	//Class - Binary search tree 
	template <class T, class Compare_Less = std::less<T>, class Node_Type = class BSTNode<T, Compare_Less> >
	class BST
	{
	protected:
		//data
		Node_Type * root;
		T fail_val;
		//functions
		Node_Type ** find_ptr(const T& val) const;
		Node_Type ** find_Max_from_Node_ptr(const Node_Type * const * Node) const;
		Node_Type ** find_Min_from_Node_ptr(const Node_Type * const * Node) const;
		void destroy_Subtree(Node_Type * Node_start);
		Node_Type * copy_Subtree(const Node_Type * original_Node);
		//Node_Type * ptr_erase(const T & val);
	public:
		class const_iterator;
		class const_reverse_iterator;
		BST(const T& fail_d = T()) : root(0), fail_val(fail_d) {};
		BST(const BST<T, Compare_Less, Node_Type> &bst) : fail_val(bst.fail_val) { root = copy_Subtree (bst.root); };
		~BST();
		void insert(const T& val);
		const T& find(const T& val) const;
		bool empty() const { return root == 0; };
		const T& find_Max() const;
		const T& find_Min() const;
		void erase(const T& val);
		const_iterator erase(const_iterator& itr) { auto val = *itr; ++itr;  erase(val); return itr; };
		const_reverse_iterator erase(const_reverse_iterator& itr);
		void clear();
		BST& operator= (const BST<T, Compare_Less, Node_Type> & rhs);
		/*const T& change_Not_Found_value(const T& fail_val) { this->fail_val = fail_val; };*/
		T& get_Not_Found_value() { return this->fail_val; };
		const_iterator begin() { return const_iterator(this); };
		const_iterator end() { return const_iterator(this, true); };
		const_iterator cbegin() { return begin(); };
		const_iterator cend() { return end(); };
		const_reverse_iterator rbegin() { return const_reverse_iterator(this); };
		const_reverse_iterator rend() { return const_reverse_iterator(this, true); };
		const_reverse_iterator crbegin() { return rbegin(); };
		const_reverse_iterator crend() { return rend(); };
		
		//class - const_iterator - forward const iterator
		class const_iterator : public std::iterator<std::forward_iterator_tag, const T>
		{
		protected:
			friend BST;
			//data
			rk::vector<Node_Type*> Node_ptrs;
			const BST* BST_containter;
			//functions
			void fill_left_Nodes(Node_Type* Node) { for (; Node != NULL; Node = Node->left) Node_ptrs.push_back(Node); };
			const_iterator(BST* BST_containter, bool bend = false) : BST_containter(BST_containter) { if (!bend) fill_left_Nodes(BST_containter->root); };
			const_iterator(const rk::vector<Node_Type*> &Node_ptrs, const BST* BST_containter) : BST_containter(BST_containter), Node_ptrs(Node_ptrs) {};
		public:
			const_iterator() : BST_containter(NULL) {};
			const_iterator(const const_iterator &itr) : Node_ptrs(itr.Node_ptrs), BST_containter(itr.BST_containter) {};
			const_iterator& operator=(const_iterator &itr) { if (this == &itr) return *this; Node_ptrs = itr.Node_ptrs; BST_containter = itr.BST_containter; return *this; };
			const_iterator operator++(int) { auto ret = *this; ++*this; return ret; };
			const_iterator& operator++();
			bool operator!=(const_iterator &itr) const { return !(*this == itr); };
			bool operator==(const_iterator &itr) const ;
			const T& operator*() const { return Node_ptrs.back()->data; };
			const T* operator->() const { return &(Node_ptrs.back()->data); };
		};
		class const_reverse_iterator : public std::iterator<std::forward_iterator_tag, const T>
		{
		private:
			friend BST;
			//data
			rk::vector<Node_Type*> Node_ptrs;
			const BST* BST_containter;
			//functions
			void fill_right_Nodes(Node_Type* Node) { for (; Node != NULL; Node = Node->right) Node_ptrs.push_back(Node); };
			const_reverse_iterator(BST* BST_containter, bool bend = false) : BST_containter(BST_containter), Node_ptrs(Node_ptrs) {};
		public:
			const_reverse_iterator() : BST_containter(NULL) {};
			const_reverse_iterator(const const_reverse_iterator &itr) : Node_ptrs(itr.Node_ptrs), BST_containter(itr.BST_containter) {};
			const_reverse_iterator& operator=(const_reverse_iterator &itr) { if (this == &itr) return *this; Node_ptrs = itr.Node_ptrs; BST_containter = itr.BST_containter; return *this; };
			const_reverse_iterator operator++(int) { auto ret = *this; ++*this; return ret; };
			const_reverse_iterator& operator++();
			bool operator!=(const_reverse_iterator &itr) const { return !(*this == itr); };
			bool operator==(const_reverse_iterator &itr) const;
			const T& operator*() const { return Node_ptrs.back()->data; };
			const T* operator->() const { return &(Node_ptrs.back()->data); };
		};
		
	};

	
	template <class T, class Compare_Less, class Node_Type >
	void BST<T, Compare_Less, Node_Type>::insert(const T& val)
	{
		Node_Type ** found = find_ptr(val);

		if (*found == 0)
		{
			*found = new Node_Type(val);
		}
		else
		{
			return;
		}
	}

	template <class T, class Compare_Less, class Node_Type >
	inline const T& BST<T, Compare_Less, Node_Type>::find(const T& val) const
	{
		Node_Type ** found = find_ptr(val);

		if (*found == 0)
			return fail_val;
		else
			return (*found)->data;
	}


	template <class T, class Compare_Less, class Node_Type >
	Node_Type ** BST<T, Compare_Less, Node_Type>::find_ptr(const T& val) const
	{
		if (root == 0)
		{
			return (Node_Type **) &root;
		}

		Node_Type ** curr_node_ptr = (Node_Type **) &root;
		while (true)
		{
			Compare_Less less;
			Node_Type * curr_node = *curr_node_ptr;

			if (less(val, curr_node->data))
			{
				if (curr_node->left == 0)
					return &curr_node->left;
				else
					curr_node_ptr = &(curr_node->left);
			}
			else if (less(curr_node->data, val))
			{
				if (curr_node->right == 0)
					return &curr_node->right;
				else
					curr_node_ptr = &(curr_node->right);
			}
			else
			{
				return curr_node_ptr;
			}
		}
	}

	template <class T, class Compare_Less, class Node_Type >
	Node_Type** BST<T, Compare_Less, Node_Type>::find_Max_from_Node_ptr(const Node_Type* const * Node) const
	{
		const Node_Type * const * curr_node_ptr = Node;
		while (true)
		{
			if ((*curr_node_ptr)->right == 0)
				return (Node_Type **) curr_node_ptr;
			else
				curr_node_ptr =(const Node_Type **) &((*curr_node_ptr)->right);
			
		}
	}

	template <class T, class Compare_Less, class Node_Type >
	Node_Type** BST<T, Compare_Less, Node_Type>::find_Min_from_Node_ptr(const Node_Type* const * Node) const
	{
		const Node_Type * const * curr_node_ptr = Node;
		while (true)
		{
			if ((*curr_node_ptr)->left == 0)
				return (Node_Type **) curr_node_ptr;
			else
				curr_node_ptr = (const Node_Type **) &((*curr_node_ptr)->left);

		}
	}

	template <class T, class Compare_Less, class Node_Type >
	inline const T & BST<T, Compare_Less, Node_Type>::find_Max() const
	{
		if (root == 0)
			return fail_val;
		else
			return (*find_Max_from_Node_ptr((const Node_Type**) &root))->data;
	}


	/*template <class T, class Compare_Less, class Node_Type >
	Node_Type* BST<T, Compare_Less, Node_Type>::ptr_erase(const T & val)
	{
		auto node_ptr_ptr = find_ptr(val);
		auto node_ptr = *node_ptr_ptr;
		Node_Type* ret;

		if (node_ptr == 0)
		{
			ret = NULL;
		}
		else if (node_ptr->left == 0 && node_ptr->right == 0)
		{
			*node_ptr_ptr = NULL;
			ret = NULL;
		}
		else if (node_ptr->left == 0)
		{
			*node_ptr_ptr = node_ptr->right;
			ret = node_ptr->right;
		}
		else if (node_ptr->right == 0)
		{
			*node_ptr_ptr = node_ptr->left;

		}
		else
		{
			auto replacement_Node_ptr_ptr = find_Max_from_Node_ptr(&node_ptr->left);
			auto replacement_Node_ptr = *replacement_Node_ptr_ptr;

			if (replacement_Node_ptr->left != 0)
			{
				*replacement_Node_ptr_ptr = replacement_Node_ptr->left;
			}
			else
				*replacement_Node_ptr_ptr = 0;

			replacement_Node_ptr->left = node_ptr->left;
			replacement_Node_ptr->right = node_ptr->right;

			*node_ptr_ptr = replacement_Node_ptr;


		}

		delete node_ptr;
		return ret;
	}*/

	template <class T, class Compare_Less, class Node_Type >
	void BST<T, Compare_Less, Node_Type>::erase(const T & val)
	{
		auto node_ptr_ptr = find_ptr(val);
		auto node_ptr = *node_ptr_ptr;

		if (node_ptr == 0)
		{
			return;
		}
		else if (node_ptr->left == 0 && node_ptr->right == 0)
		{
			*node_ptr_ptr = NULL;
		}
		else if (node_ptr->left == 0)
		{
			*node_ptr_ptr = node_ptr->right;
		
		}
		else if (node_ptr->right == 0)
		{
			*node_ptr_ptr = node_ptr->left;
		
		}
		else
		{
			auto replacement_Node_ptr_ptr = find_Max_from_Node_ptr(&node_ptr->left);
			auto replacement_Node_ptr = *replacement_Node_ptr_ptr;

			if (replacement_Node_ptr->left != 0)
			{
				*replacement_Node_ptr_ptr = replacement_Node_ptr->left;
			}
			else
				*replacement_Node_ptr_ptr = 0;

			replacement_Node_ptr->left = node_ptr->left;
			replacement_Node_ptr->right = node_ptr->right;

			*node_ptr_ptr = replacement_Node_ptr;
			

		}

		delete node_ptr;

	}

	template <class T, class Compare_Less, class Node_Type >
	inline BST<T, Compare_Less, Node_Type>::~BST()
	{
		if (root != 0)
		{
			destroy_Subtree(root);
		}
	}

	template <class T, class Compare_Less, class Node_Type >
	void rk::BST<T, Compare_Less, Node_Type>::destroy_Subtree(Node_Type* Node_start)
	{
		if ( !(Node_start->left == 0 && Node_start->right == 0) )
		{
			if (Node_start->left == 0)
			{
				destroy_Subtree(Node_start->right);

			}
			else if (Node_start->right == 0)
			{
				destroy_Subtree(Node_start->left);

			}
			else
			{
				destroy_Subtree(Node_start->left);
				destroy_Subtree(Node_start->right);
			}
		}

		delete Node_start;


	}

	template <class T, class Compare_Less, class Node_Type >
	 Node_Type* BST<T, Compare_Less, Node_Type>::copy_Subtree( const Node_Type* original_Node)
	{
		 if (original_Node == NULL)
			 return NULL;

		 auto copy_ptr = new Node_Type(*original_Node);

		 if (original_Node->left == NULL)
			 copy_ptr->left = NULL;
		 else
			 copy_ptr->left = copy_Subtree(original_Node->left);

		 if (original_Node->right == NULL)
			 copy_ptr->right = NULL;
		 else
			 copy_ptr->right = copy_Subtree(original_Node->right);

		 return copy_ptr;
	}


	 template <class T, class Compare_Less, class Node_Type >
	inline void rk::BST<T, Compare_Less, Node_Type>::clear()
	{
		if (root != 0)
		{
			destroy_Subtree(root);
			root = 0;
		}

	}

	template <class T, class Compare_Less, class Node_Type >
	inline BST<T, Compare_Less, Node_Type> & BST<T, Compare_Less, Node_Type>::operator=(const BST<T, Compare_Less, Node_Type> & rhs)
	{
		if (this == &rhs)
			return *this;

		this->clear();
		this->fail_val = rhs.fail_val;
		this->root = copy_Subtree(rhs.root);

		return *this;
	}

	template <class T, class Compare_Less, class Node_Type >
	inline const T & rk::BST<T, Compare_Less, Node_Type>::find_Min() const
	{
		if (root == 0)
			return fail_val;
		else
			return (*find_Min_from_Node_ptr((const Node_Type**) &root))->data;
	}

	template<class T, class Compare_Less, class Node_Type>
	inline typename BST<T, Compare_Less, Node_Type>::const_iterator & BST<T, Compare_Less, Node_Type>::const_iterator::operator++()
	{
		if (Node_ptrs.empty())
			return *this;

		auto right_ptr = Node_ptrs.back()->right;
		Node_ptrs.pop_back();
		fill_left_Nodes(right_ptr);
		
		return *this;
	}

	/*template<class T, class Compare_Less, class Node_Type>
	inline typename BST<T, Compare_Less, Node_Type>::const_iterator & BST<T, Compare_Less, Node_Type>::const_iterator::operator--()
	{
		if (BST_root != NULL)
		{
			if (Node_ptrs.empty())
			{
				auto ptr = BST_root;
				for (; ptr->right != NULL; ptr = ptr->right) {}
				
				Node_ptrs.push_back(ptr);
				
			}
			else if (Node_ptrs.back()->left != NULL)
			{
				Node_ptrs.push_back(Node_ptrs.back()->left);
			}
			else
			{
				auto index = Node_ptrs.size() - 2;
				for (; Node_ptrs[index]->left == Node_ptrs[index + 1]; --index)
				{
					Node_ptrs.pop_back();
				}
				Node_ptrs.push_back(Node_ptrs[index]->left);
			}
		}
		return *this;
	}*/

	template<class T, class Compare_Less, class Node_Type>
	inline bool BST<T, Compare_Less, Node_Type>::const_iterator::operator==(const_iterator & itr) const
	{
		if (BST_containter != itr.BST_containter)
			return false;

		if (Node_ptrs.empty() && itr.Node_ptrs.empty()) // both iterators are end()
			return true;
		else if (Node_ptrs.empty() || itr.Node_ptrs.empty())
			return false;
		else
			return Node_ptrs.back() == itr.Node_ptrs.back();

	}

	template<class T, class Compare_Less, class Node_Type>
	inline bool BST<T, Compare_Less, Node_Type>::const_reverse_iterator::operator==(const_reverse_iterator & itr) const
	{
		if (BST_containter != itr.BST_containter)
			return false;

		if (Node_ptrs.empty() && itr.Node_ptrs.empty()) // both iterators are end()
			return true;
		else if (Node_ptrs.empty() || itr.Node_ptrs.empty())
			return false;
		else
			return Node_ptrs.back() == itr.Node_ptrs.back();

	}


	template<class T, class Compare_Less, class Node_Type>
	inline typename BST<T, Compare_Less, Node_Type>::const_reverse_iterator & BST<T, Compare_Less, Node_Type>::const_reverse_iterator::operator++()
	{
		if (Node_ptrs.empty())
			return *this;

		auto left_ptr = Node_ptrs.back()->left;
		Node_ptrs.pop_back();
		fill_right_Nodes(left_ptr);

		return *this;
	}

	template<class T, class Compare_Less, class Node_Type>
	inline typename BST<T, Compare_Less, Node_Type>::const_reverse_iterator rk::BST<T, Compare_Less, Node_Type>::erase(const_reverse_iterator & itr)
	{
		/*if (this->empty())
			return rend();*/

		if (itr.Node_ptrs.back()->left != NULL && itr.Node_ptrs.back()->right != NULL)
		{
			auto ptr_location = find_ptr(*itr);
			erase(*itr);
			itr.Node_ptrs.back() = *ptr_location;
		}
		else
		{
			auto val = *itr; ++itr;  erase(val);
		}
		return itr;
	}
}

#endif