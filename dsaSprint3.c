#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// STRUCTS
// paciente
typedef struct {
    char nome[51]; // max 50 char para o nome, 1 char reservado para \0
    char senha[10]; // max 10 char para senha
    int prioridade; // nv de prioridade do atendimento -> comum = 0 / prioritario = 1
} Paciente;

// lista encadeada
typedef struct Node {
    Paciente dado;
    struct Node* prox; // ponteiro para proximo node
} Node;

// fila de atendimento / estrutura FIFO -> First In, First Out
typedef struct {
    Node *frente;
    Node *fim;
} Fila;

// pilha do historico de consultas / estrutura LIFO -> Last In, First Out
typedef struct {
    Node *topo;
} Pilha;
// STRUCTS FIM

// FUNCOES
void inicializarFila(Fila* f) {
    f->frente = f->fim = NULL; // fila é inicializada vazia
}

void inicializarPilha(Pilha* p) {
    p->topo = NULL; // pilha é inicializada vazia
}

// is_empty da fila
int filaVazia(Fila* f) {
    return (f->frente == NULL); // verifica se a fila esta vazia 
}

// is_empty da pilha
int pilhaVazia(Pilha* p) {
    return (p->topo == NULL); // verifica se a pilha esta vazia
}

// enqueue -> insere paciente no final da fila
void enqueue(Fila* f, Paciente pac) {
    Node* novo = (Node*)malloc(sizeof(Node)); // alocacao de memoria para novo node
    if (novo == NULL) { // verifica se houve erro na alocacao de memoria
        printf("Erro na alocação de memória\n");
        return;
    }
    novo->dado = pac; // copia dados do paciente
    novo->prox = NULL; // novo node aponta para null
    if (filaVazia(f)) {
        f->frente = f->fim = novo; // frente e fim apontam para novo node
    }
    else {
        f->fim->prox = novo; // conecta novo node ao final
        f->fim = novo; // atualiza fim da fila
    }
}

// dequeue -> remove paciente da frente da fila
Paciente dequeue(Fila* f) {
    if (filaVazia(f)) {
        Paciente vazio = {"----", "Vazio", 0};
        return vazio;
    }
    Node* temp = f->frente; // guarda node da frente
    Paciente pac = temp->dado; // copia dados do paciente
    f->frente = f->frente->prox; // avanca a frente da fila para proximo node
    if (f->frente == NULL) f->fim = NULL; // verifica se a fila ficou vazia
    free(temp); // libera a memoria do node removido
    return pac; // retorna dados do paciente removido
}

// exibe os proximos pacientes na fila / recebe a quantidade de pacientes que serao exibidos como parametro -> int limite
void exibirProximosPacientes(Fila* f, int limite) {
    Node* atual = f->frente; // comeca exibicao pela frente da fila
    int contador = 0;
    if (atual == NULL) { // verifica se a fila esta vazia
        printf("Vazia\n");
        return;
    }
    while (atual != NULL && contador < limite) { // percorre a fila ate o limite
        printf("%s - %s\n", atual->dado.senha, atual->dado.nome); // exibe dados do paciente atual
        atual = atual->prox; // avaca para proximo node
        contador++;
    }
}

// push -> adiciona consulta no topo da piha
void push(Pilha* p, Paciente pac) {
    Node* novo = (Node*)malloc(sizeof(Node)); // alocacao de memoria para novo node
    if (novo == NULL) { // verifica se houve erro na alocacao de memoria
        printf("Erro na alocação de memória\n");
        return;
    }
    novo->dado = pac; // copia dados do paciente
    novo->prox = p->topo; // novo node aponta para o topo atual
    p->topo = novo; // atualiza topo da pilha
}

// pop -> exibe e remove paciente/consulta do topo da pilha
Paciente pop(Pilha* p) {
    if (pilhaVazia(p)) {
        Paciente vazio = {"----", "Vazio", 0};
        return vazio;
    }
    Node* temp = p->topo; // guarda node do topo
    Paciente pac = temp->dado; // copia dados do paciente
    p->topo = p->topo->prox; // avanca topo da pilha
    free(temp); // libera memoria do node removido
    return pac; // retorna paciente removido
}

// peek -> exibe a paciente/consulta no topo da pilha
Paciente peek(Pilha* p) {
    if (pilhaVazia(p)) {
        Paciente vazio = {"----", "Vazio", 0};
        return vazio;
    }
    return p->topo->dado; // retorna dados do node no topo da pilha
}

// exibe o historico de consultas / recebe quantidade de consultas que serao exibidos como parametro -> int limite
void exibirHistorico(Pilha* p, int limite) {
    Node* atual = p->topo; // comeca exibicao pelo topo da pilha
    int contador = 0;
    if (atual == NULL) { // verifica se a pilha esta vazia
        printf("Vazio");
        return;
    }
    while (atual != NULL && contador < limite) { // percorre a pilha ate o limite
        printf("\n%s - %s", atual->dado.senha, atual->dado.nome); // exibe dados do paciente atual
        atual = atual->prox; // avanca para proximo node
        contador++;
    }
}

// libera memoria alocada para fila
void liberarMemoriaFila(Fila* f) {
    while (!filaVazia(f)) { // percorre a fila inteira ate estar vazia
        dequeue(f); // remove os nodes
    }
}

// libera memoria alocada para pilha
void liberarMemoriaPilha(Pilha* p) {
    while (!pilhaVazia(p)) { // percorre a pilha inteira ate estar vazia
        pop(p); // remove os nodes
    }
}

// exibe interface no output
void exibirInterface(Fila* fc, Fila* fp, Pilha* p) {
    printf("\n========== INTERFACE ==========");
    printf("\nFila prioritária:\n");
    exibirProximosPacientes(fp, 2); // exibe proximos 2 pacientes da fila prioritaria
    printf("\nFila comum:\n");
    exibirProximosPacientes(fc, 2); // exibe proximos 2 pacientes da fila comum
    if (pilhaVazia(p)) {
        printf("\nÚltima consulta:\nHistórico vazio\n");
    }
    else {
        Paciente ult = peek(p); // olha ultimo paciente/consulta
        printf("\nÚltima consulta:\n");
        printf("%s - %s\n", ult.senha, ult.nome); // exibe dados do ultimo paciente/consulta
    }
    printf("\n------------------------------\n");
}
// FUNCOES FIM

int main() {
    Fila filaComum;
    Fila filaPrioritaria;
    Pilha historico;
    inicializarFila(&filaComum);
    inicializarFila(&filaPrioritaria);
    inicializarPilha(&historico);
    int opcao;
    int senhaComum = 1;
    int senhaPrioritaria = 1;

    do {
        exibirInterface(&filaComum, &filaPrioritaria, &historico);
        printf("1. Adicionar novo paciente\n");
        printf("2. Chamar próximo paciente\n");
        printf("3. Ver histórico de consultas\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao); // le opcao escolhida por usuario

        switch (opcao) {
            case 1: { // registro do paciente
                Paciente pac;
                printf("Nome do paciente (máx. 50 caracteres): ");
                getchar(); // limpa \n do buffer / limpa quebra de linha
                fgets(pac.nome, sizeof(pac.nome), stdin); // le nome do paciente
                pac.nome[strcspn(pac.nome, "\n")] = '\0'; // substitui \n no final da string por \0 para corrigir formatacao
                printf("Prioridade (0-Comum, 1-Emergência): ");
                scanf("%d", &pac.prioridade); // le prioridade do paciente e define a qual fila ele sera adicionado
                if (pac.prioridade == 1) {
                    snprintf(pac.senha, sizeof(pac.senha), "P%03d", senhaPrioritaria++); // gera senha prioritaria
                    enqueue(&filaPrioritaria, pac); // insere na fila prioritaria
                }
                else {
                    snprintf(pac.senha, sizeof(pac.senha), "C%03d", senhaComum++); // gera senha comum
                    enqueue(&filaComum, pac); // insere na fila comum
                }
                break;
            }
            case 2: { // chamada do proximo paciente
                Paciente pac;
                if (!filaVazia(&filaPrioritaria)) { // verifica se ha pacientes prioritarios
                    pac = dequeue(&filaPrioritaria); // remove da fila prioritaria
                }
                else if (!filaVazia(&filaComum)) { // verifica se ha pacientes comuns
                    pac = dequeue(&filaComum); // remove da fila comum
                }
                else{ // se nao houver pacientes em nenhuma das filas
                    printf("\n------------------------------\n");
                    printf("Não há pacientes na fila.");
                    printf("\n------------------------------\n");
                    break;
                }
                printf("\n------------------------------\n");
                printf("Médico chamando: %s - %s", pac.senha, pac.nome); // exibe proximo paciente
                printf("\n------------------------------\n");
                push(&historico, pac); // adiciona paciente ao historico
                break;
            }
            case 3: { // exibicao do historico
                printf("\n------------------------------\n");
                printf("Histórico: ");
                exibirHistorico(&historico, 5); // exibe ultimos 5 pacientes/consultas no historico
                printf("\n------------------------------\n");
                break;
            }
        }
    }
    while (opcao != 0);
    liberarMemoriaFila(&filaComum);
    liberarMemoriaFila(&filaPrioritaria);
    liberarMemoriaPilha(&historico);
    return 0;
}