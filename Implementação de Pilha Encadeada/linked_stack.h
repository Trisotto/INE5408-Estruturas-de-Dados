// Copyright [2016] <Felipe Longarai Trisotto>
#include "./linked_list.h"

namespace structures {
/**
 * @brief  		Implementação de uma Estrutura de Pilha Encadeada em C++
 */
template<typename T>
class LinkedStack{
 public:
    LinkedStack() = default;

    ~LinkedStack() {
    }
    /**
	 * @brief 		Limpa Pilha
	 *
	 * @details 	Destroi todos os elementos da pilha.
	 */
    void clear() {
        list.clear();
    }
    /**
	 * @brief       Empilha um Elemento		
	 *
	 * @details 	Empilha um elemento na pilha.
	 *
	 * @param       data    Elemento a ser inserido na pilha.
	 */
    void push(const T& data) {
        list.push_front(data);
    }  // empilha
    /**
	 * @brief 		Retirar um Elemento da Pilha
	 * 
	 * @return      Retorna o elemento retirado da pilha.
	 */
    T pop() {
        return list.pop_front();
    }  // desempilha
    /**
	 * @brief       Acessar Elemento no Topo da Pilha	
	 *
	 * @return      Retorna o elemento que está no topo da pilha.
	 */
    const T& top() const {
       return list.at(0);
    }  // dado no topo
    /**
	 * @brief       Pilha Vazia 		
	 *
	 * @details 	Verifica se a pilha está vazia.
	 * 
	 * @return      Retorna verdadeiro se a pilha está vazia e falso caso
	 *              contrário.
	 */
    bool empty() const {
       return list.empty();
    }  // pilha vazia
    /**
	 * @brief       Tamanho da Pilha 		
	 *
	 * @details 	Verifica o tamanho da pilha.
	 * 
	 * @return      Retorna o tamanho da pilha.
	 */
    std::size_t size() const {
        return list.size();
    }  // tamanho da pilha

 private:
    LinkedList<T> list{};
};

}  // namespace structures
