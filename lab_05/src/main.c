#include "point_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

void count_points(intrusive_node *node, void *data) {
    if (node != NULL) {
        *(int *)data = *(int *)data + 1;
    }
}

void print_points(intrusive_node *node, void *data) {
    point_node *pnode = get_point(node);
    printf((char *)data, pnode->x, pnode->y);
}

int get_reversed(int x) {
    return ((~x) & ((1 << 24) - 1));
}

int from_twos_complement(int x) {
    if ((x & (1 << 23)) == 0) {
        return x;
    }
    return -get_reversed(x - 1);
}

int to_twos_complement(int x) {
    if (x >= 0) {
        return x;
    }
    return get_reversed(-x) + 1;
}

intrusive_list *loadbin(char *path) {
    FILE *file = fopen(path, "rb");

    intrusive_list *list = (intrusive_list *)malloc(sizeof(intrusive_list));
    init_list(list);

    uint8_t x[3] = {0};
    uint8_t y[3] = {0};
    while (fread(&x, sizeof(char), 3, file) > 0) {
        fread(&y, sizeof(char), 3, file);
        int xgot = (x[2] << 16) + (x[1] << 8) + x[0];
        int ygot = (y[2] << 16) + (y[1] << 8) + y[0];
        xgot = from_twos_complement(xgot);
        ygot = from_twos_complement(ygot);
        add_point(list, xgot, ygot);
    }

    fclose(file);

    return list;
}

intrusive_list *loadtext(char *path) {
    FILE *file = fopen(path, "r");

    intrusive_list *list = (intrusive_list *)malloc(sizeof(intrusive_list));
    init_list(list);

    int x, y;
    while (fscanf(file, "%d %d", &x, &y) >= 0) {
        add_point(list, x, y);
    }

    fclose(file);

    return list;
}

void savetext(char *path, intrusive_list *list) {
    FILE *file = fopen(path, "w");

    intrusive_node *cur = list->head.next;
    while (cur != &list->head) {
        point_node *pnode = get_point(cur);
        fprintf(file, "%d %d\n", pnode->x, pnode->y);

        cur = cur->next;
    }

    fclose(file);
}

void split_bin(int x, uint8_t* xgot) {
    for (int i = 0; i < 3; i++) {
        xgot[i] = (x & ((1 << 8) - 1));
        x >>= 8;  
    }
}

void savebin(char *path, intrusive_list *list) {
    FILE *file = fopen(path, "wb");

    intrusive_node *cur = list->head.next;
    while (cur != &list->head) {
        point_node *pnode = get_point(cur);
        uint8_t x[3] = {0};
        uint8_t y[3] = {0};
        split_bin(to_twos_complement(pnode->x), x);
        split_bin(to_twos_complement(pnode->y), y);
        fwrite(x, sizeof(char), 3, file);
        fwrite(y, sizeof(char), 3, file);

        cur = cur->next;
    }

    fclose(file);
}

void destroy_list(intrusive_list *list) {
    remove_all_points(list);
    free(list);
}

int main(int argc, char *argv[]) {
    assert(argc > 1); //to avoid the Warning

    intrusive_list *list = NULL;
    if (strcmp(argv[1], "loadbin") == 0) {
        list = loadbin(argv[2]);
    } else if (strcmp(argv[1], "loadtext") == 0) {
        list = loadtext(argv[2]);
    }

    if (strcmp(argv[3], "savetext") == 0) {
        savetext(argv[4], list);
    } else if (strcmp(argv[3], "savebin") == 0) {
        savebin(argv[4], list);
    } else if (strcmp(argv[3], "print") == 0) {
        apply(list, print_points, argv[4]);
    } else if (strcmp(argv[3], "count") == 0) {
        size_t len = 0;
        apply(list, count_points, &len);
        printf("%lu\n", len);
    }

    destroy_list(list);

    return 0;
}