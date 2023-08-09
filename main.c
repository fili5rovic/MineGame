#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char br = 65;


typedef struct node {
    char id;
    struct node *link1;
} LinkNode;


typedef struct graph_node {
    char id;
    double radius, x, y;
    struct node *link;
    struct graph_node *next;
} GraphNode;


typedef struct {
    struct graph_node *head;
} Graph;


typedef struct Queue {
    int tail;
    int head;
    GraphNode *items[50];
} Queue;


GraphNode *createGraphNode(double r, double x, double y) {
    GraphNode *node = malloc(sizeof(GraphNode));
    node->id = br++;
    node->x = x;
    node->y = y;
    node->radius = r;
    node->link = NULL;
    node->next = NULL;
    return node;
}


void addToGraph(Graph *graph, double radius, double x, double y) {
    GraphNode *newNode = createGraphNode(radius, x, y);
    if (graph->head == NULL) {
        graph->head = newNode;
        return;
    }
    GraphNode *tekuci = graph->head;
    while (tekuci->next != NULL) {
        tekuci = tekuci->next;
    }
    tekuci->next = newNode;

}


void printRGB(char *text, int r, int g, int b) {
    printf("\033[38;2;%d;%d;%dm%s\033[0m", r, g, b, text);
}


void print_red(char *s) {
    printf("\033[1;31m%s\033[0m", s);
}


void printC1(char *s) {
    printRGB(s, 20, 200, 150);
}


void printBlue(char *s) {
    printf("\033[1;34m%s\033[0m", s);
}


void printGraphNode(GraphNode *node) {
    printf("\033[1;34m    \xB3   %c    \xB3 %6.2lf   \xB3 %6.2lf   \xB3 %6.2lf   \xB3   \033[0m", node->id,
           node->x, node->y, node->radius);
    LinkNode *tekuci = node->link;
    if (!tekuci) {
        printBlue("            \xB3\n");
        return;
    }
    int br = 12;
    while (tekuci->link1 != NULL) {
        printf("\033[1;34m%c, \033[0m", tekuci->id);
        br -= 3;
        tekuci = tekuci->link1;
    }

    printf("\033[1;34m%c\033[0m", tekuci->id);
    br--;
    for (int i = 0; i < br; ++i) {
        putchar(' ');
    }
    printBlue("\xB3\n");
}


void printGraph(Graph *graph) {
    GraphNode *tekuci = graph->head;
    if (!tekuci) {
        print_red("\n                                Zadati graf nema sadrzaj.\n");
        return;
    }
    else {
        printBlue("    \xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC2\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC2\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC2\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC2\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF\n");
        printBlue("    \xB3   ID   \xB3     X    \xB3     Y    \xB3  RADIUS  \xB3     GRANE     \xB3\n");
        printBlue("    \xC3\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC5\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC5\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC5\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC5\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB3\n");
    }
    while (tekuci != NULL) {
        printGraphNode(tekuci);
        tekuci = tekuci->next;
    }
    printBlue("    \xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC1\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC1\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC1\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC1\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9\n");
}


Graph *createGraph() {
    Graph *graph = malloc(sizeof(Graph));
    graph->head = NULL;
    return graph;
}


GraphNode *getGraphNodeByID(Graph *graph, char id) {
    if (graph->head == NULL) {
        //printf("Graf je prazan.\n");
        return NULL;
    } else if (id == '\n') {
        printf("Pokupih novu liniju.");
        return NULL;
    }
    GraphNode *tekuci = graph->head;
    while (tekuci != NULL) {
        if (tekuci->id == id)
            return tekuci;
        tekuci = tekuci->next;
    }
    return NULL;
}


int addLink(Graph *graph, char c1, char c2, int msg) {
    GraphNode *first = getGraphNodeByID(graph, c1);
    GraphNode *new = getGraphNodeByID(graph, c2);
    if (!first || !new) {
        return 0;
    }
    LinkNode *second = malloc(sizeof(LinkNode));
    second->id = new->id;
    second->link1 = NULL;
    if (first->link == NULL) {
        first->link = second;
        return 1;
    }
    LinkNode *tekuci = first->link;
    while (tekuci->link1 != NULL) {
        if (tekuci->id == second->id) {
            if (msg)
                printf("Veza vec postoji.\n");
            return 0;
        }
        tekuci = tekuci->link1;
    }
    if (tekuci->id != second->id) {
        tekuci->link1 = second;
        return 1;
    }
    else if (msg)
        printf("Veza vec postoji.\n");
    return 0;
}

//vraca 0 ako ne uspe
int removeLink(Graph *graph, char c1, char c2) {
    GraphNode *first = getGraphNodeByID(graph, c1);
    GraphNode *new = getGraphNodeByID(graph, c2);
    if (!first || !new) {
        //printf("Neki od unetih cvorova ne postoji.\n");
        return 0;
    }
    LinkNode *second = malloc(sizeof(LinkNode));
    second->id = new->id;
    second->link1 = NULL;
    if (first->link == NULL) {
        return 0;
    }
    int uklonio = 0;
    if (first->link->id == second->id) {
        first->link = first->link->link1;
        uklonio = 1;
        return uklonio;
    } else {
        LinkNode *tekuci = first->link;
        LinkNode *old = NULL;
        while (tekuci->link1 != NULL) {
            if (tekuci->link1->id == second->id) {
                old = tekuci->link1;
                tekuci->link1 = tekuci->link1->link1;
                free(old);
                uklonio = 1;
                break;
            }
            tekuci = tekuci->link1;
        }
        return uklonio;
    }
}

void removeLinks(LinkNode *head) {
    LinkNode *dispose;
    while (head) {
        dispose = head;
        head = head->link1;
        free(dispose);
    }
}

//vraca 0 ako nije uspeo
int removeFromGraph(Graph *graph, char id) {
    GraphNode *tekuci = graph->head;
    while (tekuci != NULL) {
        removeLink(graph, tekuci->id, id);
        tekuci = tekuci->next;
    }
    tekuci = graph->head;
    GraphNode *prethodni = tekuci;
    if (tekuci->id == id) {
        graph->head = tekuci->next;
        return 1;
    }
    while (tekuci != NULL) {
        if (tekuci->id == id) {
            removeLinks(tekuci->link);
            GraphNode *old = prethodni->next;
            prethodni->next = tekuci->next;
            free(old);
            return 1;
        }
        prethodni = tekuci;
        tekuci = tekuci->next;
    }
    return 0;
}

void freeGraph(Graph *graph) {
    GraphNode *tekuci = graph->head;
    GraphNode *old;
    while (tekuci != NULL) {
        old = tekuci;
        tekuci = tekuci->next;
        removeLinks(old->link);
        free(old);
    }
    free(graph);
}

int checkCircleOverlap(double x1, double y1, double r1, double x2, double y2, double r2) {
    double distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

    if (r1 >= distance) {
        return 1;
    } else return 0;
}


void createLinksFromOverlaps(Graph *graph, int msg) {
    if (graph->head == NULL) {
        printf("Prazan graf.\n");
        return;
    } else if (graph->head->next == NULL) return;
    GraphNode *tekuci = graph->head;
    GraphNode *unutrasnji;
    while (tekuci != NULL) {
        unutrasnji = graph->head;
        while (unutrasnji != NULL) {
            if (checkCircleOverlap(tekuci->x, tekuci->y, tekuci->radius,
                                   unutrasnji->x, unutrasnji->y, unutrasnji->radius) == 1
                && tekuci->id != unutrasnji->id) {
                addLink(graph, tekuci->id, unutrasnji->id, msg);
            }
            unutrasnji = unutrasnji->next;
        }
        tekuci = tekuci->next;
    }
}


void option1(Graph *graph) {
    printRGB("\nUnesite, odvojeno razmakom, sledece parametre:\n(radijus,x,y): ", 20, 200, 150);
    double radijus, x, y;
    char linija[20];
    getchar();
    while (fgets(linija, 20, stdin) != NULL) {
        if (linija[0] == '\n') {
            break;
        }
        if (sscanf(linija, "%lf %lf %lf", &radijus, &x, &y) == 3) {
            addToGraph(graph, radijus, x, y);
            char s[25];
            sprintf(s,"\nElement (%c) dodat na graf.\n\n", br - 1);
            printC1(s);
            printGraph(graph);
            break;
        } else {
            printC1("\nUnesite, odvojeno razmakom, sledece parametre:\n(radijus,x,y): ");
        }
    }
}


void option2(Graph *graph) {
    printC1("\nUnesite identifikator cvora:\n(id): ");
    char id;
    char linija[10];
    getchar();
    while (fgets(linija, 10, stdin) != NULL) {
        if (linija[0] == '\n') {
            break;
        }
        if (sscanf(linija, "%c", &id) == 1) {
            if (removeFromGraph(graph, id)) {
                char p[40];
                sprintf(p,"\n                                 Element (%c) je uklonjen\n", id);
                print_red(p);
                printGraph(graph);
                break;
            } else printC1("\nUnesite identifikator cvora:\n(id): ");

        } else {
            printC1("\nUnesite identifikator cvora:\n(id): ");
        }
    }
}


void option3(Graph *graph) {
    printC1("\nPrvo se navodi cvor od kojeg pocinje veza, a zatim cvor ka kojem ide ta veza.\n\nUnesite, odvojeno razmakom, sledece parametre:\n(id,id): ");
    char id1, id2;
    char linija[10];
    getchar();
    while (fgets(linija, 10, stdin) != NULL) {
        if (linija[0] == '\n') {
            break;
        }
        if (sscanf(linija, "%c %c", &id1, &id2) == 2) {
            if(addLink(graph, id1, id2, 1)) {
                char s[40];
                sprintf(s,"\nUspesno dodata veza (%c->%c)\n", id1, id2);
                printC1(s);
                printGraph(graph);
            } else {
                print_red("\n                                 Vezu nije moguce dodati\n");
                return;
            }
            break;
        } else {
            printC1("\nUnesite, odvojeno razmakom, sledece parametre:\n(id,id): ");
        }
    }
}


void option4(Graph *graph) {
    printC1("\nPrvo se navodi cvor od kojeg pocinje veza, a zatim cvor ka kojem ide ta veza.\nUnesite, odvojeno razmakom, sledece parametre:\n(id1,id2): ");
    char id1, id2;
    char linija[10];
    getchar();
    while (fgets(linija, 10, stdin) != NULL) {
        if (linija[0] == '\n') {
            break;
        }
        if (sscanf(linija, "%c %c", &id1, &id2) == 2) {
            if(removeLink(graph, id1, id2)) {
                printf("\nUspesno uklonjena veza (%c->%c)\n", id1, id2);
                printGraph(graph);
            } else {
                print_red("\n                                Vezu nije moguce ukloniti\n");
                return;
            }
            break;
        } else {
            printf("\nUnesite, odvojeno razmakom, sledece parametre:\n(id,id): ");
        }
    }
}


void insert(Queue *q, GraphNode *node) {
    q->items[q->tail++] = node;
    q->tail %= 50;
}


GraphNode *delete(Queue *q) {
    GraphNode *node = q->items[q->head];
    q->items[q->head++] = NULL;
    q->head %= 50;
    return node;
}


int createGraphFromFile(Graph *graph) {
    putchar('\n');
    printC1("Unesite kompletan naziv fajla ukljucujuci i njegovu ekstenziju.\n(ime_fajla.ekstenzija): ");
    char file_name[30];
    char linija[30];
    getchar();
    while (fgets(linija, 30, stdin) != NULL) {
        if (linija[0] == '\n') {
            break;
        }
        if (sscanf(linija, "%49s", file_name) == 1) {
            break;
        } else {
            putchar('\n');
            printC1("(ime_fajla.ekstenzija): ");
        }
    }
    FILE *file = fopen(file_name, "r");
    if (!file) {
        char err[50];

        sprintf(err,"\n                   Fajl %s nije pronadjen.\n", file_name);
        print_red(err);
        return 0;
    }
    int brojac = 0;
    double r, x, y;
    if (fgets(linija, 30, file) != NULL) {
        brojac = atoi(linija);
        char por[50];
        sprintf(por,"\nUspesno kreiran graf iz fajla %s\n", file_name);
        printC1(por);
    }
    for (int i = 0; i < brojac; ++i) {
        fgets(linija, 30, file);
        if (sscanf(linija, "%lf %lf %lf", &x, &y, &r) == 3) {
            addToGraph(graph, r, x, y);
        }
    }

    //printGraph(graph);
    fclose(file);
    return 1;
}

//BFS
int getEfficiencyForMine(Graph *graph, GraphNode *root, int msg) {
    if (msg) {
        printBlue("        \xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF\n");
        char a[50];
        sprintf(a,"        \xB3 BFS (%c): \xB3  ",root->id);
        printBlue(a);
    }
    Queue *queue = malloc(sizeof(Queue));
    char niz[30] = {0};
    int brojac = 0;
    queue->head = 0;
    queue->tail = 0;
    insert(queue, root);
    int strelica_bila = 0;
    int spejsovi = 28;
    while (queue->head < queue->tail) {
        GraphNode *node = delete(queue);
        int postoji = 0;
        for (int i = 0; i < brojac; ++i) {
            if (niz[i] == node->id) {
                postoji = 1;
                break;
            }
        }
        if (!postoji) {
            if (msg) {
                if (!strelica_bila) {
                    char a[1];
                    a[0] = node->id;
                    printBlue(a);
                    strelica_bila = 1;
                    spejsovi -= 1;
                } else {
                    char a[10];
                    sprintf(a,"-> %c", node->id);
                    printBlue(a);
                    spejsovi -=4;
                }
            }
            niz[brojac++] = node->id;
        }
        LinkNode *tekuci = node->link;
        while (tekuci != NULL) {
            insert(queue, getGraphNodeByID(graph, tekuci->id));
            tekuci = tekuci->link1;
        }
    }
    //brojac--;
    if (msg) {
        char a[10];

        int i = 0;
        for (i = 0; i < spejsovi; ++i) {
            putchar(' ');
        }
        sprintf(a,"(%d)", brojac);
        printC1(a);
        for (int j = i; j < spejsovi+3; ++j) {
            putchar(' ');
        }
        printBlue("\xB3\n");
        printBlue("        \xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9\n");
    }
    return brojac;
}


void maximumEfficiencyMine(Graph *graph) {
    if (graph->head == NULL) {
        print_red("\nGraf je prazan...\n");
        return;
    }
    GraphNode *curr = graph->head;
    int max = -1;
    while (curr != NULL) {
        int tekuce_mina_BFS = getEfficiencyForMine(graph, curr, 1);
        if (tekuce_mina_BFS > max) {
            max = tekuce_mina_BFS;
        }
        curr = curr->next;
    }
    printC1("\nSpisak mina najvece efikasnosti:\n");
    curr = graph->head;
    while (curr != NULL) {
        int tekuce_mina_BFS = getEfficiencyForMine(graph, curr, 0);
        if (tekuce_mina_BFS == max) {
            printBlue("        \xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF\n");
            char p[100];
            sprintf(p, "        \xB3        Mina (%c) koja detonira %d mina          \xB3\n", curr->id, max);
            printBlue(p);
            printBlue("        \xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9\n");
        }
        curr = curr->next;
    }
}


void option_geteff(Graph *graph) {
    getchar();
    GraphNode *unetaMina;
    char id;
    char linija[2];
    printC1("\nUnesite zeljeni cvor:\n(id): ");
    while (fgets(linija, 2, stdin) != NULL) {
        if (sscanf(linija, "%c", &id) == 1 && id != '\n') {
            unetaMina = getGraphNodeByID(graph, id);
            if (unetaMina != NULL)
                break;
            else
                print_red("\nUneli ste nepostojecu minu...\n");
        }
        printC1("\nUnesite zeljeni cvor:\n(id): ");
        getchar();
    }
    getEfficiencyForMine(graph, unetaMina, 1);
}


void raketa(Graph *graph) {
    printC1("\nUnesite, odvojeno razmakom, sledece parametre:\n(radijus,x,y): ");
    double radijus, x, y;
    char linija[20];
    getchar();
    while (fgets(linija, 20, stdin) != NULL) {
        if (linija[0] == '\n') {
            break;
        }
        if (sscanf(linija, "%lf %lf %lf", &radijus, &x, &y) == 3) {
            putchar('\n');
            printGraph(graph);
            addToGraph(graph, radijus, x, y);
            char p[40];
            sprintf(p,"\n                  Raketa (%c) uspesno dodata.\n", br - 1);
            printC1(p);
            //printGraph(graph);
            break;
        } else {
            printC1("\nUnesite, odvojeno razmakom, sledece parametre:\n(radijus,x,y): ");
        }
    }
    GraphNode *raketa = getGraphNodeByID(graph, br - 1);
    createLinksFromOverlaps(graph, 0);
    getEfficiencyForMine(graph, raketa, 1);
    removeFromGraph(graph, br - 1);

    putchar('\n');
}


double generateRandomBetween(double max, double min) {
    return ((double) rand() / RAND_MAX) * (max - min) + min;
}


void getAreaForMine(Graph *graph, char c) {
    double xmin = 999999,xmax = -999999,ymin = 99999,ymax = -9999999;

    GraphNode *root = getGraphNodeByID(graph,c);
    Queue *queue = malloc(sizeof(Queue));
    char niz[30] = {0};
    int brojac = 0;
    queue->head = 0;
    queue->tail = 0;
    insert(queue, root);
    while (queue->head < queue->tail) {
        GraphNode *node = delete(queue);
        int postoji = 0;
        for (int i = 0; i < brojac; ++i) {
            if (niz[i] == node->id) {
                postoji = 1;
                break;
            }
        }
        if (!postoji) {

            niz[brojac++] = node->id;
        }
        LinkNode *tekuci = node->link;
        while (tekuci != NULL) {
            insert(queue, getGraphNodeByID(graph, tekuci->id));
            tekuci = tekuci->link1;
        }
    }

    GraphNode *nizCvorova[brojac];
    for (int i = 0; i < brojac; ++i) {
        nizCvorova[i] = getGraphNodeByID(graph,niz[i]);
    }
    for (int i = 0; i < brojac; ++i) {
        // printf("%c (%.2lf %.2lf %.2lf)",nizCvorova[i]->id,nizCvorova[i]->x,nizCvorova[i]->y,nizCvorova[i]->radius);
        if((nizCvorova[i]->x - nizCvorova[i]->radius) < xmin) {
            xmin = (nizCvorova[i]->x - nizCvorova[i]->radius);
        }
        if((nizCvorova[i]->x + nizCvorova[i]->radius) > xmax) {
            xmax = (nizCvorova[i]->x + nizCvorova[i]->radius);
        }
        if((nizCvorova[i]->y - nizCvorova[i]->radius) < ymin) {
            ymin = (nizCvorova[i]->y - nizCvorova[i]->radius);
        }
        if((nizCvorova[i]->y + nizCvorova[i]->radius) > ymax) {
            ymax = (nizCvorova[i]->y + nizCvorova[i]->radius);
        }
    }

    int unutar_kruga = 0;
    int simulacija = 1000000;
    for (int j = 0; j < simulacija; ++j) {
        double rand_x = generateRandomBetween(xmin,xmax);
        double rand_y = generateRandomBetween(ymin,ymax);
        for (int i = 0; i < brojac; ++i) {
            double distance = sqrt(pow(rand_x - nizCvorova[i]->x, 2) + pow(rand_y - nizCvorova[i]->y, 2));
            if(distance <= nizCvorova[i]->radius) {
                unutar_kruga++;
                break;
            }
        }
    }
    double povrsina = (xmax-xmin)* (ymax-ymin) * ((double)unutar_kruga/simulacija);
    putchar('\n');
    printBlue("        \xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF\n");
    char a[50];
    sprintf(a,"        \xB3       Povrsina detonacije (%c) je: %.2lf       \xB3\n",root->id,povrsina);
    printBlue(a);
    printBlue("        \xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9\n");
    putchar('\n');
}


void areaOfMaximum(Graph *graph) {
    if (graph->head == NULL) {
        print_red("\nGraf je prazan...\n");
        return;
    }
    GraphNode *tekuci = graph->head;
    int max = -1;
    while (tekuci != NULL) {
        int tekuce_mina_BFS = getEfficiencyForMine(graph, tekuci, 1);
        if (tekuce_mina_BFS > max) {
            max = tekuce_mina_BFS;
        }
        tekuci = tekuci->next;
    }
    //printf("\nSpisak mina najvece efikasnosti:\n");
    tekuci = graph->head;
    char max_mine_id[10] = {'\0'};
    int max_mine_brojac = 0;
    while (tekuci != NULL) {
        int tekuce_mina_BFS = getEfficiencyForMine(graph, tekuci, 0);
        if (tekuce_mina_BFS == max) {
            max_mine_id[max_mine_brojac++] = tekuci->id;
            //printf("Mina (%c) koja detonira %d mina\n", tekuci->id, max);
        }
        tekuci = tekuci->next;
    }
    getAreaForMine(graph,max_mine_id[0]);
//    for (int i = 0; i < max_mine_brojac; ++i) {
//        getAreaForMine(graph,max_mine_id[i]);
//    }
}


void drugi() {
    getchar();
    Graph *graph = createGraph();
    while (1) {
        if (graph->head == NULL) {
            putchar('\n');
            printC1("\t\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF\n");
            printC1("\t\xB3             INTERAKTIVNI MENI           \xB3 \n");
            printC1("\t\xB3                                         \xB3 \n");
            printC1("\t\xB3 1: Kreiranje grafa pomocu datoteke      \xB3 \n");
            printC1("\t\xB3 0. Izlaz                                \xB3 \n");
            printC1("\t\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9\n");
        } else {
            printC1("\t\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF\n");
            printC1("\t\xB3               INTERAKTIVNI MENI               \xB3 \n");
            printC1("\t\xB3                                               \xB3 \n");
            printC1("\t\xB3 1. Pronalazenje efikasnosti zadate mine       \xB3 \n");
            printC1("\t\xB3 2. Pronalazenje mine maksimalne efikasnosti   \xB3 \n");
            printC1("\t\xB3 3. Bacanje rakete                             \xB3 \n");
            printC1("\t\xB3 4. Ukupna povrsina                            \xB3 \n");
            printC1("\t\xB3 0. Izlaz                                      \xB3 \n");
            printC1("\t\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9\n");
        }
        char unos;
        while (1) {
            printC1("\n-> ");
            unos = getchar();
            if (unos != '\n') break;
        }
        int izlaz = 0;
        switch (unos) {
            case '1':
                if (graph->head == NULL) {
                    if (createGraphFromFile(graph)) {
                        createLinksFromOverlaps(graph, 1);
                        printGraph(graph);
                    }
                } else {
                    option_geteff(graph);
                    getchar();
                }
                break;
            case '2':
                putchar('\n');
                maximumEfficiencyMine(graph);
                getchar();
                break;
            case '3':
                raketa(graph);
                break;
            case '4':
                areaOfMaximum(graph);
                getchar();
                break;
            case '0':
                izlaz = 1;
                break;
            default:
                getchar();
        }
        if (izlaz) break;
    }
    putchar('\n');
    getchar();
    print_red("\t\t\t\t\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF\n");
    print_red("\t\t\t\t\xB3    Program zavrsen.   \xB3\n");
    print_red("\t\t\t\t\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9\n");
}


void meni(Graph *graph) {
    //printf("\n\n\n\n\n\n\n\n\n");
    printC1("\t\t\t\t\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF\n");
    printC1("\t\t\t\t\xB3      DOBRODOSLI      \xB3 \n");
    printC1("\t\t\t\t\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9\n");
    while (1) {
        printC1("\n");
        printC1("\t\t\t\t\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF\n");
        printC1( "\t\t\t\t\xB3   INTERAKTIVNI MENI   \xB3 \n");
        printC1( "\t\t\t\t\xB3                       \xB3 \n");
        printC1( "\t\t\t\t\xB3 F. Igra sa minama     \xB3 \n");
        printC1( "\t\t\t\t\xB3 1. Ubacite element    \xB3 \n");
        printC1( "\t\t\t\t\xB3 2. Izbrisite element  \xB3 \n");
        printC1( "\t\t\t\t\xB3 3. Ubacite vezu       \xB3 \n");
        printC1( "\t\t\t\t\xB3 4. Izbrisite vezu     \xB3 \n");
        printC1( "\t\t\t\t\xB3 5. Ispis grafa        \xB3 \n");
        printC1( "\t\t\t\t\xB3 0. Izlaz              \xB3 \n");
        printC1("\t\t\t\t\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9\n");
        printC1( "\n-> ");
        char unos = getchar();
        int izlaz = 0;
        switch (unos) {
            case '1':
                option1(graph);
                break;
            case '2':
                option2(graph);
                break;
            case '3':
                option3(graph);
                break;
            case '4':
                option4(graph);
                break;
            case '5':
                printGraph(graph);
                getchar();
                break;
            case 'F':
                freeGraph(graph);
                drugi();
                return;
            case '0':
                izlaz = 1;
                break;
            default:
                getchar();
        }
        if (izlaz) break;
    }
    getchar();
    print_red("\t\t\t\t\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF\n");
    print_red("\t\t\t\t\xB3    Program zavrsen.   \xB3\n");
    print_red("\t\t\t\t\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9\n");

}
void header() {
    printC1("\xD1 \xD2 \xD3 \xD4 \xD5 \xD6 \xD7 \xD8 \xD9 \xDA \xDB \xDC \xDD \xDE \xDF ");
    printC1("\xC1 \xC2 \xC3 \xC4 \xC5 \xC6 \xC7 \xC8 \xC9 \xCA \xCB \xCC \xCD \xCE \xCF");
    printC1("\xD1 \xD2 \xD3 \xD4 \xD5 \xD6 \xD7 \xD8 \xD9 \xDA \xDB \xDC \xDD \xDE \xDF \xDD \xDE \xDF \xD6 \xD7 ");
    printC1("\xC1 \xC2 \xC3 \xC4 \xC5 \xC6 \xC7 \xC8 \xC9 \xCA \xCB \xCC \xCD \xCE \xCF");
    printC1("\xB1 \xB2 \xB3 \xB4 \xB5 \xB6 \xB7 \xB8 \xB9 \xBA \xBB \xBB \xBD \xBE \xBF");
    printC1("\xC1 \xC2 \xC3 \xC4 \xC5 \xC6 \xC7 \xC8 \xC9 \xCA \xCB \xCC \xCD \xCE \xCF");
    printC1("\xC1 \xC2 \xC3 \xC4 \xC5 \xC6 \xC7 \xC8 \xC9 \xCA \xCB \xCC \xCD \xCE \xCF");
    printC1("\xB1 \xB2 \xB3 \xB4 \xB5 \xB6 \xB7 \xB8 \xB9 \xBA \xBB \xBB \xBD \xBE \xBF");
    printC1("\xC1 \xC2 \xC3 \xC4 \xC5 \xC6 \xC7 \xC8 \xC9 \xCA \xCB \xCC \xCD \xCE \xCF");
    printC1("\xB1 \xB2 \xB3 \xB4 \xB5 \xB6 \xB7 \xB8 \xB9 \xBA \xBB \xBB \xBD \xBE \xBF");
    printC1("\xB1 \xB2 \xB3 \xB4 \xB5 \xB6 \xB7 \xB8 \xB9 \xBA \xBB \xBB \xBD \xBE \xBF");
    printC1("\xB1 \xB2 \xB3 \xB4 \xB5 \xB6 \xB7 \xB8 \xB9 \xBA \xBB \xBB \xBD \xBE \xBF\n\n");
}

int main() {
    header();
    Graph *graph = createGraph();
    meni(graph);
    getchar();
    return 0;
}