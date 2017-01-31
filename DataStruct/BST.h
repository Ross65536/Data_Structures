#ifndef __BSTrk
#define __BSTrk

namespace rk
{
	template <class T, class Compare_Less = std::less<T> >
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
	};

	//Class - Binary search tree 
	template <class T, class Compare_Less >
	class BST
	{
	protected:
		//data
		BSTNode<T, Compare_Less> * root;
		T fail_val;
		//functions
		BSTNode<T, Compare_Less> ** find_ptr(const T& val) const;
		BSTNode<T, Compare_Less> ** find_Max_from_Node_ptr(const BSTNode<T, Compare_Less> * const * Node) const;
		BSTNode<T, Compare_Less> ** find_Min_from_Node_ptr(const BSTNode<T, Compare_Less> * const * Node) const;
		void destroy_Subtree(BSTNode<T, Compare_Less> * Node_start);
		BSTNode<T, Compare_Less> * copy_Subtree(const BSTNode<T, Compare_Less> * original_Node);
	public:
		BST(const T& fail_d = T()) : root(0), fail_val(fail_d) {};
		BST(const BST<T, Compare_Less> &bst) : fail_val(bst.fail_val) { root = copy_Subtree (bst.root); };
		~BST();
		void insert(const T& val);
		const T& find(const T& val) const;
		bool isEmpty() const { return root == 0; };
		const T& find_Max() const;
		const T& find_Min() const;
		void erase(const T& val);
		void clear();
		BST& operator= (const BST<T, Compare_Less> & rhs);
		/*const T& change_Not_Found_value(const T& fail_val) { this->fail_val = fail_val; };*/
		T& get_Not_Found_value() { return this->fail_val; };
	};

	
	template <class T, class Compare_Less >
	void BST<T, Compare_Less>::insert(const T& val)
	{
		BSTNode<T, Compare_Less> ** found = find_ptr(val);

		if (*found == 0)
		{
			*found = new BSTNode<T, Compare_Less>(val);
		}
		else
		{
			return;
		}
	}

	template <class T, class Compare_Less >
	inline const T& BST<T, Compare_Less>::find(const T& val) const
	{
		BSTNode<T, Compare_Less> ** found = find_ptr(val);

		if (*found == 0)
			return fail_val;
		else
			return (*found)->data;
	}


	template <class T, class Compare_Less >
	BSTNode<T, Compare_Less> ** BST<T, Compare_Less>::find_ptr(const T& val) const
	{
		if (root == 0)
		{
			return (BSTNode<T, Compare_Less> **) &root;
		}

		BSTNode<T, Compare_Less> ** curr_node_ptr = (BSTNode<T, Compare_Less> **) &root;
		while (true)
		{
			Compare_Less less;
			BSTNode<T, Compare_Less> * curr_node = *curr_node_ptr;

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

	template<class T, class Compare_Less>
	BSTNode<T, Compare_Less>** BST<T, Compare_Less>::find_Max_from_Node_ptr(const BSTNode<T, Compare_Less>* const * Node) const
	{
		const BSTNode<T, Compare_Less> * const * curr_node_ptr = Node;
		while (true)
		{
			if ((*curr_node_ptr)->right == 0)
				return (BSTNode<T, Compare_Less> **) curr_node_ptr;
			else
				curr_node_ptr =(const BSTNode<T, Compare_Less> **) &((*curr_node_ptr)->right);
			
		}
	}

	template<class T, class Compare_Less>
	BSTNode<T, Compare_Less>** BST<T, Compare_Less>::find_Min_from_Node_ptr(const BSTNode<T, Compare_Less>* const * Node) const
	{
		const BSTNode<T, Compare_Less> * const * curr_node_ptr = Node;
		while (true)
		{
			if ((*curr_node_ptr)->left == 0)
				return (BSTNode<T, Compare_Less> **) curr_node_ptr;
			else
				curr_node_ptr = (const BSTNode<T, Compare_Less> **) &((*curr_node_ptr)->left);

		}
	}

	template<class T, class Compare_Less>
	inline const T & BST<T, Compare_Less>::find_Max() const
	{
		if (root == 0)
			return fail_val;
		else
			return (*find_Max_from_Node_ptr((const BSTNode<T, Compare_Less>**) &root))->data;
	}


	template<class T, class Compare_Less>
	void BST<T, Compare_Less>::erase(const T & val)
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

	template<class T, class Compare_Less>
	inline BST<T, Compare_Less>::~BST()
	{
		if (root != 0)
		{
			destroy_Subtree(root);
		}
	}

	template<class T, class Compare_Less>
	void rk::BST<T, Compare_Less>::destroy_Subtree(BSTNode<T, Compare_Less>* Node_start)
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

	template<class T, class Compare_Less>
	 BSTNode<T, Compare_Less>* BST<T, Compare_Less>::copy_Subtree( const BSTNode<T, Compare_Less>* original_Node)
	{
		 if (original_Node == NULL)
			 return NULL;

		 auto copy_ptr = new BSTNode<T, Compare_Less>(original_Node->data);

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


	template<class T, class Compare_Less>
	inline void rk::BST<T, Compare_Less>::clear()
	{
		if (root != 0)
		{
			destroy_Subtree(root);
			root = 0;
		}

	}

	template<class T, class Compare_Less>
	inline BST<T, Compare_Less> & BST<T, Compare_Less>::operator=(const BST<T, Compare_Less> & rhs)
	{
		if (this == &rhs)
			return *this;

		this->clear();
		this->fail_val = rhs.fail_val;
		this->root = copy_Subtree(rhs.root);

		return *this;
	}

	template<class T, class Compare_Less>
	inline const T & rk::BST<T, Compare_Less>::find_Min() const
	{
		if (root == 0)
			return fail_val;
		else
			return (*find_Min_from_Node_ptr((const BSTNode<T, Compare_Less>**) &root))->data;
	}

}

#endif