# Sistema de Gerenciamento de Atendimento - Blua

Projeto desenvolvido para a Sprint 3 de Data Structures and Algorithms.

## Objetivo

Implementar um sistema de gerenciamento de atendimentos remotos utilizando:

- Filas (FIFO)
- Pilhas (LIFO)
- Listas encadeadas
- Linguagem C

O sistema simula o fluxo de pacientes em teleconsultas da plataforma Blua da Care Plus.

---

## Funcionalidades

- Cadastro de pacientes
- Fila comum
- Fila prioritária para emergências
- Chamada sequencial de pacientes
- Histórico de consultas usando pilha
- Interface interativa via terminal

---

## Estruturas Utilizadas

### Fila (FIFO)
Utilizada para armazenar pacientes aguardando atendimento.

Operações implementadas:
- enqueue
- dequeue
- is_empty

### Pilha (LIFO)
Utilizada para armazenar histórico das consultas realizadas.

Operações implementadas:
- push
- pop
- peek
- is_empty

---

## Como Executar

### Compilar

```bash
gcc dsaSprint3.c -o sistema
```

### Executar

```bash
./sistema
```

---

## Cenários Demonstrados

1. Cadastro de pacientes comuns
2. Atendimento prioritário de emergência
3. Consulta do histórico de atendimentos

---

## Arquivos do Projeto

- `dsaSprint3.c` → código-fonte principal
- `DSA_Sprint3.pdf` → relatório técnico

---

## Vídeo Demonstrativo

Link do vídeo:
(COLE O LINK AQUI)

---

## Integrantes

- Gabriel Augusto da Silva - RM 567057
- Leonardo Kenji Kubo Barboza - RM 567518
- Lucas Gabriel Alvarenga e Meireles - RM 567305
- Lucas Koiti Uyeno de Souza - RM 568128
- Lucas Morio Ikeda - RM 567616
