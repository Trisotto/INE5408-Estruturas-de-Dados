// Copyright [2016] <Felipe Longarai Trisotto>
#include "./array_list.h"

namespace structures {
template<typename T>
/**
 * @brief      Implementação Árvore binária
 */
class BinaryTree {
 public:
    BinaryTree() = default;

    virtual ~BinaryTree() {
        delete root;
        size_ = 0;
    }
    /**
	 * @brief  		Inseri um novo vértice na árvore
	 *
	 * @param  		data		Dado que a ser inserido
	 */
    void insert(const T& data) {
        if (empty()) {
            root = new Node(data);
        } else {
            root->insert(data);
        }
        ++size_;
    }
    /**
	 * @brief  		Remove um novo vértice na árvore
	 *
	 * @param  		data		Dado que a ser removido
	 */
    void remove(const T& data) {
        bool verif;
        if (empty()) {
            return;
        } else {
            verif = root->remove(data);
            if (verif) {
                --size_;
            }
        }
    }
    /**
	 * @brief  		Verifica se um um dado existe na árvore
	 *
	 * @param  		data		Dado que a ser verificado
	 * 
	 * @return      Retorna true caso contenha o dado
	 */
    bool contains(const T& data) const {
        if (empty()) {
            return false;
        } else {
            return root->contains(data);
        }
    }
    /**
	 * @brief      Verifica se a arvore esta vazia
	 *
	 * @return     Retorna true caso a arvore esteja vazia
	 */
    bool empty() const {
        return size_ == 0;
    }
    /**
	 * @brief      Numero de elementos na arvore
	 *
	 * @return     Retorna o numero de elementos na arvore
	 */
    std::size_t size() const {
        return size_;
    }
    /**
	 * @brief      Ordena os elementos na ordem meio esquerda direita
	 *
	 * @return     Retorna a uma lista dos elementos ordenados
	 */
    ArrayList<T> pre_order() const {
        structures::ArrayList<T> v{};
        if (!(empty())) {
            root->pre_order(v);
        }
        return v;
    }
    /**
	 * @brief      Ordena os elementos na ordem esquerda meio direita
	 *
	 * @return     Retorna a uma lista dos elementos ordenados
	 */
    ArrayList<T> in_order() const {
        structures::ArrayList<T> v{};
        if (!(empty())) {
            root->in_order(v);
        }
        return v;
    }
    /**
	 * @brief      Ordena os elementos na ordem esquerda direita meio
	 *
	 * @return     Retorna a uma lista dos elementos ordenados
	 */
    ArrayList<T> post_order() const {
        structures::ArrayList<T> v{};
        if (!(empty())) {
            root->post_order(v);
        }
        return v;
    }

 private:
    struct Node {
        explicit Node(const T& data)
            : data{data}
            , left{nullptr}
            , right{nullptr}
        {}

        T data;
        Node* left;
        Node* right;

        void insert(const T& data_) {
            Node* newNode;
            if (data_ > data) {
                if (right == nullptr) {
                    newNode = new Node(data_);
                    right = newNode;
                } else {
                    right->insert(data_);
                }
            } else {
                if (left == nullptr) {
                    newNode = new Node(data_);
                    left = newNode;
                } else {
                    left->insert(data_);
                }
            }
        }

        bool remove(const T& data_) {
            if (data_ == data) {
                if (left != nullptr && right != nullptr) {
                    auto it = mini(right);
                    data = it->data;
                    return right->remove(data);
                } else {
                    if (right != nullptr) {
                        data = right->data;
                        return right->remove(data);
                    } else {
                        if (left != nullptr) {
                            data = left->data;
                            return left->remove(data);
                        } else {
                            delete this;
                            return true;
                        }
                    }
                }
            } else {
                if (right != nullptr && data < data_) {
                    return right->remove(data_);
                } else {
                    if (left != nullptr && data > data_) {
                        return left->remove(data_);
                    }
                }
            }
            return false;
        }

        bool contains(const T& data_) const {
            if (data == data_) {
                return true;
            } else {
                if (right != nullptr && data_ > data) {
                    return right->contains(data_);
                } else if (left != nullptr && data_ < data) {
                    return left->contains(data_);
                }
            }
            return false;
        }

        void pre_order(ArrayList<T>& v) const {
            v.push_back(data);
            if (left != nullptr) {
                left->pre_order(v);
            }
            if (right != nullptr) {
                right->pre_order(v);
            }
        }

        void in_order(ArrayList<T>& v) const {
            if (left != nullptr) {
                left->in_order(v);
            }
            v.push_back(data);
            if (right != nullptr) {
                right->in_order(v);
            }
        }

        void post_order(ArrayList<T>& v) const {
            if (left != nullptr) {
                left->post_order(v);
            }
            if (right != nullptr) {
                right->post_order(v);
            }
            v.push_back(data);
        }

        Node* mini(Node* node) {
            while (node->left != nullptr) {
                node = node->left;
            }
            return node;
        }
    };

    Node* root{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures
