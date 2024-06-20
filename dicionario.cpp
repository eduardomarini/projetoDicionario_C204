// Tema do projeto: Dicionário para Línga Fictícia
// Equipe: Eduardo Ribeiro Marini, Guilherme Ferreira Silva, João Pedro Ferreira Silva

// Exemplo de palavras fictícias:
//Vega: Meditar 
//Vegafor: Espiar 
//Guilir: Rodar 
//Gyukin ou Kabal : Avião
//Dalsir: Sonhar / Flutuar
//Dhalp ou Scorp: Tapete
//Kenpuf: Faixa 
//Kenzaki: Espada / Habilidade
//Kensir ou Barak: Correr
//Balroq ou Jax: Golpear 
//Blanka: Criatura
//Hadokenki: Luvas 
//Hondat: Capacete / proteção
//Honditar: Lutar
//Zangst: Determinação / Coragem
//Zanggur: Força
//Ryusen ou Liuk: Treinar 
//Ryukin: Atacar / Superar

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Estrutura para armazenar traduções de uma palavra fictícia
struct NodeTraducao {
    string traducao; 
    NodeTraducao* next; // Ponteiro para a próxima tradução

    // Construtor é chamado quando uma nova tradução é criada
    // Inicializa a tradução e o ponteiro para a próxima tradução
    NodeTraducao(string trad) : traducao(trad), next(nullptr) {} 
};

// Estrutura para armazenar uma palavra fictícia e suas traduções
struct Vertice {
    string palavraFicticia; 
    NodeTraducao* traducoes; // Ponteiro para a lista de traduções
    int x, y, z; // Coordenadas

    // Construtor é chamado quando uma nova palavra fictícia é criada
    // Inicializa a palavra fictícia, a lista de traduções e as coordenadas
    Vertice(string palavra) : palavraFicticia(palavra), traducoes(nullptr), x(0), y(0), z(0) {} // Construtor
};

// Estrutura para representar um nó da árvore de busca binária
struct TreeNode {
    Vertice* vertice; // O vértice armazenado no nó
    TreeNode* left; // Ponteiro para o filho à esquerda
    TreeNode* right; // Ponteiro para o filho à direita
    int height; // Altura do nó

    // Construtor é chamado quando um novo vertice é inserido na árvore
    // Inicializa o vértice, os ponteiros para os filhos e a altura
    TreeNode(Vertice* vert) : vertice(vert), left(nullptr), right(nullptr), height(1) {} // Construtor
};

// Função para obter a altura de um nó
int height(TreeNode* node) {
    if (node != nullptr) {
        // Se o nó não é nulo, retorna o valor da altura armzenada no nó
        return node->height;
    } else {
        return 0;
    }
}

// Função para obter o fator de balanceamento de um nó
int getBalance(TreeNode* node) {
    if (node != nullptr) {
        //  Calcula e retorna o fator de balanceamento do nó
        return height(node->left) - height(node->right);
    } else {
        return 0;
    }
}

// Função para realizar uma rotação a direita
TreeNode* rightRotate(TreeNode* y) {
    // Define um ponteiro x que aponta para o filho à esquerda do nó y
    TreeNode* x = y->left;
    // Define um ponteiro T2 que aponta para o filho à direita do nó x
    TreeNode* T2 = x->right;

    // Realize a rotação
    x->right = y; // filho direito de x ser y
    y->left = T2; // filho esquerdo de y ser T2

    // Atualize as alturas
    y->height = max(height(y->left), height(y->right)) + 1; // Altura do nó y é 1 + a maior altura entre os filhos esquerdo e direito
    x->height = max(height(x->left), height(x->right)) + 1; // Altura do nó x é 1 + a maior altura entre os filhos esquerdo e direito

    return x;
}

// Função para realizar uma rotação à esquerdas
TreeNode* leftRotate(TreeNode* x) {
    // Define um ponteiro y que aponta para o filho à direita do nó x
    TreeNode* y = x->right;
    // Define um ponteiro T2 que aponta para o filho à esquerda do nó y
    TreeNode* T2 = y->left;

    // Realize a rotação
    y->left = x;
    x->right = T2;

    // Atualize as alturas
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Função para inserir um vértice na árvore AVL, matendo-a balanceada
TreeNode* insert(TreeNode* node, Vertice* vertice) {
    // Se a árvore está vazia, crie um novo nó
    if (node == nullptr) {
        return new TreeNode(vertice);
    }
    // Se a palavra fictícia do novo vértice é menor que a do nó atual, insira à esquerda
    if (vertice->palavraFicticia < node->vertice->palavraFicticia) {
        node->left = insert(node->left, vertice);
    // Se a palavra fictícia do novo vértice é maior que a do nó atual, insira à direita
    } else if (vertice->palavraFicticia > node->vertice->palavraFicticia) {
        node->right = insert(node->right, vertice);
    // Se a palavra fictícia já existe, retorne o nó atual
    } else {
        return node;
    }

    // Atualize a altura do nó atual
    node->height = max(height(node->left), height(node->right)) + 1;

    // Calcule o fator de balancemaento do nó atual
    int balance = getBalance(node);

    // Se o nó está desbalanceado e a palavra fictícia do novo vértice é menor que a do filho à esquerda do nó atual, faça uma rotação à direita
    if (balance > 1 && vertice->palavraFicticia < node->left->vertice->palavraFicticia) {
        return rightRotate(node);
    }

    // Se o nó está desbalanceado e a palavra fictícia do novo vértice é maior que a do filho à direita do nó atual, faça uma rotação à esquerda
    if (balance < -1 && vertice->palavraFicticia > node->right->vertice->palavraFicticia) {
        return leftRotate(node);
    }

    // Se o nó está desbalanceado, a palavra fictícia do novo vértice é maior que a do filho à esquerda do nó atual, faça uma rotação à esquerda seguida de uma rotação à direita
    if (balance > 1 && vertice->palavraFicticia > node->left->vertice->palavraFicticia) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Se o nó está desbalanceado, a palavra fictícia do novo vértice é menor que a do filho à direita do nó atual, faça uma rotação à direita seguida de uma rotação à esquerda
    if (balance < -1 && vertice->palavraFicticia < node->right->vertice->palavraFicticia) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
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
TreeNode* remove(TreeNode* root, string palavraFicticia) {
    // Se a árvore está vazia, retorna a raiz
    if (root == nullptr) {
        return root;
    }
    //  Se a palavra fictícia é menor que a do nó atual, remova à esquerda
    if (palavraFicticia < root->vertice->palavraFicticia) {
        root->left = remove(root->left, palavraFicticia);
    // Se a palavra fictícia é maior que a do nó atual, remova à direita
    } else if (palavraFicticia > root->vertice->palavraFicticia) {
        root->right = remove(root->right, palavraFicticia);
    // Se a palavra fictícia é igual à do nó atual, remova o nó atual
    } else {
        // Se o nó tem um ou nenhum filho
        if ((root->left == nullptr) || (root->right == nullptr)) {
            TreeNode* temp = root->left ? root->left : root->right;

            // Se não há filhos, libere o nó e retorne nulo
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            // Caso contrário, copie o conteúdo do filho não nulo para o nó atual
            } else {
                *root = *temp;
            }
            // Deleta o nó temporário
            delete temp;
        } 
        // Caso o nó tenha dois filhos
        else { 
            // Encontre o nó com o valor mínimo na subárvore à direita
            TreeNode* temp = minValueNode(root->right);
            // copie o valor do nó de valor mínimo para a raiz
            root->vertice = temp->vertice;
            // Remova o nó de valor mínimo
            root->right = remove(root->right, temp->vertice->palavraFicticia);
        }
    }
    // Se a árvore tem apenas um nó, retorne a raiz
    if (root == nullptr) {
        return root;
    }

    // Atualize a altura da raiz atual
    root->height = max(height(root->left), height(root->right)) + 1;

    // Obtem o fator de balanceamento para verificar se a árvore se tornou desbalanceada
    int balance = getBalance(root);

    // Se a árvore está desbalanceada e a subárvore à esquerda está balanceada ou tem altura à esquerda maior, faça uma rotação à direita
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }

    // Se a árvore está desbalanceada e a subárvore à esquerda tem altura à direita maior, faça uma rotação à esquerda seguida de uma rotação à direita
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    //  Se a árvore está desbalanceada e a subárvore à direita está balanceada ou tem altura à direita maior, faça uma rotação à esquerda
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }

    // Se a árvore está desbalanceada e a subárvore à direita tem altura à esquerda maior, faça uma rotação à direita seguida de uma rotação à esquerda
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
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

void listTranslations(TreeNode* root, string palavraFicticia) {
    // Busque a palavra ficitícia na árvore
    TreeNode* node = search(root, palavraFicticia);
    // Se o vértice foi encontrado, imprima suas traduções
    if (node != nullptr) {
        // Se encontrou o nó, imprima as traduções
        cout << "Traducoes para a palavra ficticia \"" << palavraFicticia << "\":" << endl;
        NodeTraducao* tradTemp = node->vertice->traducoes;
        while (tradTemp != nullptr) {
            cout << "- " << tradTemp->traducao << endl;
            tradTemp = tradTemp->next;
        }
    } else {
        // Se a palavra fictícia não foi encontrada, informe o usuário
        cout << "A palavra ficticia \"" << palavraFicticia << "\" nao foi encontrada." << endl;
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

// Função para calcular a distância euclidiana entre dois vértices
double euclideanDistance(Vertice* v1, Vertice* v2) {
    return sqrt(pow(v1->x - v2->x, 2) + pow(v1->y - v2->y, 2) + pow(v1->z - v2->z, 2));
}

// Função para encontrar a distância euclidiana entre duas palavras ficitícias
void findDistance(TreeNode* node) {
    string palavra1, palavra2;

    while(true) {
        // Solicite ao usuário que digite as palavras ficitícias
        cout << "Digite a primeira palavra ficticia: " << endl;
        cin >> palavra1;
        cout << "Digite a segunda palavra ficticia: " << endl;
        cin >> palavra2;

        // Procure pelos vértices correspondentes as palavras
        TreeNode* node1 = search(node, palavra1);
        TreeNode* node2 = search(node, palavra2);

    // Se amobos os vértices foram encontrados, calcule e mostre a distância
        if (node1 != nullptr && node2 != nullptr) {
            double distance = euclideanDistance(node1->vertice, node2->vertice);
            cout << "A distancia euclidiana entre as palavras " << palavra1 << " e " << palavra2 << " eh: " << distance << endl;   
            break;
        } else {
            // Se qualquer uma das palavras não for encontrada, informe o usuário
            if (node1 == nullptr) {
                cout << "A palavra " << palavra1 << " nao foi encontrada." << endl;
            }
            if (node2 == nullptr) {
                cout << "A palavra " << palavra2 << " nao foi encontrada." << endl;
            }
            cout << "Deseja tentar novamente? (s/n): " << endl;
            string opcao;
            cin >> opcao;
            if (opcao != "s") {
                break;
            }
        }
    }
}

void destructTree(TreeNode* node) {
    if (node != nullptr) {
        destructTree(node->left);
        destructTree(node->right);

        // Liberar a lista de traduções do vérice
        NodeTraducao* current = node->vertice->traducoes;
        while (current != nullptr) {
            NodeTraducao* next = current->next;
            delete current;
            current = next;
        }

        // Libera o vértice e o nó
        delete node->vertice;
        delete node;
    }
}

int main() {
    TreeNode* root = nullptr;

    while (true) {
        cout << "Escolha uma opcao:" << endl;
        cout << "1. Inserir palavras" << endl;
        cout << "2. Buscar por traducao" << endl;
        cout << "3. Remover palavra" << endl;
        cout << "4. Buscar por palavra" << endl;
        cout << "5. Calcular distancia entre palavras" << endl;
        cout << "6. Sair" << endl;

        int opcao;
        cin >> opcao;

        if (opcao == 1) {
            // Inserir palavras
            while (true) {
                insertVert(root);
                cout << "Deseja inserir outra palavra? (s/n): " << endl;
                string opcao;
                cin >> opcao;
                if (opcao != "s") {
                    break;
                }
            }

            // Imprima a árvore em ordem
            cout << "Grafo: " << endl;
            inOrder(root);

        } else if (opcao == 2) {
            // Listar palavras por tradução
            while (true) {
                string traducao;
                cout << "Digite uma traducao para listar palavras ficticias (ou 'fim' para terminar): " << endl;
                cin >> traducao;
                if (traducao == "fim") {
                    break;
                }
                cout << "Palavras ficticias para a traducao \"" << traducao << "\":" << endl;
                listWordsByTranslation(root, traducao);
            }

        } else if (opcao == 3) {
            // Remover palavra fictícia
            while (true) {
                cout << "Digite a palavra ficticia a ser removida: " << endl;
                string palavra;
                cin >> palavra;
                root = remove(root, palavra);

                // Imprime a árvore atualizada em ordem
                cout << "Grafo atualizado: " << endl;
                inOrder(root);

                // Pergunte se o usuário deseja remover outra palavra fictícia
                cout << "Deseja remover outra palavra ficticia? (s/n): " << endl;
                string opcao;
                cin >> opcao;
                if (opcao != "s") {
                    break;
                }
            }

        } else if (opcao == 4) {
            // Listar traduções de uma palavra fictícia
            while (true) {
                cout << "Digite a palavra ficticia para listar as traducoes (ou 'fim' para terminar): " << endl;
                string palavra;
                cin >> palavra;
                if (palavra == "fim") {
                    break;
                }
                listTranslations(root, palavra);
            }

        } else if (opcao == 5) {
            // Calcular distância entre palavras
            while (true) {
                cout << "Deseja calcular a distancia entre duas palavras ficticias? (s/n): " << endl;
                string opcao;
                cin >> opcao;
                if (opcao != "s") {
                    break;
                }
                findDistance(root);
            }

        } else if (opcao == 6) {
            // Sair do programa
            break;

        } else {
            cout << "Opcao invalida, por favor tente novamente." << endl;
        }
    }

    // Destruir a árvore e liberar memória
    destructTree(root);

    return 0;
}