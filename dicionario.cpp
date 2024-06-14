// Tema do projeto: Dicionário para Línga Fictícia
// Equipe: Eduardo Ribeiro Marini, Guilherme Ferreira Silva, João Pedro Ferreira Silva

// Exemplo de palavras fictícias:
//Vegur: Meditar 
//Vegafor: Espiar 
//Guilir: Rodar 
//Gyukin ou Kabal : Avião
//Dalsir: Sonhar / Flutuar
//Dhalp ou Scorp: Tapete
//Kenpuf: Faixa 
//Kenzaki: Espada / Habilidade
//Kensir ou Barak: Correr
//Balroq ou Jax: Golpear 
//Blankaor: Criatura
//Hadokenki: Luvas 
//Hondat: Capacete / proteção
//Honditar: Lutar
//Zangst: Determinação / Coragem
//Zanggur: Força
//Ryusen ou Liuk: Treinar 
//Ryukin: Atacar / Superar

#include <iostream>
#include <string>

using namespace std;

// Estrutura para armazenar traduções de uma palavra fictícia
struct NodeTraducao {
    string traducao; 
    NodeTraducao* next; // Ponteiro para a próxima tradução

    NodeTraducao(string trad) : traducao(trad), next(nullptr) {} // Construtor
};

// Estrutura para armazenar uma palavra fictícia e suas traduções
struct Vertice {
    string palavraFicticia; 
    NodeTraducao* traducoes; // Ponteiro para a lista de traduções
    int x, y, z; // Coordenadas

    Vertice(string palavra) : palavraFicticia(palavra), traducoes(nullptr), x(0), y(0), z(0) {} // Construtor
};

// Estrutura para representar um nó da árvore de busca binária
struct TreeNode {
    Vertice* vertice; // O vértice armazenado no nó
    TreeNode* left; // Ponteiro para o filho à esquerda
    TreeNode* right; // Ponteiro para o filho à direita

    TreeNode(Vertice* vert) : vertice(vert), left(nullptr), right(nullptr) {} // Construtor
};

// Função para inserir um vértice na árvore
TreeNode* insert(TreeNode* node, Vertice* vertice) {
    // Se a árvore está vazia, o novo nó será a raiz
    if (node == nullptr) {
        return new TreeNode(vertice);
    }
    // Se a palavra fictícia do vértice é menor que a do nó atual, insira à esquerda
    if (vertice->palavraFicticia < node->vertice->palavraFicticia) {
        node->left = insert(node->left, vertice);
    } else {
        // Senão, insira à direita
        node->right = insert(node->right, vertice);
    }
    return node;
}

// Função para buscar um vértice na árvore
TreeNode* search(TreeNode* node, string palavraFicticia) {
    // Se a árvore está vazia ou a palavra fictícia é encontrada, retorne o nó atual
    if (node == nullptr || node->vertice->palavraFicticia == palavraFicticia) {
        return node;
    }
    // Se a palavra fictícia é menor que a do nó atual, busque à esquerda
    if (palavraFicticia < node->vertice->palavraFicticia) {
        return search(node->left, palavraFicticia);
    } else {
        // Senão, busque à direita
        return search(node->right, palavraFicticia);
    }
}

// Função para encontrar o nó com o valor mínimo
TreeNode* minValueNode(TreeNode* node) {
    TreeNode* current = node;
    // Percorra a árvore até encontrar o nó mais à esquerda
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

// Função para remover um vértice da árvore
TreeNode* remove(TreeNode* node, string palavraFicticia) {
    // Se a árvore está vazia, retorne a mesma
    if (node == nullptr) {
        return node;
    }
    // Se a palavra fictícia é menor que a do nó atual, remova o nó à esquerda
    if (palavraFicticia < node->vertice->palavraFicticia) {
        node->left = remove(node->left, palavraFicticia);
    } else if (palavraFicticia > node->vertice->palavraFicticia) {
        // Se a palavra fictícia é maior que a do nó atual, remova o nó à direita
        node->right = remove(node->right, palavraFicticia);
    } else {
        // Se a palavra fictícia é igual à do nó atual, este é o nó a ser removido
        if (node->left == nullptr) {
            // O nó tem no máximo um filho à direita
            TreeNode* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            // O nó tem no máximo um filho à esquerda
            TreeNode* temp = node->left;
            delete node;
            return temp;
        }
        // O nó tem dois filhos; obtenha o sucessor em ordem (menor nó da subárvore à direita)
        TreeNode* temp = minValueNode(node->right);
        // Copie o conteúdo do sucessor para este nó
        node->vertice = temp->vertice;
        // Remova o sucessor em ordem
        node->right = remove(node->right, temp->vertice->palavraFicticia);
    }
    return node;
}

// Função para imprimir a árvore em ordem
void inOrder(TreeNode* node) {
    // Se o nó atual não é nulo
    if (node != nullptr) {
        // Primeiro, visite a subárvore à esquerda
        inOrder(node->left);
        // Imprima a palavra fictícia do nó atual
        cout << "Palavra: " << node->vertice->palavraFicticia << ", Traducoes: ";
        // Crie um ponteiro temporário para a lista de traduções do nó atual
        NodeTraducao* tradTemp = node->vertice->traducoes;
        // Enquanto houver traduções, imprima a tradução e avance para a próxima tradução
        while (tradTemp != nullptr) {
            cout << tradTemp->traducao << " ";
            tradTemp = tradTemp->next;
        }
        // Imprima as coordenadas do nó atual
        cout << ", Coordenadas: (" << node->vertice->x << ", " << node->vertice->y << ", " << node->vertice->z << ")\n";
        // Finalmente, visite a subárvore à direita
        inOrder(node->right);
    }
}

// Função para listar palavras fictícias por tradução
void listWordsByTranslation(TreeNode* node, string traducao) {
    // Se o nó atual não é nulo
    if (node != nullptr) {
        // Primeiro, visite a subárvore à esquerda
        listWordsByTranslation(node->left, traducao);
        // Crie um ponteiro temporário para a lista de traduções do nó atual
        NodeTraducao* tradTemp = node->vertice->traducoes;
        // Enquanto houver traduções, se a tradução é igual à procurada, imprima a palavra fictícia e pare a busca
        while (tradTemp != nullptr) {
            if (tradTemp->traducao == traducao) {
                cout << "- " << node->vertice->palavraFicticia << "\n";
                break;
            }
            tradTemp = tradTemp->next;
        }
        // Finalmente, visite a subárvore à direita
        listWordsByTranslation(node->right, traducao);
    }
}

void insertTranslation(NodeTraducao*& head, string traducao) {
    NodeTraducao* newTrad = new NodeTraducao(traducao);
    // Se a lista está vazia ou a nova tradução é menor que a primeira tradução, insira no inicio
    if(head == nullptr || head->traducao > traducao) {
        newTrad->next = head;
        head = newTrad;
    } else {
        // Encontre a posição correta para inserir a nova tradução
        NodeTraducao* current = head;
        while (current->next != nullptr && current->next->traducao < traducao) {
            current = current->next;
        }
        // Insira a nova tradução após 'current'
        newTrad->next = current->next;
        current->next = newTrad;
    }
}

// Função para inserir um vértice na lista de vértices
void insertVert(TreeNode*& root) {
    // Peça ao usuário para digitar a palavra fictícia
    string palavraFicticia;
    cout << "Digite a palavra ficticia (ou 'fim' para terminar): ";
    cin >> palavraFicticia;
    // Se o usuário digitou 'fim', termine a função
    if (palavraFicticia == "fim") {
        return;
    }

    // Crie um novo vértice com a palavra fictícia
    Vertice* vertice = new Vertice(palavraFicticia);

    // Peça ao usuário para digitar as traduções da palavra
    cout << "Digite as traducoes da palavra (separadas por espaco, terminadas por 'fim'): ";
    string traducao;
    // Enquanto o usuário não digitar 'fim', adicione a tradução à lista de traduções do vértice
    while (cin >> traducao && traducao != "fim") {
        insertTranslation(vertice->traducoes, traducao);
    }

    // Peça ao usuário para digitar as coordenadas x, y e z
    cout << "Digite as coordenadas x, y e z separadas por espaco: ";
    cin >> vertice->x >> vertice->y >> vertice->z;

    // Insira o vértice na árvore
    root = insert(root, vertice);
}


int main() {
    // Crie um ponteiro para a raiz da árvore
    TreeNode* root = nullptr;

    // Enquanto o usuário quiser inserir palavras, chame a função insertVert
    while (true) {
        insertVert(root);
        cout << "Deseja inserir outra palavra? (s/n): ";
        string opcao;
        cin >> opcao;
        if (opcao != "s") {
            break;
        }
    }

    // Imprima a árvore em ordem
    cout << "\nGrafo:\n";
    inOrder(root);

    // Enquanto o usuário quiser listar palavras por tradução, chame a função listWordsByTranslation
    while (true) {
        string traducao;
        cout << "\nDigite uma traducao para listar palavras ficticias (ou 'fim' para terminar): ";
        cin >> traducao;
        if (traducao == "fim") {
            break;
        }
        cout << "\nPalavras ficticias para a traducao \"" << traducao << "\":\n";
        listWordsByTranslation(root, traducao);
    }

    return 0;
}