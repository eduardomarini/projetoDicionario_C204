#include <iostream>
#include <string>

using namespace std;

// Tema do projeto: Dicionário para Línga Fictícia
// Equipe: Eduardo Ribeiro Marini, Guilherme Ferreira Silva, João Pedro Ferreira Silva

// Definição da struct para armazenar os dados das palavras fictícias
struct DadosPalavra {
    string palavraFicticia;
    string traducao;
    int x, y, z;
};

// Função para inserir dados de uma palavra fictícia na struct
void inserirDadosPalavra(DadosPalavra& palavra) {
    cout << "Digite a palavra ficticia: ";
    cin >> palavra.palavraFicticia;
    cout << "Digite a traducao da palavra: ";
    cin >> palavra.traducao;
    cout << "Digite as coordenadas x, y e z separadas por espaco: ";
    cin >> palavra.x >> palavra.y >> palavra.z;
}

// Função para imprimir os dados de uma palavra fictícia
void imprimirDadosPalavra(const DadosPalavra& palavra) {
    cout << "Palavra ficticia: " << palavra.palavraFicticia << endl;
    cout << "Traducao: " << palavra.traducao << endl;
    cout << "Coordenadas (x, y, z): " << palavra.x << ", " << palavra.y << ", " << palavra.z << endl;
}

int main() {
    // Criando uma variável para armazenar os dados da palavra fictícia
    DadosPalavra palavra;

    // Entrada de dados da palavra fictícia
    cout << "Insira os dados da palavra ficticia:" << endl;
    inserirDadosPalavra(palavra);

    // Imprimindo os dados da palavra fictícia
    cout << "\nDados da palavra inserida:" << endl;
    imprimirDadosPalavra(palavra);

    return 0;
}
