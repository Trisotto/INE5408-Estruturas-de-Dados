// Copyright [2016] <Felipe Longarai Trisotto>
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
/**
 * @brief  		Implementacao de uma estrutura de Lista em C++
 *
 * @param  		contents		Ponteiro para o ini­cio da Lista
 * @param  		size_		    Armazena a posicao do ultimo da Lista
 * @param  		max_size_		Armazena o tamanho da Lista
 */
class ArrayList {
 public:
    ArrayList() {
        size_ = -1;
        max_size_ = DEFAULT_MAX;
        contents = new T[max_size_];
    }
    /**
	 * @brief  		Construtor da classe Lista
	 *
	 * @param  		max_size		Valor para o tamanho da lista.
	 *
	 * @details  	Valor do max_size_ definido pelo parametro max_size.
	 */
    explicit ArrayList(std::size_t max_size) {
        size_ = -1;
        max_size_ = max_size;
        contents = new T[max_size_];
    }
    ~ArrayList() {
        delete[] contents;
    }
    /**
	 * @brief  		Limpa o Vector
	 */
    void clear() {
        delete[] contents;
        size_ = -1;
        contents = new T[max_size_];
    }
    /**
	 * @brief  		Coloca o Elemento no Final da Lista
	 *
	 * @param  		data		Elemento a ser colocado na lista.
	 *
	 * @details  	Reutiliza o metodo insert com os parametros data e size_+1
	 * @details     para colocar na ultima posicao do vector.
	 */
    void push_back(T data) {
        insert(data, size_+1);
    }
    /**
	 * @brief  		Coloca o Elemento no Inicio da Lista
	 *
	 * @param  		data		Elemento a ser colocado na lista.
	 *
	 * @details  	Reutiliza o metodo insert com os parametros data e 0
	 * @details     para colocar na primeira posicao do vector.
	 */
    void push_front(T data) {
        insert(data, 0);
    }
    /**
	 * @brief  		Coloca o Elemento na Posicao Desejada na Lista
	 *
	 * @param  		data		Elemento a ser colocado na lista.
	 * @param       index       Indice para indicar a posicao do vector a ser
	 *                          colocado o elemento.
	 */
    void insert(T data, std::size_t index) {
        if (full()) {
			throw std::out_of_range("ERRO LISTA CHEIA");
		} else {
			if(index > size_ + 1 || index < 0) {
				throw std::out_of_range("POSICAO INVALIDA");
			} else {
				size_++;
				int i = size_;
				while(i > index) {
					contents[i] = contents[i-1];
					i--;
				}
				contents[index] = data;
			}
		}
    }
    /**
	 * @brief  		Coloca o Elemento em Ordem na Lista
	 *
	 * @param  		data		Elemento a ser colocado na lista.
	 * 
	 * @details     Adiciona um dado na lista acima do que possua­ uma valor
	 * 				inferior ao seu e abaixo do que possua­ um valor superior.
	 */
    void insert_sorted(T data) {
        if (full()) {
			throw std::out_of_range("ERRO LISTA CHEIA");
		} else {
			int i = 0;
			while(i < size_+1 && data > contents[i]) {
				i++;
			}
			insert(data, i);
		}
    }
    /**
	 * @brief 		Retira o dado que esta na posicao desejada na lista
	 *
	 * @param 		index  Indice para posicao desejada a ser
	 *                     retirada o elemento.
	 */
    T pop(std::size_t index) {
        if (index > size_ || index < 0) {
			throw std::out_of_range("POSICAO INVALIDA");
		} else {
			if(empty()) {
				throw std::out_of_range("ERRO LISTA VAZIA");
			} else {
				size_--;
				T data_aux = contents[index];
				int i = index;
				while(i < size_+1) {
					contents[i] = contents[i+1];
					i++;
				}
				return data_aux;
			}
		}
    }
    /**
	 * @brief      Retira o dado na ultima posicao da lista
	 * 
	 * @details    Reutiliza o metodo pop passando como parametro size_ para
	 *             que seja retirado o elemento na ultima posicao.
	 */
    T pop_back() {
        return pop(size_);
    }
    /**
	 * @brief      Retira o dado na primeira poisicao da lista
	 * 
	 * @details    Reutiliza o metodo pop passando como parametro 0 para
	 *             que seja retirado o elemento na primeira posicao.
	 */
    T pop_front() {
        return pop(0);
    }
    /**
	 * @brief  		Retira o elemento que for passado como parametro
	 *
	 * @param  		data		Elemento a ser retirado da lista.
	 * 
	 * @details     Utiliza o metodo find() para achar o indice da posicao no
	 * 				vector que esta o elemento a ser retirado e passa esse
	 *              indice como parametro para o metodo pop para ser retirado.
	 */
    void remove(T data) {
        pop(find(data));
    }
    /**
	 * @brief      Verifica se a lista esta cheia
	 *
	 * @return     Retorna true caso a lista esteja cheia
	 */
    bool full() const {
        return size_ == max_size_-1;
    }
    /**
	 * @brief      Verifica se a lista esta vazia
	 *
	 * @return     Retorna true caso a lista esteja vazia
	 */
    bool empty() const {
        return size_ == -1;
    }
    /**
	 * @brief      Verifica se o dado esta na lista
	 *
	 * @param      data     Elemento a ser verificado se esta na lista.
	 * 
	 * @return     Retorna true caso o elemento passado como paramento
	 *             esteja na lista.
	 */
    bool contains(const T& data) const {
        return find(data) != size_+1;
    }
    /**
	 * @brief      Verifica o indice da posicao do elemento passado
	 *             como parÃ¢metro
	 *
	 * @param      data     Elemento a ser verificado seu indice.
	 * 
	 * @return     Retorna o indice da posicao do elemento passado
	 *             como paramento.
	 */
    std::size_t find(const T& data) const {
        for (int i = 0; i <= size_; i++) {
            if (data == contents[i]) {
                return i;
            }
        }
        return size_+1;
    }
    /**
	 * @brief      Numero de elementos na lista
	 *
	 * @return     Retorna o numero de elementos na lista.
	 */
    std::size_t size() const {
        return size_+1;
    }
    /**
	 * @brief      Tamanho maximo da lista
	 *
	 * @return     Retorna o tamanho maximo da lista.
	 */
    std::size_t max_size() const {
        return max_size_;
    }
    /**
	 * @brief      Acessa o elemento que esta no indice passado como parametro
	 *
	 * @param      index     Indice da posicao do elemento a ser acessado.
	 * 
	 * @return     Retorna o elemento que esta na posicao do indice passado
	 *             como paramento e verifica se o indice do elemento esta
	 *             dentro dos limites do vector.
	 */
    T& at(std::size_t index) {
        if (index <= size_) {
                return contents[index];
        }
        throw std::out_of_range("POSICAO INVALIDA");
    }
    /**
	 * @brief      Acessa o elemento que esta no indice passado como parametro
	 *
	 * @param      index     Indice da posicao do elemento a ser acessado.
	 * 
	 * @return     Retorna o elemento que esta na posicao do indice passado
	 *             como paramento e sem verificar se o indice do elemento esta
	 *             dentro dos limites do vector.
	 */
    T& operator[](std::size_t index) {
        return contents[index];
    }
    /**
	 * @brief      Acessa o elemento que esta no indice passado como parametro
	 *             para funcoes const
	 * 
	 * @param      index     Indice da posicao do elemento a ser acessado.
	 * 
	 * @return     Retorna o elemento que esta na posicao do indice passado
	 *             como paramento e verifica se o indice do elemento esta
	 *             dentro dos limites do vector.
	 */
    const T& at(std::size_t index) const {
        return at(index);
    }
    /**
	 * @brief      Acessa o elemento que esta no indice passado como parametro
	 *             para funcoes const
	 * 
	 * @param      index     Indice da posicao do elemento a ser acessado.
	 * 
	 * @return     Retorna o elemento que esta na posicao do indice passado
	 *             como paramento e sem verificar se o indice do elemento esta
	 *             dentro dos limites do vector.
	 */
    const T& operator[](std::size_t index) const {
        return contents[index];
    }

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};

}  // namespace structures

#endif
