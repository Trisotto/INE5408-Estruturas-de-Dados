// Copyright [2016] <Felipe Longarai Trisotto>

/**
 * @brief  		Implementação de uma estrutura de Pilha em C++
 */
#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint> // std::size_t
#include <stdexcept> // C++ exceptions

namespace structures {

template<typename T>
class ArrayStack {
private:
    /**
    * @param  		contents	-	Ponteiro para o início da Pilha.
    * @param  		top_ - Variável que aponta para o último elemento da pilha.
    * @param  		max_size_	 -	Tamanho máximo que a pilha deve assumir.
    */
    T* contents;
    int top_;
    std::size_t max_size_;

    const static auto DEFAULT_SIZE = 10u;
    
public:
    /**
	 * @brief  		Construtor Genérico da Classe Pilha
	 *
 	 * @details  	Valor do tamanho definido em uma constante
	 * @details     como DEFAULT_SIZE.
	 */
    ArrayStack() {
        top_ = -1;
        max_size_ = DEFAULT_SIZE;
        contents = new T[max_size_];
    }
    /**
	 * @brief  		Construtor da Classe Pilha com Parâmetro
	 *
	 * @param  		t -	Valor para o tamanho da pilha.
	 */
    ArrayStack(std::size_t max) {
        max_size_ = max;
        top_ = -1;
        contents = new T[max_size_];
    }
    /**
	 * @brief      Deleta a pilha e libera memória.
	 */
    ~ArrayStack(){
        delete contents;
    }
    /**
	 * @brief      Coloca um dado a pilha.
	 *
	 * @param  		data - Dado Template.
	 */
    void push(const T& data) {
        if (full()) {
            throw std::out_of_range("PILHA CHEIA");
        } else {
            top_++;
            contents[top_] = data;
        }
    } // empilha
    /**
	 * @brief      Retira o valor no topo da pilha.
	 */
    T pop() {
        if (empty())  {
            throw std::out_of_range("PILHA VAZIA");
        } else {
            T aux = contents[top_];
            top_--;
            return aux;
        }
    } // desempilha
    /**
	 * @brief  		Retorna o valor armazenado no topo da pilha.
	 */
    T& top() {
        if (empty()) {
           throw std::out_of_range("PILHA VAZIA");
        } else {
            return contents[top_];
        }
    }
    /**
	 * @brief      Limpa a pilha.
	 */
    void clear() {
        top_ = -1;
        contents = new T[max_size_];
    } // limpa
    /**
	 * @brief      Retorna a posição do topo da pilha.
	 */
    std::size_t size() {
        return top_ + 1;
    } // tamanho
    /**
	 * @brief      Retorna a posição do tamanho máximo da pilha.
	 */
    std::size_t max_size() {
        return max_size_;
    }
    /**
	 * @brief      Verifica se a pilha está vazia.
	 *
	 * @return     Retorna true caso a pilha esteja vazia.
	 */
    bool empty() {
        return top_ == -1;
    } // vazia
   /**
	 * @brief      Verifica se a pilha está cheia.
	 *
	 * @return     Retorna true caso a pilha esteja cheia.
	 */
    bool full() {
        return top_ == max_size_ - 1;
    } // cheia


};

}

#endif
