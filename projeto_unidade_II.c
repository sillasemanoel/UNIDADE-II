#include <stdio.h>
#include <string.h>
#include <locale.h>

void menuConta()
{
    printf("\n-- Menu Conta --\n");
    printf("1. Exibir contas cadastradas\n");
    printf("2. Adicionar conta\n");
    printf("3. Remover conta\n");
    printf("4. Voltar\n");
}

void menuEstoque()
{
    printf("\n-- Menu Estoque --\n");
    printf("1. Listar estoque\n");
    printf("2. Adicionar item\n");
    printf("3. Remover item\n");
    printf("4. Valor do estoque\n");
    printf("5. Voltar\n");
}

typedef struct
{
    char nome[120];
    int quantidade;
    float valor_unitario;
} ItemEstoque;

int compararItens(const void *a, const void *b)
{
    ItemEstoque *item1 = (ItemEstoque *)a;
    ItemEstoque *item2 = (ItemEstoque *)b;
    return strcmp(item1->nome, item2->nome);
}

float calcularValorTotalEstoque(ItemEstoque *estoque, int num_itens)
{
    float valor_total = 0.0;
    for (int i = 0; i < num_itens; i++)
    {
        valor_total += estoque[i].quantidade * estoque[i].valor_unitario;
    }
    return valor_total;
}

void gerarListaEstoque(ItemEstoque *estoque, int num_itens) {
    FILE *arquivo;
    arquivo = fopen("lista_estoque.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    fprintf(arquivo, "-- Lista de Itens do Estoque em Ordem Alfabetica --\n");
    for (int i = 0; i < num_itens; i++) {
        fprintf(arquivo, "%s - Quantidade: %d - Valor Unitário: R$ %.2f\n", estoque[i].nome, estoque[i].quantidade, estoque[i].valor_unitario);
    }
    fclose(arquivo);
    printf("Lista de estoque gerada e salva com sucesso no arquivo 'lista_estoque.txt'.\n");
}

int main()

{
    setlocale (LC_ALL,"Portuguese");
    char email_cadastrado[80];
    char senha_cadastrada[80];
    char lista_emails[100][80];

    int num_emails = 0;

    while (1)
    {
        printf("\nBem vindo ao cadastro no sistema de estoque.\n");
        printf("Por favor, cadastre um email válido: ");
        scanf("%s", email_cadastrado);

        if (strchr(email_cadastrado, '@') != NULL)
        {
            strcpy(lista_emails[num_emails], email_cadastrado);
            num_emails++;
            break;
        }
        else
        {
            printf("\nO email é inválido, ele deve conter '@' pra ser um email válido.\n");
        }
    }

    printf("Por favor, cadastre sua senha: ");
    scanf("%s", senha_cadastrada);

    printf("\nCadastro concluido, faça login para continuar.\n");

    ItemEstoque estoque[100];
    int num_itens = 0;

    while (1)
    {
        char email[80];
        char senha[80];

        printf("\nInsira seu email: ");
        scanf("%s", email);
        printf("Insira sua senha: ");
        scanf("%s", senha);

        if (strcmp(email, email_cadastrado) == 0 && strcmp(senha, senha_cadastrada) == 0)
        {
            printf("\nBem vindo ao Controle de Estoque RD.\n");

            int escolha;
            while (1)
            {
                printf("\n-- Menu Principal --\n");
                printf("1. Conta\n");
                printf("2. Estoque\n");
                printf("3. Imprimir Estoque\n");
                printf("4. Logout\n");
                printf("\nEscolha uma opção: \n");
                scanf("%d", &escolha);

                switch (escolha)
                {
                case 1:
                    while (1)
                    {
                        menuConta();
                        printf("Escolha uma opção: ");
                        scanf("%d", &escolha);
                        switch (escolha)
                        {
                        case 1:
                            printf("\nContas cadastradas:\n");
                            for (int i = 0; i < num_emails; i++)
                            {
                                printf("%d. %s\n", i + 1, lista_emails[i]);
                            }
                            break;
                        case 2:
                            printf("\nInsira um novo email: ");
                            scanf("%s", lista_emails[num_emails]);
                            printf("Insira uma senha para o novo email: ");
                            scanf("%s", senha);
                            num_emails++;
                            printf("Nova conta adicionada.\n");
                            break;
                        case 3:
                            printf("\nEscolha a conta que será removida:\n");
                            for (int i = 0; i < num_emails; i++)
                            {
                                printf("%d. %s\n", i + 1, lista_emails[i]);
                            }
                            int escolha_email;
                            scanf("%d", &escolha_email);
                            if (escolha_email >= 1 && escolha_email <= num_emails)
                            {
                                for (int i = escolha_email - 1; i < num_emails - 1; i++)
                                {
                                    strcpy(lista_emails[i], lista_emails[i + 1]);
                                }
                                num_emails--;
                                printf("Conta removida.\n");
                            }
                            else
                            {
                                printf("Opção inexistente\n");
                            }
                            break;
                        case 4:
                            break;
                        default:
                            printf("Opção inexistente. Escolha uma opção disponível.\n");
                            break;
                        }
                        if (escolha == 4)
                            break;
                    }
                    break;
                case 2:
                    while (1)
                    {
                        menuEstoque();
                        printf("Escolha uma opção: ");
                        scanf("%d", &escolha);
                        switch (escolha)
                        {
                        case 1:
                            printf("\nEstoque atual:\n");
                            if (num_itens == 0)
                            {
                                printf("Estoque vazio.\n");
                            }
                            else
                            {
                                qsort(estoque, num_itens, sizeof(ItemEstoque), compararItens);

                                for (int i = 0; i < num_itens; i++)
                                {
                                    printf("%s Quantidade: %d Valor por unidade: R$ %.2f\n", estoque[i].nome, estoque[i].quantidade, estoque[i].valor_unitario);
                                }
                            }
                            break;
                        case 2:
                            printf("\nAdicionar item ao estoque:\n");
                            printf("Nome do item: ");
                            scanf("%s", estoque[num_itens].nome);
                            printf("Quantidade do item: ");
                            scanf("%d", &estoque[num_itens].quantidade);
                            printf("Preço por unidade: ");
                            scanf("%f", &estoque[num_itens].valor_unitario);
                            num_itens++;
                            printf("Item adicionado ao estoque.\n");
                            break;

                        case 3:
                            printf("\nRemover item selecionado:\n");
                            printf("-- Estoque atual --\n");
                            if (num_itens == 0)
                            {
                                printf("Estoque vazio.\n");
                            }
                            else
                            {

                                for (int i = 0; i < num_itens; i++)
                                {
                                    printf("%d. %s Quantidade: %d Valor por unidadde: R$ %.2f\n", i + 1, estoque[i].nome, estoque[i].quantidade, estoque[i].valor_unitario);
                                }


                                printf("Digite o número correspondente ao item que deseja remover: ");
                                int escolha_item;
                                scanf("%d", &escolha_item);
                                escolha_item--;

                                if (escolha_item >= 0 && escolha_item < num_itens)
                                {

                                    printf("Digite a quantidade a ser removida: ");
                                    int quantidade_remover;
                                    scanf("%d", &quantidade_remover);


                                    if (quantidade_remover > 0 && quantidade_remover <= estoque[escolha_item].quantidade)
                                    {
                                        estoque[escolha_item].quantidade -= quantidade_remover;
                                        printf("%d unidades do item %s removidas.\n", quantidade_remover, estoque[escolha_item].nome);


                                        if (estoque[escolha_item].quantidade == 0)
                                        {
                                            for (int i = escolha_item; i < num_itens - 1; i++)
                                            {
                                                strcpy(estoque[i].nome, estoque[i + 1].nome);
                                                estoque[i].quantidade = estoque[i + 1].quantidade;
                                                estoque[i].valor_unitario = estoque[i + 1].valor_unitario;
                                            }
                                            num_itens--;
                                            printf("Item removido completamente do estoque.\n");
                                        }
                                    }
                                    else
                                    {
                                        printf("Quantidade invílida.\n");
                                    }
                                }
                                else
                                {
                                    printf("Escolha invílida.\n");
                                }
                            }
                            break;

                        case 4:
                            printf("Valor total do estoque: R$ %.2f\n", calcularValorTotalEstoque(estoque, num_itens));
                            break;
                        case 5:
                            break;
                        default:
                            printf("Opção inexistente. Escolha uma opção disponível.\n");
                            break;
                        }
                        if (escolha == 5)
                            break;
                    }
                    break;
                case 3:
                    gerarListaEstoque(estoque, num_itens);
                    break;
                case 4:
                    printf("Até o proximo login\n");
                    return 0;
                default:
                    printf("Opção inexistente. Escolha uma opção disponível.\n");
                    break;
                }
            }

            break;
        }
        else
        {
            printf("Email ou senha incorreta, tente novamente!\n");
        }
    }

    return 0;
}

